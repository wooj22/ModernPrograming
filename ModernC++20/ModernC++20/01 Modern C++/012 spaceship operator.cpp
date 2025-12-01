//우주선 연산자 ( Three-way comparison )		//C++20
//		정식명칭은 "SpaceShip (Three-way Comparison) operator"
//		3중 비교 연산자
//		객체 간의 모든 비교(<, <= , >, >= , == , != )를 한 번에 처리할 수 있도록 만든 연산자
//	
//	이 연산자는 ( a <=> b ) 라고 주어졌을때,
//	a와 b가 같은지, 다른지, a가 큰지 b가 작은지 등등 값의 대소와 값비교를 
//  한번에 다 해버릴 수가 있습니다.


#include <iostream>
#include <compare>
using namespace std;

int main()
{
	auto n{ 10 }, m{ 20 };
	auto result{ n <=> m };

	if (result < 0)			std::cout << "n < m" << std::endl;
	else if (result > 0)	std::cout << "n > m" << std::endl;
	else if (result == 0)	std::cout << "n == m" << std::endl;

	//-------------------------------------

	auto x{ 3 <=> 3 };				// 1, 0, -1  //strcmp()
	cout << std::boolalpha << (x < 0) << endl;
	cout << std::boolalpha << (x == 0) << endl;
	cout << std::boolalpha << (x > 0) << endl;
}


//	반환값 : strong_ordering 구조체  

#include <iostream>
using namespace std;

void SpaceShip()
{
	auto item = 5 <=> 4;			// std::strong_ordering

	std::cout << std::boolalpha << std::is_lt(item);
}

int main()
{
	SpaceShip();	//5가 4보다 크므로, 결과값은 "false"
}

//std::is_eq   : a == b 일때 참
//std::is_neq  : a != b 일때 참
//std::is_lt   : a < b  일때 참
//std::is_lteq : a <= b 일때 참
//std::is_gt   : a > b  일때 참
//std::is_gteq : a >= b 일때 참

//---------------------------------------------------------------------

int main()
{
	int a, b;
	std::cin >> a >> b;
	
	auto r = (a <=> b);					//
	//a < b일 경우 r < 0 
	//a = b일 경우 r = 0 
	//a > b일 경우 r > 0
	
	//결과를 출력해 보세요
	std::cout << std::boolalpha << std::is_eq(r) << " ";
	std::cout << std::boolalpha << std::is_neq(r) << " ";
	std::cout << std::boolalpha << std::is_lt(r) << " ";
	std::cout << std::boolalpha << std::is_gt(r) << " ";
}


//C++의 우주선 연산자를 사용하면 
//		객체 간의 순서와 평등을 표현할 수 있을 뿐만 아니라, 
//		관계의 특성도 표현할 수 있습니다. 

//반환값 : strong_ordering, weak_ordering, partial_ordering

//comparison categories(비교 범주)
// 
//  strong_ordering : 엄격한 순서(strict total ordering), 모든 비교 결과가 항상 결정적이고 대칭적임을 보장합니다.
//		결정적(deterministic): 모든 값은 항상 서로 비교 가능한 상태이며, 비교 결과가 일관됩니다.
//		대칭적(symmetric): 값 A와 B에 대해, A < B 또는 B < A 또는 A == B 중 하나만 참입니다.
//		정렬에 적합: 이 구조체는 정렬 알고리즘에서 안전하게 사용할 수 있습니다.
//		ex) std::sort 또는 std::set, std::map과 같은 컨테이너에서 사용
// 
//  weak_ordering : 동등(equivalent)의 개념을 지원, 보다 느슨한 조건의 순서 비교를 제공합니다.
//		순서만 유지될 수 있으면 되며, 엄격히 같을 필요는 없습니다.
//		== 대신 동등성을 나타내는 개념이 적용, 두 값이 같지 않더라도 비교에서 동일한 순서로 처리될 수 있습니다.
//		ex) 대소문자를 무시한 문자열 비교(예: "Hello"와 "hello"는 동등함).
// 
//  partial_ordering : 모든 값이 비교 가능하지 않을 수 있습니다.
//		비교 불가능(unordered)한 상태를 나타낼 수 있습니다.
//		ex) 부동소수점 비교와 같이 비교 불가능한 값이 존재하는 경우.
 
//	strong_ordering - 1. 정사각형 - operator==는 '동등' 모형화 아닌, 완벽한 '동등' 이라는 뜻  
//	weak_ordering   - 2. 직사각형 - operator==는 완벽한 '동등'이 아닌 '동등'을 모형화 한다 
//  partial_ordering 은 float 타입의 'NaN' 같은것도 허용한다는 점에서 weak_ordering보다 약합니다.

//	Conversions(변환)
// 
//  std::strong_ordering 은 세 가지 비교 범주 중 가장 강력합니다.
//  다른 범주에서 암시적으로 변환할 수 없고 다른 두 범주로 암시적으로 변환할 수 있습니다.
//
//  std::strong_ordering 은 weak_ordering 으로 암시적으로 변환할 수 있는 반면 
//  std::weak_ordering 은 암시적으로 std::partial_ordering 으로 변환할 수 있습니다.


//클래스 코드 작성 ------------------------------------------------------------------
//	연산자 오버로딩을 통하여 3방향 연산자를 제공할 수 있습니다.

	struct foo 
	{
		int i;

		std::strong_ordering operator<=> (const foo& other) {
			return i <=> rhs.i;
		}
	};

	//auto나 default 키워드가 가능합니다.

	struct MyInt {
		int value;
		explicit MyInt(int val) : value{ val } {}
		auto operator<=>(const MyInt& other) const {
			return value <=> other.value;
		}
	};
	struct MyDouble {
		double value;
		explicit constexpr MyDouble(double val) : value{ val } {}
		auto operator<=>(const MyDouble&) const = default;
	};

	//MyInt와 MyDouble은 둘 다 잘 동작합니다. 그러나 ordering의 차이가 있습니다.
	//
	//	MyInt    의 경우, strong_ordering입니다.
	//	MyDouble 의 경우, partial_ordering입니다.


// 클래스에서 사용하면 편리 ----------------------------------------------------

//c++20 이전에는 == , != , > , >= , < , <= 연산자 중에 하나라도 정의 했다면 
//  나머지 관계들도 모두 정의 해야합니다.
//
//c++20 부터는 
//  3중 비교 연산자를 직접 정의 하거나 
//  = default 를 사용해서 컴파일러에 의해 생성된 연산자를 사용할 수 있다.

/*
	class MyClass
	{
	public:
		MyClass();

		bool operator==(const MyClass& rhs);	//선언만, 정의는 별도
		bool operator!=(const MyClass& rhs);
		bool operator<(const MyClass& rhs);
		bool operator>(const MyClass& rhs);
		bool operator<=(const MyClass& rhs);
		bool operator>=(const MyClass& rhs);
	}

	class MyNewClass
	{
	public:
		auto operator<=>(const MyNewClass&) const = default;	//하나로 끝
	}
*/

// 예시 ----------------------------------------------------------
#include <iostream>
#include <compare>

class Data {
public:
	int var1;
	int var2;
	auto operator<=>(const Data&) const = default;
};

int main()
{
	Data d1{ 10, 20 }, d2{ 30, 40 };

	if (d1 < d2)	 // <=, >, >=, ==, !=, <=> 모두 사용 가능
		std::cout << "d1 < d2" << std::endl;
}

// 예시 ----------------------------------------------------------
#include <iostream>
#include <compare>

using namespace std;

struct MyInt {
	int value;
	explicit MyInt(int val) : value{ val } {}

	auto operator==(const MyInt& rhs) const { return value == rhs.value; }

	// 3중 비교 연산자에 대한 명시적 선언
	auto operator<=>(const MyInt& rhs) const {
		return value <=> rhs.value;
	}
};

struct MyIntDefualt {
	int value;
	explicit MyIntDefualt(int val) : value{ val } {}

	// 3중 비교 연산자에 대한 암시적 선언
	auto operator<=>(const MyIntDefualt& rhs) const = default;
};

int main()
{
	cout << boolalpha;

	MyInt myInt1(2017);
	MyInt myInt2(2020);

	cout << (myInt1 < myInt2) << '\n';  // true
	cout << (myInt1 > myInt2) << '\n';  // false
	cout << (myInt1 == myInt2) << '\n';  // false

	MyIntDefualt myIntD1(2017);
	MyIntDefualt myIntD2(2020);
	cout << (myIntD1 < myIntD2) << '\n';  // true
	cout << (myIntD1 > myIntD2) << '\n';  // false
	cout << (myIntD1 == myIntD2) << '\n';  // false
}

//장점)
//	코드 간결화 : 비교 연산자 6개를 일일이 구현할 필요 없음
//	멤버 기본 비교 자동 생성(= default)
//	타입 안전 : 다른 타입 비교는 컴파일 에러
//	std::sort, STL 알고리즘과 자연스럽게 호환
// 
//주의)
//	floating - point 멤버가 있으면 partial_ordering 필요(NaN 처리)
//	default 순서는 멤버 선언 순서
//	구조체 내 사용자 정의 비교 연산자가 존재하면, default와 충돌할 수 있음