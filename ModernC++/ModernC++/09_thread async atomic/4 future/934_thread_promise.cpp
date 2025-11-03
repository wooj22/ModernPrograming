// 동기(synchronous) 와 비동기(asynchronous) 실행
//
//  프로그램의 실행이, 한 번에 하나씩 순차적으로 실행되는 작업을 '동기적(synchronous)'으로 실행된다고 하고,
//  한 갈래가 아니라 여러 갈래로 갈라져서 동시에 진행되는 것을 '비동기적(asynchronous)' 실행

//  C++ 11 표준 라이브러리를 통해 매우 간단히 비동기적 실행을 할 수 있게 해주는 도구를 제공

// std::promise 와 std::future
//
//   결국 비동기적 실행으로 하고 싶은 일을, 어떠한 데이터를 다른 쓰레드를 통해 처리해서 받아내는 것.
//   내가 어떤 쓰레드<T> 를 사용해서, 비동기적으로 값을 받아내겠다 라는 의미는, 
//   미래에(future) 쓰레드가 원하는 데이터 T를 돌려 주겠다 라는 약속(promise)라고 볼 수 있다.

#include <future>
#include <iostream>
#include <string>
#include <thread>
using std::string;

void worker(std::promise<string>* p)
{
    p->set_value("some data");				// 5.약속을 이행하는 모습. 해당 결과는 future 에 들어간다.
}

int main() {

    std::promise<string> p;					// 1.promise 선언
    std::future<string> f = p.get_future(); // 2.future에 할당, 미래에 string 데이터를 돌려 주겠다는 약속.

    std::thread t(worker, &p);				// 3.promise 전달	

    f.wait();								// 4.미래에 약속된 데이터를 받을 때 까지 기다린다.		

    // wait 중에 리턴했다는 뜻이, future 에 데이터가 준비되었다는 의미.
    // 참고로 wait 없이 그냥 get 해도 wait 한 것과 같다. ***

    std::cout << "받은 데이터 : " << f.get() << std::endl;	//6. 결과 획득

    t.join();

}

//----------------------------------------------------------------------------
#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

void accumulate(std::vector<int>::iterator first,
    std::vector<int>::iterator last,
    std::promise<int> accumulate_promise)
{
    int sum = std::accumulate(first, last, 0);

    accumulate_promise.set_value(sum);      // Notify future
}

int main()
{
    // promise<int>를 사용하여 스레드 간에 결과를 전송하는 방법
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };

    std::promise<int> accumulate_promise;
    std::future<int> accumulate_future = accumulate_promise.get_future();

    std::thread work_thread(accumulate, 
        numbers.begin(), numbers.end(), std::move(accumulate_promise));                  //move
    
    // Calling wait() before get() is not needed     
    //accumulate_future.wait();  // wait for result
    std::cout << "result=" << accumulate_future.get() << '\n';

    work_thread.join();  // wait for thread completion
}


// 스레드 간에 상태를 알리기 위해 promise<void> 를 사용하는 방법

void do_work(std::promise<void> barrier)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));

    barrier.set_value();
}

int main()
{
    std::promise<void> barrier;
    std::future<void> barrier_future = barrier.get_future();

    std::thread new_work_thread(do_work, std::move(barrier));

    barrier_future.wait();

    new_work_thread.join();
}
