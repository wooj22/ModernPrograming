// MyInt 에 대하여 비교연산자를 지원해서 오류를 수정하세요.
//	C++17 이하 : 개별 비교 연산자를 명시적으로 정의.
//	C++20 이상 : 삼항 비교 연산자를 사용해 간결한 코드를 작성.

#include <iostream>
#include <compare>

using namespace std;

struct MyInt {
	int value;
	explicit MyInt(int val) : value{ val } {}	
};

int main()
{
	cout << boolalpha;

	MyInt myInt1(2017);
	MyInt myInt2(2020);

	cout << (myInt1 < myInt2) << '\n';		// true
	cout << (myInt1 > myInt2) << '\n';		// false
	cout << (myInt1 == myInt2) << '\n';		// false
}


// 비교 연산자 구현
//bool operator<(const MyInt& other) const { return value < other.value; }
//bool operator>(const MyInt& other) const { return value > other.value; }
//bool operator==(const MyInt& other) const { return value == other.value; }

// 삼항 비교 연산자
//auto operator<=>(const MyInt& rhs) const = default;