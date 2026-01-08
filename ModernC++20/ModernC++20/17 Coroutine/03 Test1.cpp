//% 실제 실행 코드가 아닌 코루틴 코드의 처리 방식에 대한 설명입니다.

//코루틴 함수를 컴파일하면 코드가 변경된다. ***
//      co_await, co_yield, co_return 의 변경 살펴보기.

#include <iostream>
#include <coroutine>

class Task
{
public:
    // 규칙 1. C++에서 정의된 규칙을 구현한 promise_type 이라는 이름의 타입이 정의되어야 한다.
    struct promise_type
    {
        // 사용자 정의 "코루틴 반환 객체"를 반환 한다
        Task get_return_object()
        {
            return Task{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        // 코루틴 최초 실행 시 호출. awaitable 객체를 반환 한다.
        auto initial_suspend() { 
            return std::suspend_always{}; 
            //return std::suspend_never{};
        }   

        // co_return을 사용하는 경우 구현. 
        void return_void() {}

        // 코루틴 종료 시 호출. 
        auto final_suspend() noexcept { return std::suspend_always{}; }

        // 코루틴 수행 중 예외 발생 시 호출
        void unhandled_exception() { std::exit(1); }
    };

    // 규칙 2. std::coroutine_handle<promise_type> 타입의 멤버 변수가 있어야 한다.
    std::coroutine_handle<promise_type> co_handler;

    // 규칙 3. std::coroutine_handle<promise_type> 을 인자로 받아
    // 멤버 변수를 초기화 하는 생성자가 있어야 한다.
    Task(std::coroutine_handle<promise_type> handler) : co_handler(handler) { }

    // 규칙 4. 소멸자에서 std::coroutine_handle<promise_type> 타입의
    // 코루틴 핸들러 멤버 변수의 destroy를 호출 해야 한다.
    ~Task() {
        if (true == (bool)co_handler) {
            co_handler.destroy();
        }
    }
};

// 코루틴 함수 만들기
//     규칙 1. co_await, co_yield, co_return 중 하나 이상을 사용한다
//     규칙 2. 코루틴 반환 객체(Task)를 리턴한다

Task foo()
{
    std::cout << "foo 1" << std::endl;
    co_await std::suspend_always{};         //코루틴 중단
    std::cout << "foo 2" << std::endl;
}

// 코루틴 사용하기
int main()
{
    Task task = foo();                      //"코루틴 반환 객체(Task)" 를 받아서
    std::cout << "main 1" << std::endl;
    task.co_handler.resume();               //코루틴 재개한다.
    std::cout << "main 2" << std::endl;
    task.co_handler.resume();
}



//co_await -----------------------------------------------------------------------------------

//  컴파일러가 컴파일 중 co_await 문을 만나게 되면 
//  foo() 함수 안에 아래와 비슷한 코드를 생성합니다.

 Task foo()
 {
    // 3. promise 객체의 생성자를 호출
    Task::promise_type promise;

    // 4. promise.get_return_object()로 부터 "코루틴 반환 객체(Task)" 생성
    Task task = promise.get_return_object();

    // 5. promise.initial_suspend()를 호출하고, 그 결과를 co_await 에게 전달
    co_await promise.initial_suspend();
    try
    {
        // 코루틴 함수의 본문
        //        std::cout << "foo 1" << std::endl;
        //        co_await std::suspend_always{};
        //        std::cout << "foo 2" << std::endl;
    }
    catch (...)
    {
        promise.unhandled_exception();
    }
    promise.return_void();
    co_await promise.final_suspend();
}
 /*

 co_await std::suspend_always{};   //코루틴 중단  

    //다음에는 awaitable 객체가 옵니다. 

 co_yield 10;                     //코루틴 중단(값 반환) 
 
    //는 다음과 같이 컴파일 됩니다.
    co_await promise.yield_value(10);

 co_return;                       //코루틴 종료
 
    //는 다음과 같이 컴파일 됩니다.
    promise.return_void();           
    co_await promise.final_suspend(); 

 co_return 10;                    //코루틴 종료(값 반환) 
 
    //는 다음과 같이 컴파일 됩니다.
    promise.return_value(10);        
    co_await promise.final_suspend(); 

 */


//co_yield -----------------------------------------------------------------------------------
//          호출자에게 값을 전달한다.

Generator foo()
{
    //co_await std::suspend_always{};   //코루틴 중단 (awaitble 객체)
    co_yield 10;                        //코루틴 중단 (값 반환)
}

//컴파일러는 'co_yield' 구문을 만나면 내부적으로 다음과 같은 코드를 생성합니다.

Generator foo()
{
    Generator::promise_type promise;
    // ...코드 생략...
    // co_yield 10;
    co_await promise.yield_value(10);
}

//co_yield 를 사용하여 호출자에게 값을 전달하기 위해서는 
//      promise_type에 전달 할 값을 저장할 멤버 변수와 
//      yield_value()함수를 정의 해주셔야 합니다.       ***

class Task
{
    struct promise_type
    {
        // 다른 코드들 생략
        int value;

        std::suspend_always yield_value(int value)  //
        {
            this->value = value;
            return {};
        }
    };
};

Generator foo()
{
    // co_yield 10;
    co_await promise.yield_value(10);
}

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



//co_return -----------------------------------------------------------------------------------

//코루틴을 종료하기 위해선 co_return 을 호출한다. 

Task foo() {
    co_return;                       //코루틴 종료
}

//컴파일러는 co_return 키워드를 만나면 아래와 비슷한 코드를 생성한다.

Task foo()
{
    promise.return_void();            //
    co_await promise.final_suspend(); //
}

//만일 아래와 같이 값을 리턴하는 코루틴이라면  ---------------                    

Task<int> foo() {
    ​​​​co_return 7;                    //코루틴 종료( 값 반환)
}

//promise의 return_vaule() 함수를 대신 호출 한다.

Task<int> foo()
{
    ​​​promise.return_value(7);          //
    ​​​co_await promise.final_suspend(); //
}

//참고로 한 promise 타입에 이 두 함수는 동시에 구현 될수 없다. 
//      값을 리턴하던지, 그렇지 않던지 둘중에 하나만 택해야 한다.

//결론은 co_return을 사용하기 위해서는 리턴 값을 유무에 따라 ***
//      promise_type에 
//      void return_void() 또는 
//      void return_value(Type value) 를 추가해 주어야 한다.
