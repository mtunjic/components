//
//  VECTOR_EXT.H
//
//
//  Created by Marko Tunjic on 05/05/16.
//  Copyright © 2016 Marko Tunjic. All rights reserved.
//

#ifndef VECTOR_EXT
#define VECTOR_EXT
#include <algorithm>
#include <vector>
#include <string>

namespace mt {

	template <typename T>
	void distinct(std::vector<T>& v) 
	{
		std::sort(std::begin(v), std::end(v));
		auto end_unique = std::unique(std::begin(v), std::end(v));
		v.erase(end_unique, std::end(v)); 
	}

	template <typename T, typename Predicate>
	void keep_if(std::vector<T>& v, Predicate pred)
	{
	    auto notpred = [&pred](const T& t) { return !pred(t); };
	    v.erase(std::remove_if(std::begin(v), 
	    	std::end(v), notpred), std::end(end));
	}

	template<typename T>
	void fast_erase(std::vector<T>& v, size_t i)
	{
	    v[i] = std::move(v.back());
	    v.pop_back();
	}

	template<typename T>
	void fill(istream& ist, vector<T>& v, char terminator)
	{
	    int i = 0;
	    while (ist >> i) v.push_back(i);
	    if (ist.eof()) return;  
	    ist.clear();             
	    char c;
	    ist>>c;                 
	    if (c != terminator) {   
	        ist.unget();         
	        ist.clear(ios_base::failbit); 
	    }
	}
}

#endif