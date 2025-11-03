//공유된 자원의 충돌 
//      연산은 각각 진행, 메모리는 공유, 각각 접근하면서 문제 발생 
// 
//경쟁 상태(race condition) 
//      서로 다른 쓰레드들이 동일한 자원을 사용할 때 발생하는 문제

#include <iostream>
#include <thread>
#include <vector>
using std::thread;
using std::vector;

void worker( int& counter ) {
    for (int i = 0; i < 10000; i++) {
        counter += 1;					//counter 에 동시 접근  //경쟁 상태(race condition) 
    }
}

int main() {
    int counter = 0;

    vector<thread> workers;
    for (int i = 0; i < 4; i++) {        
        workers.push_back(thread(worker, std::ref(counter))); // 레퍼런스로 전달, ref 함수로 감싸야 한다
    }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
    }

    std::cout << "Counter 최종 값 : " << counter << std::endl; //최종값이 보장되지 않음
}



//경쟁 상태(race condition) 해결하기
//      서로 다른 쓰레드들이 동일한 자원을 사용할 때 발생하는 문제

#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>
using namespace std;

int main()
{
	int shared_memory(0);			//

	auto count_func = [&](){
		for (int i = 0; i < 1000; ++i)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(1));
			shared_memory++;		// race condition // 스레드들이 동시에 접근
		}
	};

	thread t1 = thread(count_func);
	thread t2 = thread(count_func);

	t1.join();
	t2.join();

	cout << "After" << endl;
	cout << shared_memory << endl;
}


//레이스 컨디션 해결 방법 ***

//1. 한번에 하나씩 접근하도록 제한한다.
//		이미 작업 중이거나 작업을 하다가 말았으면 다른 스레드들이 못 건드리게 잠궈둔다
//		mutex 의 lock, unlock


#include <iostream>
#include <mutex>			// mutal exclusion 의 약자. 상호 배제.
#include <atomic>
#include <thread>
using namespace std;

int main()
{
	int shared_memory(0);
	mutex mtx;					//mutex

	auto count_func = [&]()
	{
		for (int i = 0; i < 1000; ++i)
		{
			mtx.lock();			//lock
			shared_memory++;	//임계 영역(critical section) : 한 쓰레드만이 유일하게 실행할 수 있는 코드 부분
			mtx.unlock();		//unlock
		}
	};

	std::thread t1 = std::thread(count_func);
	std::thread t2 = std::thread(count_func);

	t1.join();
	t2.join();

	cout << "After" << endl;
	cout << shared_memory << '\n';
}


//2. CPU 연산 처리를 한번에 다 실행되게끔 묶어준다. 쪼개질 수 없는 원자처럼
//		메모리가 공유되는 변수를 atomic 타입으로 설정하면 된다.
//		std::atomic


#include <iostream>
#include <atomic>
#include <thread>

using namespace std;

int main()
{
	atomic<int> shared_memory(0);

	auto count_func = [&]()
	{
		for (int i = 0; i < 1000; ++i)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(1));
			shared_memory++;		// 혹은 shared_memory.fetch_add(1);
		}
	};

	std::thread t1 = std::thread(count_func);
	std::thread t2 = std::thread(count_func);

	t1.join();
	t2.join();

	cout << "After" << endl;
	cout << shared_memory << '\n';
}
