// -------------------------------------------------------------------------
// 아래 코드를 스마트 포인터로 변경하세요. unique_ptr

#include <iostream>
using namespace std;

int main(void)
{
    // int*
    int* ptr(new int(5));
    cout << *ptr << endl;
    delete ptr;

    // unique_ptr<int>
    auto ptr = make_unique<int>(5);
    cout << *ptr << endl;
}


// -------------------------------------------------------------------------
// 소멸할 때 자동으로 삭제되도록 스마트 포인터 class 를 작성하세요.

#include <iostream>
#include <memory>
using namespace std;

class A
{
private:
    int* data;

public:
    A() { data = new int[100]; }
    ~A() { delete[] data; }
    void func() { std::cout << "일반 포인처럼 사용!" << std::endl; }
};

template<class T>
class smart_ptr
{
private:
    T* ptr;

public:
    smart_ptr(T* data)
    {
        ptr = data;
    }

    ~smart_ptr()
    {
        delete ptr;
    }

    T* operator->()
    {
        return ptr;
    }
};

void main()
{
    smart_ptr<A> sp(new A());      // smart_ptr<T> 
    sp->func();
}
