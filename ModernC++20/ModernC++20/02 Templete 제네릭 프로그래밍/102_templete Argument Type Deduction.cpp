//C++ 템플릿 타입 추론

//Template Argument Type Deduction 정리 ***

//    템플릿 인자가 값 타입 (T a)
//        함수 인자가 가진 const, volatile, reference 속성 제거 후 T 타입 결정
//        인자의 속성만 제거됨

//    템플릿 인자가 참조 타입 (T& a)
//        함수 인자가 가진 reference 속성만 제거 후 T 타입 결정
//        인자의 const, volatile 속성 유지
//        인자가(const T& a)경우 const를 제거하고 T 타입 결정

//    템플릿 인자가 forwarding 레퍼런스 타입 (T&& a)
//        lvalue면 & 로, 
//        rvalue면 && 로 모두 전달 받음

//    템플릿 인자가 배열인 경우
//        argument decay 발생

#include <iostream>
using namespace std;

// 함수 템플릿 인자 T 는 어떻게 추정되는가?
template<typename T> void foo(T a)
{
    ++a;
}

int main()
{
    int n = 0;
    int& r = n;
    const int c = n;
    const int& cr = c;

    foo(n);     // T : int
    foo(c);     // T : const int ?
    foo(r);     // T : int& ?
    foo(cr);    // T : const int& ?
}


// 함수 템플릿 인자가 값 타입(T a) 일때 --------------------------------------------

#include <iostream>
using namespace std;

template<typename T> void foo(T a) { }

int main()
{
    int n = 0;
    int& r = n;
    const int c = n;
    const int& cr = c;

    foo(n);     // T : int
    foo(c);     // T : int
    foo(r);     // T : int
    foo(cr);    // T : int

    const char* s1 = "hello";
    foo(s1);    // T : char const* // s1이 아닌 char*가 const 이므로 제거 되지 않음

    const char* const s2 = "hello";
    foo(s2);    // T : char const*  // s2가 const 이므로 인자에 대한 const만 제거됨
}


// 함수 템플릿 인자가 참조 타입(T& a) 일때 ----------------------------------------

#include <iostream>
using namespace std;

template<typename T> void foo(T& a) { ++a; }

int main()
{
    int n = 0;
    int& r = n;
    const int c = n;
    const int& cr = c;

    foo(n);  // T : int
    foo(r);  // T : int
    foo(c);  // T : const int
    foo(cr); // T : const int
}


//배열--------------------------------------------------------------------

//배열의 이름과 주소 

#include <iostream>
int main()
{
    int i = 1;
    int* px = &i;

    int x[3] = { 1, 2, 3 };
    int* p1 = x;        // 일반적으로 생각하는 배열의 주소(묵시적으로 첫번째 요소의 주소로 형변환 됨)
    int(*p2)[3] = &x;   // 정확한 배열의 주소(요소가 모두 포함된 전체 컨테이너의 주소)

    // + 1 연산을 하면 기본적으로 데이터 타입 사이즈 만큼 증가된 메모리 주소를 가르침
    printf("%p, %p\n", p1, p1 + 1); // 배열의 첫번째 요소의 주소에서 데이터 사이즈인 4바이트 증가
    printf("%p, %p\n", p2, p2 + 1); // 요소가 3개인 배열의 주소에서 데이터 사이즈인 12바이트 증가
}

//함수 템플릿을 만들때
//      배열을 값으로 받으면 T는 요소 타입의 포인터로 결정된다.
//      배열을 참조로 받으면 T는 배열 타입으로 결정된다.

#include <iostream>

template<typename T> void foo(T a) { }
template<typename T> void goo(T& a) { }

int main()
{
    int x[3] = { 1,2,3 };

    foo(x);
    goo(x);     //T를 추론하라.
}

//문자열을 
//  값으로 받으면 T는  const char* 로 결정되고, 
//  참조로 받으면     const char[] 로 결정된다.
//참조로 받으면, 크기가 다른 배열은 다른 타입이다.

#include <iostream>

template<typename T> void foo(T a, T b) { }
template<typename T> void goo(T& a, T& b) { }

int main()
{
    foo("orange", "apple"); // ok
    goo("orange", "apple"); // error 이유는?  
}
