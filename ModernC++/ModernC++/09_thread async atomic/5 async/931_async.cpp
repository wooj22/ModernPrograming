//C++ 11 표준 라이브러리를 통해 매우 간단히 비동기적 실행을 할 수 있게 해주는 도구를 제공
//async
//   std::async 에 어떤 함수를 전달한다면, 
//   아예 쓰레드를 알아서 만들어서 해당 함수를 비동기적으로 실행하고, 
//   그 결과값을 future 에 전달

#include <cstdio>
#include <future>

using namespace std;

int fun() {
	for (int i = 1; i <= 10; i++) { printf("fun[%d]\n", i); }
	return 200;
}

int main()
{
	auto fut = async( fun );
	//auto fut = async(launch::async, fun);				// 1 바로 쓰레드를 생성 함수를 실행  //default
	//auto fut = async(launch::deferred, fun);			// 2 future 의 get 함수가 호출되었을 때 실행

	for (int i = 1; i <= 10; i++) { printf("main[%d]\n", i); }


	int result = fut.get();								// get
	printf("result : %d\n", result);

	printf("end\n");

	return 0;
}

//std::launch::async	: 바로 쓰레드를 생성해서 인자로 전달된 함수를 실행한다.
//std::launch::deferred : future 의 get 함수가 호출되었을 때 실행한다. (새로운 쓰레드를 생성하지 않음)


//비동기적 실행 ---------------------------------------------------------------------
//
// std::thread 만 사용하는 '스레드 기반' 비동기적 실행
// 
//		스레드를 통해 어떤 일을 겪게 될지 알 수 없다.
//		병렬 처리로 어떤 값을 받게될지 알 수 없다.
//
// std::async 를 사용하는 '작업 기반' 비동기적 실행
// 
//		어떤 일을 할 것인가, 미래에 어떤 값을 받아낼 것인가에 더 관심이 있다.
//		병렬 처리간에 값을 주고 받기가 쉽다. 
//		스레드의 결과를 리턴으로 받는다.


//Thread의 결과값 획득하는 방법
//
//  std::future와 std::promise를 이용하면 다른 Thread의 결과값을 쉽게 획득할 수 있습니다.
//  Thread에서 연산을 완료한 후 그 결과값은 promise에 저장합니다.
//  이후, future를 이용해서 그 값을 획득할 수 있습니다.
//
//async 함수
// 
//  async 함수를 사용하면 특정 함수 등을 Thread로 구동시키고 그 결과를 리턴받을 수 있습니다.
//  std::async 는 반환 값을 std::future 로 받습니다.
//  task 기반 비동기 프로그래밍

//std::async는 다음과 같은 장점을 가집니다.
// 
//  1. 내부에서 Thread Pool을 만들어 사용한다. (해당 Thread Pool은 운영체제, 라이브러리마다 생성 방식이 다르다.)
//  2. std::async는 예외처리가 가능하다. 따라서 프로그램이 중간에 멈추는 현상을 방지할 수 있다.
//  3. std::async는 return 값을 갖는다. 따라서 Thread를 만들 때 해당 함수에 대한 반환값을 얻을 수 있다.


//일반적으로 Thread 를 사용하게 된다면 std::async 를 권장합니다. ***
//  Thread를 프로그래머에 맞게 관리를 하고 싶다면, std::thread를 사용하면 되고,
//  직접 Thread Pool를 만들어서 관리하면 됩니다.


//블로킹(Blocking)과 논블로킹(Non-Blocking)
//
//	블로킹(Blocking)
//		어떤 작업이 끝날 때까지 다음 코드가 기다리는 방식
//		현재 스레드가 잠시 멈춤(대기 상태)
//
//	논블로킹(Non - Blocking)
//		요청을 보내도 즉시 반환 → 나중에 결과를 받을 수 있음
//		대기 중에도 다른 작업을 계속 수행 가능 (스레드가 계속 움직임)
//		주로 이벤트 기반, 콜백, Future / Promise, async / await 구조로 구현
//
//	멀티스레딩, 비동기 통신, 게임 로딩, 네트워크 처리 등에서
//	논블로킹은 프레임 저하를 막고, 응답성을 높이는 핵심 기술이다.

/*
Blocking Model
┌─────────────────────────────┐
│ Main Thread → [대기중 ...]   │
└─────────────────────────────┘
       ↓
 결과 반환 후 다음 수행

Non - Blocking Model
┌─────────────────────────────┐
│ Main Thread → 계속 실행      │
├─────────────────────────────┤
│ Worker Thread → 작업 수행    │
└─────────────────────────────┘
       ↓
 완료 이벤트 / 콜백 수신

*/

