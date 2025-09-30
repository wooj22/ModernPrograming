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

//consteval / constexpr와의 차이점
// 
//항목		constexpr								consteval
//도입시기	C++11									C++20
//의미		"컴파일 타임 가능하면 계산"				"컴파일 타임 무조건 계산"
//실행시점	컴파일 타임 or 런타임(조건에 따라 다름)	반드시 컴파일 타임
//사용용도	함수, 변수, 생성자 등						함수만 가능
//실패 시	런타임 실행 가능							컴파일 오류 발생

//consteval 함수는 내부에서 constexpr 함수 호출 가능, 반대는 불가능
 
//consteval 이 필요한 경우
// 
//	값이 컴파일 타임에 항상 있어야 하는가 ? (예: 템플릿 인자, 배열 크기)
//	안전하고 강제적인 정적 검증이 필요한가 ?


//constinit --------------------------------------------------------------------------
// 
//      컴파일 시간에 static 변수가 초기화되도록 강제함.
//      전역 변수도 해당

//  기존의 static 변수들은 초기화 순서가 정해져 있지 않아
//  static 변수들끼리 서로 참조를 하는 것은(한쪽이 일방적으로 참조를 하는 경우도 포함합니다.)
//  UB(unspecified behavior) 였습니다.
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



/*
//C++20 - consteval, constinit   //테스트 필요함
//참고 https://blog.naver.com/kmc7468/221705880457

//C++20
//	    constexpr vector
//	    constexpr string
//	    constexpr new
//	    constexpr 소멸자


//C++20부터는 
//표준 라이브러리의 주요 컨테이너인 std::vector와 std::string이 constexpr을 지원하게 되었습니다. 
//즉, 이제 std::vector를 컴파일 타임 상수 표현식으로 사용할 수 있습니다. 
//이는 C++에서 컴파일 타임 프로그래밍의 범위를 크게 확장시킨 중요한 변화입니다.

#include <vector>

constexpr std::vector<int> createVector() {
	std::vector<int> vec;
	for (int i = 1; i <= 5; ++i) {
		vec.push_back(i * i);
	}
	return vec;
}

int main()
{
	constexpr auto vec = createVector();
	static_assert(vec.size() == 5, "벡터 크기는 5이어야 합니다.");
	static_assert(vec[2] == 9, "세 번째 요소는 9이어야 합니다.");
}

//주의)
//constexpr vector가 동작하려면, 관련 함수와 연산이 모두 constexpr로 선언되어야 합니다.
//컴파일 타임에 할당 가능한 메모리 크기에는 한계가 있


//constexpr new
//
//	C++20 이전에는 constexpr 함수 내에서 동적 메모리 할당(new)을 사용할 수 없었습니다.
//	C++20부터는 constexpr new가 도입되어, 컴파일 타임에도 동적 객체 생성을 할 수 있게 되었습니다. 즉, constexpr 컨텍스트에서 new 연산자를 사용할 수 있습니다.
//	이로 인해, 더 복잡한 컴파일 타임 연산과 객체 생성을 지원할 수 있게 되었고, constexpr 함수의 활용 범위가 크게 넓어졌습니다.


//constexpr 소멸자
//
//	C++20부터는 소멸자(Destructor)도 constexpr로 선언할 수 있습니다.
//	즉, 객체가 컴파일 타임에 소멸될 때, 소멸자 코드가 실행될 수 있습니다.
//	이 기능은 컴파일 타임에 리소스 정리, 메모리 해제, 기타 마무리 작업이 필요한 경우에 유용합니다.
//	예를 들어, 컴파일 타임에 동적으로 할당한 메모리를 해제하는 코드가 소멸자에 들어 있을 때, 이 소멸자가 constexpr로 선언되어 있으면 컴파일 타임 평가 시점에 소멸자가 자동으로 호출됩니다.

*/