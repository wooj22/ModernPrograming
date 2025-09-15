// weak_ptr - lock() 메서드
 
//객체의 존재 여부를 확인하기 위해 lock() 메서드를 사용하여 유효한 shared_ptr을 생성할 수 있습니다.
//lock() 메서드는 
//      weak_ptr이 참조하는 객체가 여전히 존재하면 해당 객체를 관리하는 shared_ptr을 반환하고, 
//      객체가 이미 삭제된 경우에는 빈 shared_ptr을 반환

#include <iostream>
#include <memory>

class Example {
public:
    Example() { std::cout << "Example created\n"; }
    ~Example() { std::cout << "Example destroyed\n"; }
    void show() { std::cout << "Example::show() called\n"; }
};

void use_weak_ptr(std::weak_ptr<Example> weakPtr) {
    auto sharedPtr = weakPtr.lock();            // weak_ptr을 사용해 shared_ptr 생성
    if (!sharedPtr) { // 객체가 삭제된 경우
        std::cout << "Object no longer exists\n"; 
        return;
    }

    sharedPtr->show(); // 유효한 경우 객체의 메서드 호출
}

int main() {
    std::shared_ptr<Example> sp = std::make_shared<Example>();
    std::weak_ptr<Example> wp = sp;  // shared_ptr을 weak_ptr로 변환

    use_weak_ptr(wp);  // 유효한 경우 객체 사용

    sp.reset();  // shared_ptr의 소멸로 객체 삭제

    use_weak_ptr(wp);  // 객체가 이미 삭제된 경우

    return 0;
}