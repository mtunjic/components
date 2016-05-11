//
//  STRING_EXT.H
//
//
//  Created by Marko Tunjic on 05/05/16.
//  Copyright © 2016 Marko Tunjic. All rights reserved.
//

#ifndef STRING_EXT
#define STRING_EXT
#include <algorithm>
#include <string>

namespace mt {
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

	// inplace
	static inline 
	void trim_left(std::string& s)
	{
	    s.erase(0, s.find_first_not_of(' '));
	}

	static inline 
	void trim_right(std::string& s)
	{
	    s.erase(s.find_last_not_of(' ') + 1, std::string::npos);
	}

	static inline 
	std::string trim_left(const std::string& s)
	{
	    auto p = s.find_first_not_of(' ');
	    if (p == std::string::npos) return std::string();

	    return s.substr(p, std::string::npos);
	}

	static inline 
	std::string trim_right(const std::string& s)
	{
	    auto p = s.find_last_not_of(' ');
	    if (p == std::string::npos) return std::string();

	    return s.substr(0, p + 1);
	}

	static inline 
	std::string trim(const std::string& s)
	{
	    auto p1 = s.find_first_not_of(' ');
	    if (p1 == std::string::npos) return std::string();

	    auto p2 = s.find_last_not_of(' ');
	    if (p2 == std::string::npos) return std::string();

	    return s.substr(p1 == std::string::npos ? 0 : p1,
	                    p2 == std::string::npos ? (s.length() - 1) : (p2 - p1 + 1));
	}

	// inplace
	static inline 
	void trim(std::string& s)
	{
	    auto p = s.find_last_not_of(' ');
	    if(p != std::string::npos) {
	        s.erase(pos + 1);
	        p = s.find_first_not_of(' ');
	        if(p != std::string::npos) s.erase(0, p);
	    }
	    else
	        s.erase(s.begin(), s.end());
	}



	// prefix
	// endwith for (int i = str.length() - 1; i >= 0; i--)
	bool startsWith(string str, string prefix) {
	  if (str.length() < prefix.length()) return false;
	  for (int i = 0; i < prefix.length(); i++) {
	    if (str[i] != prefix[i]) return false;
	  }
	  return true;
	}

	int countSpaces(string str) {
	    int nSpaces = 0;
	    for (int i = 0; i < str.length(); i++) {
	    if (str[i] == ' ') nSpaces++;
	    }
	    return nSpaces;
	}
	// cout << repeatChar(101, '*') << endl;
	string repeatChar(int n, char ch) {
	    string str = "";
	    for (int i = 0; i < n; i++) {
	        str += ch;
	    }
	    return str;
	}

	string reverse(string str) {
	    string rev = "";
	    for (int i = str.length() - 1; i >= 0; i--) {
	        rev += str[i];
	    }
	    return rev;
	}

	bool isDigitString(string str) {
	    if (str.length() == 0) return false;
	    for (int i = 0; i < str.length(); i++) {
	        if (!isdigit(str[i])) return false;
	    }
	          return true;
	}

	bool equalsIgnoreCase(string s1, string s2) {
	    if (s1.length() != s2.length()) return false;
	    for (int i = 0; i < s1.length(); i++) {
	        if (tolower(s1[i]) != tolower(s2[i])) return false;
	    }
	    return true;
	}

	// Unlike other languages such as Java, C++ allows you to change the characters in a string
	// by assigning new values to a particular index position.
	void toUpperCaseInPlace(string& str) {
	  for (int i = 0; i < str.length(); i++) {
	    str[i] = toupper(str[i]);
	  }
	}

	// return copy
	string toUpperCase(string str) {
	  string result = "";
	  for (int i = 0; i < str.length(); i++) {
	    result += toupper(str[i]); }
	  return result;
	}

	// The strategy that modifies the string in place is more efficient,
	// but the second is more flexible and less likely to cause unexpected results.

	bool recIsPalindrome(string input) {
	    /* Any length-0 or length-1 string is a palindrome. */
	    if (input.length() <= 1) {
	        return true;
	    } else {
	        /* If the first and last characters don't match, this cannot be a
	         * palindrome.
	         */
	        if (input[0] != input[input.length() - 1])
	            return false;

	        /* This is a palindrome precisely if the middle characters are. */
	        return recIsPalindrome(input.substr(1, input.length() - 2));
	    }
	}

	bool isPalindrome(string input) {
	    input = toLowerCase(lettersIn(input));
	    return recIsPalindrome(input);
	}

	string toLowerCase(string input) {
	    for (int i = 0; i < input.length(); i++) {
	        input[i] = tolower(input[i]);
	    }
	    return input;
	}

	string reverseString(string input) {
	    if (input == "") {
	        return "";
	    } else {
	        return reverseString(input.substr(1)) + input[0];
	    }
	}

	string lettersIn(string input) {
	    if (input == "") {
	        return "";
	    } else {
	        if (isalpha(input[0])) {
	            return input[0] + lettersIn(input.substr(1));
	        } else {
	            return lettersIn(input.substr(1));
	        }
	    }
	}
}

#endif