// 생산자(Producer) 와 소비자(Consumer) 패턴

// 하나의 컨테이너에, 
// 1부터 10 의 데이타를 전달하면, 
// 총 10개를 전달받아 출력하는 
// 프로그램을 쓰레드로 구성하세요. 


#include <chrono>              // std::chrono::miliseconds
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <future>
#include <mutex>

void producer(std::queue<std::string>* downlist, std::mutex* m, int* index)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    m->lock();
    ++*index; std::string content = "" + std::to_string(*index) + "\n";
    downlist->push(content);    // 공유되므로 critical section 에 넣어야 한다.
    m->unlock();
}

void consumer(std::queue<std::string>* downlist, std::mutex* m, int* num_processed)
{
    const int max = 10;
    while (*num_processed < max)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        m->lock();
        if (downlist->empty()) { m->unlock(); continue; }
        std::string content = downlist->front();  downlist->pop();
        (*num_processed)++;
        if (*num_processed > max) { m->unlock(); break; }
        m->unlock();
        std::cout << content;
    }
}

int main()
{
    // 현재 다운로드한 페이지들 리스트로, 아직 처리되지 않은 것들이다.
    std::queue<std::string> downlist;
    std::mutex m;
    int index = 0;
    int count = 0;

    std::vector<std::future<void>> tlist;
    for (size_t i = 0; i < 20; i++)
        tlist.push_back(std::async([&]() { producer(&downlist, &m, &index); }));

    auto c1 = std::async([&]() { consumer(&downlist, &m, &count); });
    auto c2 = std::async([&]() { consumer(&downlist, &m, &count); });
    auto c3 = std::async([&]() { consumer(&downlist, &m, &count); });
    auto c4 = std::async([&]() { consumer(&downlist, &m, &count); });

    for (size_t i = 0; i < tlist.size(); i++)  {  tlist[i].wait(); }

    c1.wait();
    c2.wait();
    c3.wait();
    c4.wait();
}

