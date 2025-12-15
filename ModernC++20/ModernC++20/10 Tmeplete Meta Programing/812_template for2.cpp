// 가변템플릿과 상속 
// 매개변수 팩을 이용하여, 가변 개수의 클래스를 정의하기

#include <iostream>

class Mixin1
{
public:
    Mixin1(int i) : m_value{ i } {}
    virtual void mixin1Func() { std::cout << "Mixin1: " << m_value << std::endl; }
private:
    int m_value;
};

class Mixin2
{
public:
    Mixin2(int i) : m_value{ i } {}
    virtual void mixin2Func() { std::cout << "Mixin2: " << m_value << std::endl; }
private:
    int m_value;
};

//MyClass에 대한 가변 개수의 믹스인 클래스를 정의 -------------------------
//  전달된 모든 믹스인 클래스를 상속하고, 
//  생성자에서도 같은 수의 인수를 받아서 각자 상속한 믹스인 클래스를 초기화합니다.

template<typename... Mixins>
class MyClass : public Mixins...
{
public:
    MyClass(const Mixins&... mixins) : Mixins{ mixins }... {}
    virtual ~MyClass() = default;
};

int main()
{
    MyClass<Mixin1, Mixin2> a{ Mixin1(11), Mixin2(22) };
    a.mixin1Func();
    a.mixin2Func();

    MyClass<Mixin1> b{ Mixin1{33} };
    b.mixin1Func();
    // b.mixin2.Func(); // Error

    MyClass<> c;
    //a.mixin1Func(); // Error
    //a.mixin2Func(); // Error
}