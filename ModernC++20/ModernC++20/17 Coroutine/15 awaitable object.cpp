// Awaitable Type의 역할
//      co_await 에서 사용하는 인터페이스
// 
//      co_await는 awaitable 객체의 세 메서드를 통해
//      "지금 쓸 수 있는가, 기다릴 것인가, 무엇을 돌려줄 것인가"를 결정한다.
 

// co_await 연산자는 3개의 함수를 요구한다. ***
// 
//      await_ready
//      await_suspend
//      await_resume
//
//  which are used by operator co_await.

//co_await을 사용하여…
//  컴파일러는 해당 라인에 중단점 (Suspend Point)을 생성한다
//  프로그래머는 조건에 맞게 코루틴의 제어 흐름을 제어할 수 있다
/*

EX) co_await awaitable; 

1. 먼저 await_ready 호출 ( bool 리턴 )

    false 면  await_suspend  - 중단 - co_awaiting will create a coroutine handle(resume point)
    true  면  await_resume   - 중단없이 진행

    //co_await: 컴파일러가 보는 코드

        if (aw.await_ready() == false) {
            auto rh = coroutine_handle<promise_type>::from_promise(*p);
            aw.await_suspend(rh);
            // ... return ...
        }
        __suspend_point_n:
        aw.await_resume();

2. await_suspend 는 bool 혹은 void or coroutine handle 리턴

    true 또는 void를 반환하는 경우
        코루틴 핸들이 저장되고, co_await는 중단(suspend) 상태로 돌아감.
    false를 반환하는 경우
        co_await는 즉시 재개(resume) 되며 바로 await_resume 메서드가 호출되어 결과 또는 예외가 처리됨

3. await_resume 은 아래 3가지 경우에 호출됨

    await_ready returns true
    await_suspend returns false
    Call coroutine handler method resume ***

    await_resume 메서드는 rvalue를 반환하며,
    결과가 필요 없는 경우에는 void 반환 타입으로 정의할 수도 있다.

*/


#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <thread>

//auto switch_to_new_thread(std::jthread& out)
//{
//    struct awaitable
//    {
//        std::jthread* p_out;
//        bool await_ready() { return false; }
//        void await_suspend(std::coroutine_handle<> h)
//        {
//            std::jthread& out = *p_out;
//            if (out.joinable())
//                throw std::runtime_error("Output jthread parameter not empty");
//            out = std::jthread([h] { h.resume(); });
//            // Potential undefined behavior: accessing potentially destroyed *this
//            // std::cout << "New thread ID: " << p_out->get_id() << '\n';
//            std::cout << "New thread ID: " << out.get_id() << '\n'; // this is OK
//        }
//        void await_resume() {}
//    };
//    return awaitable{ &out };
//}

struct awaitable
{
    bool await_ready() { return false; }
    void await_suspend(std::coroutine_handle<> h) {
        h.resume();
    };
    void await_resume() {}
};

struct coType
{
    struct promise_type
    {
        coType get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

coType coFunc()
{
    std::cout << "Coroutine started" << '\n';

    //co_await std::suspend_never();
    co_await awaitable();
    // awaiter destroyed here

    std::cout << "Coroutine end" << '\n';
}

int main()
{
    coFunc();
}