// 각 변수의 타입은 무엇입니까?

#include <iostream>
using namespace std;

int main()
{
	const int a = 3;
	decltype(a) b = 2;				//(		) 

	const int& ra = a;
	decltype(ra) rb = b;			//(		) 

	int&& x = 3;
	decltype(x) y = 2;				//(		) 

	struct A { double* d; };
	A* aa;
	decltype(aa->d) dd = 0.1;		//(		) 

	int c = 3;
	decltype(c) c1 = 2;				//타입은 int
	decltype((c)) c2 = c;			//타입은 int&

	int x, y;
	decltype(x + y) z;				//타입은? 

	int x1, y1;
	decltype(x1 = y1) z1;			//타입은? 

	int x2;
	decltype(std::move(x2)) z2;		//타입은? 

}

//---------------------------------------------------------------------
//다음 선언에 대하여 형식은 ?

#include <utility>

const int&& fx();
struct A { double x; };

int main()
{
	const A* a = new A();

	decltype(fx);			// 형식은 ???
	decltype(fx());			// 형식은 ???
	decltype(a->x);			// 형식은 ???
	decltype((a->x));		// 형식은 ???
}



//---------------------------------------------------------------------
//다음 선언에 대하여 형식은 ?

#include <vector>

struct S
{
	int m_x;
	S() { m_x = 42; }
};

const S foo() { return S(); }                       // const 구조체 S() 를 리턴한다.
const int& foobar() { return 123; }                 // const int & 를 리턴한다.

int main() {

	std::vector<int> vec = { 10, 20 };

	auto a = foo();									//(		) 
	typedef decltype(foo()) foo_type;				//(		) 

	auto b = foobar();								//(		) 
	typedef decltype(foobar()) foobar_type;			//(		) 

	auto itr = vec.begin();							//(		) 
	typedef decltype(vec.begin()) itr_type;			//(		) 

	auto			 v1 = vec[0];					//(		) 
	decltype(vec[0]) v2 = vec[0];					//(		) 
}

//---------------------------------------------------------------------
//맴버함수의 반환형을 리턴하는 함수 template을 작성하려고 합니다.
//_______에 적당한 반환형을 선언을 하세요.

#include <utility>

struct A { int f() { return 10; }  };
struct B { char f() { return 'A'; } };

template <typename T>
_______ call_function(T& t) { return t.f(); }


int main() {
	A a;
	auto val1 = call_function(a);	// int
	B b;
	auto val2 = call_function(b);	// char

}




