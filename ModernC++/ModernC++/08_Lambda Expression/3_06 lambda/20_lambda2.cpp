/*
람다식 구조

		[capture list] (받는 인자) -> 리턴 타입 { 함수 본체 }    ( 호출시 사용 )
		
		[] () -> return type { }
     	[](int i) -> bool { return false; } ;

	[] : 캡쳐 리스트, 외부변수를 참조함
	() : 인자, 함수의 인자와 동일
	mutable : 캡쳐의 값으로 넘어오는 변수를 변경 가능하게 함. 기본형은 값을 바꿀 수 없음. (constexpr)
	throw() : 예외처리
	-> type : 반환형
	{} : 실행될 코드

인자목록:
	기본적으로 생략 가능하고 생략하면 전달 인수는 없다는 뜻이다. 사용하는 경우 인수 전달 값과 매치된다.

리턴타입:
	리턴타입은 생략 가능하고 생략했을 시, { } 내부에서 리턴되는 타입이 자동으로 리턴타입이 된다.

캡쳐블록:
	외부 변수를 사용(캡쳐)한다. 
	외부 변수란 람다식이 포함된 scope의 변수를 의미한다.
	내부에서 수정 불가, 단 &를 붙이면 참조 형식으로 불러오고, 안에서 수정이 가능.

	[x]  : x 라는 외부 변수를 람다식에서 사용하겠다 (value 캡쳐) - 수정 불가
	[&x] : x 라는 외부 변수를 람다식에서 사용하겠다 (reference 캡쳐)
	[=] : {} 사이의 모든 variables를 value로 캡쳐.
	[&] : {} 사이의 모든 variables를 reference로 캡쳐

	= 를 쓰면, 명시되어있는 변수들을 제외하고 
		외부 변수를 값을 복사하는 형식으로 가져와서 사용할 수 있게 한다.
		( = 를 쓰게 된다면, 명시된 변수들은 항상 reference 캡쳐여야 한다.)
    & 를 쓰면, 명시되어있는 변수를 제외하고 
		외부 변수들을 레퍼런스 타입으로 불러온다. 
		( & 를 쓰게 된다면, 명시된 변수들은 항상  value 캡쳐여야 한다.)
예제)
	//캡쳐 목록(capture list)을 사용해서 외부 변수에 접근
	[]		: 아무것도 캡쳐 안함
	[a]		: a 라는 변수를 Value 로 캡처
	[&a]	: a 라는 변수를 Reference 로 캡처
	[&a, b] : a 는 레퍼런스로 캡쳐하고 b 는(변경 불가능한) 복사본으로 캡쳐
	[=]		: 외부의 모든 변수들을 복사본으로 캡쳐
	[&]		: 외부의 모든 변수들을 레퍼런스로 캡쳐

	[=, &x, &y] : 기본적으로 { } 사이의 모든 variable의 value를 캡쳐하되, x, y는 refrence
	[&, x]		: 기본적으로 { } 사이의 모든 variable의 reference를 캡쳐하되, x는 value
	[&, &x]		: 구문 오류 ***
	[this]		: 객체를 접근하는 것으로, this->가 없어도 동작한다.

	(C++17) [*this] : 현재 객체의 복사본을 갭처. 람다 표현식을 실행하는 시점에 객체가 살아 있지 않을 때 유용

	(C++20) [=, this] : this 포인터를 명시적으로 캡처하고, 나머지는 값으로 캡처.
		C++20 이전에는 [=]로 지정하면 암시적으로 this 포인터를 캡처했지만, C++20에서 이 기능은 폐기되었습니다.
		만약 필요하다면 명시적으로 this 를 캡처해주어야 합니다.
*/


//캡쳐블록 ------------------------------------------------------

//value 캡쳐, reference 캡쳐

#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
	int n = 2;

	auto add = [n](int x, int y) { return x + y + n; };		//value 캡쳐    //외부 변수 n

	//auto add = [&n](int x, int y) { return x + y + n; };	//reference 캡쳐

	n = 3;

	cout << add(1, 2) << endl;  // ???
}

// 람다 실행하기
//			[Capture_Variables ](Parameters)->Return_Type{ Body }

#include<iostream>
#include<string>
#include <functional>
using namespace std;

int main()
{
	auto a1 = 3;

	auto lamda = [](int i) -> bool { return false; };		// 람다 객체
	cout << (lamda(2) ? "TRUE\n" : "FALSE\n");				// 함수처럼 실행

	[]() -> void { cout << "Hello World" << endl; } ();		// 람다 + ()			//void

	cout << []() -> string { return "Hello "; } ();			// 람다 + ()			//string
	cout << endl;

	cout << [a1]() { return a1 + 1; }();					//value 캡쳐 + ()
	cout << endl;

	cout << [&a1](auto i) {	a1 = i;	return a1; }(11);		//reference 캡쳐 //매개변수에 auto 사용 가능
	cout << endl;
	

	//람다 표현식은 일종의 함수라 볼 수 있다.( Callable )
	//함수와 같이 <functional>의 function<> 을 사용할 수 있다.
	//function 변수 선언을 통해 함수의 매개변수로 전달하거나 반환이 가능.

	function<int(void)> func = []()->int {return 0; };
	cout << func();

	// Hello World 를 리턴하는 함수를 람다로 만들고, 실행하여 출력하여 보세요.
	cout << []() { return "Hello World"; } () << endl;

	return 0;
}

/*
//람다 표현식은 일종의 함수라 볼 수 있다.( Callable )
//함수와 같이 <functional>의 function을 사용할 수 있다.
//function 변수 선언을 통해 함수의 매개변수로 전달하거나 반환이 가능.

	function< 함수형식 > 변수명 = 함수;
	
	함수형식 = 반환형(입력형식)

	예) bool foo1(int a) { return true; }		// bool(int)
	예) void foo2(int a, int b) { }				// void(int,int)
	예) string foo3(float a, double b) { }		// string(float,double)

	// 위 함수를 람다함수로 변형하여 function 변수에 담아 보세요.

	function<int(void)> func = []()->int {return 0; };	
	cout << func();

//연습

	// 변수 level 이 
	// 10보다 크면 true 아니면 false 리턴하는 함수를 람다로 만들고, 
	// 실행하여 출력하라.
	int level = 11;

		//[](int n) { if (10 > n) return true; else return false; }
		bool b = [](int n) { return n > 10; } (level);
		cout << b << endl;


	// number 변수에 정수를 입력 받아,  10보다 크면 출력하는 함수를 만들고 실행하라.
	int number;
	cin >> number;

		//[](int n) { if (n > 10) cout << n << endl; }(level);
		[number]() {if (number > 10) cout << number << endl; } ();

*/

