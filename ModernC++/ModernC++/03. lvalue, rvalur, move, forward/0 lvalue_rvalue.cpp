//Value Category 

//Lvalue : Lvalue 는 객체를 참조하는 표현식이다 [메모리 위치를 가지고 있다]
//Rvalue : Lvalue 가 아닌 모든 것이다.
//      정확하게 말하자면, 구분가능한 메모리 영역을 가지는 객체를 나타낼 필요가 없는 표현식이다 
//      (임시로 존재하는 것일 수 있다).

//glvalue는 평가에서 개체, 비트 필드 또는 함수의 ID를 결정하는 식입니다.
//prvalue는 계산에서 개체 또는 비트 필드를 초기화하거나 표시되는 컨텍스트에 지정된 대로 연산자의 피연산자 값을 계산하는 식입니다.
//xvalue는 리소스를 다시 사용할 수 있는 개체 또는 비트 필드를 나타내는 glvalue입니다 (일반적으로 수명이 거의 다 되었기 때문).
//  예: rvalue 참조와 관련된 특정 종류의 식은 
//  반환 형식이 rvalue 참조이거나 rvalue 참조 형식으로 캐스팅되는 함수에 대한 호출과 같은 xvalue를 생성합니다.
//lvalue는 xvalue가 아닌 glvalue입니다.
//rvalue는 prvalue 또는 xvalue입니다.

//    glvalue    rvalue
// lvalue,  xvalue,  prvalue


#include<iostream>
#include <vector>
using namespace std;

int main()
{
    int i, j, * p;

    // Correct usage: the variable i is an lvalue and the literal 7 is a prvalue.
    i = 7;

    // Incorrect usage: The left operand must be an lvalue (C2106).`j * 4` is a prvalue.
    7 = i;      // C2106
    j * 4 = 7;  // C2106

    // Correct usage: the dereferenced pointer is an lvalue.
    *p = i;                     //역참조는 lvalue 이다.

    // Correct usage: the conditional operator returns an lvalue. 
    ((i < 3) ? i : j) = 7;      //조건연산자는 lvalue 리턴

    // Incorrect usage: the constant ci is a non-modifiable lvalue (C3892).
    const int ci = 7;
    ci = 9;     // C3892        //변경할수 없는 lvalue
}

//----------------------------------------------------------------------------------

int  NextVal_1(int* p) { return *(p + 1); }
int* NextVal_2(int* p) { return (p + 1); }

int main()
{
    int a[] = { 1,2,3,4,5 };
    NextVal_1(a) = 9;   	// 에러. left operand must be l-value
    *NextVal_2(a) = 9;    	// Fine. Now a[] = {1,9,3,4,5}   //역참조된 포인터는 Lvalue
}

//----------------------------------------------------------------------------------

class A {
    static int g();		// static 인 멤버 함수
    int f();			// static 이 아닌 멤버 함수
}
int main()
{
    A a;			    // lvalue
    a.g;			    // ???	    lvalue ( static 맴버함수 )
    a.f;			    // ???	    lvalue 아님 (prvalue) (비정적맴버함수)
}

//----------------------------------------------------------------------------------
//prvalue 식  //우측값 레퍼런스와 상수 좌측값 레퍼런스를 초기화 하는데 사용
{
    int&& r = 42;
    const int& rr = 42;
    // int& rrr = 42; <-- 불가능
}

//주의
void f(int&& a) {
    a;		    //??? lvalue    //(변수) rvalue를 가리키지만, 그렇다고 해서 a가 rvalue인 것은 아니다
}

//rvalue 참조와 xvalue   ***
// 
//      rvalue 참조와 xvalue는 C++에서 서로 다른 개념을 의미합니다.
//      rvalue 참조는 타입, xvalue는 값(표현식) 카테고리입니다.
// 
//      int&& rr = 5;에서 rr은 rvalue 참조 타입이지만, 표현식에서는 lvalue입니다.
//      int&& foo(); 에서 foo() 반환값은 xvalue입니다.