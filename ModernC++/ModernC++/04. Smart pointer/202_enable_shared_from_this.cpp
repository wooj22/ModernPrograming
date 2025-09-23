//shared_ptr
//	    여러 개의 스마트 포인터가 하나의 객체를 같이 소유 해야 하는 경우.
//	    특정 자원을 몇 개의 객체에서 가리키는 지를 추적한 다음에, 
//      그 수가 0 이 되야만 비로소 해제를 시켜주는 방식의 포인터.

#include <iostream>
#include <memory>
#include <vector>

class A {
    int* data;

public:
    A() 
    {
        data = new int[100];
        std::cout << "자원을 획득함!" << std::endl;
    }

    ~A() 
    {
        std::cout << "소멸자 호출!" << std::endl;
        delete[] data;
    }
};

int main() {
    std::vector<std::shared_ptr<A>> vec;

    vec.push_back(std::shared_ptr<A>(new A()));    
    vec.push_back(std::shared_ptr<A>(vec[0]));
    vec.push_back(std::shared_ptr<A>(vec[1]));

    // 벡터의 첫번째 원소를 소멸 시킨다.
    std::cout << "첫 번째 소멸!" << std::endl;
    vec.erase(vec.begin());

    // 그 다음 원소를 소멸 시킨다.
    std::cout << "다음 원소 소멸!" << std::endl;
    vec.erase(vec.begin());

    // 마지막 원소 소멸
    std::cout << "마지막 원소 소멸!" << std::endl;
    vec.erase(vec.begin());

    std::cout << "프로그램 종료!" << std::endl;
}


// enable_shared_from_this ---------------------------------------------------------------
// 
//      shared_ptr을 이용하여 동일한 객체에 대한 소유권을 부여하고 싶은 경우
//      class 혹은 structure를 enable_shared_from_this를 상속받게 한다.
//
//      그이유는 shared_ptr을 이용하여 단순히 객체에 대한 소유권을 공유하려고 할 때, 잘못된 참조가 발생할 수 있는데
//      먼저 객체에 대한 소유권을 보유한 쪽에서 객체를 소멸시켜 버림으로써 나중에 소유권을 공유한 쪽에서 참조 문제가 발생하는 것이다.
//      enable_shared_from_this의 사용은 이렇게 객체의 생성 및 소멸에 의한 참조 문제를 방지하기 위해 사용이 된다.


#include <iostream>
#include <memory>

class A : public std::enable_shared_from_this<A> 
{
    int* data;
public:
    A() {
        data = new int[100];
        std::cout << "자원을 획득함!" << std::endl;
    }
    ~A() {
        std::cout << "소멸자 호출!" << std::endl;
        delete[] data;
    }
    std::shared_ptr<A> get_shared_ptr() { return shared_from_this(); }
};

int main() {
    std::shared_ptr<A> pa1 = std::make_shared<A>();
    std::shared_ptr<A> pa2 = pa1->get_shared_ptr();     //
    std::cout << pa1.use_count() << std::endl;
    std::cout << pa2.use_count() << std::endl;
}
