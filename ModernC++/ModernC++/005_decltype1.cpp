// 컴파일타임의 형식 알아내기 -------------------------------------------------

//템플릿 구현할때 유용

//템플릿이란 자료형에 대하여 일반화하는 것. 
//	템플릿 함수의 구체화는 컴파일 타임에 템플릿이 호출될때 이루어진다. 
//	템플릿 클래스는 객체가 생성될때, 단 상속받는 경우는 생성유무를 떠나 구체화 한다.
//	따라서, 헤더파일에 선언과 정의 같이 포함되어야 한다.
//	컴파일러가 타입에 대한 추론을 어떻게 하는지 알아야 한다.

#include <iostream>
#include <vector>
using namespace std;

template<typename T1, typename T2>
void ex_func(T1 lvar, T2 rvar)
{
	// 방법 1️ : auto 	
	auto prod1 = lvar * rvar;						// 타입 T1, T2는 실행 후에 결정되므로 추론 어려움	

	// 방법 2️ : typedef
	typedef decltype(lvar* rvar) product_type;		// not 계산! only 추론!
	product_type prod2 = lvar * rvar;				

	// 방법 3️ : decltype
	decltype(lvar * rvar) prod3 = lvar * rvar;		// 컴파일러 단계에서 decltype 추론
}

// decltype
//    새로운 데이터 타입을 정의하는 역할을 한다.
//    컴파일 타임에 auto가 타입을 추론하기에 역부족일 때 주로 사용한다.

int main() 
{
	//  typeid() 는 cv 한정자, 참조 및 lvalue / rvalue-ness 를 버립니다

	int a = 0;
	int& b = a;
	const int& c = 0;

	cout << typeid(a).name() << '\n';
	cout << typeid(b).name() << '\n';
	cout << typeid(c).name() << '\n';


	//  decltype 는 변수가 선언이 된 타입을 그대로 가져온다. const와 &까지.

	const int&  d = 0;

	decltype(d) e1 = d;		// 마우스 커서로 확인

	auto		e2 = d;		// auto와 비교하기

	return 0;
}

//컴파일러는 다음 규칙을 사용하여 식 매개 변수의 형식을 확인합니다. MSDN ***
//
//식 매개 변수가
//	식별자 또는 클래스 멤버 액세스인 경우 				-> 명명된 엔터티의 형식
//	함수 또는 오버로드된 연산자 함수에 대한 호출인 경우 -> 함수의 반환 형식
//	rvalue이면 										-> 식의 형식
//	lvalue이면 										-> 식 형식에 대한 lvalue 참조

/*
 
문제) 다음 선언에 대하여
	
	const int&& fx();
	struct A { double x; };

	int main()
	{
		int var;
		const A* a = new A();
			

		decltype(fx());		// 형식은 ???
		decltype(var);		// 형식은 ???
		decltype(a->x);		// 형식은 ???
		decltype((a->x));	// 형식은 ???
	}

//decltype(fx());	// const int&& 에 대한 rvalue 참조 입니다.
//decltype(var);	// int		var 변수의 형식입니다.
//decltype(a->x);	// double	멤버 액세스의 형식입니다.
//decltype((a->x));	// const double&
					//		내부 괄호를 사용하면 문이 멤버 액세스가 아니라 식으로 평가됩니다.
					//		a 또한 포인터로 const 선언되므로 형식은 const double&
*/


/*

// expression 식에 따라 확인이 어려울 수 있다. 어떻게 확인 ???? ---------------------------------

	// 1. 실제로 컴파일된 형식을 확인해야 할 경우 //의도적 에러 내기

	decltype(expr) obj = 0;			//마우스 커서로 확인 ***


	// 2. TD를 선언만 해 둔다. TD는 "Type Displayer(타입 표시기)"를 뜻한다. 
	
	template <typename T>  class TD;

	TD< decltype(expr) > obj;		//선언해서 확인 ***

*/

/*

#include <iostream>
#include <utility>

const int&& fx();
struct A { double x; };

template <typename T>  class TD {};			//***

int main()
{
	int var;
	const A* a = new A();

	// 형식은 ???

	decltype(fx());
	decltype(var);
	decltype(a->x);
	decltype((a->x));

	//TD< decltype((a->x)) > td;		//선언해서 확인
}
*/