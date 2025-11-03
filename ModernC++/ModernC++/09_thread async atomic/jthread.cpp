//jthread  //C++20
//		a single thread of execution
//		파괴 시 자동으로 join 하고, 특정 상황에서 취소/중지(cancelled/stopped)할 수 있다

//		스마트 포인터와 동작이 유사
//		일반적인 std::thread 로 흐름을 만들고 join을 하지 않고 main()이 종료되면 terminate가 call
//      jthread 객체의 경우는
//		main()이 종료되면 
//      jthread 객체의 destructor가 실행되면서 이 destructor가 join을 실행하기 때문에,
//      먼저 실행되고 있던 흐름이 없어지고 난 뒤 main()함수의 thread 객체가 없어지므로 더 안전하다.
// 
//		또한 stop token을 지원하여 
//		thread로 만든 흐름이 끝나지 않아 main()함수가 무한정 기다리는 것을 막아준다.
 
// threadJoinable.cpp


#include <iostream>
#include <thread>

int main() {

    std::cout << std::endl;
    std::cout << std::boolalpha;

    std::thread thr{ [] { std::cout << "Joinable std::thread" << std::endl; } };

    std::cout << "thr.joinable(): " << thr.joinable() << std::endl;

    std::cout << std::endl;

}


https://en.cppreference.com/w/cpp/thread/jthread

//std::stop_token
//  관련된 중지 요청이 있었는지 또는 할 수 있는지 확인하는 수단을 제공
//  일반적으로 독립적으로 구성되지 않고 std::jthread 또는 std::stop_source 에서 사용됩니다. 
//  이렇게 하면 std::jthread 또는 std::stop_source 와 동일한 관련 중지 상태를 공유하게 됩니다.

//std::stop_source
//  provides the means to issue a stop request, such as for std::jthread cancellation.

#include <thread>
#include <iostream>

using namespace std::literals::chrono_literals;

void f(std::stop_token stop_token, int value)
{
    while (!stop_token.stop_requested())  //중지 상태가 중지 요청되었는지 여부를 확인
    {
        std::cout << value++ << ' ' << std::flush;
        std::this_thread::sleep_for(200ms);
    }
    std::cout << std::endl;
}

int main()
{
    std::jthread thread(f, 5); // prints 5 6 7 8... for approximately 3 seconds
    std::this_thread::sleep_for(3s);
    // The destructor of jthread calls request_stop() and join().
}