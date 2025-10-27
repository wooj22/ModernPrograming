//C++ Callable(함수로 호출가능한 것) 표현 방식
//		함수, 함수객체, 람다.
// 
//		함수 포인터는 작성이 가장 단순하나, 상태(변수)를 가지지 못한다.
// 
//		함수 객체는 상태를 가질 수 있으나, 클래스나 구조체를 정의해야 하는 번거로움이 있다.
// 
//		lambda 함수는 작성하기 용이하며(구조체 정의 작성등이 필요없다), 상태 역시 가질 수 있다.
//		lambda 함수는 함수 포인터와 함수 객체의 단점은 배제하고, 장점을 모두 가지고 있다.
 
//lambda expression
//		C++ 에서 람다를 이용해 함수형 프로그래밍을 구현이 가능.
//		람다의 사용법과 특징에 대해 알고 사용하자.

// functor vs lambda
// lambda 예제	//특정 클래스를 정렬하는 기능을 만드는 경우

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class SomeClass {
public:
	SomeClass() {}
	int data = 0;
};

class Compare
{
public:
	bool operator()(const SomeClass& o1, const SomeClass& o2) const		// compare function
	{		
		return o1.data > o2.data;
	}
};

int main()
{
	//1. functor				//STL의 알고리즘은 비교함수 등에 functor를 쓸수 있게 지원한다

	std::vector<SomeClass> v1;
	std::sort(v.begin(), v.end(), Compare());


	//2. lambda expression		//람다표현식으로 편리하게 사용 가능하다

	std::vector<SomeClass> v2;
	std::sort(v2.begin(), v2.end(), [](const auto& o1, const auto& o2)
		{	
			return o1.data > o2.data;;
		});

	return 0;
}


//가변인자 템플릿이 가능해지면서 이제 임의의 함수 타입을 담는 타입이 등장. 
//이로써 함수형 프로그래밍이 훨씬 쉬워졌다.
// 
//std::function ***

// 사칙연산을 하는 함수들을 배열로 담아 선언하세요.

void ex()
{
	std::function<int(int, int)> op[] =
	{
		[](int a, int b) {return a + b; },
		[](int a, int b) {return a - b; },
		[](int a, int b) {return a * b; },
		[](int a, int b) {return a / b; },
		//[someVar](int a, int b) {return a + b + someVar; },
	};

	for (auto f : op)
	{
		std::cout << f(1, 1) << std::endl;
	}
}


//함수 포인터는	- 작성이 가장 단순하나, 상태를 가지지 못한다.
//함수 객체는	- 상태를 가질 수 있으나, 클래스나 구조체를 정의해야 하는 번거로움이 있다.

//lambda 함수는 -  함수 포인터와 함수 객체의 단점은 배제하고, 장점을 모두 가지고 있다.
//lambda 함수는 작성하기 용이하며(구조체 정의 작성등이 필요 없다), 상태 역시 가질 수 있다.