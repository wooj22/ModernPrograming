//this 포인터 캡처
//  클래스 내부의 람다 표현식에서 this를 캡처하면, 
//  람다 내부에서 클래스의 멤버 변수와 멤버 함수에 접근할 수 있습니다. 
// 
//  this 포인터는 클래스의 현재 인스턴스를 가리킵니다.


#include <iostream>
#include <vector>

class Example {
public:
    Example(int x) : value(x) {}

    void print() {
        // `this`를 캡처하여 멤버 변수에 접근
        auto lambda = [this]() {
            std::cout << "Value: " << value << std::endl;
            };

        lambda();
    }

private:
    int value;
};

int main() {
    Example ex(42);
    ex.print();  // 출력: Value: 42
    return 0;
}
//여기서 람다[this]는 클래스의 멤버 변수 value를 접근할 수 있습니다.


//캡처 초기화와 this
//  C++14에서 도입된 초기화 캡처를 사용하면 캡처 리스트에서 변수를 선언하고 초기화할 수 있습니다.
//  this와 함께 사용할 때도 유용합니다.이 기능은 람다 내에서 외부 변수를 초기화할 때 사용됩니다.


#include <iostream>

class Example {
public:
    Example(int x) : value(x) {}

    void print() {
        // 초기화 캡처와 `this`를 함께 사용
        auto lambda = [this, capturedValue = value * 2]() {
            std::cout << "Captured value: " << capturedValue << std::endl;
            std::cout << "Member value: " << value << std::endl;
            };

        lambda();
    }

private:
    int value;
};

int main() {
    Example ex(42);
    ex.print();  // 출력: Captured value: 84
    //         Member value: 42
    return 0;
}
//위 코드에서 capturedValue는 value * 2로 초기화된 변수를 캡처합니다.
//this는 클래스의 현재 인스턴스를 캡처하여 멤버 변수 value에 접근할 수 있게 합니다.


//캡처 초기화와 this를 함께 사용한 예
//this와 초기화 캡처를 함께 사용하는 것이 가능하며, 이를 통해 클래스 멤버와 함께 초기화된 변수의 값을 사용할 수 있습니다.


#include <iostream>
#include <string>

class Example {
public:
    Example(int x, std::string str) : value(x), message(str) {}

    void print() {
        // 초기화 캡처와 `this`를 함께 사용
        auto lambda = [this, formattedMessage = "[" + message + "]"]() {
            std::cout << "Formatted message: " << formattedMessage << std::endl;
            std::cout << "Value: " << value << std::endl;
            };

        lambda();
    }

private:
    int value;
    std::string message;
};

int main() {
    Example ex(42, "Hello");
    ex.print();  // 출력: Formatted message: [Hello]
    //         Value: 42
    return 0;
}
//이 예시에서는 formattedMessage를[+message + ]로 초기화하여 캡처하고, this를 사용하여 클래스의 멤버 변수 value를 접근합니다.
//초기화 캡처를 통해 외부에서 계산된 값을 람다 내부에서 사용할 수 있습니다.


//결론

//this 포인터 캡처 : 클래스의 멤버 변수나 멤버 함수에 접근할 수 있게 해줍니다.
//                  [this]를 캡처 리스트에 포함시키면 람다 내부에서 this를 사용할 수 있습니다.
//캡처 초기화 : C++14부터 지원되는 기능으로, 캡처 리스트에서 변수를 선언하고 초기화할 수 있습니다.
//                  이를 통해 람다 내에서 사용할 변수의 초기값을 설정할 수 있습니다.
// 
//this와 초기화 캡처 : C++14의 초기화 캡처와 this를 함께 사용하여 클래스의 멤버와 초기화된 변수를 동시에 사용할 수 있습니다.
//이러한 기능을 활용하면 람다 표현식을 더욱 유연하고 강력하게 사용할 수 있습니다.

//람다캡쳐의 범위는 해당범위의 비정적 외부변수이므로,
//      참조, 포인터, 정적 개체가 람다에 포함될 때는 독립적으로 작동되지 않을 수 있다. 주의하라.
// 
//      독립적인 함수객체로 람다를 사용하려면, 람다의 토기화 캡쳐를 활용하라.
//      클래스의 멤버를 사용하려면 this 캡쳐를 명시적으로 사용하라.