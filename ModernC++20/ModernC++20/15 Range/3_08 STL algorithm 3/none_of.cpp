//std::none_of
//      만일 범위 내에 원소가 아무것도 없다면 참을 리턴합니다.

#include <algorithm>  
#include <array>      // std::array
#include <iostream>   // std::cout

int main() {
    std::array<int, 8> foo = { 1, 2, 4, 8, 16, 32, 64, 128 };

    if (std::none_of(foo.begin(), foo.end(), [](int i) { return i < 0; }))
        std::cout << "음수인 원소가 하나도 없습니다.\n";

    return 0;
}

//all_of: 범위 안에 모든 원소들이 조건을 만족하는지 확인한다.

int main() {
    std::array<int, 8> foo = { 3, 5, 7, 11, 13, 17, 19, 23 };

    if (std::all_of(foo.begin(), foo.end(), [](int i) { return i % 2; }))
        std::cout << "모든 원소들이 홀수 입니다\n";

    return 0;
}

//any_of : 범위 안의 원소들 중 조건을 만족하는 원소가 있는지 확인한다.

int main() {
    std::array<int, 7> foo = { 0, 1, -1, 3, -3, 5, -5 };

    if (std::any_of(foo.begin(), foo.end(), [](int i) { return i < 0; }))
        std::cout << "범위 내에 음수가 있습니다.\n";

    return 0;
}


// std::ranges::all_of 
// std::ranges::any_of 
// std::ranges::none_of

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

namespace ranges = std::ranges;

constexpr bool some_of(auto&& r, auto&& pred) // some but not all
{
    return not (ranges::all_of(r, pred) or ranges::none_of(r, pred));
}

constexpr auto w = { 1, 2, 3 };
static_assert(!some_of(w, [](int x) { return x < 1; }));
static_assert(some_of(w, [](int x) { return x < 2; }));
static_assert(!some_of(w, [](int x) { return x < 4; }));

int main()
{
    std::vector<int> v(10, 2);
    std::partial_sum(v.cbegin(), v.cend(), v.begin());
    std::cout << "Among the numbers: ";
    ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    if (ranges::all_of(v.cbegin(), v.cend(), [](int i) { return i % 2 == 0; }))
        std::cout << "All numbers are even\n";

    if (ranges::none_of(v, std::bind(std::modulus<int>(), std::placeholders::_1, 2)))
        std::cout << "None of them are odd\n";

    auto DivisibleBy = [](int d)
        {
            return [d](int m) { return m % d == 0; };
        };

    if (ranges::any_of(v, DivisibleBy(7)))
        std::cout << "At least one number is divisible by 7\n";
}

//find_if : 범위 안에 원소들 중 조건과 일치하는 원소를 찾는다.
 
// std::ranges::find
// std::ranges::find_if
// std::ranges::find_if_not

#include <algorithm>
#include <iostream>
#include <iterator>

int main()
{
    namespace ranges = std::ranges;

    const int n1 = 3;
    const int n2 = 5;
    const auto v = { 4, 1, 3, 2 };

    if (ranges::find(v, n1) != v.end())
        std::cout << "v contains: " << n1 << '\n';
    else
        std::cout << "v does not contain: " << n1 << '\n';

    if (ranges::find(v.begin(), v.end(), n2) != v.end())
        std::cout << "v contains: " << n2 << '\n';
    else
        std::cout << "v does not contain: " << n2 << '\n';

    auto is_even = [](int x) { return x % 2 == 0; };

    if (auto result = ranges::find_if(v.begin(), v.end(), is_even); result != v.end())
        std::cout << "First even element in v: " << *result << '\n';
    else
        std::cout << "No even elements in v\n";

    if (auto result = ranges::find_if_not(v, is_even); result != v.end())
        std::cout << "First odd element in v: " << *result << '\n';
    else
        std::cout << "No odd elements in v\n";

    auto divides_13 = [](int x) { return x % 13 == 0; };

    if (auto result = ranges::find_if(v, divides_13); result != v.end())
        std::cout << "First element divisible by 13 in v: " << *result << '\n';
    else
        std::cout << "No elements in v are divisible by 13\n";

    if (auto result = ranges::find_if_not(v.begin(), v.end(), divides_13); result != v.end())
        std::cout << "First element indivisible by 13 in v: " << *result << '\n';
    else
        std::cout << "All elements in v are divisible by 13\n";
}