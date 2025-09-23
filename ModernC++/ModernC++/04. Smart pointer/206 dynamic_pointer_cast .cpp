//std::dynamic_pointer_cast
// 
//      std::shared_ptr에서 사용되는 함수로, 
//      다형성을 활용하여 상위 클래스의 포인터를 하위 클래스의 포인터로 안전하게 변환
//      dynamic_cast와 유사하지만, std::shared_ptr를 사용하여 포인터의 소유권을 관리하는 데 적합하다.
//      타입이 맞으면 유효한 shared_ptr가 되고, 타입이 맞지 않으면 nullptr 가 된다.

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


//shared_ptr을 사용할 때 dynamic_pointer_cast를 사용하지 않고 static_pointer_cast 형변환하면 
// 
//      정확한 타입 확인 없음 : static_pointer_cast는 런타임 타입 확인을 하지 않음
//      잘못된 형변환을 하면 shared_ptr 내부의 참조 카운트 관리가 꼬여서 메모리 해제 시 문제가 발생할 수 있음.




