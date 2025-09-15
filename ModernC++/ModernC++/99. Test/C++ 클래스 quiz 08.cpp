// 아래 번호 중에서  잘못된 것을 모두 찾으세요.

#include <iostream>

int main()
{
	int n = 1;
	int& r1 = 1;			//1
	int& r2 = n;			//2

	const int& r3 = 1;		//3
	const int& r4 = n;		//4

	int&& r5 = 1;			//5
	int&& r6 = n;			//6

	auto&& r5 = 1;			//5
	auto&& r6 = n;			//6

	return 0;
}
