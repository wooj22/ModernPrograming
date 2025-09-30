#include <iostream>
#include <mutex>
using namespace std;

void func(int a) { cout << "int 호출" << endl; }
void func(int* b) { cout << "int* 호출" << endl; }

int main(void)
{
	// 어떤 함수를 호출할까요 ???
	func(0);							// int 호출
	func(NULL);							// int 호출
	func(nullptr);						// int* 호출
	func((int*)0);						// int* 호출
}


//리터럴 0은 int이지 포인터가 아니다.
//nullptr를 사용하면 오버로딩이 예상과 다르게 해소되는 일이 없다.그 뿐만 아니라, nullptr는 코드의 명확성도 높여준다.
//템플릿의 타입 추론시에도, 0과 NULL은 정수 타입으로 추론하는 반면, nullptr은 포인터 타입으로 추론한다.


/*
// 포인터와 정수 타입에 대한 오버로딩 해소 --------------------------------------

	// 포인터와 정수 타입에 대한 오버로딩
	void f(int) { std::cout << "int" << '\n'; }
	void f(bool) { std::cout << "bool" << '\n'; }
	void f(void*) { std::cout << "void*" << '\n'; }

	int main()
	{
		f(0);               // f(void*)가 아니라 f(int)를 호출
		f(NULL);			// 컴파일되지 않을 수도 있지만, 보통은 f(int)를 호출한다. f(void*)를 호출하는 경우는 없다.
		f(nullptr);         // f(void*)를 호출한다.

		// nullptr 를 사용하면 result가 포인터 타입인지 아니면 정수 타입인지를 명확히 한다.
		auto result = Call();
		if (result == NULL) {}
		if (result == nullptr) {}

		return 0;
	}
*/


/*
//nullptr는 템플릿이 관여할 때 특히 필요 --------------------------------------

	#include <iostream>
	#include <mutex>

	// 뮤텍스를 잠그고 호출해야 하는 경우
	class Widget {};

	// 뮤텍스를 잠그고 호출해야 하는 함수들
	int		f1(std::shared_ptr<Widget> spw) { return 0; }
	double	f2(std::unique_ptr<Widget> upw) { return 1.0; }
	bool	f3(Widget* pw) { return true; }

	std::mutex f1m, f2m, f3m;                 // f1, f2, f3용 뮤텍스들

	//using MuxGuard = std::lock_guard<std::mutex>;

	//MuxGuard g1(f1m);                        // f1용 뮤텍스를 잠근다.
	//auto result1 = f1(0);                    // 0을 널 포인터로서 f1에 전달

	//MuxGuard g2(f2m);                        // f2용 뮤텍스를 잠근다.
	//auto result2 = f2(NULL);                 // NULL을 널 포인터로서 f2에 전달

	//MuxGuard g3(f3m);                        // f3용 뮤텍스를 잠근다.
	//auto result3 = f3(nullptr);              // nullptr을 널 포인터로서 f3에 전달

	// 중복된 여러 호출 함수들을 template 으로 작성해 보면

	template <typename FuncType, typename MuxType, typename PtrType>
	decltype(auto) lockAndCall(FuncType func, MuxType& mutex, PtrType ptr)
	{
		using MuxGuard = std::lock_guard<MuxType>;

		MuxGuard g(mutex);
		return func(ptr);
	}

	int main()
	{
		std::mutex f1m, f2m, f3m;

		//auto result1 = lockAndCall(f1, f1m, 0);		// 오류!
		//auto result2 = lockAndCall(f2, f2m, NULL);    // 오류! // 0과 NULL의 경우 ptr의 타입은 정수로 추론
		auto result3 = lockAndCall(f3, f3m, nullptr);	// OK

		//nullptr의 경우, ptr의 타입은 std::nullptr_t로 추론
		//std::nullptr_t는 암묵적으로 모든 포인터 타입으로 변환될 수 있으므로 아무런 문제가 발생하지 않는다.

		return 0;
	}
*/
