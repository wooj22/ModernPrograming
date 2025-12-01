//템플릿
//		클래스, 함수, 변수를 제네릭타입(Generic Type)으로 동작하게 하는 것.
//		컴파일러가 사용된 자료형(데이타형, 타입)별로 알아서 추가 코드를 작성해주는 것.

//템플릿 종류
//		클래스 템플릿 - 클래스 맴버의 변수 타입에 대하여 템플릿으로 선언 
//		함수   템플릿 - 함수의 매개변수와 리턴값을 템플릿으로 선언
//		변수   템플릿 - 변수를 템플릿으로 선언했다는 의미	//C++14
//		별칭   템플릿 - 별칭을 템플릿으로 선언

//템플릿 사용 이유
//		자료형에 따라 구현이 늘어나는 경우에 편리 ***
//		특히 다중 상속과 연산자 오버로딩과 결합할 때 유용

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	std::vector<int> ints;					//int	- 동적배열
	std::vector<float> floats;				//float - 동적배열

	int max1 = std::max<int>(1, 2);
	int max2 = std::max<float>(1.2f, 2.5f);
	cout << max1 << endl;
	cout << max2 << endl;

	return 0;
}

//템플릿 만들기 ( Template Parameter )
//템플릿 인수 추론 ( Template Argument Type Deduction )	- 타입 추론
//템플릿 타입생략 ( Template Deduction Guide )			- 타입 생략
//다양한 템플릿 들 ( 함수 템플릿, 클래스 템플릿, 변수 템플릿, 별칭 템플릿 ) 
//템플릿 인스턴스화 ( Template Instantiation )			- 컴파일 시점 
//안전한 템플릿 ( Template Concept )		//C++20 - 의미,제약,요구사항 - type safe


//용어 정리 ***
//	Parameter  - 형식인자 (formal parameter ) - 변수 - 매개변수
//	argument   - 실  인자 (actual parameter)   - 값   - 인수
// 
//	매개변수(Parameter), 전달인자(argument) 
//	번역상 한국어로는 인자든 매개변수든 그냥 다 인자라고, 혼용되므로 문맥에 따라 판단하자.


//템플릿 만들기 ( Template Parameter ) --------------------------------------------------------
/*
	template <typename T[parameters]>
	[return type] Function(T a[arguments])
	{
		...
	}
*/

//템플릿으로 만들어 보세요.

int		max(int a, int b) {	return a > b ? a : b; }
double	max(double a, double b) { return a > b ? a : b; }

int main()
{
	std::cout << max(3, 7) << std::endl;				//인수 추론에 의한 호출
	std::cout << max(3.0, 7.0) << std::endl;
	return 0;
}

/*
template <typename Type>
Type max(Type a, Type b) {
	return a > b ? a : b;
}

int main()
{
	std::cout << max(3, 7) << std::endl;				//추론에 의한 호출
	std::cout << max(3.0, 7.0) << std::endl;
	std::cout << max<int>(3, 7) << std::endl;			//명시적 호출 (오버로드된 경우 주의)
	//std::cout << max<double>(3, 7.0) << std::endl;	//error  //추론 불가

	return 0;
}
*/

//템플릿 인스턴스화(구체화) ---------------------------------------------------------------
//		컴파일러가 템플릿에서 클래스 또는 함수를 생성하는 프로세스를 템플릿 인스턴스화(구체화)라고 합니다 

//템플릿 인스턴스화 (template instantiation) 
//      컴파일러가 함수(클래스) 틀(Template)로 부터 실제 C++ 함수(클래스)를 만들어 내는 과정 
//      함수가 사용되면 ***
//		컴파일러는 
//		모든 T인스턴스를 사용자가 지정하거나 컴파일러에서 추론하는 구체적인 형식 인수로 바꿉니다.

template <typename T>									//함수 템플릿
T minimum(const T& lhs, const T& rhs)						
{
	return lhs < rhs ? lhs : rhs;
}

//minimum<int> 는 템플릿 minimum<T>의 인스턴스화
 
//int minimum<int>(const int& lhs, const int& rhs)		//템플릿 함수
//{
//	return lhs < rhs ? lhs : rhs;
//}

int main()
{
	int a = 1;
	int b = 2;
	int i = minimum<int>(a, b);   // 이 순간에 함수 생성 (인스턴스화)
}	


// 사용자 정의 형식을 형식 인수로 사용하는 경우 ------------------------------------------

	#include <iostream>
	using namespace std;

	template <typename T>
	T minimum(const T& lhs, const T& rhs)
	{
		return lhs < rhs ? lhs : rhs;		//< 연산을 수행 
	}

	class MyClass {							//사용자 정의 형식 
	public:
		int num;
		std::wstring description;
	};

	int main()
	{
		MyClass mc1{ 1, L"hello" };
		MyClass mc2{ 2, L"goodbye" };
		auto result = minimum(mc1, mc2);	// Error! 이유는?  
	}

/*
	//연산자< 에 대한 오버로드 필요
	bool operator<(const MyClass& obj) const {
		if (num < obj.num) return true;
		return false;
	}
*/

//형식 매개변수가 여러개인 경우도 가능 ---------------------------------------------------- 
	template <typename T, typename U, typename V> class Foo { };

//typename, class	
	template <class T, class U, class V> class Foo { };			//동일한 표현 //초기 문법


//템플릿 파라미터(매개변수)에는 세 종류가 있습니다 -----------------------------------------
//		데이터형 (type) 파라미터				- typename T
//		데이터형이 아닌 (nontype) 파라미터	- int N
//		템플릿 템플릿 파라미터				- template<typename T> class A
//
//		type     template Parameter
//		nontype  template Parameter
//		template template Parameter


//형식이 아닌 매개변수 (nontype Parameter) -----------------------------------
//		값 매개변수, 데이터형이 아닌 파라미터, 비타입 매개변수 

	#include <iostream>
	using namespace std;

	template<typename T, size_t L>
	class MyArray
	{
		T arr[L];
	public:
		MyArray() {  }
	};

	int main()
	{
		MyArray<int*, 10> arr;
	}

	//형식이 아닌 템플릿 매개 변수에 대한 형식 추론  //auto  /std:c++17		

	template <auto x> constexpr auto constant = x;

	int main()
	{
		auto v1 = constant<5>;      // v1 == 5,		decltype(v1) is int
		auto v2 = constant<true>;   // v2 == true,	decltype(v2) is bool
		auto v3 = constant<'a'>;    // v3 == 'a',	decltype(v3) is char
	}

//템플릿 매개변수로서의 템플릿 ------------------------------------------------
//		- 템플릿 템플릿 파라미터

	template<typename T, template<typename U, int I> class Arr>
	//template<typename T, template<typename, int> class Arr>   // Arr의 형식 매개 변수 이름을 생략 가능
	class MyClass2
	{
		T t;			//OK
		Arr<T, 10> a;
	};


//템플릿 인수 (템플릿 파라미터의 값) -------------------------------------------------------
//		템플릿 인수는 템플릿이 인스턴스화 될때 템플릿 파라미터를 치환할 "값"을 말합니다
//		기본 템플릿 인수 : 기본 템플릿 인자를 쓸 수 있다면, 클래스 템플릿 인스턴스에서 템플릿 인자를 생략할 수 있습니다.
//		템플릿 인수 추론 : 명시적으로 제시되지 않은 함수 템플릿 인수는 호출시 함수 호출 인자의 데이터형을 통해 추론된다.


//기본 템플릿 인수 지정하기 ------------------------------------------------------------
//
//		템플릿에 기본 인수가 있는 경우 템플릿을 사용할 때 지정되지 않은 상태로 둘 수 있습니다

	template <class T, class Allocator = allocator<T>> class vector;
	{
		vector<int, MyAllocator> ints;
		vector<int> myInts;				//생략 가능
	}

	//매개 변수가 모두 기본값인 템플릿을 사용하는 경우 빈 꺾쇠 괄호를 사용한다.

	template<typename A = int, typename B = double>
	class Bar
	{
		//...
	};

	int main()
	{
		Bar<> bar; // use all default type arguments
	}


//템플릿 인스턴스화, 특수화 ------------------------------------------------------------------
//
//		인스턴스화된 구체화된 결과물(함수든 클래스든..)을 특수화라고 합니다.
//		특수화의 경우 이렇게 인스턴스화를 통해서만이 아니라 명시적 특수화, 부분 특수화를 통해서도 가능합니다.
//		보통은 템플릿의 특수화 라고 하면 명시적 특수화나 부분 특수화를 말합니다.

//템플릿 특수화 (specialization)
//
//		특정 형식에 대한 템플릿의 특수화를 정의할 수 있습니다. 
//		모든 매개 변수가 특수화된 특수화는 '완전한 전문화'입니다.
//		일부 매개 변수만 특수화된 경우 '부분 특수화'라고 합니다.

	#include <iostream>
	using namespace std;

	template <typename K, typename V>
	class MyMap { };
	
	template<typename V>				// partial specialization for string keys
	class MyMap<string, V> { };

	class MyClass {};

	int main()
	{
		MyMap<int, MyClass> classes;		// uses original template
		MyMap<string, MyClass> classes2;	// uses the partial specialization
	}



//가변 길이 템플릿 --------------------------------------------------------------------------
//
//		임의의 수의 0개 이상의 형식 매개 변수를 사용하는 템플릿
//		줄임표 연산자(...)를 사용

	template<typename... Types> class vtclass { };

	int main()
	{
		vtclass<> vtinstance1;
		vtclass<int> vtinstance2;
		vtclass<float, bool> vtinstance3;
	}
