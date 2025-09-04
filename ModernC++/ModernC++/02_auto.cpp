#include <iostream>
using namespace std;

void TestFunc(int) {}

void main(void)
{
	//auto ------------------------------------------  
	//auto 키워드를 사용하면 초깃값의 형식에 맟춰 선언하는 인스턴스(변수)의 형식이 '자동'으로 결정된다

	//초기화 -----------------------------------------
	int a = 1;
	int a(1);				//C++
	int a{ 1 };				//C++11
	int b(a);				//copy
	int(10);				//이름없는 인스턴스

	auto c(a);				// int
	//auto c = a;

	int x = int();			// x is an int, initialized to 0
	auto auto_x = x;


	//auto 키워드는 포인터와 참조자를 붙일 수 있다. ----------------------------------------------
	int n = 1.2;
	auto& b = n;			// &, * 는 cv 그대로 추정. 
	auto* c = &b;			// 포인터는 * 붙이지 않아도 인식, 참조자는 붙여야만 참조로 인식


	// 연습)  Widget 클래스 객체를 auto 포인터나 참조로 받아 type 확인하기.

	class Widget {
	public:
		void Fn() {}
	};

	Widget x;

	// 아래 선언된 자료형을 추론해 보세요.

	auto o = x;				// (  )				//Widget  

	auto* a1 = &x;			// (  )				//Widget* 
	auto  a2 = &x;			// (  )				//Widget* 
	a2->Fn();

	auto& r1 = x;			// (  )				//Widget&   //참조로 받으려면 선언해야 함. 
	auto r2 = x;			// (  )				//Widget  	
	r1.Fn();



	//타입 추론(type inference)-----------------------------------------------------------------
	//1. auto 경우에는				-> &, const volatile 같은 추가 지정은 읽지 않는다.

	const int& crx = x;
	auto auto_crx1 = crx;				//???
	//const auto& auto_crx2 = crx;
	volatile int vx = 1024;
	auto avx = vx;						//???
	//volatile auto vavx = vx;

	//auto로 포인터 받을 경우에는		-> *, const 를 다 읽어들인다 ***
	int i = 40;
	const int* pi = &i;
	auto p = pi;

	//타입 추론(type inference)-----------------------------------------------------------------
	//2. auto& 경우에는				-> & 무시, const 읽는다. 가독성 위해 const 쓰자.

	const int c = 0;
	auto& rc = c;						//??? //const int&


	//타입 추론(type inference)-----------------------------------------------------------------
	//3. auto&& 경우에는 				-> 좌측값은 &로 우측값은 &&로 받는다 (보편 참조)

	int d = 10;
	//auto& r = d;						//int&

	auto&& r1 = 5;						//int&&		//우측값
	auto&& r2 = d;						//int&		//좌측값
	auto&& r3 = std::move(d);			//int&&		

	// rvalue 참조와 보편 참조는 아래 참고


//r-value 참조 -------------------------------------------------

	int d = 10;
	int& r = d;				//참조
	int&& r1 = 5;			//임시객체에 대한 참조, 상수
	int&& r2 = r;			//error //move() 사용


///보편 참조(universal reference)
//		전달되는 매개변수에 따라 왼 값 또는 오른 값 참조로 작동할 수 있다.
//		오른 값 참조와 보편 참조의 가장 큰 차이는 형식(type)을 추론하는지의 여부다.

	void f(Widget&& param);				//-- 1 오른값 참조

	Widget&& var1 = Widget();			//-- 2 오른값 참조

	auto&& var2 = var1;					//-- 3 보편 참조		auto&&

	template<typename T>
	void f(std::vector<T>&& param);		//-- 4 오른값 참조

	template<typename T>
	void f(T&& param);					//-- 5 보편 참조		T&&


}

//auto 활용 --------------------------------------------------------------------------------

	//1. 함수를 받을 때 편리하게 사용 

void(*pfTest)(int) = TestFunc;		//함수포인터 객체

auto pfTest(TestFunc);				//형 자동 설정
//auto pfTest = TestFunc;	
//auto* pfTest = TestFunc;


//2. 배열이나 벡터 처리할 때 편리하게 사용 

int buffer[5] = { 0,1,2,3,4 };

for (auto i : buffer)				//형 자동 설정 //범위기반 for문
{
	cout << i << endl;
}

//3. 아래와 같이 for문에서 auto를 사용해 자료형을 추론해 출력할 수 있다.
auto arr = { 1, 2, 3, 4 };				// arr의 자료형은?

for (auto number : arr)				// 범위기반 for문
std::cout << number << '\n';

// 함수에서 auto 사용 -----------------------------------------------------------------------

	//함수의 반환 값
	//	변수를 함수의 반환 값으로 초기화 할 때도 사용 가능  //생성 시 변수를 초기화할 때만 작동

int add(int x, int y) { return x + y; }
auto sum = add(5, 6);

//C++ 14에서 함수를 위한 타입 추론 ***
//	C++ 14는 auto 키워드가 함수의 반환 타입을 자동으로 추론할 수 있도록 확장되었다.
auto Add(int x, int y) { return x + y; }		//다만 주의해서 사용, 오용 우려

//매개 변수 ?
//	auto 키워드는 함수 매개 변수와 함께 사용할 수 없다.	***

void addAndPrint(auto x, auto y) { std::cout << x + y; }


// 구조체,클래스에서 auto 사용 ---------------------------------------------------------------

	//auto 키워드는 구조체나 공용체, 클래스도 가능하다.

class MyClass {
public:
	int n = 0;
};

void main() {
	auto x = MyClass();     //MyClass
}

//멤버 변수는?
//		구조체나 클래스의 멤버 변수로는 사용 불가  *** 
//		(해당 객체 자료형 크기를 모르기 때문)

class MyClass {
public:
	auto n = 0;
};


// 람다식에 대한 auto 사용 -----------------------------------------------------------------------

#include <iostream>
using namespace std;

int main()
{
	auto test1 = [](int* a)->int& {return *a; };			//int& 리턴
	auto test2 = [](int* a) { return *a; };					//int 리턴

	int* p = nullptr;
	auto f1 = test1(p);			// f1의 자료형은 ???
	auto& f2 = test1(p);

	//함수
	//1. 참조자 리턴 시
	//				함수의 인자가 속한 괄호에 -> 를 명시해주고 리턴자료형 &를 붙여줌
	//2. 참조자 외에는
	//				자료형을 명시하지 않아도, return값을 기준으로 auto 자동으로 리턴자료형을 판단함

	return 0;
}


//auto 람다 함수는 파라미터에 auto를 사용할 수 있다. (일반 함수들에서는 파라미터에 auto를 못쓴다) ***
{
	// generic lambda
	auto func = [](auto x, auto y) {return x + y; };
	cout << func(1.1, 5) << "  " << func(3.7, 23.1) << '\n';

	//제네릭 람다, 템플릿 람다 참고
