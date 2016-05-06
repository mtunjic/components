#include <iterator>

#define Regular typename
#define Semiregular typename
#define TotallyOrdered typename
#define StrictWeakOrdering typename

//#define Pointer typename
#define Number typename
#define Unsigned typename
#define Integral typename

#define InputIterator typename
#define OutputIterator typename
#define ForwardIterator typename
#define BidirectionalIterator typename
#define RandomAccessIterator typename

#define Sorter typename
#define Incrementable typename
#define StrictWeakOrdering typename
#define Generator typename
#define BinaryOperation typename
#define Sequence typename
#define Predicate typename
#define UnaryPredicate typename
#define Integer typename
#define BinaryInteger typename
#define EuclideanDomain typename
#define Semiregular typename
#define Transformation typename

#define ValueType(I) typename std::iterator_traits<I>::value_type
#define DifferenceType(I) typename std::iterator_traits<I>::difference_type
#define IteratorCategory(I) typename std::iterator_traits<I>::iterator_category

#define IteratorBasis typename

template <InputIterator I>
using IteratorCategory = typename std::iterator_traits<I>::iterator_category;

template <InputIterator I>
using ValueType = typename std::iterator_traits<I>::value_type;

template <InputIterator I>
using DifferenceType = typename std::iterator_traits<I>::difference_type;

template <InputIterator I>
using Pointer = typename std::iterator_traits<I>::pointer;

template <InputIterator I>
using Reference = typename std::iterator_traits<I>::reference;