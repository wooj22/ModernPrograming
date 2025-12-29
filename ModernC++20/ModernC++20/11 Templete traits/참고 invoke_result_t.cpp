//함수의 반환형 알아내기 //invoke_result_t

#include <iostream>
#include <type_traits>

int add(int a, int b) {
    return a + b;
}

int main() 
{
    // 람다 함수 예시
    auto lambda = [](double a, double b) { return a + b; };

    // 람다 함수의 반환형을 알아내서 출력하세요

    using LambdaReturnType = std::invoke_result_t<decltype(lambda), double, double>;
    std::cout << "Return type of lambda: " << typeid(LambdaReturnType).name() << std::endl;

    return 0;
}