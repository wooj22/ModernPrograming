//std::iota
//      Fills  the range[first, last) with sequentially increasing values,
//      특정 범위의 구간을 연속적인 값(증가값)으로 채우는 데 사용
//      <numeric> 헤더

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

class BigData // inefficient to copy
{
    int data[1024]; /* some raw data */
public:
    explicit BigData(int i = 0) { data[0] = i; /* ... */ }
    operator int() const { return data[0]; }
    BigData& operator=(int i) { data[0] = i; return *this; }
    /* ... */
};

int main()
{
    std::list<BigData> l(10);
    std::iota(l.begin(), l.end(), -4);

    std::vector<std::list<BigData>::iterator> v(l.size());
    std::iota(v.begin(), v.end(), l.begin());
    // Vector of iterators (to original data) is used to avoid expensive copying,
    // and because std::shuffle (below) cannot be applied to a std::list directly.

    std::shuffle(v.begin(), v.end(), std::mt19937{ std::random_device{}() });

    std::cout << "Original contents of the list l:\t";
    for (auto const& n : l)
        std::cout << std::setw(2) << n << ' ';
    std::cout << '\n';

    std::cout << "Contents of l, viewed via shuffled v:\t";
    for (auto const i : v)
        std::cout << std::setw(2) << *i << ' ';
    std::cout << '\n';
}

 
//ranges::iota

#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

template <typename Proj = std::identity>
inline void print(auto comment, std::ranges::input_range auto&& range, Proj proj = {})
{
    for (std::cout << comment; auto const& element : range)
        std::cout << proj(element) << ' ';
    std::cout << '\n';
}

int main()
{
    std::list<int> list(8);

    // Fill the list with ascending values: 0, 1, 2, ..., 7
    std::ranges::iota(list, 0);
    print("Contents of the list: ", list);

    // A vector of iterators (see the comment to Example)
    std::vector<std::list<int>::iterator> vec(list.size());

    // Fill with iterators to consecutive list's elements
    std::ranges::iota(vec.begin(), vec.end(), list.begin());

    std::ranges::shuffle(vec, std::mt19937{ std::random_device {}() });
    print("Contents of the list viewed via vector: ", vec, [](auto it) { return *it; });
}


//ranges::iota_view
//views::iota