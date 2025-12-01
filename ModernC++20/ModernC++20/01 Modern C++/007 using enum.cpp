// using-enum-declaration   //C++20
// 
//  기존 C++98에서 enum의 문제점이라고 한다면 
//  enum은 별도의 이름공간(namespace)를 가지고 있지 않는 것
//  enum 들을 정확하게 구분하기 위해서 enum class 가 도입됨. 
// 
//	using namespace 를 사용하면 
//  네임스페이스 안에 있는 클래스, 함수 등을 네임스페이스 이름을 생략하고 사용할 수 있듯이,
// 
//	using enum 을 사용하면 
//  열거형(enum class / struct) 내에 있는 멤버들을 
//	열거형 이름을 생략하고, class에 있던 열거형(enum)처럼 사용할 수 있게 됩니다. ***

//https://en.cppreference.com/w/cpp/language/enum

#include<iostream>
using namespace std;

enum class fruit { orange, apple }; 

struct S {
    using enum fruit;             // OK, introduces orange and apple into S
};

void func() {
    S s;
    s.orange;                     // OK, names fruit​::​orange
    S::orange;                    // OK, names fruit​::​orange
}

int main()
{
    S s;
    fruit f = s.apple;

    func();
}