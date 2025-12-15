//C++11 표준 type_traits 예제 -------------------------------------------------------------

//std::is_same      
//      true T 와 U 가 같은 유형이면 true, 그렇지 않으면 false

/*
    template< class T, class U >
    struct is_same;

    template< class T, class U >
    inline constexpr bool is_same_v = is_same<T, U>::value;
*/


#include <iostream>
#include <type_traits>
#include <cstdint>

void print_separator()
{
    std::cout << "-----\n";
}

int main()
{
    std::cout << std::boolalpha;

    // 구현 정의 사실

    // 'int'가 32 비트이면 보통 참
    std::cout << std::is_same<int, std::int32_t>::value << ' '; // ~ 참
    // ILP64 데이터 모델이 사용되는 경우 true 일 수 있습니다.
    std::cout << std::is_same<int, std::int64_t>::value << ' '; // ~ 거짓

    // C++17의 `std::is_same_v<T, U>` 형식을 사용하는 것을 제외하고 위와 동일한 테스트
    std::cout << std::is_same_v<int, std::int32_t> << ' ';  // ~ 참
    std::cout << std::is_same_v<int, std::int64_t> << '\n'; // ~ 거짓

    print_separator();

    // 커플 변수의 유형을 비교합니다.
    long double num1 = 1.0;
    long double num2 = 2.0;
    std::cout << std::is_same_v<decltype(num1), decltype(num2)> << '\n'; // true

    print_separator();

    // 'float'는 정수 유형이 아닙니다.
    std::cout << std::is_same<float, std::int32_t>::value << '\n'; // false

    print_separator();

    // 'int'는 암시 적으로 '서명 됨'입니다.
    std::cout << std::is_same<int, int>::value << ' ';          // true
    std::cout << std::is_same<int, unsigned int>::value << ' '; // false
    std::cout << std::is_same<int, signed int>::value << '\n';  // true

    print_separator();

    // 다른 유형과 달리 'char'는 'unsigned'도 아니고 'signed'도 아닙니다.
    std::cout << std::is_same<char, char>::value << ' ';          // true
    std::cout << std::is_same<char, unsigned char>::value << ' '; // false
    std::cout << std::is_same<char, signed char>::value << '\n';  // false

    // const-qualified type T는 non-const T와 동일하지 않습니다.
    static_assert(not std::is_same<const int, int>());
}

/*
//same_as   (C++20) concept ----------------------------------------------------------

    #include <concepts>
    #include <iostream>

    template<typename T, typename ... U>
    concept IsAnyOf = (std::same_as<T, U> || ...);

    template<typename T>
    concept IsPrintable = std::integral<T> || std::floating_point<T> ||
    IsAnyOf<std::remove_cvref_t<std::remove_pointer_t<std::decay_t<T>>>, char, wchar_t>;

    void println(IsPrintable auto const ... arguments)
    {
        (std::wcout << ... << arguments) << '\n';
    }

    int main() { println("Example: ", 3.14, " : ", 42, " : [", 'a', L'-', L"Z]"); }

*/