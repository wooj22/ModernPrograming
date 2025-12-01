
//파생과 클래스 템플릿
//		클래스 템플릿을 상속하고 잘못 사용했을 경우, 
//		"가상 함수"가 제 역활을 못할 수 있거나, 컴파일 자체가 되지 않을 수 있다.


//기반이 되는 클래스 템플릿이, 파생 되는 클래스 템플릿에 기입 된 파라미터에 
//		종속 될 경우와 종속되지 않을 경우, 이름을 찾는 규칙이 변화 한다. ***

//----------------------------------------------------------------------------------------
//종속되지 않은 기반 클래스일 경우 주의 해야 할 점 
//      일반 클래스를 상속 할 때와 거의 똑같다.
//      템플릿 파라미터 식별자 이름에 같이 있을 경우, 
//		제일 먼저 종속 되지 않는 기반 클래스에 있는 이름을 먼저 찾는 것 주의.***

#include <iostream>
using namespace std;

template <typename X>
class Base {
public:
	int basefield;
	typedef int T;				//int // 이 부분이 중요.
};

template <typename T>
class D2 : public Base<double>	// 종속되지 않은 기반 클래스 (T에 종속 안됨)
{
public:
	void f() { basefield = 7; }
	T strage;					// int* ???
};

void g(D2<int*>& d2, int* p) {
	d2.strage = p;				// 이 녀석이 컴파일 되지 않음 //기반 클래스의 "typedef int T"로 평가 되었기 때문
}

int main(void) {

}

//해결책 : 가급적 중복된 이름을 피하자 *** 

//----------------------------------------------------------------------------------------
//종속된 기반 클래스일 경우 주의 해야 할 점 
//		식별자가 한정화 되지 않거나 종속되지 않으면, 종속된 기반 클래스에서 이름 자체를 찾지 않는다. ***
//		그 이유는 이름을 찾을 수 있게 될 경우, 
//		템플릿 특수화로 이름의 상태가 변경(int형 변수에서 열거형 상수로)될 수 있기 때문

template <typename X>
class Base
{
public:
	int basefield;					//1번
};

template <typename T>
class DD : Base<T>		// <T>에 종속
{
public:
	void f() { basefield = 0; }		//2번 //int 멤버를 여기에 바인드 하면 3번에서 문제가 됨.
};

template <>
class Base<bool>					//3번 Base<T> 의  명시적 특수화
{
public:
	enum {
		basefield = 42,				//basefield의 의미가 변했다.
	};
};

int main(void) {

	DD<bool> d;
	d.f();							//어쩌라고? 
}

/*
	#include <iostream>
	using namespace std;

	template <typename X> class Base	//Base
	{
	public:
		int basefield;					//1번
	};

	template <> class Base<bool>		//Base<bool> 명시적 특수화
	{
	public:
		enum {
			basefield = 42,				//3번 //basefield의 의미가 변했다.
		};
	};

	int main(void) 
	{
		Base<bool> d;
		cout << d.basefield;			//특수화로 별도 출력가능
	}
*/


//이런 문제를 우회하기 위해, 
//표준 C++는 종속적이지 않은 이름은 종속적인 기본 클래스에서 룩업되지 않는다 ***
//
//종속된 기반 클래스의 경우 :
//일부 프로그래밍 언어(특히 C++ 같은 언어)에서는 종속된 기반 클래스(dependent base class)의 멤버를 검색할 때 특별한 처리가 필요합니다.
//종속된 기반 클래스란, 템플릿 기반 클래스에서 파생된 클래스이며, 템플릿 매개변수에 따라 멤버의 정의가 달라질 수 있는 기반 클래스를 의미합니다.



//이런 경우 이름을 찾으려면 *** -------------------------------------------------------
//		종속시키는 방법 
//		this 를 사용하여 한정 시키는 방법과 
//		한정자(::) 를 사용하여 한정 시키는 방법,
//		using 을 사용 하는 방법 등이 있다.

//this->사용
template<typename T>
class DD1 : public Base<T>
{
public:
	void f() { this->basefield = 0; }
};

//2 한정된 이름 사용
template<typename T>
class DD2 : public Base<T>
{
public:
	void f() { Base<T>::basefield = 0; }
};

//3 using 선언
template<typename T>
class DD3 : public Base<T>
{
public:
	using Base<T>::basefield;
	void f() { Base<T>::basefield = 0; }
};

int main(void) {
}


//일반적으로 this 를 사용 하는 형태가 더 좋다. 
//왜냐하면 한정자를 사용하는 방법은 자칫 가상함수 호출을 억제할 수 있기 때문

template <typename T> class B
{
public:
	enum E { e1 = 6, e2 = 28, e3 = 496, };
	virtual void zero(E e = e1);
	virtual void one(E&);
};

template <typename T> class D : public B<T>
{
public:
	void f() {
		
		// this->E e 라고 선언 할수 없다! // 이 경우가 바로 한정자를 사용 해야만 할 때이다.      
		typename D<T>::E e;

		// D<T>::zero() 라고 호출하면 가상 함수를 호출 할 수 없다. // 그러므로 this를 사용 한다.      
		this->zero();

		// e가 종속적인 데이터이므로 one은 자동적으로 종속적인 함수가 되므로, 기반 클래스 템플릿에서 찾을 수 있다. 
		one(e);
	}
};

int main(void) {
}

//using을 사용 할 때 주의해야 할 점
//		바로 다중 상속을 할 경우, 동일한 이름이 있을 때, 원하는 것을 정확하게 선택하는 것을 프로그래머의 몫

template <typename T> class Base1
{
public:
	int basefield;
};
template <typename T> class Base2
{
public:
	int basefield;
};
template <typename T>class DD3 : public Base1<T>, Base2<T>
{
public:
	// 이렇게 using을 사용하여 가시화 시킨다.    
	using Base1<T>::basefield;
	//using Base2<T>::basefield;     
	void f()
	{
		basefield = 0;
	}
};
int main(void)
{
	DD3<int> d;    d.f();
}
