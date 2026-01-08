//C++ 코루틴(Coroutines)
// 
//	함수를 중단(suspend)했다가 나중에 재개(resume) 할 수 있게 해주는 언어 차원의 제어 흐름 기능입니다.
//	스레드가 아니라 컴파일러가 상태 머신으로 변환해 주는 것이 핵심입니다.

//  C++23: 기초 준비
//  C++26 : sender / receiver 본격 표준화
//  “코루틴 위에 표준 비동기 생태계를 얹는다”
/*
	auto s = read_file("data.txt")
		| then(parse)
		| then(process)
		| on_error(handle_error);

	비동기 파이프라인
	ranges와 매우 유사한 사고 방식
	👉 “ranges + async”
*/

//Main Routine, SubRoutine, CoRoutine
//
//  프로그램이 실행될 때 불려지도록 만들어진 프로그램의 중심이 되는 코드들을 Main Routine 이라고 하며, 
//  Main Routine 이외에 다른 Routine을 모두 SubRoutine 이라고 한다.
//  그리고 진입 지점을 여러 개 가질 수 있는 SubRoutine을 CoRoutine 이라고 한다.
// 
//	SubRoutine - 진입, 종료					- 함수 
//	CoRoutine -  진입, 중단, 재개, 종료		- 코루틴 함수

//
//	호출 - initial
//	중단 - suspend ***
//	재개 - resume ***
//	종료 - return


//C++ Coroutine의 구성요소(Component)들 --------------------------------------------
//◦ Operators & Awaitable Type      - 코루틴 명령어
//◦ Promise Type					- 코루틴 내부에서 initial, return
//◦ Coroutine Handle				- 코루틴 외부에서 resume, done 위한 것


// C++20 에서는
// 
// 1. 함수에 이러한 키워드(Operators)가 발생하면 코루틴이 됩니다. ***
//		co_await  (중단, 반환X)
//		co_yield  (중단, 반환O)
//		co_return (종료, 반환OX)
//
//		co_await 다음에는 awaitable 객체가 옵니다. 
//			EX) co_await std::suspend_always{};
//		co_yield 다음에는 반환할 값이 옵니다.
//			EX) co_yield 10;
//		co_return 은 코루틴 종료 (반환할 값이 올 수 있다.)
//			EX) co_return;
//			EX) co_return 10;
//
// 2. 코루틴 함수는 코루틴 반환 객체를 리턴 해야합니다. ***


//	호출, 종료는 가능하지만, 중단, 재개는 어떻게 ???
//		-> 함수의 상태를 보관하자. ( 상태를 객체로 메모리에 보관 - 코루틴상태, 코루틴프레임 )
//		Function Frame 은				stack 에서 관리.
//		Coroutine(stack-less) frame 은	heap 에서 타입시스템을 사용해서 관리한다.( promise_type )
//		-> 코루틴 상태를 '관리'하기 위한 handle 이 필요하다.( coroutine_handle )


//코루틴 반환 객체 --------------------------------------------------------------------------------

//우리가 코루틴과 소통할 수 있는 어떠한 방법이 있어야 합니다. ( 중단, 재개 )  //코루틴 반환 객체
//  코루틴 반환 객체 ***   ( 예제의 CoTask )
//	만약 아직 실행되지 않았다면, 재개(resume) 할 것이고, 
//	resume 함수를 통해 그 안에 여전히 실행될 것이 있는지를 나타낸다.

//'코루틴 반환 객체'가 컴파일러에 의해 변경될 때 promise_type 이 필요합니다.	//promise_type
//  promise_type ***
//  -	컴파일러를 위한 특별 타입(Promise Type)
//	-	코루틴 코드 생성을 위한 도움, 프레임의 할당/해제, coroutine_handle<P> 로의 접근
//  -	'특별히 정해진 함수'를 추가해야 한다.
// 
//  promise_type은 두가지 방법으로 작성할 수 있습니다.
//  1. CoTask(코루틴 반환 객체)의 멤버로 promise_type(또는 동일한 이름의 별칭) 생성
//  2. coroutine_traits 를 사용하여 promise_type을 정의(또는 동일한 이름의 별칭 생성)

//코루틴을 사용하기 위해서는 코루틴에 대한 일종의 핸들이 필요합니다.			//coroutine_handle
//  coroutine_handle ***
//  -	코루틴을 외부에서 재개, 중단, 확인하기 위한 제어 핸들. 
//  -   resume(),destroy(),done() - 간접적(안전한) 컴파일러 내장함수
// 
//  std::coroutine_handle<promise_type>
//  co_await 연산자는 함수의 현재 상태가 힙의 어딘가에 묶여 있는지 확인하고 
//  호출이 현재 함수의 실행을 계속하는 호출 가능 개체를 만듭니다.



// 요약 하면 -------------------------------------------------------------------------------------------------
// 
//	함수를 정의할 때
//	co_await, co_yield, co_return 키워드들 중 최소한 하나를 사용하면 코루틴이 되고, ***
//  코루틴 객체를 반환해야 한다. ***
// 
//	코루틴 반환 객체 - 
//		코루틴이 반환하는 객체 ( promise_type, coroutine_handle<> 필요 ), 
//		사용할 때 선언하는 객체. 
// 
//	promise_type 
//		- 코루틴 내부에서 관리되는 객체 (코루틴의 시작이나, 종료, 결과나 예외 처리를 하는 기능을 정의 )
//	coroutine_handle 
//		- 코루틴 외부에서 관리되는 객체 ( 코루틴을 resume 하거나 코루틴 프레임을 제거 할 때 사용)

//	코루틴이 최초 실행 되면, coroutine state 가 힙에 생성되어, 상태를 관리하는 식으로 동작합니다.

//C++ Coroutine의 구성요소Component들 --------------------------------------------
//◦ Operators& Awaitable Type
//◦ Promise
//◦ Coroutine Handle
/*
Awaitable
	co_await의 피연산자
	◦ await_ready, await_suspend, await_resume
	중단 Suspension 제어(== 프로그래머 의도를 반영)
Promise
	코루틴 코드 생성
	◦ 프레임의 수명주기
		◦ 할당 / 해제
		◦ Initial / Final suspend
	◦ 반환 / 예외 처리
Handle
	컴파일러가 생성한 구조체와 내장함수로의 인터페이스
	◦ Suspend
	◦ Resume
	◦ Destroy
*/

//개념	C++ Coroutine -----------------------------------------------------------
//호출	변화 없음
//종결	co_return
//중단	co_await, co_yield		// unary operator (1항 연산자)
//재개	handle.resume()			// coroutine_handle<P>::resume()

//EX) 기본 예시 ---------------------------------------------------------------------------

#include <iostream>
#include <coroutine>
#include <concepts>
#include <exception>
using namespace std;

class CoTask											//코루틴 반환 객체
{
public:
	struct promise_type;									//promise_type
	using coHandle = std::coroutine_handle<promise_type>;	//coroutine_handle

	struct promise_type {
		auto get_return_object() { return coHandle::from_promise(*this); }	// 객체 반환
		auto initial_suspend() noexcept { return std::suspend_always(); }	// 객체 초기화
		void return_void() {}												//
		auto final_suspend() noexcept { return std::suspend_always(); }		// 객체 종료
		void unhandled_exception() { std::terminate(); }					// 예외처리
	};

	CoTask(coHandle handle) : handler(handle) {}
	~CoTask() { handler.destroy(); }

	void resume() { return handler.resume(); }
	bool done() { return handler.done(); }
private:
	coHandle handler;
};

CoTask coFunc()
{
	cout << "coFunc 1" << endl;
	co_await std::suspend_always();
	cout << "coFunc 2" << endl;
}

int main()
{
	CoTask co = coFunc();				//코루틴객체를 받아두었다가

	cout << "main 1" << endl;
	co.resume();						//코루틴 resume(); 진행,재개
	cout << "main 2" << endl;
	co.resume();
	cout << "main 3" << endl;

	//if (!co.done())	co.resume();	//코루틴 done(); 종료 체크
}


//-------------------------------------------------------------------------
//함수에 이러한 키워드(Operators)가 발생하면 코루틴이 됩니다 ***

	co_await		//중단, 반환 X
	co_yield		//중단, 반환 O
	co_return		//종료, 반환 OX

// co_await ---------------------------------------------------------

#include <iostream>
#include <coroutine>
#include <concepts>
#include <exception>
using namespace std;

struct co_noreturn			//코루틴 반환 객체
{
	struct promise_type;										//1.promise_type
	using handle_type = std::coroutine_handle<promise_type>;	//2.coroutine_handle

	struct promise_type {
		std::exception_ptr exception_;

		co_noreturn get_return_object() {
			return co_noreturn(handle_type::from_promise(*this));
		}
		std::suspend_always initial_suspend() { return {}; }
		void return_void() {}
		std::suspend_always final_suspend() noexcept { return {}; }
		void unhandled_exception() { exception_ = std::current_exception(); }
	};

	handle_type handle;

	co_noreturn(handle_type handler) : handle(handler) {}
	~co_noreturn() { handle.destroy(); }

	bool done() { return handle.done(); }		//done()

	void operator()() {
		handle();		//resume()
		if (handle.promise().exception_)
			std::rethrow_exception(handle.promise().exception_);
	}
};

co_noreturn co_func_a()				//cotask_noreturn - 코루틴 반환 객체
{
	cout << "co_func_a 01" << endl;
	co_await std::suspend_always();			//co_await - 중단
	cout << "co_func_a 02" << endl;
}

co_noreturn co_func_b()
{
	cout << "co_func_b 01" << endl;
	co_await std::suspend_always();			//co_await - 중단
	cout << "co_func_b 02" << endl;
}

int main()
{
	auto cotask0 = co_func_a();					//코루틴 객체 
	auto cotask1 = co_func_b();

	while (!cotask0.done() || !cotask1.done())	//handle.done()
	{
		if (!cotask0.done()) {
			cotask0();							//handle.resume()
		}
		if (!cotask1.done()) {
			cotask1();							//handle.resume()
		}
	}
	return 0;
}

// co_return ---------------------------------------------------------

#include <iostream>
#include <coroutine>
#include <concepts>
#include <exception>
using namespace std;

template<typename T>
struct co_retuen {
	struct promise_type;
	using handle_type = std::coroutine_handle<promise_type>;

	struct promise_type {
		T return_value_;									//
		std::exception_ptr exception_;

		co_retuen get_return_object() {
			return co_retuen(handle_type::from_promise(*this));
		}
		std::suspend_always initial_suspend() { return {}; }
		std::suspend_always final_suspend() noexcept { return {}; }
		void unhandled_exception() { exception_ = std::current_exception(); }

		template<std::convertible_to<T> From>
		void return_value(From&& from)				// co_return 0
		{
			return_value_ = std::forward<From>(from);
		}
	};

	handle_type handle;

	co_retuen(handle_type handler) : handle(handler) {}
	~co_retuen() { handle.destroy(); }

	bool done() { return handle.done(); }

	void operator()() {
		handle();
		if (handle.promise().exception_)
			std::rethrow_exception(handle.promise().exception_);
	}

	T return_value()	//***
	{
		return handle.promise().return_value_;
	}
};

co_retuen<int> co_func_ra()
{
	cout << "co_func_ra 01" << endl;
	co_await std::suspend_always();		//co_await - 중단
	cout << "co_func_ra 02" << endl;

	co_return 100;						//co_return - 반환, return_value
}

co_retuen<int> co_func_rb()
{
	cout << "co_func_rb 01" << endl;
	co_await std::suspend_always();
	cout << "co_func_rb 02" << endl;

	co_return 200;
}


int main()
{
	auto cotask0 = co_func_ra();
	auto cotask1 = co_func_rb();

	while (!cotask0.done() || !cotask1.done())
	{
		if (!cotask0.done()) {
			cotask0();
		}
		if (!cotask1.done()) {
			cotask1();
		}
	}

	cout << cotask0.return_value() << endl;		// return_value
	cout << cotask1.return_value() << endl;

	return 0;
}

// co_yield ---------------------------------------------------------

#include <iostream>
#include <coroutine>
#include <concepts>
#include <exception>
#include <optional>
#include <vector>
using namespace std;

template<typename T>
struct co_enumarator
{
	struct promise_type;
	using handle_type = std::coroutine_handle<promise_type>;

	struct promise_type {
		std::optional<T> value_ = std::nullopt;
		std::exception_ptr exception_;

		co_enumarator get_return_object() {
			return co_enumarator(handle_type::from_promise(*this));
		}
		std::suspend_always initial_suspend() { return {}; }
		std::suspend_always final_suspend() noexcept { return {}; }
		void unhandled_exception() { exception_ = std::current_exception(); }

		template<std::convertible_to<T> From>
		std::suspend_always yield_value(From&& from) {			// co_yield 0
			value_ = std::forward<From>(from);
			return {};
		}

		void return_void() {}
	};

	handle_type handle;

	co_enumarator(handle_type handler) : handle(handler) {}

	~co_enumarator() { handle.destroy(); }

	bool done() { return handle.done(); }

	std::optional<T> operator()() {
		handle();
		if (handle.promise().exception_)
			std::rethrow_exception(handle.promise().exception_);

		auto ret = std::move(handle.promise().value_);
		handle.promise().value_ = std::nullopt;
		return ret;
	}
};

co_enumarator<int> co_func_enum()
{
	vector<int> items{ 1,2,3,4,5 };

	for (auto item : items)
	{
		co_yield item;						// yield_value - 중단(반환) - yield_value
	}
}

int main(int argc, char* argv[])
{
	auto cotask = co_func_enum();

	while (!cotask.done())
	{
		auto value = cotask();				// std::optional<T> value
		if (value.has_value())
		{
			cout << value.value() << endl;	// 반환값 - yield_value
		}
	}
	return 0;
}