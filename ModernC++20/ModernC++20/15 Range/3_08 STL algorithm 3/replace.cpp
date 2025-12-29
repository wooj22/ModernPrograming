//replace
// 
//  범위 내에 조건에 맞는 원소들을 새로운 값으로 치환한다.

#include <algorithm>
#include <array>
#include <iostream>

int main() {
    std::array<int, 10> s{ 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };

    // s 에 등장하는 모든 8 을 88 로 변경한다.
    std::replace(s.begin(), s.end(), 8, 88);

    for (int a : s) { std::cout << a << " "; }
    std::cout << '\n';

    // s 에 5 보다 작은 값을 모두 55 로 변경한다.
    std::replace_if( s.begin(), s.end(), [](const int& i) { return i < 5; }, 55);

    for (int a : s) { std::cout << a << " "; }
    std::cout << '\n';
}


//ranges::replace

#include <algorithm>
#include <array>
#include <iostream>

int main()
{
    auto print = [](const auto& v) {
            for (const auto& e : v) std::cout << e << ' ';
            std::cout << '\n';
        };

    std::array p{ 1, 6, 1, 6, 1, 6 };
    print(p);
    std::ranges::replace(p, 6, 9);
    print(p);

    std::array q{ 1, 2, 3, 6, 7, 8, 4, 5 };
    print(q);
    std::ranges::replace_if(q, [](int x) { return 5 < x; }, 5);
    print(q);
}