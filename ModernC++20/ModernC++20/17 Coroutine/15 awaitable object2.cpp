// 코루틴을 스레드로 작동시키기.

#include <iostream>
#include <coroutine>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

class Task {
public:
    struct promise_type {
        Task get_return_object() { return Task{ handle_type::from_promise(*this) }; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };

    using handle_type = std::coroutine_handle<promise_type>;

    explicit Task(handle_type handle) : handle_(handle) {}
    Task(Task&& t) noexcept : handle_(t.handle_) { t.handle_ = nullptr; }
    Task& operator=(Task&& other) noexcept {
        if (handle_) handle_.destroy();
        handle_ = other.handle_;
        other.handle_ = nullptr;
        return *this;
    }
    ~Task() { if (handle_) handle_.destroy(); }

    void resume() { handle_.resume(); }
    bool done() const { return handle_.done(); }

private:
    handle_type handle_;
};

Task count(int from, int to) {
    for (int i = from; i <= to; ++i) {
        std::cout << i << '\n';
        co_await std::suspend_always();
    }
}

//-----------------------------------------------------------
struct await_second
{
    int sec = 1;
    await_second(int s) : sec(s) {}
    bool await_ready() noexcept { return false; }
    void await_suspend(std::coroutine_handle<> h) noexcept
    {
        //std::cout << "await_suspend" << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(sec));
        if (!h.done()) h.resume();
    }
    void await_resume() noexcept {
        //std::cout << "await_resume" << '\n';
    }
};

Task coFunc() {

    std::cout << "coFunc 1" << '\n';
    co_await await_second(2);

    std::cout << "coFunc 2" << '\n';
    co_await await_second(3);

    std::cout << "coFunc 3" << '\n';
}

int main() {

    //Task t = count(1, 5);
    //while (!t.done()) {        t.resume();    }


    // 코루틴을 스레드로 작동시키기.
    // 
    std::cout << "main s" << '\n';
    std::jthread jt([]() { coFunc(); });

    std::cout << "main 1" << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "main end" << '\n';
    return 0;
}
