// Awaitable 객체 예시
// 
// co_await 연산자는 3개의 함수를 요구한다. ***
//      await_ready
//      await_suspend
//      await_resume

#include <iostream>
#include <coroutine>
#include <thread>
#include <chrono>

// Awaitable 객체
struct suspend_after_2_seconds {
    bool await_ready() noexcept {
        // 즉시 대기하지 않고 항상 대기하도록 설정
        return false;
    }

    void await_suspend(std::coroutine_handle<> h) noexcept {
        // 코루틴을 일시 중지하고, 2초 후에 다시 실행하도록 예약
        std::cout << "2초 후에 코루틴을 다시 실행합니다...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));  // 2초 대기
        h.resume();  // 2초 후 코루틴 재개
    }

    void await_resume() noexcept {
        // 코루틴이 다시 실행될 때 호출됩니다.
        std::cout << "코루틴이 다시 실행되었습니다!\n";
    }
};

// 코루틴의 반환 객체를 위한 PromiseType
struct my_coroutine {
    struct promise_type {
        auto get_return_object() {
            return my_coroutine{};  // 코루틴 객체를 반환
        }

        std::suspend_never initial_suspend() {   // 코루틴이 처음 시작할 때 일시 중지하도록 설정 - suspend_after_2_seconds
            std::cout << "코루틴 시작\n";
            return {};  // 대기 객체 반환
        }

        std::suspend_never final_suspend() noexcept {  // 코루틴이 종료될 때 일시 중지하도록 설정 - suspend_after_2_seconds
            std::cout << "코루틴 종료\n";
            return {};  // 대기 객체 반환
        }

        void return_void() {}
        void unhandled_exception() {}
    };

    void operator()() {
        // 코루틴이 실행 중일 때 호출
        std::cout << "코루틴 실행 중...\n";
    }
};

my_coroutine coFunc()
{
    std::cout << "Coroutine started" << '\n';

    //co_await std::suspend_never();
    co_await suspend_after_2_seconds();  //일시 중지하도록 설정
    // awaiter destroyed here

    std::cout << "Coroutine end" << '\n';

}
int main() {
    my_coroutine co = coFunc();
    co();  // 코루틴 시작
    std::cout << "메인 함수 종료\n";
    return 0;
}