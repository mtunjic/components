#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>

 
using namespace std;
 
string reverse_string(const string& s)
{
    cout << "Reversing " << s << endl;
    string ss(s);
    reverse(ss.begin(), ss.end());
    return ss;
}
 
template <typename RAIter>
int parallel_sum(RAIter beg, RAIter end)
{
    auto len = end - beg;
    if(len < 1000)
        return std::accumulate(beg, end, 0);
 
    RAIter mid = beg + len/2;
    auto handle = std::async(std::launch::async,
                             parallel_sum<RAIter>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}
 
int main()
{

    future<string> f = async(launch::async, reverse_string, "Roma tibi subito motibus ibit amor");
    auto g = async(launch::async, reverse_string, "Anita lava la tina");
    auto h = async(launch::async, reverse_string, "A man, a plan, a canal: Panama");
     
    cout << "SHOWING RESULTS...." << endl;
     
    cout << "R1: " << f.get() << endl << endl;
    cout << "R2: " << g.get() << endl << endl;
    cout << "R3: " << h.get() << endl << endl;

    std::vector<int> v(1000000, 1);
    std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';
}