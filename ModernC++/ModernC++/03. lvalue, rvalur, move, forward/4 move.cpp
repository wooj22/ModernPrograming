//move 함수(move semantics)
// 
//  좌측값도 이동을 시키고 싶다면 어떨까?
//  우측값 레퍼런스를 통해서, 기존에는 불가능하였던 우측값에 대한 (복사가 아닌) 이동의 구현이 가능해졌다.
//  C++ 11 부터 <utility> 라이브러리에서, 좌측값을 우측값으로 바꾸어주는 move 함수를 제공

#include <iostream>
#include <utility>

class Foo {
public:
	Foo()				{ std::cout << "일반 생성자 호출!" << std::endl; }
	Foo(const Foo& a)	{ std::cout << "복사 생성자 호출!" << std::endl; }
	Foo(Foo&& a)		{ std::cout << "이동 생성자 호출!" << std::endl; }
};

int main() {
	Foo a;

	std::cout << "---------" << std::endl;
	Foo b(a);

	std::cout << "---------" << std::endl;
	Foo c(std::move(a));
}

//std::move 함수는 이동을 수행하지 않는다. 그냥 인자로 받은 객체를 우측값으로 변환할 뿐이다.
//		이동 자체는 std::move 를 실행함으로써 발생하는 것이 아니라, 
//		우측값을 받는 함수들이 오버로딩 되면서 수행되는 것. ***

/*

//문제) 

// 만약 B 객체를 생성할 때, 
// 이미 생성되어 있는 A 객체를, B 객체안으로 집어 넣고 싶다면 어떻게 할까요 ?
// 복사없이 이동되도록 구현해 보세요.

	#include <iostream>

	class A {
	public:
		A() { std::cout << "A()\n"; }
		A(const A& a) { std::cout << "A() copy\n"; }
		A(A&& a) { std::cout << "A() move\n"; }
	};

	class B {
	public:
		B(A a) {  }
		A m_a;
	};

	int main() {
		A a;
		std::cout << "create B \n";
		B b(a);							//???
	}


정답 ---------------------------------

	class A {
	public:
		A() { std::cout << "A()\n"; }
		A(const A& a) { std::cout << "A() copy\n"; }
		A(A&& a) { std::cout << "A() move\n"; }
	};

	class B {
	public:
		B(const A& a): m_a(a) { }					//lvalue
		B(A&& a) : m_a(std::move(a)) {}				//rvalue
		A m_a;
	};

	int main() {
		A a;
		std::cout << "create B \n";
		B b(std::move(a));
	}
*/


//참고) const 객체의 이동

#include <iostream>
#include <utility>  // for std::move

int main() {
	const int a = 10;
	// const 변수에서 std::move를 사용
	int&& rvalue_ref = std::move(a);				// a는 const이므로 이동이 불가능
	std::cout << rvalue_ref << std::endl;

	return 0;
}

//객체의 이동 - 기존 객체를 사용안하고 이동시키려는 의도. 이동 후 무효화
//		const 는 이동 후 무효화되지 않고 그대로 남아있습니다. 
//		이는 std::move의 원래 목적을 달성하지 못하게 합니다.
//		결론: 이동하려는 변수가 const가 아니어야 하고, 변경 가능한 상태여야 합니다.

// const rvalue 를 이동이나 복사 시킬 수 았나 ?
//		const rvalue는 복사는 가능하지만, 이동은 불가능합니다.
//		함수에 const T&& 형태로 매개변수를 선언하면, 이동 생성자는 불리지 않고 복사 생성자로만 처리됩니다.
//		이동을 강제적으로 원한다면, const 한정자를 떼어내어야 이동이 제대로 이루어집니다.

// const rvalue 에 참조(type&& const) 가능한가
//		참조 변수는 한 번 바인딩되면 본래부터 변경이 불가능하므로 불필요
//		T&& const: 의미 없음. 실제로 사용하는 경우가 없고, 효과도 없습니다
//		const rvalue 참조를 의도한다면 const T&& 형태만 의미가 있습니다.
