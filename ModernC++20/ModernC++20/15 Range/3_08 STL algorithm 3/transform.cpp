https://en.cppreference.com/w/cpp/algorithm

// transform
//      입력 범위의 요소를 변환하여 출력 범위에 저장하는 알고리즘

//std::ranges::transform -----------------------------------------------------

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    namespace ranges = std::ranges;

    std::string s{ "hello" };
    ranges::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) -> unsigned char { return std::toupper(c); });


    std::vector<std::size_t> ordinals;
    ranges::transform(s, std::back_inserter(ordinals),
        [](unsigned char c) -> std::size_t { return c; });

    std::cout << s << ':';
    for (auto ord : ordinals) std::cout << ' ' << ord;
    std::cout << '\n';


    ranges::transform(ordinals, ordinals, ordinals.begin(), std::plus{});

    for (auto ord : ordinals) std::cout << ord << ' ';
    std::cout << '\n';


    struct Foo { char bar; };
    const std::vector<Foo> f = { {'h'},{'e'},{'l'},{'l'},{'o'} };
    std::string bar;
    ranges::transform(f, std::back_inserter(bar), &Foo::bar);
    std::cout << bar << '\n';
}

//범위 어댑터와 결합

#include <iostream>
#include <vector>
#include <ranges>

int main() {
    std::vector<int> input = { 1, 2, 3, 4, 5 };

    // 입력 요소를 제곱한 새로운 범위 생성
    auto squared = input | std::views::transform([](int x) { return x * x; });

    for (int n : squared) {
        std::cout << n << " ";
    }
    return 0;
}