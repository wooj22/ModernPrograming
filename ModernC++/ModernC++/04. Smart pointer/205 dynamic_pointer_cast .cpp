//std::dynamic_pointer_cast
// 
//      std::shared_ptr에서 사용되는 함수로, 다형성을 활용하여 상위 클래스의 포인터를 하위 클래스의 포인터로 안전하게 변환
//      dynamic_cast와 유사하지만, std::shared_ptr를 사용하여 포인터의 소유권을 관리하는 데 적합
//      타입이 맞면 유효한 shared_ptr가 되고, 타입이 맞지 않으면 nullptr가 된다.

#include <iostream>
#include <memory>

class Base {
public:
    virtual ~Base() = default;  // 가상 소멸자
};

class Derived : public Base {
public:
    void show() {
        std::cout << "Derived 클래스입니다!" << std::endl;
    }
};

int main() {
    // Base 타입의 shared_ptr 생성
    std::shared_ptr<Base> basePtr = std::make_shared<Derived>();

    // dynamic_pointer_cast를 사용하여 Derived로 변환
    std::shared_ptr<Derived> derivedPtr = std::dynamic_pointer_cast<Derived>(basePtr);

    if (derivedPtr) {
        derivedPtr->show();  // 출력: Derived 클래스입니다!
    }
    else {
        std::cout << "변환에 실패했습니다." << std::endl;
    }

    return 0;
}