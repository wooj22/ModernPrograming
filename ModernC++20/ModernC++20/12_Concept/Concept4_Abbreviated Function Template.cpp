//함수 매개변수에 auto를 사용할 경우
//      auto는 타입 추론, 함수 템플릿 작성이 간소화된 것
//      템플릿 함수의 축약 문법

//Abbreviated Function Template ( 축약 함수 템플릿 )
//		C++20에서 도입된 기능, '축약 함수 템플릿', '약식 함수 템플릿', 'auto 템플릿 함수'
//		기존의 템플릿 함수 선언 방식보다 간결하게 작성할 수 있도록 지원합니다.
//		특히, 함수의 매개변수에서 개념(concept)을 바로 지정하여 제약 조건을 적용하는 것이 가능합니다.


// 전통적인 템플릿 함수 선언 방식

#include <concepts>
#include <iostream>

template <typename T>
    requires std::integral<T> // T가 integral 타입이어야 한다는 제약 조건
void print(T i) {
    std::cout << "Integral: " << i << '\n';
}

int main() {
}


// Abbreviated Function Template 방식 (C++20)

#include <concepts>
#include <iostream>

void print(std::integral auto i) {
    std::cout << "Integral: " << i << '\n';
}

int main() {
}

//기존 템플릿 함수 선언 방식을 더 직관적으로 바꿔주는 C++20의 강력한 기능입니다.
//이를 활용하면 코드 가독성이 높아지고, 컴파일러가 타입 제약 조건을 명확히 강제할 수 있습니다.
