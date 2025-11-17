// 범위 없는 enum 보다 범위 있는 enum 을 사용하자.

//		범위 없는(unscoped) enum  - C++98 스타일의 enum
//		범위 있는(scoped) enum	 - C++11의 새로운 열거형, 
//								"enum class" 라는 구문으로 선언한다.

#include <iostream>
using namespace std;

int main()
{
	//범위 없는 enum  --------------------------------------------------
	{
		enum Color { black, white, red };

		// black, white, red는  { } 범위로 제한되는 일반적인 규칙을 따르지 않는다.
		// Color가 속한 범위에 속함 ***
		// 따라서, 그 범위에 같은 이름이 있으면 안 된다. 

		auto color1 = white;
		auto color2 = Color::white;

		auto white = false;			//error //재정의

		if (black < 2.5) {}

	}

	// 범위 있는 enum //enum class -------------------------------------
	{
		enum class Color : int { black, white, red };

		// 범위 있는 enum의 열거자들은 그 안에서만 보인다. 
		// 이 열거자들은 오직 캐스팅을 통해서만 다른 타입으로 변환된다.

		auto color1 = white;		//error
		auto color2 = Color::white;

		auto white = false;			//변수 선언
	
	}
	return 0;
}