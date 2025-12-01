//Trivial  : (간단한, 사소한) 하는 일이 없는 객체 or 데이타.
//		C++의 클래스 또는 구조체에 컴파일러에서 제공하거나 
//		명시적으로 '기본 설정'된 특수 멤버 함수가 있는 경우.
 
//Trivial 조건
//		1. 가상함수가 없어야 함
//		2. 사용자 정의 생성자가 없어야 함
//		3. 객체형 멤버가 없거나 객체형 멤버의 생성자가 trivial 하면 됨
//		4. 기반 클래스가 없거나 기반 클래스의 생성자가 trivial 해야 함
//		5. C++ 11부터 지원하는 멤버 선언시 초기화 하는 과정이 없어야 함

//C++의 클래스 또는 구조체에 
//컴파일러에서 제공하거나 명시적으로 기본 설정된 특수 멤버 함수가 있는 경우
//C++에서 컴파일러는 이 상황에서 멤버의 순서를 지정하는 방법을 자유롭게 선택할 수 있습니다. ***


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
	std::cout << "A:   " << std::is_trivial<A>::value << std::endl;
	std::cout << "B:   " << std::is_trivial<B>::value << std::endl;
	std::cout << "C:   " << std::is_trivial<C>::value << std::endl;
	std::cout << "D:   " << std::is_trivial<D>::value << std::endl;
	return 0;
}

//---------------------------------------------------------------

#include <iostream>
#include <type_traits>
using namespace std;

struct Base {};

class Trivial : public Base		// Base 는 Trivial 해야 함
{
	int n;
	Base t;					// 객체형 멤버는 Trivial 한 것만 허용
public:
	Trivial() = default;
	void foo() {}
};

class NonTrivial
{
	int n = 10;				// 초기화 X
public:
	NonTrivial() {}			// 사용자정의 생성자 X

	virtual void foo() {}	// 가상함수 X	// 생성자가 가상함수테이블 만드는 "일"을 함
};

int main()
{
	cout << is_trivially_constructible<Trivial>::value << endl;		// true
	cout << is_trivially_constructible<NonTrivial>::value << endl;	// false
}


//Trivial  유형에는 
//
// Trivial 기본 생성자, Trivial 복사 생성자, Trivial 복사 할당 연산자 및 Trivial 소멸자가 있습니다.
// 각각의 경우에 trivial은 생성자 / 연산자 / 소멸자를 사용자가 제공하지 않고 
// 다음과 같은 클래스에 속함을 의미합니다.
//	   가상 함수 또는 가상 기본 클래스 없음,
//	   Trivial 않은 해당 생성자 / 연산자 / 소멸자가 있는 기본 클래스 없음
//	   해당하는 Trivial 않은 생성자 / 연산자 / 소멸자가 있는 클래스 유형의 데이터 멤버가 없습니다.

struct Trivial
{
	int i;
private:
	int j;
};

struct Trivial2
{
	int i;
	Trivial2(int a, int b) : i(a), j(b) {}
	Trivial2() = default;
private:
	int j;   // Different access control
};


//Trivial Type의 용도
//
//최적화
//  Trivial Type은 생성 및 복사 시 추가적인 작업이 없으므로 더 빠릅니다.
//  컴파일러는 Trivial Type에 대해 메모리 복사와 같은 최적화를 수행할 수 있습니다.
//
//저수준 시스템 프로그래밍
//  Trivial Type은 C 스타일 데이터와 호환되며, 직접적인 메모리 조작이 가능합니다.
//
//타입 속성 확인
//  템플릿 기반 프로그래밍에서 std::is_trivial(C++11 이상)을 사용하여 Trivial 여부를 확인할 수 있습니다.

//POD(Plain Old Data) 유형
// 
//  클래스 또는 구조체가 Trivial 하고 표준 레이아웃이면 POD(Plain Old Data) 유형입니다.
//  따라서 POD 유형의 메모리 레이아웃은 연속적이며 각 구성원은 이전에 선언된 구성원보다 높은 주소를 가지므로 
//  이러한 유형에서 바이트 복사 및 이진 I/O용 바이트를 수행할 수 있습니다.
//  int와 같은 스칼라 유형도 POD 유형입니다.
//  클래스인 POD 유형은 비정적 데이터 멤버로 POD 유형만 가질 수 있습니다.

//Trivial vs.Standard Layout
//  Trivial : 타입이 복잡한 사용자 정의 동작 없이 단순한 초기화 및 소멸 동작을 가지는지에 초점.
//  Standard Layout : 타입의 메모리 배치가 C와 호환되는 표준 메모리 레이아웃을 따르는지에 초점.