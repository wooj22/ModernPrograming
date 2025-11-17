// auto 변수 
//		C++ 11에서 타입 추론 
//		변수의 자료형을 컴파일 시간에 자동으로 추론
// 
//		C++ 복잡한 타입의 사용을 자동화하여 편리하게 사용
//		하지만, 어떻게 추론되는지를 잘 알아야 함.

#include <iostream>
#include <vector>
using namespace std;

void main()
{
	double d = 5.0;			// Type과 Value 가 같아야 하는 것이 원칙 - 오류 체크가 쉬워진다.
	auto d2 = 5.0;			// 5.0 is a double literal, so d will be type double 

	auto i = 1 + 2;			// 1 + 2 evaluates to an integer, so i will be type int

	// 타입 추론

	auto n = 0.123;						//자료형은?  //0.123f 로 변경한다면?
	int size = sizeof(n);				//바이트수 확인
	std::cout << n << " " << size << std::endl;	//출력은 ???

	unsigned char x = 1;
	auto ax = x;						//컴파일 타임에 자료형 결정된다.
	ax = 1.3;
	printf("%d %f \n", x, ax);			//출력은 ???   //%f 값 할당 안됨


	//auto 키워드
	//	  자료형을 추론합니다. 
	//    실제 자료형은 '컴파일'하는 동안 결정됩니다. 따라서, 반드시 auto 변수를 초기화해야 됩니다.
	// 
	//	  C#, JavaScript, Python 등의 언어에 있는 동적인 타입과는 다릅니다.	
	//    일반적인 자바스크립트와 파이썬과 활용하는 방식은 비슷하지만, 
	//    자료형이 바뀌지는 않으므로 유의해야 합니다.

	auto an;							//error   //추론할 수 없음 ***

	const int& a = 0;
	auto aa = a;						//aa 자료형은?   //int - const, & 무시 ***

	//cf) typeid(변수이름).name()을 사용하면 자료형을 확인할 수 있다. 런타임에 타입을 알아냄. 정확하지 않음


	//문제) auto 로 선언된 변수의 자료형은 ? ---------------------------------------

	auto a{ 1 };							// int
	auto c = "abc";							// const char*
	auto b = { 1, 2, 3, 4 };				// initializer_list<int>
	auto f1 = { 1 };						// initializer_list<int>
	auto f2{ 1 };							// int
	std::string g = { "abc" };				// std::string
	auto h = g.begin();						// std::string::iterator

	class Base {};
	auto base1 = new Base();				// Base*
	auto* base2 = new Base();				// Base*

	int ff;
	int& r = ff;
	auto rr = r;							// int
	const auto& cc = ff;					// const int&
}


//auto로 포인터와 참조 받기 --------------------------------------------------------------
//		auto를 사용하며 포인터와 참조를 받을 수 있습니다.
//
// 		포인터를 받을 떄       : auto / auto *			//둘다가능
//  	참조로 받을 떄는 명시  : auto&					//***

class Cat {
	string	name = "";
	int		age = 0;
public:
	Cat(string s, int n) { name = 5; age = n; }
};

{
	Cat* myCat = new Cat("CoCo", 2);
	auto	myCatPtr1 = myCat;			//자료형은? Cat*
	auto* myCatPtr2 = myCat;			//자료형은? Cat*
	//myCat과 myCatPtr은 동일한 포인터의 값을 갖습니다.컴파일러가 어느 형인지 알아낼 수 있기 때문입니다.
	//다만, 가독성이 떨어질 수 있습니다. 따라서 포인터 형을 받을 떄는 auto* 을 활용하는게 좋다.

	Cat myCat2("Coco", 2);
	Cat& myCat2Ref = myCat2;
	auto	CatRef1 = myCat2Ref;		//Cat
	auto& CatRef2 = myCat2Ref;		//Cat&
	//auto로 참조도 받을 수 있다면 받는게 참조인지 아닌지 컴파일러가 구분할 수 없습니다.
	//따라서, 다른 참조 복사를 하기 위해서는 auto& 를 확실하게 선언해주어야만 합니다.
}

//auto& 로 const 받기
const int b = 1;
auto& a1 = b;				// const int&
const auto& a2 = b;			// const int&

//auto& 는 const를 이어 받습니다.컴파일러가 알아낼 수 있기 떄문입니다.
//하지만, const인지 아닌지, 개발자가 구별하기 어려워, 가독성이 떨어질 수 있습니다.
//따라서, const 참조를 받을 떄는 const auto& 를 직접적으로 선언하여 활용하는 것이 좋다.


// auto 키워드가 매우 유용한 경우 ---------------------------------------------------

//auto와 함수 반환형

	//   auto 키워드는 함수가 반환하는 걸 저장하는 데 때론 유용합니다.
	//   함수 반환형이 변해도 auto는 그대로 활용되기 때문입니다.
	//   개발시에, 반환형이 바꾸어져도 auto는 바꾸어질 필요가 없습니다. 

//auto와 반복자 - 반복자에는 auto 키워드가 매우 유용합니다.

#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<int> v = { 1,2,3,4,5 };
	for (auto it = v.begin(); it != v.end(); ++it) {}
}
//반복자를 직접 구현해서 for문을 돌리는 것은 매우 골치 아픕니다. 
//만약 map을 for문에는 더더욱 골치아픕니다.
//이러한 것들을 auto를 활용하면 타이핑도 줄이고, 매우 간결해집니다.

//auto와 템플릿 - 일부 템플릿에서도 마찬가지입니다

MyArray<int>* a = new MyArray<int>(10);    //MyArray<int>의 포인터

auto* a = new MyArray<int>(10);
//누가 보아도 알 수 있는 타입인지 알 수 있는 경우에는 auto를 활용해도 무방하다고 할 수 있습니다.


//auto변수로 인해 c++에서는 보다 유연한 코드 작성이 가능하게 되고,

	//특히, 
int (*funcPtr)(int, int);
//와 같이 선언하기도 귀찮은 함수 포인터형을 사용하고 싶을때는,위와 같은 귀찮은 선언을 할 필요가 없이,
auto funcPtr = TestFunc;
//와 같이 함수 이름만 대입해주면 auto 변수가 저절로 해당 함수 포인터형이 되는 것이다.


// auto 키워드 사용시 주의사항 ---------------------------------------------------
// 
//		auto 키워드가 타이핑을 확실히 줄여줄 수 있습니다. 허나 '가독성'을 떨어트릴 수 있습니다.
// 
//		auto에 관해서는 모두가 동의하는 '코딩 표준'이 존재하지는 않습니다. 
//		코딩 표준에서는 auto 보다 실제 자료형을 선호합니다. ***

//auto보다 실제 자료형 사용을 권장합니다.
// 
//		다만, 템플릿 매개변수와 반복자에는 auto를 사용합니다.
//		포인터에서는 auto 보다 auto* 를 사용하고 
//		const 참조에서는 auto& 보다 const auto& 를 사용하도록 합니다.
//		전부 가독성과 관련된 내용들이라고 할 수 있습니다.
//		auto를 사용해도 런타임 성능은 동일합니다. ***
