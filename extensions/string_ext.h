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
	static inline void trim_left(std::string &str)
	{
	    str.erase(0, str.find_first_not_of(' '));
	}

	static inline 
	void trim_right(std::string &str)
	{
	    str.erase(str.find_last_not_of(' ') + 1, std::string::npos);
	}

	static inline 
	std::string trim_left(const std::string &str)
	{
	    std::string::size_type pos = str.find_first_not_of(' ');
	    if (pos == std::string::npos) return std::string();

	    return str.substr(pos, std::string::npos);
	}

	static inline 
	std::string trim_right(const std::string &str)
	{
	    std::string::size_type pos = str.find_last_not_of(' ');
	    if (pos == std::string::npos) return std::string();

	    return str.substr(0, pos + 1);
	}

	static inline 
	std::string trim(const std::string& str)
	{
	    std::string::size_type pos1 = str.find_first_not_of(' ');
	    if (pos1 == std::string::npos) return std::string();

	    std::string::size_type pos2 = str.find_last_not_of(' ');
	    if (pos2 == std::string::npos) return std::string();

	    return str.substr(pos1 == std::string::npos ? 0 : pos1,
	                      pos2 == std::string::npos ? (str.length() - 1) : (pos2 - pos1 + 1));
	}

	// inplace
	static inline 
	void trim(std::string& str)
	{
	    std::string::size_type pos = str.find_last_not_of(' ');
	    if(pos != std::string::npos) {
	        str.erase(pos + 1);
	        pos = str.find_first_not_of(' ');
	        if(pos != std::string::npos) str.erase(0, pos);
	    }
	    else
	        str.erase(str.begin(), str.end());
	}

#endif