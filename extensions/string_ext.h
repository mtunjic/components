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
	void trim_left(std::string &s)
	{
	    s.erase(0, s.find_first_not_of(' '));
	}

	static inline 
	void trim_right(std::string &s)
	{
	    s.erase(s.find_last_not_of(' ') + 1, std::string::npos);
	}

	static inline 
	std::string trim_left(const std::string &s)
	{
	    auto p = s.find_first_not_of(' ');
	    if (p == std::string::npos) return std::string();

	    return s.substr(p, std::string::npos);
	}

	static inline 
	std::string trim_right(const std::string &s)
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
}

#endif