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

        {
            std::lock_guard<std::mutex> lock(mutex);
            sQueue.push(i);
            std::cout << "Push: " << i << std::endl;
        }

        cv.notify_one();
    }

    finished = true;
    cv.notify_one();
}

// 소비
void Consume()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mutex);

        cv.wait(lock, [] {
            return !sQueue.empty() || finished;
            });

        if (!sQueue.empty())
        {
            int value = sQueue.front();
            sQueue.pop();
            std::cout << "Pop: " << value << std::endl;

            lock.unlock(); /// 잠금 해제 후 처리
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if (finished)
        {
            break; // Queue empty + finished -> 종료
        }
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
