// 생산자(Producer) 와 소비자(Consumer) 패턴
// 조건 변수(condition_variable) 를 통해 해결 ***

// 하나의 컨테이너에, 
// 1부터 10 의 데이타를 전달하면, 
// 총 10개를 전달받아 출력하는 
// 프로그램을 쓰레드로 구성하세요. 

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <queue>
#include <chrono>

std::queue<int> sQueue;
std::mutex mutex;
std::condition_variable cv;
std::atomic<bool> finished = false;

// 생산
void Produce()
{
    for (int i = 1; i <= 10; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::unique_lock<std::mutex> lock(mutex);
        sQueue.push(i);
        lock.unlock();
        std::cout << "Push: " << i << std::endl;

        cv.notify_one();
    }

    // 생산 완료
    finished = true;
    cv.notify_one();
}

// 소비
void Consume()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [] { return !sQueue.empty() || finished; });

        while (!sQueue.empty())
        {
            int value = sQueue.front();
            sQueue.pop();
            std::cout << "Pop: " << value << std::endl;
            lock.unlock();

            std::this_thread::sleep_for(std::chrono::seconds(1)); // 소비 지연

            lock.lock();
        }

        if (finished && sQueue.empty())
            break; // 종료 조건
    }

    std::cout << "소비 완료" << std::endl;
}

int main()
{
    std::thread producer(Produce);
    std::thread consumer(Consume);

    producer.join();
    consumer.join();

    return 0;
}
