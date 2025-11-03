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

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread()
{
    // main()이 데이터를 보낼 때까지 대기
    std::unique_lock lk(m);
    cv.wait(lk, [] {return ready; });

    // 대기 후 잠금을 소유합니다. 
    std::cout << "Worker thread is processing data\n";
    data += " after processing";

    // 데이터를 다시 main()으로 보냅니다. 
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";

    // 알리기 전에 수동 잠금 해제가 수행
    // to avoid waking up the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
}

int main()
{
    std::thread worker(worker_thread);

    data = "Example data";
    // 작업자 스레드에 데이터 보내기 
    {
        std::lock_guard lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();

    // wait for the worker
    {
        std::unique_lock lk(m);
        cv.wait(lk, [] {return processed; });
    }
    std::cout << "Back in main(), data = " << data << '\n';

    worker.join();
}


/*
condition_variable의 좋은 점은 
    조건을 만족하지 않을 때 무한대기하며 CPU를 낭비하지 않고, 해당 스레드를 바로 블락해버린다는 것입니다.
    스레드가 블락되면 CPU의 제어권이 다른 스레드에게 넘어가기 때문에 CPU를 효율적으로 사용할 수 있습니다. 

wait()는 condition_variable이 통지되거나 가짜 깨우기가 일어날 때까지 블락되며 
    선택적으로, 조건이 참일 때까지 반복됩니다. 
    깨어나면 lock을 획득하고 조건이 있으면 확인합니다. 

    lock을 획득할 때 데이터 레이스가 일어나긴 합니다만, 
    무조건적인 데이터 레이스가 아니라 
    notify_xxx()가 호출된 이후이기 때문에 CPU의 낭비를 최소화할 수 있습니다.

unique_lock은 lock_guard와 비슷하지만 기능이 더 많습니다. 
    lock을 획득하는 시점을 미룰 수 있고 lock을 잡기 위해 무한대기를 하지 않아도 되며 
    데드락을 피하기 위해 락을 획득하는 순서를 보장해주는 기능도 있습니다. 
    lock을 획득하는 시점을 정할 수 있고 unlock() 함수도 호출할 수 있기 때문에 

    condition_variable에서는 unique_lock을 써야 합니다. ***
    어차피 문법적으로 해당 unique_lock만 사용할 수밖에 없긴 합니다.

condition_variable 의 wait() 함수는 
    unique_lock 객체를 하나만 넣어도 되고, ( 깨우기 통지를 통해서만 락을 획득 )
    두 번째 인자에 Predicate을 넣어줄 수도 있습니다.
    ( 조건을 넣어주면 해당 조건이 참일 때 락을 획득합니다.)

*/



// wait_for 과 wait_until
//https://en.cppreference.com/w/cpp/thread/condition_variable


//notify_one 함수
//      void notify_one() noexcept;
//      condition variable에 대해서 대기하고 있는 하나의 스레드를 깨웁니다.

//notify_all 함수
//      condition variable에 대해서 대기하고 있는 모든 스레드를 깨웁니다.
 
//<예제>
    std::mutex				m_;
    std::condition_variable		cv_;
    std::queue<std::string>		con_;

    // queue에 데이터를 추가하고 대기하고 있는 스레드들에게 알림을 통지합니다. 
    void Push(const std::string& obj) {
        {
            std::unique_lock<std::mutex> sl(m_);
            con_.push(obj);
        }

        // 대기중인 하나의 스레드 알림 통지
        cv_.notify_one();
        // 대기중인 모든 스레드 알림 통지
        // cv_.notify_all();
    }


//wait 함수
//
//  condition_variable에서 통지를 받을 때까지 현재의 스레드를 중단 합니다. 
//  wait()가 수행되면 
//  내부적으로 스레드에 안전하게 락을 해제하고 
//  현재 수행 중인 스레드를 중단하고 대기 스레드 리스트에 추가합니다.

    std::mutex				    m_;
    std::condition_variable		cv_;
    std::queue<std::string>		con_;

    // queue에서 데이터를 추출하고, queue가 비어 있다면 condition_variable을 통해서 대기 합니다.                            
    bool Pop(std::string& obj) {
        std::unique_lock<std::mutex> ul(m_);
        if (con_.empty())
        {
            cv_.wait(ul, [] {return !con_.empty(); });
        }

        obj = con_.front(); con_.pop();
        return true;
    }


//wait_for 함수
// 
//  wait함수와 기본적인 동작은 동일하며 추가적으로 시간을 입력받아서 time out을 발생시킵니다.
//  std::chrono를 사용해서 기간을 입력받으며 입력 받은 기간이 지날 때까지 통지가 없다면 
//  timeout을 발생시키고 스레드의 wait를 중단합니다.
//  스레드 스케줄링에 의해서 입력한 시간보다 더 오래 대기 할 수도 있습니다.

    using namespace std::chrono_literals;

    // wait_for를 통해서 10초 이상 기다리면 timeout을 발생합니다. 
    auto status = cv_.wait_for(ul, 10s, [] {return !con_.empty(); });
    if (!status) {
        // cv_status::timeout
    }


//wait_until 함수
// 
//  wait_for 다른 점은 
//  기간이 아니고 '특정 시점의 시간'을 지정해서 특정 시점까지 통지를 받지 못하면 
//  timeout이 발생합니다.

    using namespace std::chrono_literals;
    auto now = std::chrono::system_clock::now();

    // wait_until를 통해서 지정된 시간까지 통지를 못받으면 timeout을 발생합니다. 
    auto status = cv_.wait_until(ul, now + 10s);
    if (status == std::cv_status::timeout) {
        // cv_status::timeout
        return false;
    }