#include <iostream>

//예외를 방출하지 않을 함수는 noexcept로 선언하라
//		C++11(VS2015)부터 throw()가 deprecated 되고, noexcept 키워드가 추가되었다.
//		noexcept 키워드는 연산자(operator)의 형태로, 그리고 한정자(specifier)의 형태로 제공된다.

// noexcept 한정자(specifier) ------------------------------------------------------

	//함수의 noexcept 여부는 멤버 함수의 const 여부만큼이나 중요한 정보이다.
	int f(int x) throw();	// f는 예외를 방출하지 않음: // C++98 방식	
	int f(int x) noexcept;	// f는 예외를 방출하지 않음: // C++11 방식

	//C++98에서 예외 지정(exception specification)은 코드 사이의 일관성 유지에 아무런 도움도 주지 않았다.
	int f(int x) throw(int);
	int f(int x) throw(int,double);

//C++11 제정 과정에서, 함수의 예외 방출 행동에 관해 정말로 의미 있는 정보는
//	함수가 예외를 하나라도 던질지, 아니면 절대로 던지지 않는지의 여부라는 점에 대한 공감대가 형성
//	그 함수가 예외를 방출하지 않을 것임을 명시할 때에는 noexcept라는 키워드를 사용하면 된다. ***

	void f() noexcept(true);	//예외던질 가능성 없음
	void f() noexcept(false);	//예외던질 가능성 있음
	void f() noexcept;			//noexcept(true)


//noexcept 연산자(operator) -------------------------------------------------------
//	noexcept(expression)
//  표현식은 상수 표현식이거나, bool로 변환가능해야 한다.
//	컴파일 타임에 해당 표현식이 예외를 던지지 않는 표현식인지 체크하여, true/false를 반환

	#include <iostream>
	using namespace std;

	void f();
	void g() noexcept;

	int main()
	{
		cout << noexcept(f()) << endl;	//false
		cout << noexcept(g()) << endl;	//true

		return 0;
	}

//예제------------------------------------------------------------------------
		
	// 예외를 던지지 않는다	
	void bar() noexcept(true) {}

	// 예외를 던지지 않는다고 명시해놓고 예외를 던졌다.
	void baz() noexcept { throw 42; }	

	int main()
	{
		bar();			// OK
		baz();			// 컴파일은 문제 없으나, 런타임에 std::terminate가 호출된다.
	}


	// T() 생성자가 예외를 던지느냐에 따라, foo 함수의 예외 던질지 여부가 결정된다
	// 기존 throw() 로는 이러한 처리가 불가능하다
	// noexcept(T())는 operator로써, 이를 감싸는 외부 noexcept는 specifier로 사용되었다.
	template <typename T>
	void foo() noexcept(noexcept(T())) {}

	int main()
	{
		foo<int>();		// noexcept(noexcept(int())) => noexcept(true) OK
	}


//컴파일러 최적화와 관련하여 ---------------------------------------------------

	//noexcept 함수에서 컴파일러의 최적화기(optimizer)는 
	//	예외가 함수 바깥으로 전파될 수 있다고 해도 실행시점 스택을 풀기 가능 상태로 유지할 필요가 없다. 
	//	또한, 예외가 noexcept 함수를 벗어난다고 해도 
	//	noexcept 함수 안의 객체들을 반드시 생성의 반대 순서로 파괴해야 하는 것도 아니다.

	//그러나 예외 지정이 "throw()"인 함수에는 그러한 최적화 유연성이 없으며, 
	//	예외 지정이 아예 없는 함수 역시 마찬가지로 그런 유연성이 없다.

//함수에서 예외를 던지지 않겠다고 명시한 다음 예외를 던지면 std::terminated 가 호출된다.

	//std::terminated가 호출되면 std::terminated_handler를 호출하는데, 기본 handler 함수는 std::abort이다.
	//std::abort가 호출되면, 프로그램이 조용히 종료되어 버린다.
	// 
	//이는 throw 에서도 문제로 지적되었던 것인데 throw 와의 차이점은 다음과 같다. 
	//throw는 std::unexpected를 호출하였고, noexcept는 std::terminated를 호출한다.
	//throw 와는 달리 noexcept는 stack unwinding이 발생할수도 아닐 수도 있어 
	//컴파일러가 조금 더 최적화를 할 수 있게 한다.