// std::for_each
//      범위 내에 원소들에 대해 함수를 실행시킵니다.

#include <algorithm>  
#include <iostream>   // std::cout
#include <vector>     // std::vector

void myfunction(int i) {  // function:
    std::cout << ' ' << i;
}

struct myclass {  // function object type:
    void operator()(int i) { std::cout << ' ' << i; }
} myobject;

int main() {
    std::vector<int> myvector;
    myvector.push_back(10);
    myvector.push_back(20);
    myvector.push_back(30);

    // 일반적인 함수 포인터 전달
    std::cout << "myvector contains:";
    for_each(myvector.begin(), myvector.end(), myfunction);
    std::cout << '\n';

    // Functor 를 전달
    std::cout << "myvector contains:";
    for_each(myvector.begin(), myvector.end(), myobject);
    std::cout << '\n';

    // 람다 함수를 전달
    std::cout << "myvector contains:";
    for_each(myvector.begin(), myvector.end(),
        [](const int& n) { std::cout << ' ' << n; });
    std::cout << '\n';

    return 0;
}

// std::ranges --------------------------------------------------------

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Sum
{
    void operator()(int n) { sum += n; }
    int sum{ 0 };
};

int main()
{
    std::vector<int> nums{ 3, 4, 2, 8, 15, 267 };

    auto print = [](const auto& n) { std::cout << ' ' << n; };

    namespace ranges = std::ranges;
    std::cout << "before:";
    ranges::for_each(std::as_const(nums), print);
    print('\n');

    ranges::for_each(nums, [](int& n) { ++n; });

    // calls Sum::operator() for each number
    auto [i, s] = ranges::for_each(nums.begin(), nums.end(), Sum());
    assert(i == nums.end());

    std::cout << "after: ";
    ranges::for_each(nums.cbegin(), nums.cend(), print);

    std::cout << "\n" "sum: " << s.sum << '\n';

    //---------------------------------------------------------

    using pair = std::pair<int, std::string>;
    std::vector<pair> pairs{ {1,"one"}, {2,"two"}, {3,"tree"} };

    std::cout << "project the pair::first: ";
    ranges::for_each(pairs, print, [](const pair& p) { return p.first; });

    std::cout << "\n" "project the pair::second:";
    ranges::for_each(pairs, print, &pair::second);
    print('\n');
}

//ranges::for_each_n
  

  
