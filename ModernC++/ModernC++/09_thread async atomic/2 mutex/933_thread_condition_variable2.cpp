// 생산자(Producer) 와 소비자(Consumer) 패턴
// 
//      생산자의 경우, 무언가 처리할 일을 받아오는 쓰레드를 의미합니다.
//      소비자의 경우, 받은 일을 처리하는 쓰레드를 의미합니다.
// 
//      예를 들어서, 인터넷에서 페이지를 긁어서 분석하는 프로그램을 만든다면
//      이 경우 페이지를 긁어 오는 쓰레드가 바로 생산자가 되겠지요.

//consumer가 계속 할 일이 있는지 확인하는 것 보다는
//   
//      producer 에서 데이터가 뜸하게 오는 것을 안다면 그냥 consumer 는 아예 재워놓고, 
//      producer 에서 데이터가 온다면 consumer 를 깨우는 방식이 낫지 않을까?
//
// 조건 변수(condition_variable) 를 통해 해결 ***
 
//예시)
// 생산자(Producer) 와 소비자(Consumer) 패턴
// 조건 변수(condition_variable) 를 통해 해결 ***

#include <chrono>              // std::chrono::miliseconds
#include <condition_variable>  // std::condition_variable
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

void producer(
    std::queue<std::string>* downloaded_pages,
    std::mutex* m, std::condition_variable* cv, int index)
{
    for (int i = 0; i < 5; i++) {
        // 웹사이트를 다운로드 하는데 걸리는 시간이라 생각하면 된다. // 각 쓰레드 별로 다운로드 시간이 다르다.
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
        std::string content = "웹사이트 : " + std::to_string(i) + " from thread(" + std::to_string(index) + ")\n";

        m->lock();
        downloaded_pages->push(content); // 공유되므로 critical section 에 넣어야 한다.
        m->unlock();

        cv->notify_one();                           //notify    // consumer 에게 content 가 준비되었음을 알린다. ***
    }
}

void consumer(
    std::queue<std::string>* downloaded_pages,
    std::mutex* m, std::condition_variable* cv, int* num_processed)
{
    while (*num_processed < 25)
    {
        std::unique_lock<std::mutex> lk(*m);
        cv->wait(                                   //wait  // notify를 기다린다. ***
            lk, [&] { return !downloaded_pages->empty() || *num_processed == 25; });

        if (*num_processed == 25) {
            lk.unlock();
            return;
        }

        // 맨 앞의 페이지를 읽고 대기 목록에서 제거한다.
        std::string content = downloaded_pages->front();
        downloaded_pages->pop();
        (*num_processed)++;
        lk.unlock();

        // content 를 처리한다.
        std::cout << content;
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }
}

int main()
{
    // 현재 다운로드한 페이지들 리스트로, 아직 처리되지 않은 것들이다.
    std::queue<std::string> downloaded_pages;
    std::mutex m;
    std::condition_variable cv;

    std::vector<std::thread> producers;
    for (int i = 0; i < 5; i++) {
        producers.push_back(
            std::thread(producer, &downloaded_pages, &m, &cv, i + 1));
    }

    int num_processed = 0;
    std::vector<std::thread> consumers;
    for (int i = 0; i < 3; i++) {
        consumers.push_back(
            std::thread(consumer, &downloaded_pages, &m, &cv, &num_processed));
    }

    for (int i = 0; i < 5; i++) {
        producers[i].join();
    }

    // 나머지 자고 있는 쓰레드들을 모두 깨운다.
    cv.notify_all();

    for (int i = 0; i < 3; i++) {
        consumers[i].join();
    }
}
//연습)
// 하나의 컨테이너에, 
// 
// 1부터 10 의 데이타를 전달하면,                    - 생산자 쓰레드 n 개// 
// 컨테이너에서 
// 총 10개를 모두 읽어 출력하는 출력하는              - 소비자 쓰레드 m 개
// 
// 프로그램을 쓰레드로 구성하세요. 

// 뮤텍스와 조건변수를 통해 생산자와 소비자 동기화.
// 총 10개 데이터가 모두 소비되면 프로그램 종료.