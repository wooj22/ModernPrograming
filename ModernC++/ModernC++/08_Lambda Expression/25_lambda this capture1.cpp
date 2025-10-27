// this, *this 캡처 ----------------------------------------------------

// this
//		C++11 캡처리스트에 this 는 람다식이 속하는 클래스 오브젝트가 참조로 캡처된다.
// *this
//		C++17에서 추가된 *this 로 복사 캡처 가능

//C++17에서는 [=, this]를 사용하면 this가 이미 캡처된 상태이기 때문에 오류.
//
//하지만 this를 캡처하는 것을 명시하면 가독성 개선에 도움이 되기 때문에 
//C++20부터는 [=, this]가 허용된다. ***

/*
	struct S { void f(int i); };

	void S::f(int i) 
	{
		[&, i] {};      // OK
		[&, &i] {};     // ERROR: i preceded by & when & is the default
		[=, this] {};   // ERROR: this when = is the default   //C++20 허용
		[=, *this] {};  // OK: captures this by value. See below.
		[i, i] {};      // ERROR: i repeated
	}
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

struct Test {

	int N = 7;

	auto AddNum1() {
		[this] () { N += 10; } ();				// this  참조이므로 N 은 변경됨
	}

	auto AddNum2() {
		[*this] () mutable { N += 10; } ();		//*this  복사이므로 스코프 벗어나면 원래대로 돌아감
	}

};

int main()
{
	Test test1;
	test1.AddNum1();
	cout << test1.N << endl;		//출력값은 ???

	Test test2;
	test2.AddNum2();
	cout << test2.N << endl;		//출력값은 ???

	return 0;
}

