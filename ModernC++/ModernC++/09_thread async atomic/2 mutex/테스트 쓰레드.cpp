// 하나의 컨테이너에, 
// 1부터 10 의 데이타를 전달하면,                     - 생산자 쓰레드 n 개
// 컨테이너에서 
// 총 10개를 모두 읽어 출력하는 출력하는              - 소비자 쓰레드 m 개
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
    std::queue<int>* numbers, std::mutex* m, std::condition_variable* cv, int data)
{
    std::this_thread::sleep_for(std::chrono::seconds(data)); //임의의 시간

    m->lock();
    numbers->push(data);
    m->unlock();

    cv->notify_all();
}

void consumer(
    std::queue<int>* numbers, std::mutex* m, std::condition_variable* cv, int* num_count)
{
    while (*num_count < 10)
    {
        std::unique_lock<std::mutex> lk(*m);
        cv->wait(lk, [&] { return !numbers->empty() || *num_count == 10; });

        if (*num_count == 10) {
            lk.unlock();
            return;
        }

        // 맨 앞의 페이지를 읽고 대기 목록에서 제거한다.
        int content = numbers->front();
        numbers->pop();
        (*num_count)++;
        lk.unlock();

        // content 를 처리한다.
        std::cout << content;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main()
{
    // 현재 다운로드한 페이지들 리스트로, 아직 처리되지 않은 것들이다.
    std::queue<int> numbers;
    std::mutex m;
    std::condition_variable cv;

    std::vector<std::thread> producers;
    for (int i = 0; i < 10; i++) {
        producers.push_back(std::thread(producer, &numbers, &m, &cv, i + 1));
    }

    int num_count = 0;
    std::vector<std::thread> consumers;
    for (int i = 0; i < 3; i++) {
        consumers.push_back(std::thread(consumer, &numbers, &m, &cv, &num_count));
    }

    for (auto& p : producers) p.join();

    cv.notify_all(); // 나머지 자고 있는 쓰레드들을 모두 깨운다.
    for (auto& c : consumers) c.join();

}