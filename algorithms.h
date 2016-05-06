//
//  ALGORITHMS.H
//
//
//  Created by Marko Tunjic on 05/05/16.
//  Copyright © 2016 Marko Tunjic. All rights reserved.
//

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


namespace mt {

	
	template <Integer N>
	bool odd(N n) { return bool(n & 0x1); }

	template <Integer N>
	N half(N n) { return n >> 1; }


	// random_iota
	template <ForwardIterator I>
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

	// remove_if_not
	template <ForwardIterator I, Predicate P>
	I remove_if_not(I first, I last, P pred)
	{
			return std::remove_if(first, last,
														[&](const ValueType(I)& x){ return !pred(x); });
	}
	
	// keep_if
	template <Sequence S, Predicate P>
	void keep_if(S&& s, P pred)
	{
		auto p = remove_if_not(std::begin(s), std::end(s), pred);
		s.erase(p, std::end(s));
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
	
	// find_backward
	// (reverse neighbor find) searches a sequential data structure from end to beginning.
	template<InputIterator I, typename T>
	I find_backward(I first, I last, const T& x)
	{
		while (last != first && last[-1] != x)
			--last;
		return last;
	}
	
	// random_range
	// Usage:
	// 	 std::vector<double> vec(12);
	//	 random_range(vec, 5.0, 0.5);
	template <InputIterator I, Number T>
	void random(I first, I last, T min, T max) {
		
		std::random_device rnd_device;
		std::mt19937_64 rng {rnd_device()};
		std::normal_distribution<> norm {min, max};
		
		std::generate(first, last,[&norm, &rng]{ return norm(rng); });
		
	}
	
	// find_if_n
	// For counted ranges, formed by specifying a position and a count of elements n.
	template <InputIterator I, Number N, UnaryPredicate P>
	auto find_if_n(I first, N n, P p) -> std::pair<I, N>
	{
		while (n && !p(*first)) {
			++first;
			--n;
		}
		return {first, n}; // n is how many more steps are left
	}
	
	// copy_n
	template <InputIterator I, OutputIterator O, Number N>
	auto copy_n(I first, N n, O dest) -> std::pair<I, O>
	{
		while (n) {
			*dest = *first;
			++first;
			++dest;
			--n;
		}
		return {first, dest};
	}

	
	// slide by Sean Parent
	template <RandomAccessIterator I>
	auto slide(I first, I last, I p) -> std::pair<I, I>
	{
		if (p < first) return { p, std::rotate(p, first, last) };
		if (last < p)  return { std::rotate(first, last, p), p };
		return { first, last };
	}
	
	// gather by Sean Parent
	template <BidirectionalIterator I, Predicate P>
	auto gather(I first, I last, I pos, P pred) -> std::pair<I, I>
	{

		return{ std::stable_partition(first, pos,
																	[&](const ValueType(I)& x){ return !pred(x); }),
			std::stable_partition(pos, last, pred) };
	}
	

	// swap_ranges_n by Stepanov
	template <ForwardIterator I, Integer N>
 	auto swap_ranges_n(I first1, I first2, N n) -> std::pair<I, I>
	{
		while (n) {
			std::swap(*first1, *first2);
			++first1;
			++first2;
			--n;
		}
		return {first1, first2};
	}
	
	// reverse by Stepanov
	// reverse that works on forward iterators and uses not more than O(log(n)) of
	// additional storage and not more than O(nlog(n)) steps, where n is the size of the range
	template <ForwardIterator I, Integer N>
	I reverse_n(I first, N n)
	{
		if (n == 0) return first;
		if (n == 1) return ++first;
		
		I middle = reverse_n(first, n/2);
		if (n % 2 == 1) ++middle;
		I result = reverse_n(middle, n/2);
		swap_ranges_n(first, middle, n/2);
		return result;
	}

	template <ForwardIterator I>
	void reverse(I first, I last)
	{
		reverse_n(first, std::distance(first, last));
	}



	// ======================= EXT ======================================
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

	// random
	template <Sequence S, Number T>
	void random(S first, S last, std::pair<T, T> range) {
		random(first, last, range.first, range.second);
	}

	template <Sequence S, Number T>
	void random(S& s, T min, T max) {
		random(std::begin(s), end(s), min, max);
	}

	template <Sequence S, Number T>
	void random(S& s, std::pair<T, T> range) {
		random(std::begin(s), end(s), range.first, range.second);
	}


	std::default_random_engine& global_urng() {
		static std::default_random_engine  u{};
		return u;
	}

	void randomize() {
		static std::random_device  rd{};
		global_urng().seed(rd());
		
	}

	template<typename I>
	void randomize(I first, I last) {
		randomize();
		std::shuffle(first, last, global_urng());
	}

	template<typename C>
	void randomize(C& c) {
		randomize(std::begin(c), std::end(c));
	}


	template<typename T>
	T pick_a_number(T from, T thru) {
		static std::normal_distribution<>  d{};
		using  parm_t  = decltype(d)::param_type;
		return d(global_urng(), parm_t{from, thru});
	}

}

#endif