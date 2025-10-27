//Recursive lambda ---------------------------------------------------------
// 
//	lamba 함수 역시 함수의 특성을 모두 가지고 있으므로, 재귀(recursive)가 가능하다.


#include <iostream>
#include <functional>
using namespace std;

int main(int argc, char* argv[])
{
	// function을 사용하였음에 주의하세요.
	function<int(int)> Factorial = [&Factorial](int num) -> int
	{
		return num <= 1 ? 1 : num * Factorial(num - 1);
	};

	// 5 * 4 * 3 * 2 * 1 = 120
	int fact5 = Factorial(5);
	cout << fact5 << endl;

	return 0;
}
