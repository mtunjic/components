#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "concepts.h"
#include <iterator>

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

#endif