//동기(synchronous) 와 비동기(asynchronous) 실행
//   프로그램의 실행이, 한 번에 하나씩 순차적으로 실행되는 작업을 동기적(synchronous)으로 실행된다고 하고,
//   한 갈래가 아니라 여러 갈래로 갈라져서 동시에 진행되는 것을 비동기적(asynchronous) 실행

//C++ 11 표준 라이브러리를 통해 매우 간단히 비동기적 실행을 할 수 있게 해주는 도구를 제공

//async
//   std::async 에 어떤 함수를 전달한다면, 
//   아예 쓰레드를 '알아서' 만들어서 해당 함수를 비동기적으로 실행하고, 
//   그 결과값을 future 에 전달

#include <future>
#include <iostream>
#include <thread>

int do_work(int x)  // 실행할 함수
{	
	std::this_thread::sleep_for(std::chrono::seconds(3));
	return x;
}

void do_work_sequential()		//synchronous
{
	do_work(3);
	do_work(3);
	do_work(3);
}

void do_work_parallel()			//asynchronous
{
	auto f1 = std::async( []() { do_work(3); } );		//f1은 future
	auto f2 = std::async( []() { do_work(3); } );
	do_work(3);

	f1.get();
	f2.get();
}


int main() 
{
	do_work_sequential();	// 1

	//do_work_parallel();		// 2
}
