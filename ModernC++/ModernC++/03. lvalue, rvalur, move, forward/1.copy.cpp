//Copy , Move

#include <iostream>
#include <vector>
using namespace std;

/*

//복사 생성자와 복사 대입 연산자
    T(const T& p);

//복사 생성자가 사용되는 경우

    1. 객체의 선언 및 초기화 : Foo a(b);
    2. 객체의 값에 의한 전달 : void foo(Foo a) { … }
    3. 객체의 값에 의한 반환 : Foo foo() { return Foo(); }

*/

class Foo {
public:
    Foo()               { cout << "생성자" << endl; }
    Foo(const Foo& rhs) { cout << "복사 생성자" << endl; }
    Foo& operator=(const Foo& rhs) {
        if (this != &rhs) { cout << "복사 대입연산자" << endl; }
        return *this;
    }
};

void func_Value(Foo a) {};
void func_Reference(Foo& a) {};
void func_Pointer(Foo* a) {};

int main()
{
    //객체
    cout << "객체" << endl;
    Foo a1;                     // 생성자만 호출
    Foo a2;                     // 생성자만 호출
    Foo a3 = a1;                // 복사생성자 호출됨 (초기화되는 시점)
    a2 = a1;                    // 복사 대입 연산자 호출

    //함수 호출
    cout << endl;
    func_Value(a1);             //복사 생성자 호출됨
    func_Reference(a1);         //복사 생성자 호출 안됨
    func_Pointer(&a1);          //복사 생성자 호출 안됨

    return 0;
}