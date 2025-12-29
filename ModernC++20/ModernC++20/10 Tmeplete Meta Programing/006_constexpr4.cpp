//consteval --------------------------------------------------------------------------
// 
//      함수를 컴파일 시간에만 평가할 수 있는 함수로 바꿈

//  기존의 constexpr 함수들은 
//      함수가 컴파일 시간에 평가될 수도 있었지만, 런타임 때 평가될 수도 있었다.
//      consteval 함수들은 반드시 컴파일 시간에만 평가될 수 있는 함수가 됩니다.

#include <iostream>

constexpr int f(int x) {
    return 5 * x;
}
consteval int g(int x) {
    return 5 * x;
}

constexpr int a = f(5); // OK
constexpr int b = g(5); // OK

int main() {
    int input;
    std::cin >> input;

    int c = f(input); // OK
    int d = g(input); // Error
}

// constexpr , constexpr const -----------------------------------------------------------------

#include <iostream>
using namespace std;

int main()
{
	static size_t sz = sizeof(constexpr int); // 오류, constexpr int는 타입이 아닙니다.

	constexpr char* str = "Hello";		// 오류: "Hello"를 char *로 캐스팅 할 수 없습니다.
	constexpr const char* str = "Hello"; // 정상

	static int a = 0;
	constexpr int& ra = a; // 정상

	static const int b = 0;
	constexpr int& rb = b; // 오류, const int를 int&로 캐스팅 할 수 없습니다.

	class T;
	const T f();
	constexpr T(*pf)() = f;			// 오류: const T()를 T(*)()로 캐스팅
	constexpr const T(*pf)() = f;		// 정상


	//결론
	//	const 와 constexpr 이 같이 지정되어도 constexpr 하나와 같다.
	//	constexpr 지정자 specifier의 대상은 type이 아니라 변수 자체이다. ***

	return 0;
}


https://blog.naver.com/kmc7468/221705880457

//C++20 - consteval, constinit   //테스트 필요함
//C++20
//	    constexpr vector
//	    constexpr string
//	    constexpr new
//	    constexpr 소멸자


//constinit --------------------------------------------------------------------------
//
//      컴파일 시간에 static 변수가 초기화되도록 강제함.
//      전역 변수도 해당

//  기존의 static 변수들은 초기화 순서가 정해져 있지 않아
//  static 변수들끼리 서로 참조를 하는 것은(한쪽이 일방적으로 참조를 하는 경우도 포함합니다.)
//  unspecified behavior 였습니다.
//
//  반드시 컴파일 시간에 초기화 되도록 강제하므로 이런 문제 해결
//  상수성을 가지고 있을 것 같지만 그렇지 않다.

static constinit int a = 5;
static const constinit int b = 5;
static const constinit int c = a;   // Error

static int d = 5;
static int e = d; // UB?

int main() {
	a = 4; // OK
	b = 4; // Error
}

//전역 변수나 static 객체는 두 단계로 초기화될 수 있습니다.
//	정적 초기화(compile - time)
//	동적 초기화(runtime, main 이전 실행) ← 문제의 근원
//	constinit을 쓰면 2번이 발생하면 컴파일 에러가 납니다.

//const, constexpr, constinit 차이
// 키워드			의미
// const			수정 불가(초기화 시점은 상관없음)
// constexpr		컴파일 타임 평가 가능 + 상수 표현식
// constinit		컴파일 타임 초기화 강제 (상수일 필요는 없음)
