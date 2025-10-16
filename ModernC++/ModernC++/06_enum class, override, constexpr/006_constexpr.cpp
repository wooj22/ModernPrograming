// constexpr 
// 
//	 키워드는 객체나 함수 앞에 붙일 수 있는 키워드로, 
//   해당 객체나 함수의 리턴값을 "컴파일타임"에 값을 알 수 있다 는 의미.
// 
//	 정수 상수 표현식(integral constant expression)이 요구되는 문맥에서 사용할 수 있다.
//	 객체의 정의에 constexpr 이 오게 된다면, 해당 객체는 어떠한 상수식에도 사용될 수 있습니다.


// 상수식 (Constant expression), 
// 정수 상수식 (Integral constant expression)

	//1 배열 선언하는 경우
	int arr[size];						//size 는 상수여야 한다.

	//2 템플릿 타입 인자
	template <int N>
	struct A {
		int operator()() { return N; }
	};

	A<num> a;							//num 는 상수여야 한다.

	//3 enum 에서 값을 지정
	enum B { x = number, y, z };		//number 는 상수여야 한다.

//----------------------------------------------------------------------
#include <iostream>
using namespace std;

template <int N>
struct A {
	int operator()() { return N; }
};

int main() 
{
	// const

	const int i = 3;	// 컴파일러에 따라, 런타임 or 컴파일에 초기화 할지 다를 수 있다.

	// const vs constexpr -------------------------------------------------

	int sz = 10;
	const auto arraySize1 = sz;
	std::array<int, arraySize1> data1;		//Error

	constexpr auto arraySize2 = 10;			//10은 확실히 컴파일 시점 상수
	std::array<int, arraySize2> data2;		// OK

	// constexpr ----------------------------------------------------------

	constexpr int size = 3;					//컴파일 타임에 상수를 확실히 사용
	int arr[size];							// Good! 

	constexpr int N = 10;
	A<N> a;									// Good!
	std::cout << a() << std::endl;

	constexpr int number = 3;
	enum B { x = number, y, z };			// Good!
	std::cout << B::x << std::endl;
}

