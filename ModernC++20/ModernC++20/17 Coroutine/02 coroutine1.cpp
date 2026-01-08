//https://en.cppreference.com/w/cpp/language/coroutines
/*
코루틴 함수

1.코루틴 성립 조건

    C++에서 함수가 코루틴으로 취급되기 위해서는
    다음 키워드 중 하나 이상을 반드시 사용해야 합니다.

        co_await
        co_yield
        co_return

2. 코루틴 키워드의 역할

    co_await
        awaitable 객체에 의해 코루틴을 중단(suspend)하고 재개(resume) 시점을 외부에 위임합니다.

    co_yield
        호출자에게 값을 전달하면서 코루틴을 중단합니다.
        주로 generator 패턴에서 사용됩니다.

    co_return
        코루틴의 실행을 완전히 종료합니다.
        최종 결과를 반환하거나 반환 없이 종료할 수 있습니다.

3. 코루틴 반환 객체 정의

    코루틴 함수는 반드시 코루틴 규약을 만족하는 '반환 타입'을 반환해야 합니다.
    이 반환 타입은 내부에 promise_type을 정의하며, 코루틴의 수명과 실행 흐름을 관리합니다.

4. 제약 사항
    다음과 같은 경우에는 코루틴을 사용할 수 없습니다.

    일반 return 문만 사용하는 함수
    auto, concept 등 placeholder 반환 타입
    constexpr 함수
    생성자 / 소멸자
    main 함수
    C 스타일 가변 인자 (...)를 사용하는 함수

==> C++ 코루틴은 “함수를 중단하는 기능”이 아니라, 실행 흐름을 사용자가 설계할 수 있게 해주는 언어 도구입니다.


//C++ 코루틴은 크게 아래 세가지로 이루어져 있습니다.-------------------------------

promise_type. 
    "코루틴 내부"에서 관리 되는 객체. 
    코루틴의 결과나 예외를 이 객체를 통해 호출자에게 전달 하는 용도로 사용합니다.
coroutine handle. 
    "코루틴 외부"에서 관리 되는 객체. 
    코루틴을 resume하거나 코루틴 프레임을 제거 할 때 사용 됩니다.
coroutine state. 
    "힙 메모리 영역"에 할당 되는 코루틴 상태를 나타내는 객체.
	coroutine state는 promise 객체를 가진다.
	coroutine state는 코루틴 함수 파라미터의 복사된 값들을 가진다.
	coroutine state는 resume을 위한 현재 중단 포인트와 
    destroy를 위한 지역 변수들을 가진다.
	지역 변수와 임시 변수들은 현재 중단 포인트에서 살아 있는 것들을 의미한다


//코루틴 실행 시 일어나는 일 .------------------.-------------------------------

코루틴의 구성을 대략적이나마 파악했으니, 
이젠 코루틴이 어떻게 동작하는지 살펴 보도록 하겠습니다.

1. 코루틴이 최초 실행 되면, 
    new를 이용해 힙 메모리 영역에 coroutine state 를 생성합니다.

2. 코루틴 함수의 모든 인자들을 coroutine state 에 복사합니다. 
    이때 모든 인자들은 move 되거나 복사 됩니다. 
    단, 레퍼런스들은 그대로 레퍼런스로 남아 있습니다.
	NOTE - 만일 코루틴이 재개(resume) 될 때, 레퍼런스 변수들의 생명 주기가 이미 종료 되었다면 
    뎅글링 레퍼런스를 참조할 수 있으므로, 코루틴 함수의 인자로 레퍼런스 타입을 사용 할 때는 주의가 필요 합니다.

3. promise 객체의 생성자를 호출 합니다.
	NOTE -  만일 promise 타입의 생성자가 모든 코루틴 함수의 인자를 가지고 있다면 해당 생성자가 호출 됩니다. 
    그렇지 않다면 기본 생성자가 호출 됩니다.

4. promise.get_return_object() 함수를 호출 합니다. 
    get_return_object() 함수는 "코루틴 반환 객체"를 생성하여 리턴하며, 
    이 값은 로컬 변수에 저장되었다가 
    최초 코루틴 중단(suspend) 시 코루틴 호출자에게 리턴 됩니다.

5. promise.initial_suspend() 를 호출하고 그 결과를 
   co_await 오퍼레이터에게 전달 합니다. 

    일반적으로 initial_suspend() 함수는 
    게으른 시작(lazily-start)을 위해 suspend_always를 리턴하거나, 
    즉시 시작(eagerly-start)을 위해 suspend_never를 리턴합니다.

6. co_await promise.initial_suspend() 이후 코루틴이 다시 재게(resume) 되면 
    코루틴은 그제서야 본문(사용자가 정의한 코루틴 함수의 내용들)을 실행 합니다.

코루틴이 중단(suspend) 포인트에 닿으면 일어나는 일
	위 promise.get_return_object()에 의해 생성된 코루틴 반환 객체가 
    호출자(caller)에게 리턴 됩니다.


//코루틴 반환 객체는 promise_type을 정의하고 있어야 합니다.

	코루틴 반환 객체는 C++에서 정의한 규칙을 구현한 
    promise_type 이라는 이름의 타입이 정의되어야 한다 (필수). ***

	std::coroutine_handle<promise_type> 타입의 멤버 변수가 있어야 한다(선택).
	std::coroutine_handle<promise_type> 을 인자로 받아 멤버 변수를 초기화 하는 생성자가 있어야 한다(선택).
	소멸자에서 std::coroutine_handle<promise_type> 타입의 코루틴 핸들러 멤버 변수를 해제해야 한다(선택).

//promise_type은 아래 함수들을 구현해야 합니다 (중요합니다!!).

	get_return_object()   : 코루틴 중단을 위한 사용자 정의 "코루틴 반환 객체"를 반환 한다.
	initial_suspend()     : 코루틴 최초 실행 시 호출. awaitable 객체를 반환 한다.
    final_suspend()       : 코루틴 종료 시 호출. (나중에 코루틴 종료를 설명 할 때 같이 설명)
    unhandled_exception() : 코루틴 수행 중 예외 발생 시 호출

	yield_value()       : co_yield 를 사용하는 경우 구현.
	return_void()       : co_return 을 사용하는 경우 구현.(결과 없는 경우)
    return_value()      : co_return 이 결과를 리턴하는 경우 (return_void() 대신 사용)

*/

// 코루틴 반환 객체

#include <iostream>
#include <coroutine> // 코루틴을 사용하기 위한 헤더
using namespace std;

class CoTask
{
public:
    // 규칙 1. C++에서 정의된 규칙을 구현한 promise_type 이라는 이름의 타입이 정의되어야 한다.
    struct promise_type
    {
        // 사용자 정의 "코루틴 반환 객체"를 반환 한다
        CoTask get_return_object() {
            return CoTask{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }
        auto initial_suspend() { return std::suspend_always{}; }
        void return_void() {}
        auto final_suspend() noexcept { return std::suspend_always{}; }
        auto unhandled_exception() { return exit(1); }

        int value = 0;
        auto yield_value(int n) { value = n; return std::suspend_always{}; }
    };

    // 규칙 2. std::coroutine_handle<promise_type> 타입의 멤버 변수가 있어야 한다.
    std::coroutine_handle<promise_type> co_handler;

    // 규칙 3. std::coroutine_handle<promise_type> 을 인자로 받아
    // 멤버 변수를 초기화 하는 생성자가 있어야 한다.
    CoTask(std::coroutine_handle<promise_type> handler) : co_handler(handler) { }

    // 규칙 4. 소멸자에서 std::coroutine_handle<promise_type> 타입의
    // 코루틴 핸들러 멤버 변수의 destroy를 호출 해야 한다.
    ~CoTask()
    {
        if (true == (bool)co_handler) { co_handler.destroy(); }
    };
};

// 코루틴 함수
//     규칙 1. co_await를 사용한다
//     규칙 2. 코루틴 반환 타입(CoTask)를 리턴한다

CoTask CoFunc()
{
    std::cout << "CoFunc 1" << std::endl;
    co_await std::suspend_always{};
    std::cout << "CoFunc 2" << std::endl;
}

//promise_type
//coroutine_handle
//      코루틴의 재개, 완료여부를 체크한다.

int main()
{
    // 코루틴 CoFunc()를 실행하면 본문 실행 전에 중단하고 호출자(main)에게 제어권 넘김
    // 최초 중단시 코루틴 반환 객체(CoTask)를 호출자에게 돌려 준다
    CoTask task = CoFunc();

    std::cout << "main 1" << std::endl;

    // 코루틴 반환 객체의 멤버 coroutine_handle.resume()을 이용해 코루틴 재개
    task.co_handler.resume();   //"CoFunc 1"

    std::cout << "main 2" << std::endl;

    task.co_handler.resume();   //"CoFunc 2"
}

//연습)  코루틴객체와 코루틴 함수를 만들어 보세요.
// 
//       호출시 처음에는 100 출력 후 중단
//       재호출시 200 출력 후 중단
//       재호출시 300 출력 후 종료

    #include <coroutine>
    #include <iostream>

    //코루틴 반환 타입
    struct MyCoroutine {
        struct promise_type {
            MyCoroutine get_return_object() {
                return MyCoroutine{
                    std::coroutine_handle<promise_type>::from_promise(*this)
                };
            }

            std::suspend_always initial_suspend() { return {}; }
            std::suspend_always final_suspend() noexcept { return {}; }

            void return_void() {}
            void unhandled_exception() { std::terminate(); }
        };

        std::coroutine_handle<promise_type> handle;

        void resume() {
            if (!handle.done())
                handle.resume();
        }

        ~MyCoroutine() {
            if (handle)
                handle.destroy();
        }
    };

    //코루틴 함수
    MyCoroutine coroutine_func() {
        std::cout << "100\n";
        co_await std::suspend_always{};

        std::cout << "200\n";
        co_await std::suspend_always{};

        std::cout << "300\n";
        co_return;
    }

    //코루틴 호출
    int main() {
        MyCoroutine c = coroutine_func();

        c.resume(); // 100
        c.resume(); // 200
        c.resume(); // 300
    }

    //코루틴은 “함수를 여러 번 호출하는 것처럼 보이지만, 실제로는 하나의 실행 흐름을 중단·재개하는 구조”이다.