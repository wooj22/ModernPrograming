//RTTI( Run Time Type Info )

#include <iostream>   

class Base
{
public:
    // virtual 테이블을 위한 함수
    virtual ~Base() {}
};

class Drived1 : public Base {};
class Drived2 : public Base {};

// RTTI(Run Time Type Info)
void F(Base* pB)
{
    // typeid
    if (typeid(*pB) == typeid(Drived2))
    {
        std::cout << typeid(*pB).name() << std::endl;
    }
    else
    {
        std::cout << "No!" << std::endl;
    }

    // dynamic_cast
    if (dynamic_cast<Drived2*>(pB))
    {
        std::cout << typeid(*pB).name() << std::endl;
    }
    else {
        std::cout << "No!" << std::endl;
    }
}

int main()
{
    Base* d1 = new Drived1;
    Base* d2 = new Drived2;

    // Derived2 가 아니면 "No" 출력하도록 F 함수 구현하기
    F(d1);
    F(d2);

    return 0;
}




// is_base_of_v ----------------------------------------------

#include <iostream>

class A {};
class B : public A {};
class C : private A {};

// std::is_base_of == true also for private inheritance
static_assert(std::is_base_of_v<B, B> == true);      // same class: true
static_assert(std::is_base_of_v<int, int> == false); // same primitive type: false
static_assert(std::is_base_of_v<A, B> == true);      // public inheritance: true
static_assert(std::is_base_of_v<A, C> == true);      // private inheritance: true

int main() {}


// 객체 타입 비교하기 //C++17 ----------------------------------

#include <iostream>
using namespace std;

class P1 { };
class P2 : public P1 { };

int main(void)
{
    cout << is_same_v<P1, P1> << endl;
    cout << is_same_v<P1, P2> << endl;

    P1 p1;
    P2 p2;
    cout << is_same_v<decltype(p1), decltype(p1)> << endl;
    cout << is_same_v<decltype(p1), decltype(p2)> << endl;
}

