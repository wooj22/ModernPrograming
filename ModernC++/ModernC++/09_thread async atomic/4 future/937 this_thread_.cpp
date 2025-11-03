
//std::this_thread
// 
//    현재 쓰레드에 적용되는 도우미 함수들.
//    get_id(), sleep_for(), sleep_until(), yield()

#include <iostream>
#include <chrono>
#include <string>
#include <thread>

void PrintCurrentTime() {
    // 현재 시간 출력
}

void PrintMessage(const std::string& message)
{
    std::cout << "Sleep now ... \n";
    PrintCurrentTime();

    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << message << "\n";
    PrintCurrentTime();
}
int main()
{
    std::thread thread(PrintMessage, "Message from a child thread.");

    PrintMessage("Message from a main thread.");

    thread.join();

    return 0;
}

//std::this_thread::get_id()                                    //스레드의 id

//std::thread::hardware_concurrency()                           //내 컴퓨터의 논리프로세서

//std::this_thread::sleep_for(std::chrono::milliseconds(100));  //스레드 지연