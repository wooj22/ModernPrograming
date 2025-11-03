// 생산자(Producer) 와 소비자(Consumer) 패턴
// 조건 변수(condition_variable) 를 통해 해결 ***


// 하나의 컨테이너에, 
// 1부터 10 의 데이타를 전달하면, 
// 총 10개를 전달받아 출력하는 
// 프로그램을 쓰레드로 구성하세요. 

#include <chrono>              // std::chrono::miliseconds
#include <condition_variable>  // std::condition_variable
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

void producer(
    std::queue<std::string>* downlist, std::mutex* m, std::condition_variable* cv, int index)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::string content = "" + std::to_string(index) + "\n";

    m->lock();
    downlist->push(content);    // 공유되므로 critical section 에 넣어야 한다.
    m->unlock();
    cv->notify_one();                   //notify    // consumer 에게 content 가 준비되었음을 알린다. ***
}

void consumer(
    std::queue<std::string>* downlist, std::mutex* m, std::condition_variable* cv, int* num_processed)
{
    while (*num_processed < 10)
    {
        std::unique_lock<std::mutex> lk(*m);
        cv->wait(                                   //wait  // notify를 기다린다. ***
            lk, [&] { return !downlist->empty() || *num_processed == 10; });

        if (*num_processed == 10) {
            lk.unlock();
            return;
        }

        // 맨 앞의 페이지를 읽고 대기 목록에서 제거한다.
        std::string content = downlist->front();  downlist->pop();
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
    std::queue<std::string> downlist;
    std::mutex m;
    std::condition_variable cv;

    std::vector<std::thread> producers;
    for (int i = 0; i < 10; i++) {
        producers.push_back( std::thread(producer, &downlist, &m, &cv, i + 1) );
    }

    int num_processed = 0;
    std::vector<std::thread> consumers;
    for (int i = 0; i < 3; i++) {
        consumers.push_back( std::thread(consumer, &downlist, &m, &cv, &num_processed ));
    }

    for (int i = 0; i < 10; i++) { producers[i].join(); }    
    cv.notify_all(); // 나머지 자고 있는 쓰레드들을 모두 깨운다.
    for (int i = 0; i < 3; i++) { consumers[i].join(); }
}

