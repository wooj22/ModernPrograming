//별칭 선언 (alias declaration) 
//		typedef보다 별칭 선언을 선호하라!
// 
//		typedef type표현식 별칭이름;
//		using  별칭이름 = type표현식;

#include <iostream>
#include <list>
#include <unordered_map>

//복잡한 표현식
std::unique_ptr<std::unordered_map<std::string, std::string>> sptr;

//이럴 때 사용할 수 있는 것이 typedef
typedef	std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS;

//C++11은 별칭 선언(alias declaration) 제공
using UPtrMapSS = std::unique_ptr<std::unordered_map<std::string, std::string> >;



//typedef보다 우월한 점 ---------------------------------------------------------------

//1. 이해하기 쉽다.

typedef void (*FP)(int, const std::string&);	// typedef

using FP = void (*)(int, const std::string&);	// 별칭 선언 (alias declaration) ***


//2. typedef는 템플릿화를 할 수 없지만, 별칭 선언은 템플릿화할 수 있다.

	class Widget { };

	template <typename T>
	class MyAlloc {};

// typedef 의 경우

	template <typename T>
	struct MyAllocList1 {
		typedef std::list<T, MyAlloc<T> > type;		// MyAllocList<T>::type은 // std::list<T,MyAlloc<T> >와 동의어이다.
	};

	int main()
	{
		MyAllocList1<Widget>::type lw;              // 클라이언트 코드	
	}

//별칭 템플릿(alias templates) ***	// 더 간단하고, 직접적으로 표현 

	template <typename T>
	using MyAllocList2 = std::list<T, MyAlloc<T> >;

	int main()
	{
		MyAllocList2<Widget> lw;                    // 클라이언트 코드 //::type 접미어를 붙일 필요가 없다
	}


//별칭 템플릿에서는 "::type" 접미어를 붙일 필요가 없다. ------------------------------------------
/*
	template <typename T>
	class Widget {                                  // Widget<T>에는
	private:
		typename MyAllocList<T>::type list;         // MyAllocList<T> 타입의 데이터 멤버가 있다.
		//...
	};


	template <typename T>
	using MyAllocList = std::list<T, MyAlloc<T> >;  // 이전과 동일

	template <typename T>
	class Widget {
	private:
		MyAllocList<T> list;						// "typename" 없음 // "::type" 없음
	};

*/


//C++14는 C++11의 모든 타입 특성 변환에 대한 별칭 템플릿들을 제공한다.------------------------------------------
/*
	//<type_traits> 헤더 안에 있는 일단의 템플릿
	//		템플릿 메타 프로그래밍(TMP)을 하다 보면 어떤 타입 T가 주어졌을 때,
	//		T에 담긴 임의의 const 한정사나 기타 참조 한정사들을 제거하거나 붙여야 할 경우가 있다.
	//		C++은 이런 종류의 변환을 타입 특성(type trait)의 형태로 수행할 수 있는 도구들을 제공한다.

	//적용하고자 하는 타입 T가 주어졌을 때, 변환을 적용한 결과로 나온 타입은 항상 std::변환<T>::type이다.
	//		이런 변환들을 적용할 때 "::type"라는 접미어를 붙여야 한다는 점에 주목하자.
	//		템플릿 안의 타입 매개변수에 그 접미어를 붙인다면, 그 앞에 typename도 반드시 붙여야 한다.

	std::remove_const<T>::type                // const T를 T로 변환
	std::remove_reference<T>::type            // T&나 T&&를 T로 변환
	std::add_lvalue_reference<T>::type        // T를 T&로 변환

	std::remove_const_t<T>                    // 해당 C++14 버전
	std::remove_reference_t<T>                // 해당 C++14 버전
	std::add_lvalue_reference_t<T>            // 해당 C++14 버전


// C++14 버전 아닌 경우라도  //별칭 템플릿들 작성하여 사용 가능

	template <class T>
	using remove_const_t = typename remove_const<T>::type;

	template <class T>
	using remove_reference_t = typename remove_reference<T>::type;

	template <class T>
	using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
*/