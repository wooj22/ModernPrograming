//보편적 레퍼런스 (Universal reference)
// 
//   템플릿 인자 T 에 대해서, 
//	 우측값 레퍼런스를 받는 형태를 보편적 레퍼런스(Universal reference) 라고 합니다.    // 템플릿인자 T&&
//   보편적 레퍼런스는 우측값만 받는 레퍼런스와 다르게, 
//   우측값 뿐만이 아니라 좌측값 역시 받아낼 수 있습니다.								// auto&&
// 
//	 forward<T>( v ) 는 우측값을 우측값으로, 좌측값은 좌측값으로 그대로 전달한다. ***
//   따라서, forward() : 우측값 레퍼런스 일 때에, 마치 move 를 적용한 것처럼 작동한다.

//	 보편 참조, forward 참조

/*
	const int i = 10;
	auto&& var1 = i;			// 보편참조 = const int &으로 연역

	const auto&& var2 = i;		// const auto&&은 보편 참조 아님 error

	auto&& var3 = 12;			// 보편 참조 = int && 으로 연역
*/

#include <iostream>

class A {};

void foo(A& a)		{ std::cout << "좌측값 레퍼런스 호출" << std::endl; }
void foo(const A& a){ std::cout << "좌측값 상수 레퍼런스 호출" << std::endl; }
void foo(A&& a)		{ std::cout << "우측값 레퍼런스 호출" << std::endl; }

template <typename T>
void wrapper(T&& u) {				//T&&   보편 참조	//우측값, 좌측값 모두 가능

	foo(u);							//1. u는 좌측값이다 
	//foo(std::forward<T>( u ));		//2. T가 좌측값일때는 &, 우측값일때는 && 리턴  ***
}

int main() {
	A a;
	const A ca;

	std::cout << "원본 --------" << std::endl;
	foo(a);
	foo(ca);
	foo(A());		//

	std::cout << "Wrapper -----" << std::endl;
	wrapper(a);
	wrapper(ca);
	wrapper(A());	//
}

/*
함수 매개변수에서 우측값 레퍼런스 형태는 ( int&& a ) 
	우측값만을 인자로 받을 수 있다.

템플릿 타입의 보편적 레퍼런스는 ( T&& a )
	우측값만 받는 레퍼런스와 다르게, 우측값 뿐만이 아니라 좌측값 역시 받아낼 수 있다.

C++ 컴파일러가 템플릿 타입을 추론할 때, 
	템플릿 인자 T 가 레퍼런스가 아닌 일반적인 타입이면 const 를 무시한다.
	아예 우측값을 레퍼런스로 받을 수 있도록 const A& 와 A&& 따로 만들어주는 방법이 있으나
	번거로움 -> T&& 와 forward 로 해결 ***

forward<>()	

	forward<T>(val) 사용하면, val의 type에 따라 Lvalue, Rvalue 로 리턴
	즉
	forward< int& >( val ) 면		int& 리턴
	forward< int&& >( val ) 면		int&& 리턴

	//내부 정의
	{
		template< class T >
		constexpr T&& forward( std::remove_reference_t<T>& t ) noexcept;
		template< class T >
		constexpr T&& forward( std::remove_reference_t<T>&& t ) noexcept;
	}

	//std::forward가 가장 많이 쓰이는 곳은, 보편 참조 매개변수로 받아서 처리하는 로직

*/

#include <iostream>
using namespace std;

int main()
{
	int val = 1;
	int& r1 = forward< int& >(val);     //lvalue 참조로 변환
	int&& r2 = forward< int&& >(val);    //rvalue 참조로 변환
}

/*
레퍼런스 겹침 규칙
	C++ 11 에서는 다음과 같은 레퍼런스 겹침 규칙(reference collapsing rule) 에 따라 
	T 의 타입을 추론하게 됩니다.

	typedef int& T;
	T& r1;				// int&  &	r1;		r1 은 int&
	T&& r2;				// int&  &&	r2;		r2 는 int&

	typedef int&& U;
	U& r3;				// int&& &	r3;		r3 는 int&
	U&& r4;				// int&& &&	r4;		r4 는 int&&

	즉 쉽게 생각하면 & 는 1 이고 && 은 0 이라 둔 뒤에, OR 연산을 한다고 보면 됩니다.
	즉 하나라도 & 면 &, 모두 && 면 &&
*/

