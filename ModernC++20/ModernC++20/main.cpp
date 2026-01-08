#include <iostream>
#include <coroutine>
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
    CoTask(std::coroutine_handle<promise_type> handler) : co_handler(handler) {}

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