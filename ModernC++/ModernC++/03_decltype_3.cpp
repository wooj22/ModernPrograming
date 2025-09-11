#include <iostream>
#include <vector>
using namespace std;

int main() 
{
	// 다음 선언의 타입은 무엇입니까? 
    int x = 0;
    decltype(x) ;					// int
	decltype((x));					// int&


	// 다음 선언의 타입은 무엇입니까? 
	class C {
	public:
		float a;
	};

	C cc;
    decltype(cc.a);					// float 

    const C ccc;
    decltype((ccc.a));				// const float&  // () 로 인해 & 가 되면서 const 필요


	// 다음 선언의 타입은 무엇입니까? 
	const int&& fx();

	decltype(fx());					// const int&&		// 함수호출 -> 함수의 반환 형식

	decltype(fx )  v;				// const int&& ()	// 함수
}

/*
const int&& a() { return 1; }

int main()
{
	const int&& fx();

	decltype(fx) a;				//const int&& ()  형식의 함수 a 

	cout << a();
}

*/

// decltype(( )) ----------------------------------------------------------------------------------------

struct S
{
	int m_x;				// m_x 멤버를 가지고 있고
	S()	{ m_x = 42;	}		// 구조체를 생성하면 m_x 값을 42 로 초기화 한다.
};

void main()
{
	int x;
	const int cx = 42;
	const int& crx = x;			// crx는 x를 참조하며 const로서 참조하는 대상을 x에서 다른 걸로 바꿀 수 없다.
	const S* p = new S();		// 구조체 S의 포인터 p는 const, 가리키는 대상을 new S()에서 다른걸로 바꿀 수 없다.

	// auto
	auto a = x;					// int	
	auto b = cx;				// int   (const int 가 아님)
	auto c = crx;				// int   (const int & 가 아님)
	auto d = p;					// const S *  (포인터라 그대로 다 따라 온다.)
	auto e = p->m_x;			// int  (p는 const 포인터이기 때문에 간접참조로 구조체 멤버의 값을 바꿀 수 없고 p->m.x 이렇게 읽을 수만 있다.)

	//decltype
	typedef decltype(x) x_type;					// int
	typedef decltype(cx) cx_type;				// const int
	typedef decltype(crx) crx_type;				// const int &	
	typedef decltype(p->m_x) m_x_type;			// int

	//decltype  - (표현식)
	typedef decltype((x)) x_type2;			    // int &	
	typedef decltype((cx)) cx_type2;		    // const int &
	typedef decltype((crx)) crx_type2;	        // const int & (원래 레퍼런스였다면 그대로 & 유지함)	
	typedef decltype((p->m_x)) m_x_type2;	    // const int & (p는 const이기 때문에 간접참조로 멤버의 값을 바꾸면 안되기 때문에 & 레퍼런스가 되니 값을 바꾸면 안된다는 const까지 따라왔다.)
}


//리턴 타입을 auto 와 decltype 에 넣을 때.---------------------------------------------------------------------

const S foo() { return S(); }                       // const 구조체 S() 를 리턴한다.
const int& foobar() { return 123; }                 // const int & 를 리턴한다.

void main()
{
	vector<int> vec = { 10, 20 };

	auto a = foo();									// S			// 선언에서 결정
	typedef decltype(foo()) foo_type;				// const S		// 리턴타입과 동일

	auto b = foobar();								// int
	typedef decltype(foobar()) foobar_type;			// const int &	// 리턴타입과 동일

	auto itr = vec.begin();							// std::vector<int>::iterator
	typedef decltype(vec.begin()) iterator_type;	// std::vector<int>::iterator

	
	auto firstElement = vec[0];						// int
	firstElement = 1;
	decltype(vec[0]) secondElement = vec[0];		// int &
	secondElement = 1;

	//내부적으로 vector[] 는 레퍼런스를 리턴한다 ***
}

//L-value, R-value ------------------------------------------------------------------------------------------
//		식별자가 아닌 경우에,  식의 결과가 lvalue 면 &, xvalue 면 &&

void main()
{
	int x = 0;
	int y = 0;
	const int cx = 40;
	const int cy = 50;
	double d1 = 3.14;
	double d2 = 9.8;

	auto a = x * y;										// int		
	typedef decltype(x * y)		xy_type;				// int			//rvalue

	auto b = cx * cy;									// int
	typedef decltype(cx * cy)	cxcy_type;				// int			//rvalue

	auto c = d1 < d2 ? d1 : d2;							// double	
	typedef decltype(d1 < d2 ? d1 : d2) cond_type;		// double&		//lvalue

	auto d = x < d2 ? x : d2;							// double
	typedef decltype(x < d2 ? x : d2) cond_type_mixed;	// double  //비교한 두 변수가 다른 타입이면 &가 붙지 않는다.***

}

// 다음 선언의 타입은 무엇입니까?
	int main()
	{
		int n = 0;
		int x = 0;
		double d = 1.0;

		decltype(n < x ? n : x) obj1;		//
		decltype(n < d ? n : d) obj2;		//

	}

// decltype 레퍼런스 없애기 std::remove_reference -------------------------------------------------------------

	// 두 인수 중에서 더 작은 값을 리턴해주는 함수 구현하는 경우
	template<typename T1, typename T2>	// decltype 특성상 두 인수 T1과 T2의 자료형이 같을 경우 &가 붙는다는 단점이 존재한다. 
	auto fpmin1(T1 x, T2 y) -> decltype(x < y ? x : y) {
		return x < y ? x : y;
	}

	template<typename T1, typename T2>	// 두 인수가 자료형이 같을 경우 &가 붙는 단점을 없애버린다.
	auto fpmin2(T1 x, T2 y) -> typename std::remove_reference<decltype(x < y ? x : y)>::type {
		return x < y ? x : y;
	}

	void main()
	{
		int i = 42;
		double d = 45.1;
		auto a = std::min(static_cast<double>(i), d);
		int& j = i;

		typedef decltype(fpmin1(i, d)) fpmin_return_type2;		// double
		typedef decltype(fpmin1(j, d)) fpmin_return_type3;		// double
		typedef decltype(fpmin1(d, d)) fpmin_return_type1;		// double&		//lvalue

		typedef decltype(fpmin2(d, d)) fpmin_return_type4;      // double		//& 제거해서 일관된 타입으로 
	}


//decltype 은 런타임이 아닌 컴파일 타임에 결정된다. ----------------------------------------------------------

	#include <iostream>
	#include <vector>
	int main()
	{
		vector<int> vec;					// 생성 할당 없음 
		typedef decltype(vec[0]) integer;	// error ???

		// vec[0] 는 원래 접근하면 error
		// decltype 에서는 '런타임 실행'하지는 않으므로 문제 X	

		return 0;
	}

//decltype //클래스 템플릿, 클래스 안에 있는 타입 접근하기 ----------------------------------------------------

	template<typename R>
	class SomeFunctor
	{
	public:
		typedef R result_type;
		SomeFunctor() {}
		result_type operator()() { return R(); }	// () 연산자 오버로딩
	};

	void ex()
	{
		SomeFunctor<int> func;  //func 으로 <int> 형식을 알아내려고 하는 경우는?

		decltype(func)::result_type inst;
		
		typedef decltype(func)::result_type integer;	// integer = int 
	}


//decltype //람다 함수의 타입 접근하기------------------------------------------------------------------------
	void ex()
	{
		auto func = []() { return 42; };
		decltype(func) func2(func);		        // func2 = func;	copy로 가져온다.
		decltype((func)) func3(func);	        // &func3 = func;	ref 로 가져온다.

		cout << "func  주소 = " << &func  << "\tfunc  값 = " << func() << '\n';
		cout << "func2 주소 = " << &func2 << "\tfunc2 값 = " << func2() << '\n';		//별개의 람다 함수
		cout << "func3 주소 = " << &func3 << "\tfunc3 값 = " << func3() << '\n';		//동일한 주소의 람다 함수
	}


// declval -------------------------------------------------------------------------------
//	- 타입의 생성자 호출을 우회해서 멤버 함수의 타입에 접근	

//   T 의 생성자를 직접 호출하지 않더라도 T 가 생성된 객체를 나타낼 수 있습니다
//   실제로 런타임에 사용하면 오류

//   decltype 안에 들어가는 식은, 그냥 식의 형태로만 존재할 뿐 
//   컴파일 시에,  decltype() 전체 식이 타입으로 변환되기 때문에 
//   decltype 안에 있는 식은 런타임 시에 실행되는 것이 아닙니다.

	#include <iostream>
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
		int f() { return 1; }
	};

	int main() {
		A a;
		B b(1);

		std::cout << call_f_and_return(a);  // ok
		std::cout << call_f_and_return(b);  // ok
	}