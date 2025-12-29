//두 값을 받아 더 큰 값을 반환하는 템플릿 함수를 작성하라.
//단, 자료형이 char 인 경우는 대문자 값을 반환합니다.

#include <concepts>
#include <iostream>

template<typename T, typename U>
auto max_value(const T& a, const U& b)
{
    return (a > b) ? a : b;
}

//template<>
//auto max_value<char, char>(const char& a, const char& b)
//{
//    auto temp = a, temp2 = b;
//    if (temp - 32 == temp2 || temp + 32 == temp2)
//    {
//        return (a < b) ? a : b;
//    }
//
//    return (a > b) ? a : b;
//}

template<>
auto max_value<char, char>(const char& a, const char& b)
{
    unsigned char ua = static_cast<unsigned char>(a);
    unsigned char ub = static_cast<unsigned char>(b);

    char upperA = static_cast<char>(std::toupper(ua));
    char upperB = static_cast<char>(std::toupper(ub));

    // 같은 알파벳이면 (대소문자 무시하고 비교)
    if (upperA == upperB) {
        return upperA; // 대문자를 반환
    }

    return (a > b) ? a : b;
}

int main() {
    std::cout << max_value(5, 7) << std::endl;         // 7
    std::cout << max_value(1.3, 3.14) << std::endl;    // 3.14
    std::cout << max_value('b', 'c') << std::endl;                 // 'C' (둘 중 더 큰 'c'를 대문자)
    std::cout << max_value('C', 'c');
}


