#include <iostream>
#include <type_traits>

// 호출 가능 여부를 확인하는 템플릿
template<typename Func, typename... Args>
using is_callable = std::is_invocable<Func, Args...>;

// 호출 가능한 함수 예시
void example_function(int a, double b) {}
// 호출 불가능한 함수 예시
void non_callable_function(const std::string& s) {}

int main() {
    // example_function이 int, double 타입의 인수를 받을 수 있는지 확인
    if constexpr (is_callable<decltype(example_function), int, double>::value) {
        std::cout << "example_function can be called with int, double." << std::endl;
    }

    return 0;
}