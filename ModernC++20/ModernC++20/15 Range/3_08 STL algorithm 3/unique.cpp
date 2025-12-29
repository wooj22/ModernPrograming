//std::ranges::unique
//      연속적으로 중복된 요소를 제거하는 알고리즘

//주의사항
//연속된 중복만 제거 : 중복 제거를 위해 먼저 std::ranges::sort로 정렬해야 할 수도 있습니다.
//컨테이너 크기 변경 없음 : 중복 제거 이후에도 컨테이너 크기는 변하지 않습니다.
//      제거된 요소를 처리하려면 추가로 std::erase 또는 std::erase_if를 사용해야 합니다.

#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

struct id {
    int i;
    explicit id(int i) : i{ i } {}
};

void print(id i, const auto& v)
{
    std::cout << i.i << ") ";
    std::ranges::for_each(v, [](auto const& e) { std::cout << e << ' '; });
    std::cout << '\n';
}

int main()
{
    // a vector containing several duplicated elements
    std::vector<int> v{ 1, 2, 1, 1, 3, 3, 3, 4, 5, 4 };

    print(id{ 1 }, v);

    // remove consecutive (adjacent) duplicates
    const auto ret = std::ranges::unique(v);
    // v now holds {1 2 1 3 4 5 4 x x x}, where 'x' is indeterminate
    v.erase(ret.begin(), ret.end());
    print(id{ 2 }, v);


    // sort followed by unique, to remove all duplicates
    std::ranges::sort(v); // {1 1 2 3 4 4 5}
    print(id{ 3 }, v);

    const auto [first, last] = std::ranges::unique(v.begin(), v.end());
    // v now holds {1 2 3 4 5 x x}, where 'x' is indeterminate
    v.erase(first, last);
    print(id{ 4 }, v);


    // unique with custom comparison and projection
    std::vector<std::complex<int>> vc{ {1, 1}, {-1, 2}, {-2, 3}, {2, 4}, {-3, 5} };
    print(id{ 5 }, vc);

    const auto ret2 = std::ranges::unique(vc,
        // consider two complex nums equal if their real parts are equal by module:
        [](int x, int y) { return std::abs(x) == std::abs(y); }, // comp
        [](std::complex<int> z) { return z.real(); }             // proj
    );
    vc.erase(ret2.begin(), ret2.end());
    print(id{ 6 }, vc);
}

//범위 어댑터와 결합

#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main() {
    std::vector<int> v = { 1, 1, 2, 2, 3, 3, 3, 4 };

    // 중복을 제거한 새 범위 생성
    auto unique_range = v | std::views::unique;

    for (int n : unique_range) {
        std::cout << n << " ";
    }

    return 0;
}

//원래 컨테이너의 요소 유지

#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

int main() {
    std::vector<int> v = { 1, 1, 2, 2, 3, 3, 3, 4 };

    // 연속된 중복 제거
    auto result = std::ranges::unique(v);

    // 유효 범위 출력
    std::cout << "Unique range: ";
    for (auto it = v.begin(); it != result.begin; ++it) {
        std::cout << *it << " ";
    }

    // 남아 있는 요소 확인
    std::cout << "\nRemaining: ";
    for (auto it = result.begin; it != v.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}


// 사용자 정의 비교 함수 사용 ( std::ranges::unique )

#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

int main() {
    std::vector<std::string> v = { "apple", "Apple", "banana", "Banana", "banana" };

    // 대소문자를 무시하고 중복 제거
    auto result = std::ranges::unique(v, [](const std::string& a, const std::string& b) {
        return std::equal(a.begin(), a.end(), b.begin(), b.end(), [](char c1, char c2) {
            return std::tolower(c1) == std::tolower(c2);
            });
        });

    // 유효 범위 출력
    for (auto it = v.begin(); it != result.begin(); ++it) {
        std::cout << *it << " ";
    }

    //v.erase(result.begin(), result.end());

    //for (auto e : v) std::cout << e << " ";

    return 0;
}