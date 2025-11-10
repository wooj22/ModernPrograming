// future
//
//  wait() / get() 은 
//      thread에서 return 또는 set_value() 함수가 호출될 때까지 무한정 대기
// 
//  wait_for()를 사용하면 
//      일정 시간만큼 thread에서 값이 전달되기 기다리다, timout이 되면 block 상태가 해제된다. 


#include <chrono>
#include <iostream>
#include <future>
#include <thread>

int fib(int n)
{
    if (n < 3) return 1;
    else return fib(n - 1) + fib(n - 2);
}

int main()
{
    std::future<int> f1 = std::async(std::launch::async, []() {
        return fib(40);
        });
    std::future<int> f2 = std::async(std::launch::async, []() {
        return fib(43);
        });

    std::cout << "waiting... " << std::flush;
    const auto start = std::chrono::system_clock::now();            //time_point

    f1.wait();                                          //wait
    f2.wait();                                          //wait

    const auto diff = std::chrono::system_clock::now() - start;     //duration
    std::cout << std::chrono::duration<double>(diff).count() << " seconds\n";

    std::cout << "f1: " << f1.get() << '\n';            //get
    std::cout << "f2: " << f2.get() << '\n';            //get
}


//wait_for ------------------------------------------------------

#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int main()
{
    std::future<int> future = std::async(std::launch::async, []() {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 8;
    });

    std::cout << "waiting...\n";

    std::future_status status;
    do {
        status = future.wait_for(std::chrono::seconds(1));      // wait_for ***

        if (status == std::future_status::deferred) {
            std::cout << "deferred\n";
        }
        else if (status == std::future_status::timeout) {       //future_status::timeout
            std::cout << "timeout\n";
        }
        else if (status == std::future_status::ready) {
            std::cout << "ready!\n";
        }
    } while (status != std::future_status::ready);

    std::cout << "result is " << future.get() << '\n';
}
