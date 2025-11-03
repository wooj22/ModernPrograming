// 뮤텍스 m 
//      - 한 번에 한 쓰레드에서만 m 의 사용 권한을 갖는다
//      - m 을 반환할 때 까지 무한정 기다리게 됩니다.
//
//      매 번 언제 올지 모르는 데이터를 확인하기 위해 
//      지속적으로 mutex 를 lock 하고, 큐를 확인 - 비효율
// 
//      더 좋은 방안은?
//      '어떠 어떠한 조건을 만족할 때 까지'라고 명령한다면 해결 가능하다..

// 조건 변수(condition_variable) 
//      스레드 간 효율적 대기 및 통신을 가능하게 하는 동기화 도구
// 
//      unique_lock 락을 건 후 ( unique_lock 은 unlock 후에 다시 lock 할 수 있습니다.)
//      wait() 함수를 호출, 이때 mutex가 해제되어 스레드는 대기 상태로 들어감.      
//      깨워주기를 기다리거나, 조건이 만족(true)할 때까지 기다림.
//      notify_one() 또는 notify_all()로 대기 중인 스레드를 깨워주면 다시 mutex를 얻고 실행을 재개
// 
// EX1)
//      std::unique_lock<std::mutex> lk(m); 
//      cv.wait( lk );                      // 깨워주기를 기다림
// 
//      뮤텍스의 잠금을 풀고 notify_one() 또는 notify_all()을 기다립니다. 
//      깨어나면, 뮤텍스를 다시 잠급니다. 
// 
// EX2)
//      std::unique_lock<std::mutex> lk(m); 
//      cv.wait( lk , 조건);              //조건이 만족(true)할 때까지 기다림.
// 
//      만일 해당 조건이 거짓이라면, lk 를 unlock 한 뒤에, 영원히 sleep. 깨워주기 전까지 계속 sleep.
//      해당 조건이 참이라면,    cv.wait 는 그대로 리턴 후 실행. 작업 후 unlock 수행하면 됨.

#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

std::mutex mutex_;
std::condition_variable condVar;

void doTheWork() {
    std::cout << "Processing shared data." << std::endl;
}

void waitingForWork() {
    std::cout << "Worker: Waiting for work." << std::endl;

    std::unique_lock<std::mutex> lck(mutex_);
    condVar.wait(lck);                                        //
    doTheWork();
    std::cout << "Work done." << std::endl;
}

void setDataReady() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Sender: Data is ready." << std::endl;
    condVar.notify_one();                                     //
}

int main() {

    std::thread t1(waitingForWork);
    std::thread t2(setDataReady);

    t1.join();
    t2.join();
    std::cout << std::endl;
}

//----------------------------------------------------------------------------------
// 조건 추가

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
bool ready1 = false;
bool ready2 = false;

int data = 0;

void worker_thread1()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2));

    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [] {return ready1; });   //wait //기다린다.
    printf("worker_thread1\n");
    data++;
    //m.unlock(); // 더 이상 락이 필요 없으면 명시적으로 언락
}

void worker_thread2() {

    std::this_thread::sleep_for(std::chrono::milliseconds(2));

    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [] {return ready2; });   //wait //기다린다.
    printf("worker_thread2\n");
    data++;
    //m.unlock();
}

int main()
{
    printf("main_start\n");
    std::thread worker1(worker_thread1);
    std::thread worker2(worker_thread2);

    printf("main_thread\n");

    std::this_thread::sleep_for(std::chrono::seconds(2));

    ready1 = true;        //프리디케이트 있으면, true가 될 때 깨어난다.     
    ready2 = true;        //프리디케이트 있으면, true가 될 때 깨어난다. 

    //cv.notify_one();      //하나 깨움.
    cv.notify_all();        //notify_all 을 하지 않는다면, 자고 있는 쓰레드들의 경우 join 되지 않는 문제가 발생

    worker1.join();
    worker2.join();
    printf("main_end\n");
}

//----------------------------------------------------------------------------------

//td::condition_variable::wait
// 
//  현재 쓰레드 뮤텍스의 잠금을 풀고 notify_one() 또는 notify_all()을 기다립니다.
//  깨어나면, 뮤텍스를 다시 잠급니다.
//  다시말해, notify_xxx가 wait()보다 먼저 호출되면, 해당 쓰레드는 풀리지 않고, 영원히 기다리게 됩니다.

//Predicate 변수를 활용해 잘못 깨어날 위험을 줄입니다.

#include <iostream>
#include <mutex>
#include <queue>

static std::mutex sQueueLock;
static std::condition_variable sEvent;
static std::queue<int> sQueue;

void Consume()
{
    while (true)
    {
        int val;
        {
            std::unique_lock<std::mutex> lock(sQueueLock);
            sEvent.wait(lock);
            //sEvent.wait(lock, [] {return !sQueue.empty(); });

            val = sQueue.front();
            sQueue.pop();
        }

        std::cout << val << std::endl;
    }
}

void Produce()
{
    std::unique_lock<std::mutex> lock(sQueueLock);
    sQueue.push(1);

    sEvent.notify_one();
}

int main()
{
    std::thread producer(Produce);
    std::thread consumer(Consume);

    consumer.join();
    producer.join();

    return 0;
}

//std::unique_lock을 쓰는 이유

// 가짜 깨우기 (spurious wakeup) ( POSIX 스레드, 윈도우 API)   
// 사라진 깨우기 (lost wakeup) 

