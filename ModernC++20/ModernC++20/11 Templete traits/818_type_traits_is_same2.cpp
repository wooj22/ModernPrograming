// template class 타입 제한하기. 
//		enable_if, is_same 활용하는 경우

#include <iostream>
using namespace std;

template <typename T>
class EllipseT {
	
	//Numeric 을 double,float,int 로 제한한다.
	using Numeric = typename std::enable_if<
		std::is_same<double, T>::value
		|| std::is_same<float, T>::value
		|| std::is_same<int, T>::value
		, T>::type;

	Numeric x, y, a, b;		
	//...Something
};

int main()
{
	EllipseT<int> e1;
	
	EllipseT<char> e2;  //다른 타입으로 템플릿 클래스를 선언할 경우 컴파일 에러가 발생한다.
}

//std::enable_if 는 아래와 같이 생겼고 B 가 참이면 T가 해당 타입으로 정의 된다.
//
//	template< bool B, class T = void >
//	struct enable_if
