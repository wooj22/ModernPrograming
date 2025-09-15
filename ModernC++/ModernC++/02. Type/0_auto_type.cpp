// auto의 타입 추론 규칙 ----------------------------------------------------------------
//   auto 타입 추론은 대체로 템플릿 타입 추론과 같지만, 
//   auto 타입 추론은 중괄호 초기치가 std::initializer_list를 나타낸다고 가정하는 반면 
//   템플릿 타입 추론은 그렇지 않다는 차이가 있다.

#include <iostream>
#include <vector>
using namespace std;

int main()
{

    //---------------------------------------------------------------------------------
    // auto를 이용해서 변수를 선언할 때
    //   auto는                                 템플릿의 T와 동일한 역할을 하며, 
    //   변수의 타입 지정자(type specifier)는    ParamType과 동일한 역할을 한다.

    auto x = 27;            // 여기서 x의 타입 지정자는 그냥 auto 자체이다. 반면, 다음 선언에서

    const auto cx = x;      // 타입 지정자는 const auto이다.

    const auto& rx = x;     // 타입 지정자가 const auto&이다.

/*
    // 이 예들에서 x와 cx, rx의 타입들을 추론할 때, 
    // 컴파일러는 마치 선언마다
    // 템플릿 함수 하나와 해당 초기화 표현식으로 그 템플릿 함수를 호출하는 구문이 존재하는 것처럼 행동한다. 즉:

    template <typename T>                // x의 타입을 추론하기 위한 개념적인 템플릿
    void func_for_x(T param);            // auto param = 27;

    func_for_x(27);                      // 개념적인 호출: param에 대해 추론된 타입이 바로 x의 타입이다.


    template <typename T>                // cx의 타입을 추론하기 위한 개념적인 템플릿
    void func_for_cx(const T param);     // const auto param = x;

    func_for_cx(x);                      // 개념적인 호출: param에 대해 추론된 타입이 곧 cx의 타입이다.

    
    template <typename T>                // rx의 타입을 추론하기 위한 개념적인 템플릿
    void func_for_rx(const T& param);    const auto& param = x;

    func_for_rx(x);                      // 개념적인 호출: param에 대해 추론된 타입이 바로 rx의 타입이다.
*/


    //-----------------------------------------------------------------------------
    // 경우 1: 타입 지정자가 포인터도 아니고 참조도 아닌 경우.
    // 경우 2: 타입 지정자가 포인터나 참조 타입이지만 보편 참조(universal reference)는 아닌 경우. 
    // 경우 3: 타입 지정자가 보편 참조(universal reference)인 경우.
       
    // 경우 1과 2의 예 - cvr 명시해서 사용, &의 경우는 const 유지.
    auto x = 27;                // 경우 1 (x는 포인터도 아니고 참조도 아님)
    const auto cx = x;          // 경우 1 (cx 역시 포인터도 아니고 참조도 아님)
    const auto& rx = x;         // 경우 2 (rx는 보편 참조(universal reference)가 아닌 참조)

    // 경우 3 - lvalue 는 &로 rvalue 는 &&
    auto&& uref1 = x;           // x는 int이자 좌측값이므로          // uref1의 타입은 int&
    auto&& uref2 = cx;          // cx는 const int이자 좌측값이므로   // uref2의 타입은 const int&
    auto&& uref3 = 27;          // 27은 int이자 우측값이므로         // uref3의 타입은 int&&


    // 마지막으로, 비참조 타입 지정자의 경우 // 배열과 함수 이름이 포인터로 붕괴(decay)했다.
    // auto 타입 추론에 대해서도 그러한 붕괴(decay)가 일어난다.

    const char name[] = "abc";  // name의 타입은 const char [3]     //배열
    auto arr1 = name;           // arr1의 타입은 const char*
    auto& arr2 = name;          // arr2의 타입은 const char (&)[3]

    void someFunc(int, double); // someFunc는 함수;    // 그 타입은 void(int, double)
    auto func1 = someFunc;      // func1의 타입은      // void (*)(int, double)
    auto& func2 = someFunc;     // func2의 타입은      // void (&)(int, double)


    //---------------------------------------------------------------------------------------------
    // 이상의 예들에서 보듯이, auto의 타입 추론은 템플릿 타입 추론과 똑같이 작동한다.
    // 그러나 다른 점이 하나 있다.


    // 우선, 27을 초기 값으로 해서 int 변수를 선언하는 예를 살펴보자.

    // C++98에서는 다음 두 가지 구문이 가능했다.
    int x1 = 27;
    int x2(27);
    // 균일 초기화(uniform initialization)를 지원하는 C++11에서는 
    // 위의 두 구문과 더불어 다음과 같은 구문들을 사용할 수도 있다.
    int x3 = { 27 };
    int x4{ 27 };

    // 총 네 가지 구문이 존재한다. 결과적으로 값이 27인 int가 생긴다는 점은 모두 동일하다.
    // 하지만 int 대신 auto를 사용하면 의미가 좀 달라진다.

    auto x1 = 27;
    auto x2(27);
    auto x3 = { 27 };
    auto x4{ 27 };

    // 처음 두 선언문은 실제로 타입이 int이고 값이 27인 변수를 선언한다.
    // 그러나 나머지는 값이 27인 원소 하나를 담은 std::initializer_list<int> 타입의 변수를 선언한다!

    auto x1 = 27;               // 타입은 int, 값은 27
    auto x2(27);                // 타입은 int
    auto x3 = { 27 };           // 타입은 std::initializer_list<int>, 값은 { 27 }
    auto x4{ 27 };              // 타입은 int  //C++17


    // 이는 auto에 대한 특별한 타입 추론 규칙 때문이다.  ***
    // 
    //      auto로 선언된 변수의 초기치(initializer)가
    //      중괄호 쌍으로 감싸인 형태이면, 추론된 타입은 std::initializer_list<> 이다. ***
    //
    //      만일 그런 타입을 추론할 수 없으면 
    //      (이를테면 중괄호 초기치의 값들의 타입이 서로 달라서) 컴파일이 거부된다.
        
        auto x5 = { 1, 2, 3.0 };    // 오류! std::initializer_list<T>의 T를 추론할 수 없음
        auto x6 = { 1, 2, 3 };

        // 이 예에서 사실은 두 종류의 타입 추론이 진행된다.
        // 첫 번째는 변수 선언에 auto를 사용했다는, 따라서 x5의 타입을 추론해야 한다는 사실에서 비롯된 타입 추론이다.
        // x5의 초기치가 중괄호 형태이므로 x5의 타입은 반드시 std::initializer_list로 추론된다.
        // 그런데 std::initializer_list는 템플릿이다.
        // 이 템플릿의 인스턴스는 이떤 타입 T에 대한 std::initializer_list<T>이며,
        // 선언을 완성하기 위해 컴파일러는 T의 타입도 추론해야 한다.
        // 해당 템플릿 함수에 동일한 중괄호 초기치를 전달하면 타입 추론이 실패해서 컴파일이 거부된다.


    //정리하면 ------------------------------------------------------------------------------

    // auto
        auto x = { 11, 23, 9 };         // x의 타입은 std::initializer_list<int>

    // template
        template <typename T>           // x의 선언에 해당하는 매개변수 선언을 가진 템플릿
        void f(T param);             

        f({ 11, 23, 9 });               // 오류! T에 대한 타입을 추론할 수 없음
/*
        #include <iostream>

        template <typename T>
        void fn(T param);

        int main()
        {
            auto p = { 11, 23, 9 };   //ok

            fn({ 11, 23, 9 });		  //error	

            return 0;
        }
*/

    // 하지만 param의 타입이 std::initializer_list<T>인 템플릿에 그 중괄호 초기치를 전달하면 
    // 템플릿 타입 추론 규칙들에 의해 T의 타입이 제대로 추론된다.

        template <typename T>
        void f(std::initializer_list<T> initList);

        f({ 11, 23, 9 });            // T는 int로 추론되며, initList의 타입은 // std::initializer_list<int>로 추론된다.

	return 0;
}
