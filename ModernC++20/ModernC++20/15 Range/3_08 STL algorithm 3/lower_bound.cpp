//lower_bound
//  범위[first, last) 안의 원소들 중, value 보다 작지 않은(크거나 같은) 첫 번째 원소를 리턴한다.
//  만일 그런 원소가 없다면 last 를 리턴한다. 이름 그대로 어떠한 값의 '하한선' 을 의미한다.

//upper_bound
//  범위[first, last) 안의 원소들 중, value 보다 큰 첫 번째 원소를 리턴한다.
//  만일 그런 원소가 없다면 last 를 리턴한다. 이름 그대로 어떠한 값의 '상한선' 을 의미한다.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
	std::vector<int> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };

	auto lower = std::lower_bound(data.begin(), data.end(), 4);
	auto upper = std::upper_bound(data.begin(), data.end(), 4);

	std::copy(lower, upper, std::ostream_iterator<int>(std::cout, " "));
	return 0;
}


//ranges::upper_bound
//      정렬된 범위에서 특정 값보다 큰 첫 번째 위치를 찾습니다
//      해당 값보다 큰 첫 번째 요소를 가리키는 이터레이터를 반환
//      적합한 요소가 없다면 range.end()를 반환
//      입력 범위는 반드시 정렬되어 있어야 합니다.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    namespace ranges = std::ranges;

    std::vector<int> data{ 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };

    {
        auto lower = ranges::lower_bound(data.begin(), data.end(), 4);
        auto upper = ranges::upper_bound(data.begin(), data.end(), 4);

        ranges::copy(lower, upper, std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
    }
    {
        auto lower = ranges::lower_bound(data, 3);
        auto upper = ranges::upper_bound(data, 3);

        ranges::copy(lower, upper, std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
    }
}

//std::ranges::lower_bound

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace ranges = std::ranges;

template<std::forward_iterator I, std::sentinel_for<I> S, class T,
    class Proj = std::identity,
    std::indirect_strict_weak_order<
    const T*,
    std::projected<I, Proj>> Comp = ranges::less>
    constexpr
    I binary_find(I first, S last, const T& value, Comp comp = {}, Proj proj = {})
{
    first = ranges::lower_bound(first, last, value, comp, proj);
    return first != last && !comp(value, proj(*first)) ? first : last;
}

int main()
{
    std::vector data{ 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5 };
    //                                 ^^^^^^^^^^
    auto lower = ranges::lower_bound(data, 4);
    auto upper = ranges::upper_bound(data, 4);

    std::cout << "found a range [" << ranges::distance(data.cbegin(), lower)
        << ", " << ranges::distance(data.cbegin(), upper) << ") = { ";
    ranges::copy(lower, upper, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "}\n";

    // classic binary search, returning a value only if it is present

    data = { 1, 2, 4, 8, 16 };
    //               ^
    auto it = binary_find(data.cbegin(), data.cend(), 8); // '5' would return end()

    if (it != data.cend())
        std::cout << *it << " found at index " << ranges::distance(data.cbegin(), it);
}

//사용자 정의 비교 함수

#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

int main() {
    struct Person {
        std::string name;
        int age;
    };

    std::vector<Person> people = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 30},
        {"David", 35}
    };

    // 나이가 30보다 큰 첫 번째 사람 찾기
    auto it = std::ranges::upper_bound(people, 30, [](int age, const Person& person) {
        return age < person.age;
        });

    if (it != people.end()) {
        std::cout << "First person older than 30: " << it->name << " (" << it->age << ")\n";
    }
    else {
        std::cout << "No person older than 30 found.\n";
    }

    return 0;
}

//범위 어댑터와 결합

#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

int main() {
    std::vector<int> v = { 10, 20, 30, 30, 40, 50 };

    // 범위 어댑터로 일부 범위에서 검색
    auto subrange = v | std::views::drop(2); // {30, 30, 40, 50}

    auto it = std::ranges::upper_bound(subrange, 30);

    if (it != subrange.end()) {
        std::cout << "First element greater than 30: " << *it << "\n";
    }
    else {
        std::cout << "No element greater than 30 found.\n";
    }

    return 0;
}