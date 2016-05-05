#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "concepts.h"
#include <iterator>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <list>
#include <functional>
#include <random>


template <Integer N>
bool odd(N n) { return bool(n & 0x1); }

template <Integer N>
N half(N n) { return n >> 1; }


// random_iota
template <ForwardIterator I>
inline
void iota(I first, I last) {
  iota(first, last, ValueType(I)(0), ValueType(I)(1));
}
template <RandomAccessIterator I>
  void random_iota(I first, I last) {
  iota(first, last);
  std::random_shuffle(first, last);
}

// split
template <typename T, typename C>
void split(const std::basic_string<T>& s, std::string separators, C& c) {

	size_t n = s.length();
	// find non-separtor chras
	auto start = s.find_first_not_of(separators, 0);

	while (start < n) {  // until we have non separator charceter
		// find end of current word
		auto stop = s.find_first_of(separators, start);
		if (stop > n) stop = n;
		// add word to list of words
		c.push_back(s.substr(start, stop - start));
		// find start of next word
		start = s.find_first_not_of(separators, stop+1);
		
	}
}

// keep_if
template <typename T, typename Predicate>
void keep_if(std::vector<T>& v, Predicate pred)
{
    auto notpred = [&pred](const T& t) { return !pred(t); };
    v.erase(remove_if(v.begin(), v.end(), notpred), v.end());
}

// remove_if_not
template <ForwardIterator I, typename P>
I remove_if_not(I first, I last, P pred)
{
    first = std::find_if(first, last, pred);

    if (first != last)
    {
        I i = first;
        while (++i != last)
        {
            if (pred(*i))
            {
                *first = std::move(*i);
                ++first;
            }
        }
    }
    return first;
}

// apply
template<ForwardIterator I, class Function>
void apply(I first, I last, Function f)
{
	while (first != last) {
		*first = f(*first);
		++first;
	}
}


// random_range
template <typename C, typename T>
void random_range(C& c, T min, T max) {

	random_range(std::begin(c), end(c), min, max);
	
}

template <typename C, typename T>
void random_range(C& c, std::pair<T, T> range) {
	
	random_range(std::begin(c), end(c), range.first, range.second);
	
}

template <typename I, typename T>
void random_range(I first, I last, std::pair<T, T> range) {
	
	random_range(first, last, range.first, range.second);
	
}

template <typename I, typename T>
void random_range(I first, I last, T min, T max) {
	
	std::random_device rnd_device;
	std::mt19937_64 rng {rnd_device()};
	std::normal_distribution<> norm {min, max};
	
	std::generate(first, last,[&norm, &rng]{ return norm(rng); });
	
}

// find_all
template<typename T>
using Iterator = typename T::iterator; 
template<typename C, typename V>
std::vector<Iterator<C>> find_all(C& c, V v) { 
	std::vector<Iterator<C>> result;
	for (auto p = c.begin(); p != c.end(); ++p)
		if (*p == v)
			result.emplace_back(p);
	return result;
}





#endif