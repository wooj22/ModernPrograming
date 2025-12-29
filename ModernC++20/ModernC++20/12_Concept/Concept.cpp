//C++20의 Concept 이란, 
//		"타입이 가져야 하는 요구 조건을 정의하는 문법"
//		Named sets of requirements", 즉 "이름을 가진 요구조건의 집합"
//		일정 타입을 묶어 별칭을 붙임, 타입으로 사용 가능

//Concept을 이용하여 '템플릿 인자들'에 대한 '제약 조건'을 지정 할 수 있다.
// 
//		이 제약 조건들은 컴파일 타임에 예측 되고, 평가 되며, 
//		제약 조건으로 사용되는 템플릿 인터페이스의 일부가 된다.
//		또한, 함수 오버로딩이나 템플릿 특수화에서 가장 적절한 함수를 선택하는데 사용된다.

//유용한 이유
//		컨셉을 이용하면, 템플릿 인자 타입을 넘어 
//		해당 타입이 가지는 '속성' 또는 '오퍼레이션'에 따라 함수 오버로딩을 할 수 있다 ***
//
//		기존에 런타임에 수행 되던 논리 연산들을 컴파일 타임에 결정하여, 보다 빠른 실행 속도를 제공 할 수 있으며 
//		런타임에 발생할 수 있는 오류들을 컴파일 타임에 '검출' 해낼 수 있다.

/*
//C++20에 추가된 두개의 키워드

concept : 템플릿 인자의 제약 조건을 기술하는데 사용되는 키워드. ***

requires : 템플릿 인자가 가져야 하는 조건을 표기하는 키워드. ***

		조건을 만족하는 경우에만 템플릿을 사용하여 함수 생성. 
		requires 절에 표기 할 수 있는 것은 concept 뿐만 아니라 type_traits 등도 사용 가능.
 
		type traits : 
		C++11 부터 <type_traits> 헤더로 제공 되는 
		컴파일 타임에 타입에 대한 정보를 얻거나 변형된 타입을 얻을 때 사용하는 메타함수.
*/

//concept 선언
//		#include <concepts>
// 
//		template <typename T>				//반드시 template 필요
//		concept 컨셉이름 = bool값의 식 또는 requires 구문

//concept 사용
//
//		concept<int>


#include <iostream>
#include <concepts>					// 컨셉 사용을 위한 헤더 ***
using namespace std;

//컨셉 정의 *** --------------------------------------

template <class T>
concept GreaterThan4 = sizeof(T) >= 4;		// 단순히 타입 T의 사이즈가 4이상인지 판단 하는 컨셉	

//컨셉 사용 *** --------------------------------------

template <class T> requires GreaterThan4<T>		//1. template 선언 다음에 사용
void foo(T arg) {
	cout << "size of " << typeid(T).name() << " is greater than 4" << endl;
}

int main()
{
	int i = 10;
	short s = 10;
	double d = 3.14;
	foo(i);			// int의 사이즈는 4와 같으므로 OK
	foo(s);			// short의 사이즈는 4보다 작으므로 ERROR
	foo(d);			// double의 사이즈는 4보다 크므로 OK
}

// 아래의 방법들도 동일한 의미를 가진다.
/*

template <class T>
void foo(T arg) requires GreaterThan4<T> { }   //2. 함수 선언 다음에 requires 절을 사용해도 된다

template <GreaterThan4 T>   //3. requires를 사용하지 않고, 템플릿 타입으로, 정의된 concept를 사용 할 수 있다
void foo(T arg) { }

*/

//concept 사용 ***
// 
//	1. 템플릿 선언 다음에 requires 절에서
//	2. 함수 선언   다음에 requires 절에서
//	3. 템플릿 타입으로 직접 사용

// 각각 선언해서 실행 테스트하세요. *****


//제약 조건에 만족하지 못하는 경우 - 인스턴스화 실패, 컴파일 에러 ***
//
//일반 템플릿 함수를 추가하면 
//	제약 조건에 만족하지 못하는 모든 타입들은 이 일반 템플릿 함수를 이용

template <class T>
void foo(T t) {
	std::cout << "size of " << typeid(T).name() << " is less than 4" << endl;
}


//--------------------------------------------------------------------------------------

//주의: 컨셉은 자기 자신을 재귀적으로 참조 할 수 없으며, 자기 자신의 제약 조건이 될 수 없다. ***

template<typename T>
concept V = V<T*>;			// Error: 재귀 참조  // V를 선언하면서 자신을 사용


template<class T> 
concept C1 = true;			// 컨셉 선언

template<C1 T>
concept Error1 = true;		// Error: C1 T은 컨셉을 컨셉 조건으로 사용하려 함.

template<class T> requires C1<T>
concept Error2 = true;		// Error: requires절이 컨셉 조건으로 사용 됨.


//연습) 아래 함수템플릿을 int 타입만 사용할 수 있도록 수정하세요 ---------------------------

#include <iostream>
#include <concepts>
using namespace std;

template<typename T>
int increase(T t) {
	return t + 1;
}

int main()
{
	cout << increase(1) << endl;	//ok
	cout << increase(1.0) << endl;	//ok -> error
}
/*
template<typename T>
concept INT = std::is_same_v<T, int> == true;

template<INT T>
int increase(T t) {
	return t + 1;
}

//template<typename T> requires INT<T>
//int increase(T t) 
//{
//	return t + 1;
//}

*/


//연습) 아래 코드를 컨셉으로 변경해서 표현하세요 -----------------------------------------

#include <iostream>
using namespace std;

template<typename T1, typename T2,
	typename = enable_if_t<is_convertible_v<T1, int>&& is_convertible_v<T2, int>>>
long long add_int(T1 t1, T2 t2)
{
	return { t1 + t2 };
}

int main()
{
	cout << add_int(1, 1);
}

/*
//1 ---------------------------

template<typename T>
concept Integer = is_convertible_v<T, int>;

template<typename T1, typename T2> requires Integer<T1> && Integer<T2>
long long add_int(T1 t1, T2 t2)
{
	return { t1 + t2 };
}

//2 ---------------------------

template<typename T1, typename T2>
long long add_int(T1 t1, T2 t2) requires Integer<T1> && Integer<T2>
{
	return { t1 + t2 };
}

//3 ---------------------------

#include <iostream>
#include <concepts>
using namespace std;

template<typename T>
concept Integer = is_convertible_v<T, int>;

template<Integer T1, Integer T2>
long long add_int(T1 t1, T2 t2)
{
	return { t1 + t2 };
}

int main()
{
	add_int(1, 1);
}

*/