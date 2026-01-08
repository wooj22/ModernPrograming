//co_yield - 값을 반환하며 중단

#include <iostream>
#include <coroutine>
#include <concepts>
#include <exception>
using namespace std;

class Task
{
public:
    struct promise_type
    {
        int value;  // 코루틴에서 호출자에게 리턴 할 값

        Task get_return_object() { return Task{ std::coroutine_handle<promise_type>::from_promise(*this) }; }
        auto initial_suspend() { return std::suspend_always{}; }

        // 코루틴에서 co_yield를 호출하기 위해 필요한 함수
        std::suspend_always yield_value(int v)
        {
            this->value = v;
            return {};
        }

        void return_void() { return; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void unhandled_exception() { std::exit(1); }
    };

    std::coroutine_handle<promise_type> co_handler;
    Task(std::coroutine_handle<promise_type> handler) : co_handler(handler)
    {
    }
    ~Task() { if (co_handler) { co_handler.destroy(); } }
};

Task foo()
{
    int value = 10;
    std::cout << "foo 1" << " " << value << std::endl;

    co_yield value;

    value += 10;
    std::cout << "foo 2" << " " << value << std::endl;
}

int main()
{
    Task task = foo();
    task.co_handler.resume(); // start coroutine	
    std::cout << "main 1" << " " << task.co_handler.promise().value << std::endl;
    task.co_handler.resume();
    std::cout << "main 2" << " " << task.co_handler.promise().value << std::endl;
}


/*
//템플릿을 적용하여
//      코루틴의 리턴 타입이 달라진다고 해도
//      매번 새로운 타입의 promise_type을 정의하는 것이 아니라
//      기존 클래스에 템플릿 인자만 다르게 사용하는 방식도 적용 가능
*/

/*

//co_yield - 값을 반환하며 중단

#include <iostream>
#include <coroutine>
#include <concepts>
#include <exception>
using namespace std;

template <class T>
class Coroutine
{
private:
    struct promise_base
    {
        Coroutine get_return_object() { return Coroutine{}; }
        auto initial_suspend() { return std::suspend_always{}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { throw std::exception("unhandled exception"); }
        void return_void() { return; }
    };

    template <class R>
    struct promise_type_impl : public promise_base
    {
        Coroutine get_return_object() { return Coroutine{ std::coroutine_handle<promise_type>::from_promise(*this) }; }

        R value;
        std::suspend_always yield_value(const R& value) {
            this->value = value;
            return {};
        }
    };
    template <>
    struct promise_type_impl<void> : public promise_base {    };

public:
    typedef promise_type_impl<typename T> promise_type;

    std::coroutine_handle<promise_type> co_handler;
    Coroutine(std::coroutine_handle<promise_type> handler) : co_handler(handler)
    {
    }
    ~Coroutine() { if (co_handler) { co_handler.destroy(); } }
};

Coroutine<int> foo()
{
    int value = 10;
    std::cout << "foo 1" << " " << value << std::endl;

    co_yield value;

    value += 10;
    std::cout << "foo 2" << " " << value << std::endl;
}

int main()
{
    Coroutine task = foo();
    task.co_handler.resume(); // start coroutine
    std::cout << "main 1" << " " << task.co_handler.promise().value << std::endl;
    task.co_handler.resume();
    std::cout << "main 2" << " " << task.co_handler.promise().value << std::endl;
}

*/
