#ifndef UTILS_H
#define UTILS_H

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

#endif /* util_h */