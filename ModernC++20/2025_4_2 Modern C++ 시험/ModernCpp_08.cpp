// Ranges
//
// 주어진 vector에서 최고 점수 3개를 골라 순서(내림차순)대로 출력하라. 
// ranges 라이브러리 활용하세요

#include <iostream>
#include <algorithm>
#include <vector>
#include <ranges>

using namespace std;

int main()
{
    std::vector<int> v = { 10, 5, 6, 1, 3, 7, 7 };

    std::ranges::sort(v, std::greater<int>());
    auto r = v
        | std::views::take(3);

    for (auto n : r) std::cout << n << " ";
}