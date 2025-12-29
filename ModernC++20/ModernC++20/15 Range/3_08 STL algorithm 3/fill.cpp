//ranges::fill

#include <algorithm>
#include <iostream>
#include <vector>

void println(std::vector<int> const& vi)
{
    for (int e : vi)
        std::cout << e << ' ';
    std::cout << '\n';
}

int main()
{
    std::vector<int> v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // 벡터 v 값을 -1 로 채우기

    std::ranges::fill(v.begin(), v.end(), -1);
    println(v);

    std::ranges::fill(v, 10);
    println(v);
}