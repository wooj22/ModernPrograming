//C++ 에서 자원을 관리하는 방법

//RAII 패턴 
//      - Resource Acquisition Is Initialization  
//      - 자원의 획득은 초기화다 
//      스택에 할당된 메모리는 자동으로 해제되는 것을 이용한 디자인 패턴 - 자원 관리를 안전하게

//스마트 포인터(smart pointer)
//    포인터 '객체' 로 만들어서 자신이 소멸 될 때 자신이 가리키고 있는 데이터도 같이 delete 하게
//    소멸자들 안에 다 사용한 자원을 해제하는 루틴


//unique_ptr 를 구현해보자 ------------------------------------------------------------
//    특정 객체에 유일한 소유권을 부여하는 포인터 객체

#include <iostream>
#include <memory>

class A             //RAII - 자원의 획득은 초기화다 
{
    int* data;
public:
    A() {
        std::cout << "자원 획득함!" << std::endl;
        data = new int[100];
    }
    ~A() {
        std::cout << "자원 해제함!" << std::endl;
        delete[] data;
    }
    void some() { std::cout << "일반 포인터와 동일하게 사용가능!" << std::endl; }
};

class A_SPtr;        //자동으로 해제시 삭제되도록 스마트 포인터 클래스를 작성하세요.

void ex()
{
    A* p = new A();
    delete p;                       //delete 필요하다.


    //A_SPtr 사용
    A_SPtr sp(new A());           //생성하여 넣어주면, 객체소멸시 자동 해제 ***
    //A_SPtr sp = new A();
    sp->some();


    //unique_ptr 는 이런 방식을 다양한 타입에 사용가능도록 템플릿화 한 것

    std::unique_ptr<A> pa(new A());
    pa->some();                     //포인터를 다루는 것과 똑같이 사용
}

int main() { ex(); }


/*

class A_SPtr        //자동으로 해제시 삭제되도록 스마트 포인터 클래스를 작성하세요.
{
    A* data;
public:
    A_SPtr(A* d) : data(d) { }
    ~A_SPtr() { delete data; }

    A& operator*() const { return *data; }
    A* operator->() const { return data; }
};


//자동으로 해제시 삭제되도록 스마트 포인터 작성  //템플릿으로 변경하세요.

template<typename T>
class SPtr        
{
    T* data;
public:
    SPtr(T* d) : data(d) { }
    ~SPtr() { delete data; }

    SPtr(const SPtr& d) = delete;

    T& operator*() const { return *data; }
    T* operator->() const { return data; }
};

*/