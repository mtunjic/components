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

	template <UnsignedIntegral N>
	uint8_t high_byte(N x) {
  		return x >> ((sizeof(N) - 1) * 8);
	}
	
	template <InputIterator I>
	inline
	I successor(I x) { return ++x; }

	template <BidirectionalIterator I>
	inline
	I predecessor(I x) { return ++x; }

	template <RandomAccessIterator I, Integral N>
	inline
	I successor(I x, N n, std::random_access_iterator_tag) { 
	  return x + n;
	}

	template <InputIterator I, Integral N>
	inline
	I successor(I x, N n, std::input_iterator_tag) { 
	  while (n != N(0)) {
	    ++x;
	    --n;
	  }
	  return x;
	}

	template <InputIterator I, Integral N>
	inline
	I successor(I x, N n) {
	  typedef typename std::iterator_traits<I>::iterator_category C;
	  return successor(x, n, C());
	}

	template <BidirectionalIterator I>
	void hill(I first, I last)
	{
	  I middle = successor(first, std::distance(first, last)/2);
	  iota(first, middle);
	  reverse_iota(middle, last);
	}

	template <BidirectionalIterator I>
	void valley(I first, I last)
	{
	  I middle = successor(first, std::distance(first, last)/2);
	  reverse_iota(first, middle);
	  iota(middle, last);
	}
	
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
	
	// remove_if_not
	template <ForwardIterator I, Predicate P>
	I remove_if_not(I first, I last, P pred)
	{
		return std::remove_if(first, last,
			[&](const ValueType(I)& x){ return !pred(x); });
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
	
	// find_if_backward
	// (reverse neighbor find) searches a sequential data structure from end to beginning.
	template<BidirectionalIterator I, Predicate P>
	I find_if_backward(I first, I last, P pred)
	{
		if (first != last) {
			I p = last;
			do {
				if (pred(*--p))
					return p;
			} while (p != first);
		}
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
	
	// gather by Marshall Clow
	template <BidirectionalIterator I, Predicate P>
	auto gather(I first, I last, I pos, P pred) -> std::pair<I, I>
	{
		
		return{ std::stable_partition(first, pos,
			[&](const ValueType(I)& x){ return !pred(x); }),
			std::stable_partition(pos, last, pred) };
	}

	// stable_partition_position by Sean Parent
	template <InputIterator I, UnaryPredicate P>
	auto stable_partition_position(I first, I last, P p) -> I
	{
	    auto n = last - first;
	    if (n == 0) return first;
	    if (n == 1) return first + p(first);
	    I middle = first + half(n);
	    return std::rotate(stable_partition_position(first, middle, p),
	                  		middle,
	                  		stable_partition_position(middle, last, p));
	}

	// sort_subrange
	template <RandomAccessIterator I0, RandomAccessIterator I1>
	void sort_subrange(I0 first0, I0 last0, I1 first1, I1 last1)
	{
    	if (first1 == last1) return;
    	if (first1 != first0) {
        	std::nth_element(first0, first1, last0);
			++first1; 
		}
    	std::partial_sort(first1, last1, last0);
	}
	
	// partition_point_n by Stepanov
	template <InputIterator I, Integral N, UnaryPredicate P>
	I partition_point_n(I first, N n, P pred) 
	{  // precondition: is_partitioned_n(first, n, pred)
	  	while (n) {
	  		N half = half(n);
	  		I middle = first;
	  		std::advance(middle, half);

	  		if (pred(*middle)) {
	  			n = half;
	  		} else {
	  			n -= (half + 1);
	  			first = ++middle;
	  		}
		}
  		return first;
  	}

	// swap_ranges_n by Stepanov
	template <ForwardIterator I0, ForwardIterator I1, Integer N>
	auto swap_ranges_n(I0 first0, I1 first1, N n) -> std::pair<I0, I1>
	{
		while (n != N(0)) {
			std::swap(*first0++, *first1++);
			--n;
		}
		return {first0, first1};
	}
	
	// reverse by Stepanov
	// reverse that works on forward iterators and uses not more than O(log(n)) of
	// additional storage and not more than O(nlog(n)) steps, where n is the size of the range
	// which came in handy when we want to reverse ForwardIterator
	template <ForwardIterator I, Integer N>
	I reverse_n(I first, N n)
	{
		if (n == 0) return first;
		if (n == 1) return ++first;
		
		N h = half(n);
		I middle = reverse_n(first, h);
		if (odd(n)) ++middle;
		I result = reverse_n(middle, h);
		swap_ranges_n(first, middle, h);
		return result;
	}
	
	template <BidirectionalIterator I, Integer N>
	void reverse_n(I first, I last, N n)
	{
		n = half(n);
		while (n-- > N(0)) {
			std::swap(*first++, *--last);
		}
	}
	
	template <ForwardIterator I>
	void reverse(I first, I last)
	{
		reverse_n(first, std::distance(first, last));
	}

	template <BidirectionalIterator I> 
	auto reverse_until(I first , I middle, I last) -> std::pair<I,I>
	{
		while (first != middle && middle != last) {
			--last;
			std::swap(*first, *last);
			++first;
		}
		return {first , last};
	}

	template <ForwardIterator I, Integer N, BidirectionalIterator B>
	I reverse_n_with_buffer(I f, N n, B buffer)
	{
	    B buffer_end = copy_n(f, n, buffer);
	    return std::reverse_copy(buffer, buffer_end, f);
	}

	// ======================= EXT ======================================
	
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