// 메인 루틴과 코루틴 사이에 1초 간격으로 값을 전달받아 출력시키는 코드.
/*
    main 1
    cofunc 1
    10
    main 2
    cofunc 2
    20
    main 3
    cofunc 3
    end
*/

#include <iostream>
#include <coroutine>
#include <Windows.h>

// Coroutine을 사용하기 위한 최소한의 구현 객체 Coroutine framework
template<typename T>
class Generator
{
public:
    struct Promise
    {
    private:
        T value;
    public:
        T Getvalue() { return value; }
        Generator get_return_object() {
            return Generator{ std::coroutine_handle<Promise>::from_promise(*this) };
        }
        auto yield_value(int n)
        {
            value = n;
            return std::suspend_always{};
        }
        auto initial_suspend() { return std::suspend_always{}; }
        void return_void() { }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        auto unhandled_exception() { return exit(1); }
    };

    using promise_type = Promise;
    std::coroutine_handle<promise_type> handle;

    Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); }
};

Generator<int> foo()
{
    std::cout << "cofunc 1" << std::endl;
    Sleep(1000);
    //co_await std::suspend_always {}; // 작업 중단 시점 명시, suspend_always -> awaitable object
    co_yield 10;

    std::cout << "cofunc 2" << std::endl;
    Sleep(1000);
    co_yield 20;

    std::cout << "cofunc 3" << std::endl;
}

int main()
{
    Generator<int> g = foo();

    std::cout << "main 1" << std::endl;
    Sleep(1000);
    g.handle.resume();

    std::cout << g.handle.promise().Getvalue() << std::endl; // 코루틴과 값 주고 받기

    std::cout << "main 2" << std::endl;
    Sleep(1000);
    g.handle.resume();

    std::cout << g.handle.promise().Getvalue() << std::endl;

    std::cout << "main 3" << std::endl;
    Sleep(1000);
    g.handle.resume();


    std::cout << "end " << std::endl;
/*
    while (true)
    {        
        g.handle.resume();//    
        if (g.handle.done()) break; // 코루틴이 작업중인지 확인 가능
    }
*/
}


/*

//Awatible object (멀티 스레딩) --------------------------------------------------------

#include <iostream>
#include <coroutine>
#include <thread>

template<typename T>
class Generator
{
public:
    struct Promise
    {
    private:
        T value;
    public:
        T Getvalue() { return value; }
        Generator get_return_object()        {
            return Generator{ std::coroutine_handle<Promise>::from_promise(*this) };
        }
        auto yield_value(int n)
        {
            value = n;
            return std::suspend_always{};
        }
        auto initial_suspend() { return std::suspend_always{}; }
        auto return_void() { }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        auto unhandled_exception() { return exit(1); }
    };
    using promise_type = Promise;

    std::coroutine_handle<promise_type> coro;

    Generator(std::coroutine_handle<promise_type> c) : coro(c) {}

    ~Generator() { if (coro) coro.destroy(); }
};

struct resume_new_thread
{
    constexpr bool await_ready() const noexcept {
        return false;
    }
    void await_suspend(std::coroutine_handle<> handle)
    {
        std::thread t( [handle]() { handle(); } );
        t.detach();
    }
    void await_resume() const noexcept {
    }
};

Generator<int> foo()
{
    std::cout << "Run 1 : " << std::this_thread::get_id() << std::endl;

    co_await resume_new_thread{}; //여기에 걸리면 새로운 thread를 만들어라

    std::cout << "Run 2 : " << std::this_thread::get_id() << std::endl;
}

int main()
{
    Generator<int> g = foo();
    g.coro.resume();    // resume시 새로운 스레드가 생겨서 Run 2 실행(멀티스레딩)

    std::cout << "main" << std::endl;

    int n; std::cin >> n;  //wait
}

*/