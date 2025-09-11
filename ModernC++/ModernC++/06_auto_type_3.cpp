//auto가 원치 않은 타입으로 추론될 때에는 명시적 타입의 초기치를 사용하라.

//명시적 타입 초기화 ***
//		타입 명시 초기치 관용구(explicitly typed initializer idiom) 
//		static_cast <T>

//-------------------------------------------------------------------------------------------------
//"보이지 않는" 프록시 타입 때문에 auto가 초기화 표현식의 타입을 "잘못" 추론할 수 있다

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int a = 0;
	auto& val1 = a;										//val1
	decltype((a)) val2 = a;								//val2
	int arr[] = { 1,2,3 };	auto& val3 = arr[0];		//val3
	std::vector<bool> v = { };	auto val4 = v[0];		//val4 ???
}

//----------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Widget {};

std::vector<bool> features(const Widget& w) { std::vector<bool> v(5);  return v; }

int main()
{
	Widget w;

	bool highPriority1 = features(w)[3];			//vector 의 [3] 요소
	std::cout << highPriority1 << std::endl;

	// 하지만 bool 대신 auto로 highPriority를 선언하면 어떻게 될까?
	auto highPriority2 = features(w)[3];			
	std::cout << highPriority2 << std::endl;		//bool이 아님 ***
}

	// 여전히 컴파일되지만, 이제는 그 행동을 예측할 수 없다. // 미정의 행동!
	// 해결책 -> 타입 명시 초기치 관용구를 사용 하라

	// 그 이유는 std::vector<bool>::operator[]가
	// bool& 을 반환하는 것이 아니라, 
	// std::vector<bool>::reference 라는 프록시 객체를 반환하고, 
	// 이러한 객체의 수명이, 한 문장 이상으로 연장되지 않도록 만들어지는 것이 보통이기 때문이다.

	// 예를 들어 다음은, std::vector<bool>::operator[]의 명세이다.
	//namespace std {
	//	template <class Allocator>
	//	class vector<bool, Allocator> {
	//	public:
	//		...
	//		class reference { ... };
	//		reference operator[](size_type n);
	//		...
	//	};
	//}


	// 정리하자면, 다음과 같은 형태의 코드는 피해야 한다. ***

	// auto someVar = "보이지 않는" 프록시 클래스 타입의 표현식;


//--------------------------------------------------------------------------------------------------
//타입 명시 초기치 관용구(explicitly typed initializer idiom) - 명시적 타입 초기치
				
	auto highPriority2 = features(w)[3];				// [] 반환

	// features의 반환 타입은 std::vector<bool> 이고 
	// std::vector<bool>::operator[]의 반환 타입은 std::vector<bool>::reference 인데, 
	// 우리가 필요한 것은 bool 타입이다.
	 
	// 다음은 highPriority2 가 bool 로 추론되도록 강제하는 예이다.

	auto highPriority2 = static_cast<bool>(features(w)[3]);	 // static_cast <> 사용


//-----------------------------------------------------------------------------
// 타입 명시 초기치 관용구는 
//    초기화에 쓰이는 표현식이 산출하는 타입과는 다른 타입으로 변수를 생성 하고자 하는 의도를 
//    명확하게 나타내는 데에도 유용하다.

// 예를 들어 어떤 허용 한계치를 계산하는 다음과 같은 함수가 있다고 하자.

	double calcEpsilon(void) { return 1.1; }	// 허용 한계치를 돌려준다. 
	{	
		float ep = calcEpsilon();		// double에서 float로의 암묵적 변환이 일어남	

		// 타입 명시 초기치 관용구를 이용하면 그런 의도가 표현된다.
		auto ep = static_cast<float>(calcEpsilon());
		return 0;
	}
