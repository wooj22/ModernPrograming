//std::invoke   //C++17
// 
//      callable한 객체를 인자들을 넘겨받아 '실행'해주는 역할.
//      std::invoke를 사용하면 호출할 객체의 종류에 관계없이 '일관된 방식'으로 호출할 수 있습니다.
// 
//      <functional> 헤더에 정의되어 있습니다
//      ex) std::thread 에서 스레드 함수를 받을 때 사용되는 함수

#include <functional>   //
#include <iostream>

int do_something(const int i)
{
    return 5 + i;
}

struct S
{
    const int j = 5;

    int do_something(const int i) { return j + 1; }
};

int main()
{
    //함수
    std::cout << std::invoke(&do_something, 5) << '\n';         //

    //맴버함수
    S s;
    std::cout << s.do_something(3) << '\n';

    std::cout << std::invoke(&S::do_something, s, 10) << '\n';  //맴버 함수
    //멤버함수의 경우에는 함수 이름이 암시적으로 주소값 변환이 일어나지 않기에 &연산자를 붙여야 한다.

    std::cout << std::invoke(&S::j, s) << '\n';                 //멤버 변수

    /*
    //맴버함수의 포인터로 실행하기

    auto fp = &S::do_something;
    int (S:: * fp2)(int) = &S::do_something;

    std::cout << (s.*fp)(2) << '\n';
    std::cout << (s.*fp2)(1) << '\n';
    */
}

// callable한 객체는 모두 가능하기 때문에,
//      함수 뿐만이 아니라 
//      공개된 멤버 변수도 사실상 callable 이므로, std::invoke를 통해 확인할 수 있다. ***
//      공개된(public) 멤버 변수도, 
//      그 타입이 operator() 를 제공하거나 std::function 같은 callable 타입이면, 호출 가능한 존재가 된다.

// 공개된 멤버 변수 자체는 callable(호출 가능한 것)이 아니다.
//      다만, std::invoke는 '멤버 변수 포인터' 에도 동작한다는 점 때문에 오해.
//      std::invoke는 “호출(call)”만 하는 도구가 아니라, member pointer dispatch 유틸리티에 가깝습니다.

    #include <iostream>
    #include <functional>

    struct A {
        int value = 10;
        int foo(int x) { return value + x; }
    };

    int main() {
        A a;

        // 멤버 함수 포인터 호출
        std::cout << std::invoke(&A::foo, a, 5) << '\n'; // OK → 15

        // 멤버 변수 포인터 접근
        std::cout << std::invoke(&A::value, a) << '\n';  // OK → 10
    }

    //여기서& A::value는 함수가 아닌 멤버 변수 포인터인데도 std::invoke가 동작합니다.


//std::invoke를 사용하는 주요 이유는 
//      다양한 호출 가능한 객체를 동일한 방식으로 호출할 수 있도록 추상화하는 것입니다.
//      템플릿에서 호출 가능한 객체를 처리할 때 코드의 복잡성을 줄임.
//      표준 라이브러리와 잘 통합되어 일관된 인터페이스 제공.