
//명시적 인스턴스화를 통해 
//코드에서 실제로 사용하지 않고, 템플릿 기반 클래스 또는 함수의 인스턴스를 만들 수 있다.
//하지만 컴파일 중복 우려
// 
//키워드를 extern 사용하여 멤버의 자동 인스턴스화를 방지할 수 있습니다.

//extern template
//      키워드를 extern 사용하여 멤버의 자동 인스턴스화를 방지할 수 있습니다.
//      같은 템플릿 객체가 2번 이상 인스턴스화 되어 컴파일 시간 및 오브젝트 크기가 증가하는 것을 막아준다. 



//명시적 인스턴스화 방지 (explicit instantiation declaration)

//math.hpp

    #pragma once

    template <typename T>
    T add(T a, T b);
    // 명시적 인스턴스화 선언 → 여기선 인스턴스화 하지 마!
    extern template int add<int>(int, int);

//math.cpp (구현 파일)

    #include "math.hpp"

    template <typename T>
    T add(T a, T b) {
        return a + b;
    }
    // 명시적 인스턴스화 정의 → 여기서만 add<int>를 생성함
    template int add<int>(int, int);

//main.cpp

    #include <iostream>
    #include "math.hpp"

    int main() {
        std::cout << add(3, 4) << '\n'; // OK: add<int>는 math.cpp에서 생성됨
    }



//----------------------------------------------------------------------
// header.h
 
template<typename T>
void ReallyBigFunction()
{
    // 뭔가 엄청 길고 큰 작업이 작성돼 있음
}
 
// source1.cpp
 
#include "header.h"

void something1()
{
    ReallyBigFunction<int>();	//여러 파일에서 사용
}
 
// source2.cpp
 
#include "header.h"

void something2()
{
    ReallyBigFunction<int>();	//여러 파일에서 사용
}

//----------------------------------------------------------------------

// source2.cpp		
 
#include "header.h"
extern template void ReallyBigFunction<int>();    //source2.cpp 를 이렇게 변경 그럼 한번만 컴파일 합니다. (전역적)

void something2()
{
    ReallyBigFunction<int>();        
}

/*
source1.o
    void something1()
    void ReallyBigFunction<int>() // 한번만 컴파일 됩니다.
 
source2.o
    void something2()
    //  ReallyBigFunction<int> 는 여기 없습니다. 왜냐면 extern으로 선언.
*/


/*
% 키워드는 extern 전역 변수, 함수 또는 템플릿 선언에 적용할 수 있습니다.
% 템플릿 선언 extern 에서는 템플릿이 이미 다른 곳에서 인스턴스화되었음을 지정합니다.

    template class MyStack<int, 6>;                     // 모든 멤버를 int 명시적으로 인스턴스화
    template MyStack<int, 6>::MyStack(void);            // 생성자 멤버 함수만 명시적으로 인스턴스화

    extern template class MyStack<int, 6>;              // 자동 인스턴스화를 방지
    extern template MyStack<int, 6>::MyStack( void );   // 특정 멤버를 외부 및 인스턴스화되지 않음으로 표시


% 자료형이 다를땐 엄연히 다른 코드입니다. float를 사용하기 위해 int를 extern 하면 안됩니다.

    template class CMyClass<int>;               
    template class CMyClass<float>;

*/