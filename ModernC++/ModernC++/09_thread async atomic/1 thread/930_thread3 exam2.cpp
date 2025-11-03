// 쓰레드 실행 제어

//std::this_thread::sleep_for( ) 
//      최소 sleep_duration 만큼의 시간 동안 현재 쓰레드의 실행을 멈춥니다.
//      주로 지연 실행, 타이밍 조절, 테스트 목적으로 많이 사용

#include <iostream>
#include <chrono>
#include <string>
#include <thread>

void PrintCurrentTime() {
    // 현재 시간 출력
}

void PrintMessage(const std::string& message)
{
    std::cout << "Sleep now ... ";
    PrintCurrentTime();

    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << message << " ";
    PrintCurrentTime();
}
int main()
{
    std::thread thread(PrintMessage, "Message from a child thread.");

    PrintMessage("Message from a main thread.");

    thread.join();

    return 0;
}

//-------------------------------------
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    using namespace std::chrono_literals;

    std::cout << "Hello waiter\n" << std::flush;

    const auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(2000ms);
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "Waited " << elapsed.count() << '\n';
}

//std::this_tread::sleep_until(  )
//      지정된 시점까지 현재 thread의 실행을 중지합니다.

#include <iostream>
#include <chrono>
#include <thread>

auto now() { return std::chrono::steady_clock::now(); }

auto awake_time() {
    using std::chrono::operator""ms;
    return now() + 2000ms;
}

int main()
{
    std::cout << "Hello, waiter...\n" << std::flush;
    const auto start{ now() };
    std::this_thread::sleep_until( awake_time() );
    std::chrono::duration<double, std::milli> elapsed{ now() - start };
    std::cout << "Waited " << elapsed.count() << " ms\n";
}

//std::this_tread::yield(  )
//      yield는 계속 실행 대기 상태를 유지합니다.

#include <iostream>
#include <chrono>
#include <string>
#include <thread>

void PrintMessage(const std::string& message, std::chrono::seconds delay)
{
    auto end = std::chrono::high_resolution_clock::now() + delay;

    while (std::chrono::high_resolution_clock::now() < end)
    {
        std::this_thread::yield();
    }

    std::cout << message << std::endl;
}

int main()
{
    std::thread thread(PrintMessage, "Message from a child thread.", std::chrono::seconds(3));

    PrintMessage("Message from a main thread.", std::chrono::seconds(2));

    thread.join();

    return 0;
}