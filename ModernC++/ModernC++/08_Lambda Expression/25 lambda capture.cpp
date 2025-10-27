//람다 캡처 시점
/*
람다 캡처 시점은 람다가 변수나 객체를 캡처할 때, 그 변수나 객체의 상태가 람다가 생성될 때의 상태를 의미합니다.

캡처 시점의 중요성:
    캡처 시점에 대해 이해하는 것은 람다의 동작과 메모리 관리를 이해하는 데 중요합니다.
    캡처된 변수는 람다 객체가 생성될 때의 상태를 기억하며, 이후 람다가 호출될 때 그 상태를 사용합니다.

값 캡처와 참조 캡처의 차이 :

    값 캡처([x]) : 캡처된 변수의 복사본이 람다 객체에 저장됩니다.
                따라서 람다를 생성한 후 변수의 값이 변경되어도 람다 내에서는 원래의 값이 사용됩니다.
    참조 캡처([&x]) : 캡처된 변수에 대한 참조가 람다 객체에 저장됩니다.
                따라서 변수의 값이 변경되면 람다 내에서도 변경된 값을 사용할 수 있습니다.
*/

//캡처 시점의 예제 :
//캡처 시점에 따라 람다의 동작이 달라질 수 있습니다.


//1. 값 캡처

#include <iostream>

void valueCaptureExample() {
    int x = 10;
    auto lambda = [x]() { // 값 캡처
        std::cout << "Captured x: " << x << std::endl;
        };
    x = 20; // x의 값을 변경
    lambda(); // 출력: Captured x: 10 (캡처 시점의 값이 사용됨)
}

int main() {
    valueCaptureExample();
    return 0;
}

//2. 참조 캡처

#include <iostream>

void referenceCaptureExample() {
    int x = 10;
    auto lambda = [&x]() { // 참조 캡처
        std::cout << "Captured x: " << x << std::endl;
        };
    x = 20; // x의 값을 변경
    lambda(); // 출력: Captured x: 20 (변경된 값이 사용됨)
}

int main() {
    referenceCaptureExample();
    return 0;
}

//캡처 시점과 객체 수명
//  람다의 캡처 시점과 객체 수명 관리도 중요합니다.
//  람다가 캡처한 객체는 람다가 유효할 동안 계속 존재해야 하며, 캡처된 객체의 수명이 람다의 수명과 일치해야 합니다.

//예제: 유효하지 않은 참조 캡처

#include <iostream>

void invalidReferenceCapture() {
    int* ptr = new int(10);
    auto lambda = [ptr]() { // 포인터 참조 캡처
        std::cout << "Captured pointer value: " << *ptr << std::endl;
        };
    delete ptr; // 메모리 해제
    lambda(); // 정의되지 않은 동작: 이미 해제된 메모리를 참조
}

int main() {
    invalidReferenceCapture();
    return 0;
}

//정리
// 
//  값 캡처([x]) : 캡처 시점의 변수 값을 복사하여 람다에 저장.이후 변수 값이 변경되어도 람다의 값은 변하지 않음.
//  참조 캡처([&x]) : 변수에 대한 참조를 저장.변수 값이 변경되면 람다 내에서도 변경된 값을 사용.
//
//  캡처 시점과 객체 수명 : 캡처된 객체가 람다가 사용될 때까지 유효해야 하며, 객체 수명 관리를 신경 써야 함.
// 
//  람다 캡처 시점에 대한 이해는 코드의 안정성과 예측 가능성을 높이는 데 중요합니다.
//  람다 캡처를 올바르게 사용하여 코드의 의도를 명확히 하고, 메모리 안전성을 보장할 수 있습니다.



// 람다 클로저

/*
람다 클로저는 C++에서 람다 함수가 캡처한 변수들을 포함하여 그들의 상태를 저장하고, 
이후 호출 시 그 상태를 참조할 수 있도록 하는 메커니즘입니다.

클로저는 람다 함수와 관련된 데이터를 저장하는 객체로, 변수의 캡처와 상태 저장 기능을 제공합니다.
이를 통해 람다는 자신이 정의된 컨텍스트의 정보를 "클로즈" 하여 유지할 수 있습니다.

람다 클로저의 개념

    캡처된 변수: 람다가 변수나 객체를 캡처하면, 그 변수의 복사본(값 캡처) 또는 참조(참조 캡처)를 람다의 상태로 저장합니다.
    상태 저장: 람다는 클로저 객체로 구현되어, 자신이 캡처한 변수들의 상태를 유지하고, 람다가 호출될 때 그 상태를 참조할 수 있습니다.

람다 클로저의 구성 요소
    람다 클로저는 다음과 같은 요소로 구성됩니다:

    캡처 리스트: [=], [&], [x], [&x]와 같이 캡처할 변수를 지정합니다.
    파라미터 리스트: 람다 함수의 입력 파라미터를 정의합니다.
    본문: 람다 함수가 수행할 작업을 정의합니다.

람다 클로저의 특징

    캡처된 변수의 수명:
    값 캡처: 캡처된 변수의 복사본이 람다에 저장되므로, 원래 변수의 수명과 상관없이 람다가 생성된 시점의 값을 사용합니다.
    참조 캡처: 캡처된 변수에 대한 참조가 저장되므로, 원래 변수의 수명이 람다의 수명보다 길어야 합니다.

    람다의 타입:
    람다는 operator()를 정의하는 객체로 구현됩니다. 이는 std::function 객체와 유사하지만, 더 최적화되어 있습니다.

    복잡한 캡처:
    여러 변수나 객체를 캡처할 수 있으며, 캡처된 변수는 람다의 데이터 멤버로 저장됩니다.
*/

//예제: 복잡한 캡처와 클로저

#include <iostream>
#include <string>

void complexCaptureExample() {
    int x = 10;
    std::string str = "Hello";

    auto lambda = [x, str]() mutable {      // x와 str을 값으로 캡처, mutable 사용
        std::cout << "Captured x: " << x << std::endl;
        std::cout << "Captured str: " << str << std::endl;
        x += 10;                            // mutable 사용으로 x를 변경 가능
        str += " World";
        std::cout << "Modified x: " << x << std::endl;
        std::cout << "Modified str: " << str << std::endl;
        };

    lambda(); // 캡처된 변수와 수정된 값을 출력
    std::cout << "Outside lambda - x: " << x << std::endl; // x는 원본 값 유지
    std::cout << "Outside lambda - str: " << str << std::endl; // str은 원본 값 유지
}

int main() {
    complexCaptureExample();
    return 0;
}
