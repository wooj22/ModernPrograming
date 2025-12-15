// decltype  
//		decltype( 타입을 알고자 하는 식별자 표현식(id-expression) ) 
//		식의 타입을 알려준다.
// 
//		타입 연산에서만 사용, 런타임이 아닌 컴파일타임에 결정됨

#include <iostream>
using namespace std;

struct A {
	double d;
};

int main() 
{
	//괄호로 둘러쌓이지 않은 식별자 표현식(id-expression) 이라면? - 해당 식의 타입을 얻을 수 있다
	// 
	//    어떠한 연산을 하지 않고 단순히 객체 하나만을 가리키는 식인 경우
	//    변수의 이름, 함수의 이름, enum 이름, 클래스 멤버 변수 등
	

	int a = 3;
	decltype(a) b = 2;			// int	

	int& ra = a;
	decltype(ra) rb = b;		// int&

	int&& x = 3;
	decltype(x) y = 2;			// int&&

	A* aa;
	decltype(aa->d) dd = 0.1;   // double

	int c = 3;
	decltype(c) c1 = 2;			// int
	decltype((c)) c2 = 2;		// int&

	//괄호로 둘러쌓이지 않은 식별자 표현식(id-expression) 아니라면?
}

/*
https://modoocode.com/294

// decltype 규칙 -----------------------------------------------------------------

// 1.괄호로 둘러쌓이지 않은 '식별자 표현식(id-expression)' 이라면, 해당 식의 타입을 얻을 수 있습니다.

    변수의 이름, 함수의 이름, enum 이름, 클래스 멤버 변수 등
    어떠한 연산을 하지 않고 단순히 객체 하나만을 가리키는 식

// 2.식별자 표현식이 아닌 식을 전달하면,

	만일 식의 값 종류가 prvalue 라면	decltype 는 T 가 됩니다.
	만일 식의 값 종류가 lvalue 라면	decltype 는 T& 가 됩니다.
	만일 식의 값 종류가 xvalue 라면	decltype 는 T&& 가 됩니다.

	int a, b;
	decltype(a + b) c;		// c 의 타입은?  //int

	int a, b;
	decltype(a = b) c ;		// c 의 타입은?  //int&

	int a;
	decltype((a)) b;		// b 의 타입은??  //int&  //()를 하면 lvalue
		

//Value Category 참고할 것 ***

*/

// decltype 필요한 경우 -----------------------------------------------------------------------
//		주로 주어진 템플릿 인자에 기반한 generic programming 의 어려움을 해소하기 위해 도입

	//auto와 구별하기 - auto 는 엄밀히 말하자면 정확한 타입을 표현하지 않습니다.
	//
	//	auto	  가 값에 상응하는 타입을 추론시켜주는 키워드라면,
	//	decaltype 은 값으로부터 타입을 추출해 낼 수 있는 키워드

	const int i = 4;
	auto j = i;					// int			j = i;
	decltype(i) k = i;			// const int	k = i;		//decltype 의 경우 const 그대로 보존

	int arr[10];
	auto arr2 = arr;			// int*		arr2 = arr;
	decltype(arr) arr3;			// int		arr3[10];		//decltype 의 경우 배열 타입 그대로를 전달


	//EX) 어떤 객체의 타입이 템플릿 인자들에 의해서 결정되는 경우

	template <typename T, typename U>
	void add(T t, U u, ??? result) {					// 무슨 타입이 와야 할까요?
		*result = t + u;
	}

	template <typename T, typename U>
	void add(T t, U u, decltype(t + u)* result) {		//decltype 으로 해결
		*result = t + u;
	}

	//결과를 리턴해야하는 경우는

	template <typename T, typename U>
	decltype(t + u) add(T t, U u) {			 // error	// t, u 를 알지 못함
		return t + u;
	}

	template <typename T, typename U>
	auto add(T t, U u) -> decltype(t + u)    //후행리턴 //함수의 리턴값을 인자들 정의 부분 뒤에 //C++14 추가된 문법
	{
	  return t + u;
	}


// declval ----------------------------------------------------------------------------------
//		- 타입의 생성자 호출을 우회해서 '멤버 함수'의 타입에 접근
//		T 의 생성자를 직접 호출하지 않더라도 T 가 생성된 객체를 나타낼 수 있습니다
//		실제로 런타임에 사용하면 오류

//		decltype 안에 들어가는 식은, 그냥 식의 형태로만 존재할 뿐,
//		컴파일 시에 decltype() 전체 식이 타입으로 변환되기 때문에,
//		decltype 안에 있는 식은 런타임 시에 실행되는 것이 아닙니다.

	#include <utility>

	template <typename T>
	decltype(std::declval<T>().f()) call_f_and_return(T& t) {
	  return t.f();
	}

	struct A {
	  int f() { return 0; }
	};
	struct B {
	  B(int x) {}
	  int f() { return 0; }
	};

	int main() {
	  A a;
	  B b(1);

	  call_f_and_return(a);  // ok
	  call_f_and_return(b);  // ok
	}

//참고로 C++14 부터는 함수의 리턴 타입을 컴파일러가 알아서 유추해주는 기능이 추가되었습니다.
//이 경우 그냥 함수 리턴 타입을 auto 로 지정해주면 됩니다.

	template <typename T>
	auto call_f_and_return(T& t) {
	  return t.f();
	}

// decltype(auto)
//		- auto 타입은 템플릿 타입 추론에 의해 결정이므로, 그대로 전달하려면 decltype로 감싸면 됨

//		즉, auto 타입 반환을 하려거든 다음 둘 중 하나를 선택하면 된다.
//
//		C++11의 후행 반환 형식을 지정해 주던가
//		C++14의 decltype(auto)의 형태로 반환하던가 ***

	template <typename T>
	decltype(auto) call_f_and_return(T& t) {
		return t.f();
	}


//최종 예시

	#include <iostream>
	#include <utility>

	template <typename T>
	decltype(std::declval<T>().f()) call_f_and_return(T& t) {
		return t.f();
	}

	template <typename T>
	decltype(auto) call_f_and_return2(T& t) {
		return t.f();
	}

	struct A {
		int f() { return 1; }
	};
	struct B {
		B(int x) {}
		int f() { return 2; }
	};

	int main() {
		A a;
		B b(1);

		int n1 = call_f_and_return(a);  // ok
		int n2 = call_f_and_return2(b);  // ok
		std::cout << n2;
	}
