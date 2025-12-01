//템플릿으로 만들어진 기본 클래스 안의 이름에 접근하는 방법 
//      템플릿 종속성 : 템플릿 매개변수 T에 따라 달라지는 경우.
//      기본 클래스의 이름은 "종속된 이름(dependent name)"으로 간주되며, 기본적으로 이름 검색 과정에서 무시됩니다.

//1. 기본 클래스에서 선언된 기호를 사용할 때 //this->사용

template <typename T>
class Base
{
public:
    void bar();
};

template <typename T>
class Derived : Base<T>
{
public:
    void foo()
    {
        this->bar();                //this-> 붙여 한정
    }
};

//2. 기본 클래스 안의 이름에 접근 방법  // using 선언

template <typename T>
class Derived : Base<T>
{
public:
    using Base<T>::bar;             //using
    void foo()
    {
        bar();
    }
};

//3 기본클래스 함수 명시적 사용

template <typename T>
class Derived : Base<T>
{
public:
    void foo()
    {
        Base<T>::bar();             //Base<T>::
    }
};

//C 컴파일러는 템플릿으로 만들어진 '기본 클래스'를 뒤져서 상속된 이름을 찾는 것을 거부합니다.
//      기본 클래스 템플릿은 언제라도 특수화 될 수 있고, 
//      이런 특수화 버전에서 제공하는 인터페이스가 원래의 일반형 템플릿과 같으리란 법이 없다
//해결책
//      기본 클래스 템플릿이 이후에 어떻게 특수화되더라도 
//      원래의 일반형 템플릿에서 제공하는 인터페이스를 그대로 제공할 것이라고 컴파일러에게 약속하는 것


// 템플릿 상속과 특수화 ----------------------------------------------

class A {};
class B {};

template <typename T>
class Base
{
public:
    void bar() {}
};

template<>
class Base<B>               //클래스 B에 대해 완전템플릿 특수화 입니다
{
public:
    void bar2() {}
    //bar() 함수가 없습니다
};

template <typename T>
class Derived : Base<T>
{
public:
    //using Base<T>::bar;             //using
    void foo()
    {
        bar();              //T가 A라면 이 코드를 호출가능하나요?
    }
};

int main()
{
    //Derived<A> x;  x.foo();         //this->bar(); 혹은 using Base<T>::bar;  필요

    Derived<B> x;  x.foo();         //this->bar2(); 혹은 Base<T>::bar2();
}

//기본 클래스의 멤버에 대한 참조가 무효한지를 컴파일러가 진단하는 과정이 
//      미리(파생클래스 템플릿의 정의가 구문분석 될 때) 들어가느냐? - 특수화 고려 안함
//      아니면 
//      나중에(파생 클래스 템플릿이 특정한 템플릿 매개변수를 받아 인스턴스화 될 때) 들어가느냐?
//      이번 항목의 핵심 입니다
//
//C++은 이른바 '이른 진단(early diagnose)'을 선호하는 정책으로 결정한 것입니다 ***


//C 컴파일러는 템플릿으로 만들어진 '기본 클래스'를 뒤져서 상속된 이름을 찾는 것을 거부합니다
//
//      객체지향C에서 템플릿C로 옮겨 갈때 상속 매커니즘이 끊기는 것. ***

//동적 다형성, 정적 다형성 구분