//Circular references - 순환 참조 문제
 
//서로 참조하는 shared_ptr --------------------------------------------------------------------------------
//  앞서 shared_ptr 는 참조 개수가 0 이 되면 가리키는 객체를 메모리에서 해제 시킨다고 했습니다.
//  그런데, 객체들을 더이상 사용하지 않는되도 불구하고 참조 개수가 절대로 0 이 될 수 없는 상황이 있습니다.

#include <iostream>
#include <memory>

class A {
    int* data;
    std::shared_ptr<A> other;

public:
    A() {
        data = new int[100];
        std::cout << "자원을 획득함!" << std::endl;
    }

    ~A() {
        std::cout << "소멸자 호출!" << std::endl;
        delete[] data;
    }

    void set_other(std::shared_ptr<A> o) { other = o; }
};

int main() {
    std::shared_ptr<A> pa = std::make_shared<A>();
    std::shared_ptr<A> pb = std::make_shared<A>();

    pa->set_other(pb);
    pb->set_other(pa);
}

// A 객체 소멸자 호출 안됨
