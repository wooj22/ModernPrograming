//std::search
//      범위 내의 문자열을 검색해서 그 첫 번째로 발견된 위치를 리턴한다.

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// cont 안에 s 가 있는지 없는지를 리턴한다.
template <typename Container>
bool in_quote(const Container& cont, const std::string& s) {
    return std::search(cont.begin(), cont.end(), s.begin(), s.end()) != cont.end();
}

int main() {
    std::string str = "why waste time learning, when ignorance is instantaneous?";
    // str.find() can be used as well
    std::cout << std::boolalpha
        << in_quote(str, "learning") << '\n'
        << in_quote(str, "lemming") << '\n';

    std::vector<char> vec(str.begin(), str.end());
    std::cout << std::boolalpha
        << in_quote(vec, "learning") << '\n'
        << in_quote(vec, "lemming") << '\n';
}

//std::search

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string in =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
        " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua";
    std::string needle = "pisci";

    // Boyer-Moore 알고리즘을 사용해서 검색을 수행한다.
    auto it =
        std::search(in.begin(), in.end(),
            std::boyer_moore_searcher(needle.begin(), needle.end()));
    if (it != in.end())
        std::cout << "The string " << needle << " found at offset " << it - in.begin() << '\n';
    else
        std::cout << "The string " << needle << " not found\n";
}


//std::ranges::search

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <string_view>

using namespace std::literals;

void print(int id, const auto& haystack, const auto& needle, const auto& found)
{
    std::cout << id << ") search(\"" << haystack << "\", \"" << needle << "\"); ";
    const auto first = std::distance(haystack.begin(), found.begin());
    const auto last = std::distance(haystack.begin(), found.end());
    if (found.empty())
        std::cout << "not found;";
    else
    {
        std::cout << "found: \"";
        for (const auto x : found)
            std::cout << x;
        std::cout << "\";";
    }
    std::cout << " subrange: {" << first << ", " << last << "}\n";
}

int main()
{
    constexpr auto haystack{ "abcd abcd"sv };
    constexpr auto needle{ "bcd"sv };

    // the search uses iterator pairs begin()/end():
    constexpr auto found1 = std::ranges::search(
        haystack.begin(), haystack.end(),
        needle.begin(), needle.end());
    print(1, haystack, needle, found1);

    // the search uses ranges r1, r2:
    constexpr auto found2 = std::ranges::search(haystack, needle);
    print(2, haystack, needle, found2);

    // 'needle' range is empty:
    constexpr auto none{ ""sv };
    constexpr auto found3 = std::ranges::search(haystack, none);
    print(3, haystack, none, found3);

    // 'needle' will not be found:
    constexpr auto awl{ "efg"sv };
    constexpr auto found4 = std::ranges::search(haystack, awl);
    print(4, haystack, awl, found4);


    // the search uses custom comparator and projections:
    constexpr auto bodkin{ "234"sv };
    auto found5 = std::ranges::search(haystack, bodkin,
        [](const int x, const int y) { return x == y; }, // pred
        [](const int x) { return std::toupper(x); }, // proj1
        [](const int y) { return y + 'A' - '1'; }); // proj2
    print(5, haystack, bodkin, found5);
}



//find_end: 주어진 범위에서 어떤 원소가 가장 마지막으로 등장하는 위치를 찾는다.

//includes : 어떤 원소열이 다른 원소열을 포함하고 있는지 확인한다.

//equal : 두 원소열이 같은지 다른지를 확인한다.

//find, find_if, find_if_not : 특정 조건을 만족하는 원소를 찾는다.

//lexicographical_compare : 두 원소열의 사전적 크기 비교를 수행한다.

//mismatch : 두 원소열에서 서로 다른 첫 번째 위치를 찾는다.

//search_n : 특정 원소가 여러번 반복되는 위치를 찾는다.