// 생산자(Producer) 와 소비자(Consumer) 패턴
// std::async

// 하나의 컨테이너에, 
// 1부터 10 의 데이타를 전달하면, 
// 총 10개를 전달받아 출력하는 
// 프로그램을 쓰레드로 구성하세요. 


#include <iostream>
#include <future>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <chrono>

std::queue<int> sQueue;
std::mutex mutex;
std::condition_variable cv;
bool finished = false;

// Producer: 1~10 넣기
void Produce()
{
    for (int i = 1; i <= 10; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        {
            std::lock_guard<std::mutex> lock(mutex);
            sQueue.push(i);
            std::cout << "Push: " << i << std::endl;
        }

        cv.notify_one();
    }

    {
        std::lock_guard<std::mutex> lock(mutex);
        finished = true;
    }
    cv.notify_one();
}

// Consumer: Queue에서 꺼내서 출력
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

            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        else if (finished)
        {
            break;
        }
    }

    std::cout << "소비 완료" << std::endl;
}

int main()
{
    auto producerFuture = std::async(std::launch::async, Produce);
    auto consumerFuture = std::async(std::launch::async, Consume);

    producerFuture.get();
    consumerFuture.get();

    return 0;
}
