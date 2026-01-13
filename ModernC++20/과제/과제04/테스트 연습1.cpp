
// 짝수 요소중에 3개만 선택해서 역순 출력하라 ( ranges )
// 	    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

    // 짝수 요소중에 3개만 선택해서 역순 출력
    auto view =
        v
        | std::views::filter([](int x) {return x % 2 == 0; })
        | std::views::take(3)
        | std::views::reverse;

    for (int x : view)
        std::cout << x << std::endl;
}



// 최고 점수 3개를 골라 순서대로 출력하라 -----------------------------------
// std::ranges::sort, std::views::take

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <ranges>
using namespace std;

int main()
{
    std::vector<int> v = { 10, 5, 6, 1, 3, 7, 7 };

    std::ranges::sort(v, std::greater<int>());
    auto top3 = v | std::views::take(3);

    for (int x : top3)
        std::cout << x << std::endl;
}


// 문자열을 ',' 기준으로 분리한 후, 각 문자열의 크기를 출력하라. --------------
// std::views::split, std::views::transform

#include <string>
#include <ranges>
#include <iostream>

int main()
{
    std::string str = "hello,hi,good";   //출력: 5 2 4

    auto view =
        str
        | std::views::split(',')
        | std::views::transform([](auto&& part)
            {
                return std::ranges::distance(part);
            });

    for (auto len : view)
        std::cout << len << " ";
}