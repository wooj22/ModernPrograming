//https://modoocode.com/293

//constexpr는
// 
//   일반화된 상수 표현식(Generalized constant expression)을 사용할 수 있게 해주며,
//   일반화된 상수 표현식을 통해
//   변수나 함수, 생성자 함수에 대하여 컴파일 타임에 평가될 수 있도록 처리해 줄 수 있다.
//   (C++17부터는 람다 함수에도 constexpr 키워드 사용이 가능하다)


// constexpr vs const  -----------------------------------------------------------------------

	//const와 constexpr의 주요 차이점은
	//		const 변수의 초기화를 런타임까지 지연시킬 수 있는 반면,
	//		constexpr 변수는 반드시 컴파일 타임에 초기화가 되어 있어야 한다.
	//		초기화가 안 되었거나, 상수가 아닌 값으로 초기화 시도시 컴파일이 되지 않는다.

	//const 로 정의된 상수들은 굳이 컴파일 타임에 그 값을 알 필요가 없습니다.
	//컴파일 타임에 상수를 확실히 사용하고 싶다면 constexpr 키워드를 꼭 사용해야 합니다 ***

	int a;
	// Do something...
	const		int b = a;				// b 의 값을 지정해주면 바꿀 수 없다
	constexpr	int b = a;				// error

	bool value = true;
	const     bool value1 = value;
	constexpr bool value2 = value1;		// error //식에 상수값이 있어야 합니다.


//constexpr 키워드는 numeric limits를 사용할 때 발생하는 C++98의 문제점을 고쳤습니다.

	// C++11 이전에는 아래와 같은 표현식은
	std::numeric_limits<short>::max()

	//기능적으로 매크로인 INT_MAX와 동일하지만, 정수형 상수로 사용될 수 없었습니다.

	//하지만, C++11부터 constexpr 덕분에 아래와 같이 배열을 선언하거나 컴파일 시간 연산(metaprogramming)이 가능하게 되었습니다.

	std::array< short, std::numeric_limits<short>::max()> a;


// constexpr 함수 -----------------------------------------------------------------------------------

	//constexpr을 사용하여 함수의 리턴값을 컴파일 타임 상수로 만들 수 있습니다.

	constexpr int square(int x)
	{
		return x * x;
	}

	float a[ square(9) ];		// OK, since C++11: a has 81 elements	

	//constexpr 키워드가 등장하기 이전에는 
	//		컴파일 타임 상수인 객체를 만드는 함수를 작성하는 것이 불가.
	//		난해한 템플릿 메타프로그래밍을 사용해야 했습니다.

	/*
		template <int X>
		struct Square
		{
			static constexpr int value = X * X;
		};

		constexpr int result = Square<5>::value;
	*/

//constexpr 함수 예시

	#include <iostream>

	template <int N>
	struct Factorial {  static const int value = N * Factorial<N - 1>::value; };
	template <>
	struct Factorial<0> {  static const int value = 1; };

	template <int N>
	struct A { int operator()() { return N; }};

	int main() {
	  A<Factorial<10>::value> a;  // 컴파일 타임에 값이 결정되므로 템플릿 인자로 사용 가능!
	  std::cout << a() << std::endl;
	}

	//함수의 리턴 타입에 constexpr 을 추가한다면
	//	조건이 맞을 때, 해당 함수의 리턴값을 컴파일 타임 상수로 만들어버릴 수 있다.

	constexpr int Factorial(int n) {
	  int total = 1;
	  for (int i = 1; i <= n; i++) { total *= i; }
	  return total;
	}

	template <int N>
	struct A { int operator()() { return N; } };	

	int main() {
	  A<Factorial(10)> a;		// constexpr 함수 호출
	  std::cout << a() << std::endl;
	}

//constexpr 함수 제약 조건 ----------------------------------------------------------------------

//C++14 부터 constexpr 함수 제약 조건들이 완화되어서
// 
//	아래의 제약조건들 빼고는 모두 constexpr 함수 내부에서 수행할 수 있습니다.

	//제약조건
	리터럴 타입이 아닌 변수의 정의	  ***
	초기화 되지 않는 변수의 정의
	실행 중간에 constexpr 이 아닌 함수를 호출하는 경우
	goto 문 사용 불가
	예외 처리 (try 문; C++ 20 부터 가능하게 바뀌었습니다)

	//리터럴 타입? ----------------------------------------
	//	컴파일러가 컴파일 타임에 정의할 수 있는 타입
	void 형
	스칼라 타입(char, int, bool, long, float, double) 등등
	레퍼런스 타입
	리터럴 타입의 배열
	혹은 디폴트 소멸자를 가지고 다음 중 하나를 만족하는 타입
	람다 함수
	Aggregate 타입(사용자 정의 생성자, 소멸자가 없으며 모든 데이터 멤버들이 public).쉽게 말해 pair 같은 종류.
	constexpr 생성자를 가지며 복사 및 이동 생성자가 없음

//C++14 constexpr 함수 제한 조건 완화 ***
// 
//		변수 선언 가능 (static, thread_local 제외)
//		if / switch 분기문 사용 가능
//		range-based for 루프를 포함한 모든 반복문 사용 가능

	constexpr bool is_prime(int n)
	{
		if (n <= 1)
			return false;
		for (int i = 2; i * i <= n; ++i) {
			if (n % i == 0)	return false;
		}
		return true;
	}

//만일 조건을 만족하지 않는 작업을 함수 내에서 하게 된다면 컴파일 타임 오류가 발생

	int not_constexpr(int x) { return x++; }
	constexpr int Factorial(int n) {
		int total = 1;
		for (int i = 1; i <= n; i++) {
			total *= i;
		}
		not_constexpr(total);		//
		return total;
	}


//constexpr 함수는 컴파일 타임 상수들만 인자로 받을 수 있는 것일까요?
//		constexpr 함수에 인자로 컴파일 타임 상수가 아닌 값을 전달하였다면, 그냥 일반 함수 처럼 동작.
//		즉, constexpr 함수의 경우 반드시 상수가 되는 것은 아니다. ***

#include <iostream>

	constexpr int Factorial(int n) {
		int total = 1;
		for (int i = 1; i <= n; i++) { total *= i; }
		return total;
	}

	int main() {
		int num;
		std::cin >> num;
		std::cout << Factorial(num) << std::endl;
	}

	//constexpr 을 함수에 붙일 수 있다면 붙여주는 것이 좋다.
	//왜냐하면 constexpr 처럼 동작하지 못한다면 그냥 일반 함수처럼 동작하고,
	//컴파일 타임 상수를 생성할 수 있는 상황이라면 간단히 이용할 수 있기 때문


// constexpr 생성자 --------------------------------------------------------------------------

	//C++ 14 부터 constexpr 생성자를 지원함으로써 사용자들이 리터럴 타입들을 직접 만들 수 있게 되었다.
	//리터럴 타입은 쉽게 생각하면 컴파일러가 컴파일 타임에 정의할 수 있는 타입을 의미.
	// 
	//단, constexpr 생성자의 인자들은 반드시 리터럴 타입이여야만 하고, 
	//해당 클래스는 다른 클래스를 가상상속 받을 수 없습니다.

	#include <iostream>

	class Vector {
	public:
		constexpr Vector(int x, int y) : x_(x), y_(y) {}   //constexpr 생성자
		constexpr int x() const { return x_; }
		constexpr int y() const { return y_; }
	private:
		int x_;
		int y_;
	};

	constexpr Vector AddVec(const Vector& v1, const Vector& v2) {
	   return {v1.x() + v2.x(), v1.y() + v2.y()};
	}

	template <int N>
	struct A {
		int operator()() { return N; }
	};

	int main() {
		constexpr Vector v1{1, 2};
		constexpr Vector v2{2, 3};

		A<v1.x()> a;				//A<1> a; // constexpr 객체의 constexpr 멤버 함수는 역시 constexpr!
		std::cout << a() << std::endl;

		A<AddVec(v1, v2).x()> b;	// AddVec 역시 constexpr 을 리턴한다.
		std::cout << b() << std::endl;
	}

	//constexpr 객체의 constexpr 멤버 함수만이 constexpr 을 줍니다. ***


// if constexpr -----------------------------------------------------------------------

	//타입에 따라 형태가 달라지는 함수를 짜고 싶다면, if 문은 템플릿 특수화, 템플릿 타입 유추를 통해 구현.
	//if constexpr 로 처리 가능.
	//if constexpr 은 조건이 반드시 bool 로 타입 변환될 수 있어야 하는 컴파일 타임 상수식이어야만 합니다.
	//if constexpr 이 참이라면 else 에 해당하는 문장은 컴파일 되지 않고 (완전히 무시), 따라서 오류 발생 안함.

	#include <iostream>
	#include <type_traits>

	template <typename T>
	void show_value(T t) 
	{
		if constexpr (std::is_pointer<T>::value) {				//std::is_pointer_v<T>
			std::cout << "포인터 이다 : " << *t << std::endl;
		} else {
			std::cout << "포인터가 아니다 : " << t << std::endl;
		}
	}

	int main() 
	{
		int x = 3;		show_value(x);
		int* p = &x;	show_value(p);
	}

//참고로, if constexpr 대신 템플릿 타입 유추를 이용하면 다음과 같이 작성

	template <typename T>
	void show_value(T t) {  std::cout << "포인터가 아니다 : " << t << std::endl;	}

	template <typename T>
	void show_value(T* t) {  std::cout << "포인터 이다 : " << *t << std::endl; }


//아래 코드는 컴파일이 될까요? 실행은?

	#include <iostream>

	extern int x;

	int f()
	{
		if constexpr (true) return 0;
		else                return x;
	}

	int main() {

		f();
		return 0;
	}
