//co_done ----------------------------------------------------------------
//      코루틴이 완료되었는지 체크하기

//coroutine_handle의 done 함수는 
//      코루틴의 수행이 
//      완료 되면 (promise_type의 final_suspend 에서 suspend 된 상태) true를 리턴하고,
//      그렇지 않은 경우 false를 리턴.
// 
//      우리는 resume() 이후 제어권이 호출자에게 넘어 올때 마다 
//      done() 을 체크하여 
//      코루틴이 완료되었는지 그렇지 않은지 알아 낼 수 있다.

#include <iostream>
#include <coroutine>

template <class T>
class Range
{
public:
    struct promise_type
    {
        T value;
        Range get_return_object()
        {
            return Range{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        auto initial_suspend() { return std::suspend_always{}; }
        void return_void() { return; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void unhandled_exception() { std::exit(1); }

        std::suspend_always yield_value(const T& t)
        {
            value = t;
            return {};
        }
    };
    std::coroutine_handle<promise_type> cohandle;
    Range(std::coroutine_handle<promise_type> coroutine) : cohandle(coroutine) { }
    ~Range() { if (cohandle) cohandle.destroy(); }
};

Range<int> CreateRange(int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        co_yield i;
    }
}

int main()
{
    Range<int> range = CreateRange(10, 20);

    while (true)
    {
        range.cohandle.resume();                //resume

        if (true == range.cohandle.done())      //done
        {
            break;
        }
        std::cout << range.cohandle.promise().value << std::endl;
    }
}



//매번 루프 안에서 done()을 체크하는 것이 아닌 
//ranged for를 이용해 코드를 좀 더 간단히 쓸수 있도록 Range 클래스에 iterator를 추가 하기.

#include <iostream>
#include <coroutine>

template <class T>
class Range
{
public:
    struct promise_type
    {
        T value;
        Range get_return_object() {
            return Range{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }
        auto initial_suspend() { return std::suspend_always{}; }
        void return_void() { return; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void unhandled_exception() { std::exit(1); }

        std::suspend_always yield_value(const T& t)
        {
            value = t;
            return {};
        }
    };

    struct iterator
    {
    public:
        explicit iterator(std::coroutine_handle<promise_type> coroutine)
            : coroutine(coroutine)
        {
        }

        const T& operator* () const {
            return coroutine.promise().value;
        }

        iterator& operator++() {
            coroutine.resume();            return *this;
        };

        bool operator == (std::default_sentinel_t) const {
            return !coroutine || coroutine.done();
        }
    private:
        std::coroutine_handle<promise_type> coroutine;
    };

    Range(std::coroutine_handle<promise_type> coroutine) : coroutine(coroutine) {
    }
    ~Range() {
        if (coroutine) { coroutine.destroy(); }
    }

    iterator begin() {
        if (coroutine) { coroutine.resume(); }
        return iterator{ coroutine };
    }

    std::default_sentinel_t end() {
        return {};
    }

    std::coroutine_handle<promise_type> coroutine;
};

Range<int> CreateRange(int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        co_yield i;
    }
}

int main()
{
    Range<int> range = CreateRange(10, 20);

    /*
    while(true)
    {
        range.coroutine.resume();

        if (true == range.coroutine.done())
        {
            break;
        }
        std::cout << range.coroutine.promise().value << std::endl;
    }
    */

    for (auto value : range)
    {
        std::cout << value << std::endl;
    }
}