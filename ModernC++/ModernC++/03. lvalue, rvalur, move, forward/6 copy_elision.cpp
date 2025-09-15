//Copy Elision (복사 생략) - C++11
//      컴파일러가 복사 또는 이동 연산자를 회피 할 수 있으면 회피하는 것을 허용하는 방식
//
//      1) Return Value Optimization - 반환 값 최적화(Return Value Optimization, RVO)
//         Named Return Value Optimization - 네임드 반환 값 최적화(Named Return Value Optimization, NRVO)
//      
//      2) Passing Temporary as Value
// 
//      주의) 컴파일러에 따라 지원 여부 다를 수 있음 


// 1) Return Value Optimization / Named Return Value Optimization
// 
//      RVO / NRVO는 함수의 반환값이 특정 객체의 '값 형식'일 때 
//      복사 생성을 회피할 수 있도록 '컴파일러 최적화'를 의미한다.
// 
//      최적화 옵션 /O1부터 동작함, 비주얼 스튜디오의 Debug 모드는 NRVO가 동작하지 않는다 ***

#include <iostream>
#include <vector>
#include <cstring>
#pragma warning(disable:4996)

struct Foo
{
    Foo() { std::cout << "Constructed\n"; }
    Foo(const Foo&) { std::cout << "Copy-constructed\n"; }
    Foo(Foo&&) { std::cout << "Move-constructed\n"; }
    ~Foo() { std::cout << "Destructed\n"; }
};

Foo RVO_F()         // Return Value Optimization ( RVO )
{
    return Foo();   //함수 반환 시 임시 객체를 반환 값
}

Foo NRVO_F()        // Named Return Value Optimization ( NRVO )
{
    Foo foo;        //함수 내에 명명된 객체를 반환할 때 복사를 생략
    return foo;
}

int main()
{
    // 아래 대입문들에서 복사생성 생략  // release  에서 확인 ***
    {
        Foo rvo_foo = RVO_F();
    }
    // "Constructed"
    // "Destructed"

    {
        Foo nrvo_foo = NRVO_F();
    }
    // "Constructed"
    // "Destructed"
}


//2) Passing Temporary as Value
// 
//      임시 객체가 참조되는 대상 없이 함수의 인자로 넘어갈 때(즉, 값으로써 전달될 때), 
//      복사/이동 생성자가 '생략'될 수 있음.

void f(Foo f)
{
    std::cout << "Fn\n";
}

int main()
{
    f(Foo());                   //임시 객체

    // with Copy Elision
    /*
        Constructed
        Fn
        Destructed
    */

    f(std::move(Foo()));      //Value 로 전달해야 한다.

    // without Copy Elision
    /*
        Constructed
        Move-Construected
        Fn
        Destructed
        Destructed
    */
}

// % 복사 생략은 이동과 달리 컴파일러 최적화를 의미한다.

// C++17부터는 복사 생략이 강제되어, 반환 시 복사 생성자나 이동 생성자가 호출되지 않아도 된다.
// NRVO 도 가능하지만, 이 부분은 강제 사항이 아니고 여전히 컴파일러 최적화에 의존한다.
// 함수인자 전달 시에도 복사 생략이 보장되지 않고 컴파일러 및 빌드 옵션에 의존한다.