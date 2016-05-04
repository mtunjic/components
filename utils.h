#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <list>
#include <functional>

template <typename Container>
void print(const Container& c, std::ostream& out = cout) {
    if (c.empty()) {
        out << "(empty)";
    } else {
        auto iter = begin(c); 
        out << "[ " << *iter++; 
        while (iter != end(c)) {
            out << ", " << * iter++;
        }
        out << " ]" << std::endl;

    }
}

template<typename T>
void print_queue(std::priority_queue<T> pq, size_t count = 5)
{
  size_t n{count};
  while (!pq.empty())
  {
    std::cout << pq.top() << " ";
    pq.pop();
    if (--n) continue;
    std::cout << std::endl;
    n = count; 
  }
  std::cout << std::endl;
}

template <InputIterator I>
void print_range(I first, I last, const char* msg = nullptr) {
  if (msg) std::cout << msg << ": ";
  while (first != last) std::cout << *first++ << " ";
  std::cout << std::endl;
}

template<typename T>
void fast_erase(std::vector<T>& v, size_t i)
{
    v[i] = std::move(v.back());
    v.pop_back();
}

template<typename C>
void sort(C& c)
{
    std::sort(begin(c), end(c)); 
}

template<typename C, typename Pred>
void sort(C& c, Pred p)
{
    std::sort(begin(c), end(c), p);
}


// string / text
template<typename T>
string to_string(const T& t)
{
   ostringstream os;
   os << t;
   return os.str();
}

struct bad_from_string : std::bad_cast { 
  const char* what() const override
   {
     return "bad cast from string";
   }
};

// int i = FromString<int>(s);
// std::string str = ToString(i);
template<typename T>
T from_string(const string& s)
{
  istringstream is {s};
  T t;
  if (!(is >> t)) throw bad_from_string{};
  return t;
}


inline void wait()
{
  cin.clear();
  cout << "Please enter to exit\n";
  char ch;
  cin >> ch;
  return;
}

std::string random_string( size_t length )
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
    std::generate_n( str.begin(), length, randchar );
    return str;
}

// timer
class timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    double stop() {
        auto stop_time = std::chrono::high_resolution_clock::now();
        return double(std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time).count());
    }
};

#endif /* util_h */