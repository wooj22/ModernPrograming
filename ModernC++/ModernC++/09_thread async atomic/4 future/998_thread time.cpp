//std::this_thread::sleep_for()
// 
//      최소 sleep_duration 만큼의 시간 동안 현재 쓰레드의 실행을 멈춥니다.

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

    std::this_thread::sleep_for(std::chrono::seconds(3));   //

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


//std::this_tread::yield();
// 
//      sleep과 비슷하나, sleep이 쓰레드를 일시 정지 상태로 바꾸는 반면, 
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
        std::this_thread::yield();                  //
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

// sleep() : 지정된 시간 동안 실행을 중지하여 CPU 자원을 절약.
//           목적: 주로 특정 작업이 완료되기를 기다리거나 일정 시간 간격을 두고 작업을 수행할 때 사용
// 
// yield() : 바로 실행을 중지하지 않고, 다른 쓰레드가 있을 경우 CPU 사용을 양보.
//           목적: 현재 작업의 우선순위가 낮아, 다른 쓰레드가 실행되기를 원할 때 사용합니다.


//C# 쓰레드 
//
//주어진 시간동안 일시 정지 - sleep() 
//  Thread.sleep() 메소드를 호출한 스레드는 주어진 시간 동안 일시 정지 상태가 되고, 
//  다시 실행 대기 상태로 돌아갑니다.
// 
//다른 스레드에게 실행 양보 - yield()
//  실행 대기 상태로 돌아가고 
//  동일한 우선순위 또는 높은 우선순위를 갖는 다른 스레드가 실행 기회를 가질 수 있도록 해줍니다.
//
//Thread.Sleep(0) 은 남아 있는 현재의 쓰레드의 타임 슬라이스를 모두 포기하여, 
//자발적으로 다른 쓰레드에게 CPU 타임을 양보합니다. 
//NET4.0에서는 새롭게 Thread.Yield() 메서드가 추가되어 같은 기능을 실행합니다. 
// 
//Thread.Sleep(0)과 Thread.Yield()의 유일한 차이는 
//Thread.Yield()의 경우는 같은 프로세서에서 실행되고 있는 쓰레드에 대해서만 CPU 타입을 양보한다는 것이 다릅니다.
