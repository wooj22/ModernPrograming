//ranges::equal

// equal to test if a string is a palindrome - 회문 판별하기

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <string_view>

constexpr bool is_palindrome(const std::string_view s)
{
    namespace views = std::views;
    auto forward = s | views::take(s.size() / 2);
    auto backward = s | views::reverse | views::take(s.size() / 2);
    return std::ranges::equal(forward, backward);
}

void test(const std::string_view s)
{
    std::cout << std::quoted(s) << " is "
        << (is_palindrome(s) ? "" : "not ")
        << "a palindrome\n";
}

int main()
{
    test("radar");
    test("hello");
    static_assert(is_palindrome("ABBA") and not is_palindrome("AC/DC"));
}

//std::quoted( ) - 출력 시 문자열에 따옴표를 추가