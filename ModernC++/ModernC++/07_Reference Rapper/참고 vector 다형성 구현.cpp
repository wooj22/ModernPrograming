//std::reference_wrapper<Base>
//
//      #include <functional>을 해주어야 사용 가능하다.
//      일반 객체를 참조 형태로 리턴해주는 역할을 한다.

// vector 다형성 구현

#include <iostream>
#include <vector>
#include <functional>
using namespace std;

struct Base
{
    virtual void print() { cout << "Base" << endl; }
};
struct Derived : public Base
{
    virtual void print() override { cout << "Derived" << endl; }
};

int main()
{
    Base b;
    Derived d;

    std::vector<Base*> my_vec;
    my_vec.push_back(&b);
    my_vec.push_back(&d);

    for (auto& ele : my_vec)
        ele->print();
}

//std::vector는 참조 형태의 원소는 받지 않는다. 따라서 다형성을 위해 위와 같이 포인터로 넣어줄 수도 있지만
//꼭 참조 형태로 넣어주고 싶다면 ???
//reference_wrapper를 사용하여, 그냥 객체인 Base 타입을 참조 형태로 리턴 받아 다형성을 실현할 수 있다.

int main()
{
    Base b;
    Derived d;

    std::vector<std::reference_wrapper<Base>> my_vec;
    my_vec.push_back(b);
    my_vec.push_back(d);

    for (auto& ele : my_vec)
        ele.get().print();
}
