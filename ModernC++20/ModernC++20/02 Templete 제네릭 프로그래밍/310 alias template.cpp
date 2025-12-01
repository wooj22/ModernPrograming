//별칭 템플릿 ( alias template )
 
//https://docs.microsoft.com/ko-kr/cpp/cpp/aliases-and-typedefs-cpp?view=msvc-170
//별칭 및 typedef
//		이전에 선언된 형식의 동의어로 사용할 이름을 선언

//using 키워드
//		using identifier = type;    
//		using 별칭 이름 = 형식 식별자
 

// 이전 버전에서는 typedef 사용했다. ----------------------------------------------

	typedef long counter;			// C++03 equivalent:
	using counter = long;			// C++11

//std::ios_base::fmtflags에 대해서는 이와 같은 형식 별칭이 더 유용 -----------------

	typedef std::ios_base::fmtflags fmtfl;  // C++03 equivalent:
	using fmtfl = std::ios_base::fmtflags;	// C++11

	fmtfl fl_orig = std::cout.flags();
	fmtfl fl_hex = (fl_orig & ~std::cout.basefield) | std::cout.showbase | std::cout.hex;
	// ...
	std::cout.flags(fl_hex);


//별칭은 함수 포인터에서도 작동 -------------------------------------------------

	typedef void (*func)(int);	// C++03 equivalent:
	using func = void(*)(int);	// C++11

	// func can be assigned to a function pointer value
	void actual_function(int arg) { /* some code */ }
	func fptr = &actual_function;


//---------------------------------------------------------------------------------
//별칭 템플릿 ( alias template )

template<typename T> 
using ptr = T*;

//usage // the name 'ptr<T>' is now an alias for pointer to T
ptr<int> ptr_int;


//---------------------------------------------------------------
//기존의 typedef 는 템플릿을 지원하지 않음
template<typename T>
typedef T(*Func)(T, T);		//typedef

template<typename T>
using Func = T(*)(T, T);	//using

//예제 ------------------------------------------------
//	함수 포인터 Func 의 별칭을 템플릿으로 만드세요.

#include <iostream>
using namespace std;

int add(int a, int b) { return a + b; }

using Func = int(*)(int, int);

int main()
{
	Func<int> adder = add;
	cout << add(1, 2) << endl;
}

//template<typename T> using Func = T(*)(T, T);


//----------------------------------------------------------------
// 템플릿 별칭이 가능하기 전엔, 템플릿 구조체안으로 별칭을 숨겨야했다.

#include <iostream>
#include <vector>
using namespace std;

template <typename T> struct myAllocator {};

// 기존의 typedef
template <typename T>
struct xvector
{
	typedef vector<T, myAllocator<T>> type;		//type
};

int main() {
	xvector<int>::type idList{ 1, 2, 3 };
}

//예제) 템플릿 별칭으로 변경해 보세요.
/*
template <typename T>
using xvector = vector<T, myAllocator<T>>;		//using

int main() {
	xvector<int> idList{ 1, 2, 3 };				// 간결
}
*/

//----------------------------------------------------------------
//기존의 typedef 대비 using을 이용한 별칭 선언은 
//		template 별칭 직접 지원, 코드 가독성 향상의 잇점
//		가급적 typedef 보다 using 별칭 선언으로 습관 들이는 것을 추천
 
// C++ 11
	// template-struct-typedef 방식 사용했음을 유추할 수 있다.
	std::add_const<T>::type
	std::remove_const<T>::type
	std::remove_reference<T>::type

// C++ 14
	// 기존의 이름 충돌 방지를 위한 _t suffix ***
	std::add_const_t<T>
	std::remove_const_t<T>
	std::remove_reference_t<T>

// 위 add_const_t는 다음과 같이 별칭
	template<typename T>
	using add_const_t = typename std::add_const<T>::type;
	//	rhs에 typename 키워드가 있는 이유는 ::type이 전적으로 T에 의존하기 때문이다.
	//	using template은 이런 의존성도 없기에, typename이 필요치 않으며 붙여서도 안 된다.



