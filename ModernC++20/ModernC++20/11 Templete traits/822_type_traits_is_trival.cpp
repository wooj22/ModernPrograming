//Trivial : 하는 일이 없는…
//		사소한 형식
//		스칼라 형식, 일반적으로 복사할 수 있는 클래스 형식, 이러한 형식의 배열 및 이러한 형식의 cv 한정 버전
//		생성자나 소멸자, 복사자, 이동자 등의 기본 특수 멤버들이 아무것도 하지 않는 타입 
//		생성자가 없거나 default, 가상함수테이블 없어야 함
 
//Trivial 조건
//		1. 가상함수가 없어야 함
//		2. 사용자 정의 생성자가 없어야 함
//		3. 객체형 멤버가 없거나 객체형 멤버의 생성자가 trivial하면 됨
//		4. 기반 클래스가 없거나 기반 클래스의 생성자가 trivial해야 함
//		5. C++ 11부터 지원하는 멤버 선언시 초기화 하는 과정이 없어야 함

//Trivial 의 용도
//		가끔 생성자같은게 호출되지 않는 기존 C 기능과의 호환을 위해서다.
//		trivial한 타입만이 생성자 등을 호출하지 않는 malloc이나 memcpy같은 기능에 사용될 수 있다.
//		깊은 복사를 해야 하는지 판단하기 위해서 사용하기도 한다.


#include <iostream>
#include <type_traits>

class A {};
class B { B() {} };
class C : B {};
class D { virtual void fn() {} };

int main() {
	std::cout << std::boolalpha;
	std::cout << "is_trivial:" << std::endl;
	std::cout << "int: " << std::is_trivial<int>::value << std::endl;
	std::cout << "A: " << std::is_trivial<A>::value << std::endl;
	std::cout << "B: " << std::is_trivial<B>::value << std::endl;
	std::cout << "C: " << std::is_trivial<C>::value << std::endl;
	std::cout << "D: " << std::is_trivial<D>::value << std::endl;
	return 0;
}

/*
#include <iostream>
struct Base {};

class Trivial : public Base // Base 는 Trivial 해야 함
{
	int n;
	Base t;		// 객체형 멤버는 Trivial 한 것만 허용
public:
	B() = default;
	void foo() {}
};

class NonTrivial
{
	int n = 10;					// 초기화 X
public:
	C() {}						// 사용자정의 생성자 X

	virtual void foo() {}		// 가상함수 X  // 생성자가 가상함수테이블 만드는 "일"을 함
};

int main()
{
	cout << is_trivially_constructible<Trivial>::value << endl; // true
	cout << is_trivially_constructible<NonTrivial>::value << endl; // false
}
*/


/*
template<typename T>
enable_if<is_trivially_copyable<T>::value, void>::type
copy(T* dest, T* src, size_t sz)
{
	memcpy(dest, src, sizeof(T) * sz);
}

template<typename T>
enable_if<!is_trivially_copyable<T>::value, void>::type
copy(T* dest, T* src, size_t sz)
{
	while(sz--)
	{
		new (dest) T(*src);
		++dest;
		++src;
	}
}

class Trivial
{
	Trivial() {}
	Trivial(const Test&) = default;
};

class NonTrivial
{
	NonTrivial() {}
	NonTrivial(const Test&) {}
};

int main()
{
	Trivial t1[10];
	Trivial t2[10];

	copy(t2, t1, 10);

	NonTrivial nt1[10];
	NonTrivial nt2[10];

	copy(nt2, nt1, 10);
}
*/

//enable_if
//	enable_if 는 2개의 템플릿 인자 <bool Test, typename Type>를 받아,
//	Test가 참인 경우 Type에 대한 type aliasing을 제공하는 구조체이다.
//	따라서, bool 형 조건이 false인 경우 아무런 타입을 제공하지 않음으로써, 컴파일 타임 에러를 유발할 수 있다.

/*
// 아래에서 trivial 한 타입을 고르세요.

	#include <iostream>
	#include <type_traits>

	class A { };
	class B { int m; };
	class C { int m = 0; };
	class D { D() {} };
	class E { virtual void fn() {} };
	class F : A {};

	int main() {
		std::cout << std::boolalpha;
		std::cout << "A: " << std::is_trivial<A>::value << std::endl;	//출력은?
		std::cout << "B: " << std::is_trivial<B>::value << std::endl;	//?
		std::cout << "C: " << std::is_trivial<C>::value << std::endl;	//?
		std::cout << "D: " << std::is_trivial<D>::value << std::endl;	//?
		std::cout << "E: " << std::is_trivial<E>::value << std::endl;	//?
		std::cout << "F: " << std::is_trivial<F>::value << std::endl;	//?
		return 0;
	}
*/