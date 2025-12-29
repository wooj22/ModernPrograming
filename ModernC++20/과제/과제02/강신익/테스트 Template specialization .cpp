//두 값을 받아 더 큰 값을 반환하는 템플릿 함수를 작성하라.
//단, 자료형이 char 인 경우는 대문자 값을 반환합니다.

#include <concepts>
#include <iostream>

template<typename T>
T max_value(T a, T b)
{
    return a > b ? a : b;
}

template<>
char max_value(char a, char b)
{
    char result = a > b ? a : b;
    if (result >= 'a')
    {
        result -= 'a' - 'A';
    }

    return result;
}

int main() {
    std::cout << max_value(5, 7) << std::endl;         // 7
    std::cout << max_value(1.3, 3.14) << std::endl;    // 3.14
    std::cout << max_value('b', 'c');                  // 'C' (둘 중 더 큰 'c'를 대문자)
}

