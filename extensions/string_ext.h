//
//  STRING_EXT.H
//
//
//  Created by Marko Tunjic on 05/05/16.
//  Copyright © 2016 Marko Tunjic. All rights reserved.
//

// The non-copy version operates in-place modifying the range.
// The copy version writes the modified range into an output
// range leaving the original untouched.
// if function end with _if you can use a predicate (functor or lambda expression)


#ifndef STRING_EXT
#define STRING_EXT

#include <algorithm>
#include <string>
#include <locale>
#include <map>
#include <ios>
#include <ostream> // for the << operator
#include <sstream> // for ostringstream

#include "lib/algorithms.h"
#include "lib/utils.h"




namespace mt {

// Code point
template <typename T>
using rune = std::basic_string<T>;
using 	StringMap = std::map<std::string, int>;

// chars
// Without a argument, use the default locale (which is obtained from the OS).
struct ToLower
{
    char operator() (char ch, const std::locale& loc = std::locale{}) const  {
        return std::tolower(ch,  loc);
    }
};

struct ToUpper
{
    char operator() (char ch, const std::locale& loc = std::locale{}) const  {
        return std::toupper(ch,  loc);
    }
};


// Test for letter.
template<class Char>
inline
bool letter(Char ch, const std::locale& loc = std::locale{})
{
    return std::isalnum(ch, loc);
}

// Test for non-letter.
template<class Char>
inline
bool non_letter(Char ch, const std::locale& loc = std::locale{})
{
    return not std::isalpha(ch, loc);
}

// Convert to lowercase.
template<class Char>
inline
Char lowercase(Char ch, const std::locale& loc = std::locale{})
{
    return std::tolower(ch, loc);
}

// Convert to lowercase.
template<class Char>
inline
Char uppercase(Char ch, const std::locale& loc = std::locale{})
{
    return std::toupper(ch, loc);
}

// Compare two characters - ignore case.
template<class Char>
inline
bool same_char(Char a, Char b)
{
    return lowercase(a) == lowercase(b);
}

// faster than std library function
inline
bool is_space(char x) {
    if (x > ' ') return false;
    return (x == ' ' || x == '\r' || x == '\t' || x == '\n');
}

// functor for lexicographical comparisons
template <typename C>
bool lex_cmp(const C& a, const C& b) {
    return std::lexicographical_compare(a.begin(), a.end(),
                                        b.begin(), b.end());
}

//===================== remove_copy, remove_copy_if =====================

template<class Char, class Traits, class Allocator>
bool is_palindrome(std::basic_string<Char, Traits, Allocator> str)
{
    typedef typename std::basic_string<Char, Traits, Allocator> string;
    typename string::iterator end{
        std::remove_if(str.begin(), str.end(), non_letter<Char>)};
    string rev{str.begin(), end};
    std::reverse(rev.begin(), rev.end());
    return not rev.empty() and
           std::equal(str.begin(), end, rev.begin(), same_char<Char>);
}

template <typename T, typename  F>
void copy_if(const rune<T>& src, rune<T>& dest, F fun) {
    dest.clear();
    dest.reserve(src.length());
    std::copy_if(src.begin(), src.end(),
                 std::back_inserter(dest), fun);
}

// remove_if
template <typename T, typename  F>
void remove_if(const rune<T>& src, rune<T>& dest, F fun) {
    dest.clear();
    dest.reserve(src.length());
    std::remove_if(src.begin(), src.end(),
                   std::back_inserter(dest), fun);
}

// remove_copy_if_not
//	template <typename T, typename  F>
//	void remove_copy_if_not(const rune<T>& src, rune<T>& dest, F fun) {
//		dest.clear();
//		dest.reserve(src.length());
//		std::remove_if(src.begin(), src.end(),
//					   std::back_inserter(dest),
//					   [&fun](const T& t) { return !fun(t); });
//	}
//
// remove_copy_if_not
template<typename T, typename  F>
rune<T> remove_copy_if_not(const rune<T>& s, F f)
{
    std::string result;
    result.reserve(s.length());
    std::remove_copy_if(s.begin(), s.end(),
                        std::back_inserter(result),
    [&f](const T& t) {
        return !f(t);
    });
    return result;

}

template<typename T, typename  F>
void remove_if(T& s, F f)
{
    auto p = std::remove_if(s.begin(), s.end(), f);
    s.erase(p, s.end());
}

template<typename T, typename  F>
void remove_if_not(rune<T>& s, F f)
{
    auto p = std::remove_if(s.begin(), s.end(), [&f](const T& t) {
        return !f(t);
    });
    s.erase(p, s.end());

}

//===========================split, strim, ========================================
// split string
template <typename T>
void split(const std::string& s, std::string sep, std::vector<T>& v) {

    if (s.empty())
        return;

    size_t n = s.length();
    v.clear();
    v.reserve(n);

    auto start = s.find_first_not_of(sep, 0);

    while (start < n) {
        auto stop = s.find_first_of(sep, start);
        if (stop > n) stop = n;
        std::istringstream is {s.substr(start, stop - start)};
        T t;
        if (is >> t)
            v.push_back(t);

        start = s.find_first_not_of(sep, stop+1);

    }
}

// Trimming single characters from a string
// trim_right_if("demo!!!!", '!'); => demo
template<typename T>
void trim_right_if(rune<T>& s, const T c)
{
    if (s.empty()) return;
    s.erase(s.find_last_not_of(c) + 1, std::string::npos);
}

template<typename T, typename F>
void trim_right_if(rune<T>& s, F fun)
{
    if (s.empty()) return;
    typename std::basic_string<T>::iterator p;

    for (p = s.end(); p != s.begin() && fun(*--p););
    if (!fun(*p))
        p++;

    s.erase(p, s.end());
}

// trim right
template<typename T>
void trim_right(rune<T>& s) {
    trim_right_if(s, is_space);
}

// trim left inplace
template<typename T>
void trim_left(rune<T>& s)
{
    s.erase(0, s.find_first_not_of(' '));
}

// inplace
void trim(std::string& s)
{
    trim_left(s);
    trim_right(s);
}

void strip(std::string& s)
{
    remove_if_not(s, ::isalpha);
}

// reversed in place
void reverse(std::string& s) {
    std::reverse(std::begin(s), std::end(s));
}

// reversed copy
std::string reverse_copy(std::string& s)
{
    std::string result{};
    result.reserve(s.length());
    result.assign(s.rbegin(), s.rend());
    return result;
}


// Sanitize a string by keeping only alphabetic characters.
// std::string copy{sanitize(word)};
template<typename T>
void sanitize(rune<T>& s)
{
    auto p = std::remove_if(s.begin(), s.end(), non_letter);
    s.erase(p, s.end());
    std::transform(s.begin(), s.end(), s.begin(), ToLower());
}

template<typename T>
void sanitize_copy(const rune<T>& src, const rune<T>& dest)
{
    rune<T> result{};
    result.reserve(src.length());
    std::remove_copy_if(src.begin(), src.end(),
                        std::back_inserter(dest), non_letter);
    return result;
}


// ================= to_upper, lower =======================
// return copy
std::string to_upper(const std::string& s)
{
    if (s.empty()) return "";
    std::string result{};
    result.reserve(s.length());
    std::transform(std::begin(s), std::end(s),
                   std::back_inserter(result), ToUpper());
    return result;
}


std::string to_lower(const std::string& s)
{
    if (s.empty()) return "";
    std::string result{};
    result.reserve(s.length());
    std::transform(std::begin(s), std::end(s),
                   std::back_inserter(result), ToLower());
    return result;
}

template <typename T>
void to_lower(rune<T>& s)
{
    std::transform(std::begin(s), std::end(s),
                   std::begin(s), ToLower());
}

template <typename T>
void to_upper(rune<T>& s)
{
    std::transform(std::begin(s), std::end(s),
                   std::begin(s), ToUpper());
}


// extract letters from string
// "some12test29710-1sss" => sometestsss
template <typename T>
rune<T> letters_copy(const rune<T>& s)
{

    rune<T> result{};
    if (s.empty()) return result;
    result.reserve(s.length());
    std::copy_if(std::begin(s), std::end(s),
                 std::back_inserter(result), letter);
    return result;
}

// titlecase
// capitalize in place
template <typename T>
void capitalize(std::basic_string<T>& s,
                const std::locale& loc = std::locale{}) {
    if (!s.empty())
        s[0] = uppercase(s[0], loc);

}

// extract digits from string
// "some12test29710-1sss" => 12297101
template <typename T>
rune<T> digits_copy(const rune<T>& s)
{
    rune<T> result{};
    if (s.empty()) return result;
    result.reserve(s.length());
    std::copy_if(std::begin(s), std::end(s),
                 std::back_inserter(result), ::isdigit);
    return result;
}

// pad or fill, a string with a number of occurrences of some
// character to a certain width
// right_pad(s, 5, '*'); => *****
// left pad s.insert(s.begin(), 20 – s.length(), 'X');
template<typename T>
void right_pad(std::basic_string<T>& s,
               typename std::basic_string<T>::size_type n, T c) {
    if (n > s.length())
        s.append(n - s.length(), c);
}
void init_streams(std::locale locale)
{
    std::cin.imbue(std::locale{});
    std::cout.imbue(std::locale{});
}

void init_locale()
{
    std::locale native{""};
    init_streams(native);
}

// string / text
template<typename T>
std::string to_string(const T& t)
{
    std::ostringstream os;
    os << t;
    return os.str();
}

template<typename T>
T from_string(const std::string& s)
{
    std::istringstream is {s};
    T t;
    if (!(is >> t)) throw std::bad_cast{};
    return t;
}

std::string random_string(size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

}

