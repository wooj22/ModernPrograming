// spaceship operator 활용
// 
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

	std::strong_ordering result = myInt1.value <=> myInt2.value;
	if (result < 0)		 cout << "myInt1 < myInt2" << '\n';
	else if (result > 0) cout << "myInt1 > myInt2" << '\n';
	else				 cout << "myInt1 == myInt2" << '\n';
}
