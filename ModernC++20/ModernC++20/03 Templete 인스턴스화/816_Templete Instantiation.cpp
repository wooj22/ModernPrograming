//템플릿 인스턴스화(template instantiation)
//      컴파일러가 함수(클래스) 틀(Template)로 부터 실제 C++ 함수(클래스)를 만들어 내는 과정
// 
//      함수가 '호출'되는 코드가 있으면 
//		컴파일러는 모든 인스턴스를 T 사용자가 지정하거나 컴파일러에서 추론하는 '구체적인 형식 인수'로 바꾼다.
//      컴파일러가 템플릿에서 클래스 또는 함수를 '생성'하는 프로세스를 템플릿 인스턴스화라고 합니다.

//암시적 구체화 (인스턴스화)
//		컴파일러는 '호출부를 보고' 필요한 함수를 생성한다. ***
//		호출하지 않은 타입에 대해서는 사용할 일이 없으니 함수를 만들 필요가 없다.

//명시적 구체화 (인스턴스화)
//		'호출하지 않아도' 미리 함수를 만들어 놓아야할 필요가 있을 때.
//		호출 여부에 상관없이 지정한 타입에 대해 함수를 만들 것을 컴파일러에게 지시하는 것. ***


//명시적 구체화 선언문 -------------------------------------------------
//      명시적으로 구체화하도록 선언하는 것이 가능하다.
//      템플릿 모양을 알아야 함수를 만들 수 있으므로 
//      명시적 구체화 선언문은 템플릿 선언보다 더 뒤에 와야한다. ***

    template void swap<float>(float, float);

    template class CTest<float>;
    //클래스 템플릿도 함수 템플릿과 마찬가지
    //클래스의 경우. 인스턴스화에 필요한 것만 생성된다. ( 비정적 맴버변수, 사용하는 함수 ) ***


//----------------------------------------------------------------------------
// 암시적 인스턴스화(Implicit Instantiation) 예시

    template<typename T>
    T add(T a, T b) {
        return a + b;
    }

    int main() {
        int x = add(3, 5);        // 자동으로 add<int> 생성
        double y = add(2.5, 3.1); // 자동으로 add<double> 생성
    }

// 명시적 인스턴스화 예시
//      템플릿 정의와 사용을 다른 파일에 분리하고 싶을 때 사용
//      컴파일 시간 / 크기를 줄이기 위해 사용
//      라이브러리 헤더 숨기기 등에 사용


//예제(헤더 / 소스 분리) :

    //math.hpp
        #pragma once
        template<typename T>  T add(T a, T b);

    //math.cpp
        #include "math.hpp"
        template<typename T> T add(T a, T b) {
            return a + b;
        }
        // 명시적 인스턴스화
        template int add<int>(int, int);

    //main.cpp
        #include <iostream>
        #include "math.hpp"

        int main() {
            std::cout << add(2, 3); // OK, add<int>는 이미 인스턴스화됨
        }


// 암시적 템플릿 인스턴스화(implicit template instantiation)
// 
//      명시적 인스턴스화를 하지 않고 템플릿을 사용하는 경우, 암시적으로 인스턴스화가 발생함
//      사용 방법
//          사용자가 타입을 직접 전달하는 방법
//          함수 인자를 통해서 컴파일러가 타입을 추론하는 방법(template argument type deduction)
//          클래스 생성자를 통한 컴파일러 타입 추론하는 방법(class template type deduction, C++17이상)
// 
//      클래스 템플릿의 경우 사용하지 않는 멤버 함수는 인스턴스화 되지 않음(lazy instantiation)


// 지연 인스턴스화 (lazy instantiation)
//      클래스 템플릿의 경우, 사용하지 않으면 인스턴스화 되지 않음 ***
//
//	    컴파일러는 항상 제너릭 클래스에 있는 '모든 가상 메소드'에 대한 코드를 생성합니다.
//	    하지만 non-virtual 메소드 중에서는
//      '실제로 호출하는' non-virtual 메소드만 컴파일러가 코드를 생성합니다. ***

    Grid<int> myIntGrid;
    myIntGrid.at(0, 0) = 10;

// 선택적 인스턴스화(selective instantiation)
//
//	그러면 컴파일러는 int 버전의 Grid에서 
//  zero-argument 생성자, 소멸자, 사용 메소드만 컴파일합니다. ***
//	복사 생성자나 대입 연산자, 사용하지 않는 다른 메소드는 생성하지 않습니다. ***
//	이를 선택적 인스턴스화(selective instantiation)이라고 합니다.
//  이런 이유로, 문법 에러 체크를 하기 어렵게 됩니다.

// 명시적 템플릿 인스턴스화(explicit template instantiation)를 사용하면
// 
//  모든 virtual, non-virtual 메소드에 대한 코드를 컴파일러가 생성하도록 강제할 수 있습니다. ***
//  코드 크기 예측 가능성 증가, 링크 타임 오류 방지, 라이브러리 코드 보호
     
    template class Grid<int>;
        

//연습 명시적 인스턴스화  ----------------------------------------------------------


#include <iostream>
#include <string>
using namespace std;

template<typename T> class Test
{
public:
    void foo() {}
    void goo() {}
};

//template class Test<int>;     // 명시적 인스턴스화(클래스 템플릿), foo, goo 모두 인스턴스화

template<typename T> T square(T a)
{
    return a * a;
}

//template int square<int>(int); // 명시적 인스턴스화(함수 템플릿)

int main()
{
    int n1 = square(3);         // 암시적 인스턴스화(인자를 통한 컴파일러 타입 추론)
    int n2 = square<int>(3);    // 암시적 인스턴스화

    Test<int> t1;               // 암시적 인스턴스화(클래스)
    t1.foo();                   // Test 클래스의 foo 멤버함수만 사용하므로 foo 멤버함수만 인스턴스화됨(goo x)
}


//-----------------------------------------------------------------------
// Lazy Instantiation
//
//    사용되지 않은 템플릿 클래스는 인스턴스화 되지 않음
//    사용되지 않은 템플릿 클래스의 멤버 함수도 인스턴스화 되지 않음
//    사용되지 않은 템플릿 클래스의 static 함수도 인스턴스화 되지 않음
//    사용되지 않은 전역 템플릿 변수도 인스턴스화 되지 않음

    #include <iostream>
    using namespace std;    

    template<typename T> class A
    {
        T data;
    public:
        void foo(T n) { *n = 10; }      // 참조 오류 코드
    };

    int main()
    {
        A<int> a;       //템플릿의 멤버 함수가 호출되지 않는다면, 인스턴스화 되지 않으므로 컴파일 성공
        // a.foo(1);    
    }

    //인스턴스화 여부 확인하기  ------------------------------
    #include <iostream>
    using namespace std;

    struct Resource1
    {
        Resource1() { cout << "Resource1()" << endl; }
        ~Resource1() { cout << "~Resource1()" << endl; }
    };

    struct Resource2
    {
        Resource2() { cout << "Resource2()" << endl; }
        ~Resource2() { cout << "Resource2()" << endl; }
    };

    template<typename T> struct Test
    {
        Resource1 res1;             // 클래스내 메모리 할당이 필요하므로 인스턴스화됨
        static Resource2 res2;      // static 멤버는 별도 메모리 할당으로 인스턴스화 되지 않음
    };

    template<typename T> Resource2 Test<T>::res2; // 사용되지 않아서 인스턴스화 되지 않음

    int main()
    {
        cout << "main" << endl;     // 1. 메인 출력
        Test<int> t;                // 2. Resource1 생성자 출력

        //Test<int>::res2;          // static 멤버 사용
    }


//if 문과 Lazy Instantiation ----------------------------------------------------------------

//  if 문은 "실행시간 조건문" 으로 
//      컴파일 시간에 조건이 false로 결정되어도 if 문에 있는 코드는 항상 사용되는 것으로 간주함
//
//  if constexpr (C++17) 는 "컴파일 시간 조건문"으로 
//      조건이 false로 결정되면 if 문에 포함된 코드는 사용되지 않는 것으로 간주됨
//      동일한 이름의 함수가 여러개 있을 때 어떤 함수를 호출할 지 결정하는 것은 컴파일 시간에 결정되므로
//      선택되지 않은 함수가 템플릿이라면 인스턴스화 되지 않음

    #include <iostream>
    using namespace std;

    template<typename T> void foo(T n)
    {
        *n = 10;        // 참조 오류 코드
    }

    int main()
    {
        if (false) foo(0);              // 런타임 조건식이므로 foo는 인스턴스화 됨

        if constexpr (false) foo(0);    // C++17의 컴파일타임 조건식이므로 foo는 인스턴스화 되지 않음
    }



//템플릿 인스턴스화가 이루어지는 흐름을 보면, 해당 템플릿이 쓰이던 쓰이지 않던   
//  1. 문법 검사를 무조건 하고, 
//  2. 쓰이는 것들만(명시적이지 않아도 virtual 함수의 경우 묵시적으로 쓰인다) 인스턴스화 하고 
//  3. 쓰이지 않는 것들은 인스턴스화 자체를 하지 않는다. ***



//연습) 아래코드에 대해 컴파일 가능여부를 체크하세요.

//https://www.ikpil.com/1083?category=177580   // C++ 컴파일러마다 다를 수 있음 

#include <iostream>

template <typename T>
class Safe { };

template <int N>
class Danger {
public:
    typedef char Block[N];
};

template <typename T, int N>
class Tricky
{
public:
    virtual ~Tricky() { }                           // 1    //자동생성 함수
    void no_body_here(Safe<T> = 3);                 // 2    //인자명이 없어 문법검사 안함  
    void inclass() { Danger<N> no_boom_yet; }       // 3    //사용하지 않았음
    void error() { Danger<0> boom; }                // 4    //MSVC에선 음수일 경우에만 컴파일 시 오류
    void unsafe(T(*p)[N]) {}                        // 5    //MSVC에선 음수가 아닌 이상 정상 컴파일
    T operator->();                                 // 6
    //virtual Safe<T> suspect();                    // 7    //가상함수의 정의가 없어서 컴파일 에러
    struct Nested { Danger<N> pfew; };              // 8    //사용하지 않았음
    union { int align; Safe<T> anonymous; };        // 9
};

int main(void)
{
    Tricky<int, 0> t;                               // 10

    return 0;
}