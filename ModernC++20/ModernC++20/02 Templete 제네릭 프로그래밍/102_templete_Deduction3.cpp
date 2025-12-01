//함수 템플릿 사용시 
//      사용자가 반드시 타입을 전달하도록 하고 싶을때 사용하는 기법
// 
//      함수 템플릿 파라미터로 클래스 템플릿을 사용해서
//      컴파일러에 의한 타입 추론이 원하지 않는 타입으로 추론되는 경우 방지하는 방법

#include <iostream>

template<typename T> struct identity
{
    typedef T type;
};

template<typename T> void foo(T a) {}
template<typename T> void goo(typename identity<T>::type a) {}

int main()
{
    identity<int>::type n; // int

    foo<int>(3);    // ok
    foo(3);         // ok

    goo<int>(3);    // ok
    goo(3);         // error, 클래스 템플릿의 인자는 추론이 불가
}
