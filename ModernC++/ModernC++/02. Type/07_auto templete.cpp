//매개변수에 auto 사용하기

//매개변수에 auto 사용 불가, VC++20 이전

//자동으로 템플릿 작성 , VC++20

#include <iostream>
using namespace std;

auto add_int(auto t1, auto t2) -> decltype(t1 + t2)
{
	return { t1 + t2 };
}

int main()
{
	//템플릿
	cout << add_int(1.1, 1.1) << endl;

	//람다
	auto add = [](auto t1, auto t2) {return t1 + t2; };
	cout << add(1.1, 1.1) << endl;

}
