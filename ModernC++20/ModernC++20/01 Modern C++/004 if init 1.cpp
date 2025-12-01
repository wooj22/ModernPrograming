// 초기화 문 ( Init Statement )

//C++17 
//	if / switch 에 대한 초기화 문
//	if 문과 switch 문에서 조건식 왼쪽에 세미콜론(;)을 붙이고, 
//	그 왼쪽에 for문의 초기화 문처럼 변수를 선언하거나 변수에 값을 대입시킬 수 있는 기능이 추가됨
//
//C++20 부터는 
//	Ranged for 문에서도 사용할 수 있다.

//초기화문은
//	지역 변수를 선언·초기화하는 시점을 분기 로직과 밀착시켜, 
//	코드의 범위·가독성·안전성을 크게 높여준다.

//----------------------------------------------------------
// if/switch에 대한 초기화 문 (c++17부터 지원)

#include <iostream>

int foo() { return -1; }

int main()
{
	// 기존에 자주 사용하는 방식의 코드
	int ret = foo();
	if (ret == -1) {
		std::cout << "print 1" << std::endl;
	}

	// 초기화 문으로 바꾸기	// 변수가 블럭안에서만 사용되는 경우
	/*
		if (int ret = foo(); ret == -1)
		{
			std::cout << "print 1" << std::endl;
		}
	*/


	// 기존에 자주 사용하는 방식의 코드
	int n = foo();
	switch (n)
	{
	case 10: break;
	case 20: break;
	}

	// 초기화 문으로 바꾸기
	/*
		switch (int n = foo(); n)
		{
		case 10: break;
		case 20: break;
		default:
			std::cout << "print 2" << std::endl;
		}
	*/

}

//---------------------------------------------

#include <iostream>
using namespace std;

struct Coo {
	int g() { return 4; }
};

Coo f() {
	return  Coo();
}

int main()
{
	//if 문에서의 초기화 문 ;

	if (int n = 1; n > 0) {  
		cout << "ok" << endl;
	}

	//if 문에서의 초기화 문 ;

	if (auto coo = f(); coo.g() == 5)
	{
		cout << "ok" << endl;
	}

	//switch 문에서의 초기화 문

	switch (int things; things = f().g())
	{
	case 3:
		cout << things << endl;
		break;
	case 4:
		cout << things << endl;
		break;
	}	
}


/*
	//if 문에서의 초기화 문 ;

	if (int n = 1; n <  0) {
		cout << "ok" << endl;
	}
	else if (int m = 1; m < 0) {
		cout << "ok" << endl;
	}
	else {
		cout << n << endl;
	}
*/


//----------------------------------------------------------------
#include <iostream>

int main()
{
	const std::string myString = "My Hello World Wow";

	const auto it = myString.find("Hello");
	if (it != std::string::npos)
		std::cout << it << " Hello\n";

	const auto it2 = myString.find("World");
	if (it2 != std::string::npos)
		std::cout << it2 << " World\n";

	/*
		//초기화문 사용
		if (const auto it = myString.find("Hello"); it != std::string::npos)
			std::cout << it << " Hello\n";

		if (const auto it = myString.find("World"); it != std::string::npos)
			std::cout << it << " World\n";
	*/


	//if 문에서 정의한 변수는 블록에서도 볼 수 있다. ***

	if (const auto it = myString.find("World"); it != std::string::npos)
		std::cout << it << " World\n";
	else
		std::cout << it << " not found!!\n";

}


