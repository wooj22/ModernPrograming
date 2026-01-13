// 우주선 연산자
// 
// MyInt 클래스의 객체를 비교하려고 합니다.
// 삼항 비교연산자 <=> 를 지원해서, 아래 오류를 수정하세요.

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

	auto result = myInt1.value <=> myInt2.value;

	cout << (result < 0) << '\n';		// true
	cout << (result > 0) << '\n';		// false
	cout << (result == 0) << '\n';		// false
}
