//std::thread, std::async
/*
std::thread
	어떤 스레드가 끝나기를 기다리려면, join 함수를 통해 대기해야 한다.

std::async
	알아서 future 객체를 리턴하므로 스레드처럼 promise를 사용할 필요가 없다.
	소멸자가 끝나는 것을 알아서 대기를 해준다.
	따로 명시하지 않아도 자동으로 future 객체를 사용하기 전까지는 대기한다.
*/

#include <iostream>
#include <thread>
#include <future>		// async, future, promise 를 사용 할 수 있다.

using namespace std;

int main()
{
	// thread 방식에서는 thread를 생성해서 '어떤 thread가 작업을 할지' 컨트롤 하는 것이 중점
	// 그러나 task-based는 '어떤 task를 할 것인가' 를 위주로 프로그래밍 한다.

	// multi-threading, thread 위주의 프로그래밍 ------------------------------------------------
	{
		int result;		
		std::thread t( [&] { result = 1 + 2; } );
		
		t.join();
		cout << result << endl;

		//result 입장에서 스레드를 통해 어떤 일을 겪을지 알 수 없다.
	}

	// task-based parallelism, 작업 기반 프로그래밍 ---------------------------------------------
	{
		// std::future<int> fut = ...
		auto fut = std::async( [] { return 1 + 2; } );

		// return 값은 현재 받을 수 있는 값이 아닐 수도 있다. 
		// 즉 바로 return을 받는 것이 보장이 안 되어 있다.
		// 커서를 대보면 future. 즉 async에서 실행된 작업과 결합이 되는 방식이다. ***

		// 값은 get()으로 확인이 가능하다. 
		// 따라서 fut.get()은 async가 작업(task)을 마칠 때까지 기다린다.

		cout << fut.get() << endl;

		//작업 기반 std::async, std::future
		//	std::async의 결과가 futrue에 리턴될 때까지 future.get() 작업은 실행하지 않고 기다린다.
		//	future변수는 정확하게 async를 통해 자신이 어떤 일을 겪게 될지를 정확하게 알 수 있다.
	}

	// future and promise -------------------------------------------------------------
	{
		// future를 async에서만 사용하는 것이 아니라 thread에서도 사용할 수 있다.
		// 이 경우에는 promise를 미리 선언해야 한다.
		// 최근 멀티쓰레딩 프로그래밍에는 future와 promise를 적절히 사용하는 추세.

		std::promise<int> promi;
		auto fut = promi.get_future();		// future<int>

		// future를 받을 수 있는 존재가 필요하기 때문에 promise를 이용한다.
		// promise에 값을 넣어준다면 future가 발동한다.
		 
		auto t = std::thread( 
						[](std::promise<int>&& prom) { prom.set_value(1 + 2); }, 
						std::move(promi) );

		cout << fut.get() << endl;	// future는 promise가 값을 받을 때까지 대기

		t.join();					// thread 이기 때문에 join()은 사용.


		// auto t = std::async( )   // 이것도 가능
		// 그러면 t가 thread가 아니고 future가 된다. 문제에 따라 다르게 사용할 수 있다. 
		// 
		// 결국 task <-> thread 어떤 based이냐의 차이가 된다.
		// thread 자체를 제어해야 하는 경우  vs  task 기반으로 멀티쓰레딩 자동 제어하기

	}	

	return 0;
}
