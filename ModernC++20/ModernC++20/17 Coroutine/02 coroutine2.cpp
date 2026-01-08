//C++20 에서는 함수에 이러한 키워드가 발생하면 코루틴이 됩니다. ***
//		co_await
//		co_yield
//		co_return

//promise_type
//		코루틴 키워드에 따라서, promise_type 에 적합한 인터페이스 함수가 필요하다.
//coroutine_handle
//      코루틴의 재개, 완료여부를 체크한다.


//------------------------------------------------------------
//코루틴 키워드에 따라서, promise_type 에 적합한 인터페이스 함수가 필요하다.
// 
//		co_yield 0		- yield_value()
// 
//		co_return		- return_void()
//		co_return 0		- return_value()

// co_await ---------------------------------------------------------
// 
//		co_await 뒤에는 'awaitable 객체' 가 온다.
//		std::suspend_always
//		std::suspend_never

#include <iostream>
#include <coroutine>
#include <concepts>
#include <exception>
using namespace std;

struct cotask_noreturn			//코루틴 반환 객체
{
	struct promise_type;											//promise_type
	using handle_type = std::coroutine_handle<promise_type>;		//coroutine_handle

	struct promise_type {
		std::exception_ptr exception_;
		cotask_noreturn get_return_object() {
			return cotask_noreturn(handle_type::from_promise(*this));
		}
		std::suspend_always initial_suspend() { return {}; }		//suspend_never //즉시 시작
		std::suspend_always final_suspend() noexcept { return {}; }
		void unhandled_exception() { exception_ = std::current_exception(); }

		void return_void() {}										// co_return;
	};

	handle_type handler_;

	cotask_noreturn(handle_type handler) : handler_(handler) {}
	~cotask_noreturn() { handler_.destroy(); }

	bool done() { return handler_.done(); }

	void operator()() {
		handler_();
		if (handler_.promise().exception_)
			std::rethrow_exception(handler_.promise().exception_);
	}
};

cotask_noreturn cotask_func_a()				//cotask_noreturn - 코루틴 반환 객체
{
	cout << "cotask_func_a 01" << endl;
	co_await std::suspend_always();			//co_await - 중단  
	cout << "cotask_func_a 02" << endl;
	//co_return;
}

int main(int argc, char* argv[])
{
	auto cotask0 = cotask_func_a();

	//initial_suspend()	- suspend_always - 지연실행
	//initial_suspend()	- suspend_never - 즉시 실행

	cout << "main 01" << endl;

	while (!cotask0.done())
	{
		cotask0();
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
struct cotask_return {
	struct promise_type;
	using handle_type = std::coroutine_handle<promise_type>;

	struct promise_type {
		T return_value_;									//
		std::exception_ptr exception_;
		cotask_return get_return_object() {
			return cotask_return(handle_type::from_promise(*this));
		}
		std::suspend_always initial_suspend() { return {}; }
		std::suspend_always final_suspend() noexcept { return {}; }
		void unhandled_exception() { exception_ = std::current_exception(); }

		template<std::convertible_to<T> From>
		void return_value(From&& from)						// co_return 0;
		{
			return_value_ = std::forward<From>(from);		// 값 할당 ***
		}
	};

	handle_type handler_;

	cotask_return(handle_type handler) : handler_(handler) {}
	~cotask_return() { handler_.destroy(); }

	bool done() { return handler_.done(); }

	void operator()() {
		handler_();
		if (handler_.promise().exception_)
			std::rethrow_exception(handler_.promise().exception_);
	}

	T return_value()
	{
		return handler_.promise().return_value_;			// 값 반환 ***
	}
};

cotask_return<int> cotask_func_ra()
{
	cout << "cotask_func_ra 01" << endl;
	co_await std::suspend_always();	
	cout << "cotask_func_ra 02" << endl;

	co_return 100;									// return_value()
}

cotask_return<int> cotask_func_rb()
{
	cout << "cotask_func_rb 01" << endl;
	co_await std::suspend_always();
	cout << "cotask_func_rb 02" << endl;

	co_return 200;		
}


int main(int argc, char* argv[])
{
	auto cotask0 = cotask_func_ra();
	auto cotask1 = cotask_func_rb();

	while (!cotask0.done() || !cotask1.done())
	{
		if (!cotask0.done())
		{
			cotask0();
		}

		if (!cotask1.done())
		{
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
struct cotask_enumarator {
	struct promise_type;
	using handle_type = std::coroutine_handle<promise_type>;

	struct promise_type {
		std::optional<T> value_ = std::nullopt;
		std::exception_ptr exception_;

		cotask_enumarator get_return_object() {
			return cotask_enumarator(handle_type::from_promise(*this));
		}
		std::suspend_always initial_suspend() { return {}; }
		std::suspend_always final_suspend() noexcept { return {}; }
		void unhandled_exception() { exception_ = std::current_exception(); }

		template<std::convertible_to<T> From>
		std::suspend_always yield_value(From&& from) {			// co_yield 0;
			value_ = std::forward<From>(from);
			return {};
		}

		void return_void() {}
	};

	handle_type handler_;

	cotask_enumarator(handle_type handler) : handler_(handler) {}

	~cotask_enumarator() { handler_.destroy(); }

	bool done() { return handler_.done(); }

	std::optional<T> operator()() {
		handler_();
		if (handler_.promise().exception_)
			std::rethrow_exception(handler_.promise().exception_);

		auto ret = std::move(handler_.promise().value_);
		handler_.promise().value_ = std::nullopt;

		return ret;
	}
};

cotask_enumarator<int> cotask_func_enum()
{
	vector<int> items{ 1,2,3,4,5 };

	for (auto item : items)
	{
		co_yield item;								// yield_value()
	}
}

int main(int argc, char* argv[])
{
	auto cotask = cotask_func_enum();

	while (!cotask.done())
	{
		auto value = cotask();						// std::optional<T> value
		if (value.has_value())
		{
			cout << value.value() << endl;
		}
	}
	return 0;
}

