//concepts + constexpr if 분기 문제
// 
//문제. 출력 가능 타입에만 작동하는 describe() 함수 구현

#include <concepts>
#include <iostream>
#include <string>

template<typename T>
concept Streamable = requires(T a) {
    { std::cout << a } -> std::same_as<std::ostream&>;
};

template<typename T>
void describe(const T& val) {
    if constexpr (Streamable<T>) {
        std::cout << "Value: " << val << "\n";
    }
    else {
        std::cout << "Not printable.\n";
    }
}

struct Silent {};

int main() {
    describe(42);               // 출력: Value: 42
    describe(std::string("Hi")); // 출력: Value: Hi
    describe(Silent{});         // 출력: Not printable.
}