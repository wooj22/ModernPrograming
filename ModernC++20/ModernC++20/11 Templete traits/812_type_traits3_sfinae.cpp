//SFINAE
//		C++ 에선 흔히 이를 치환 실패는 오류가 아니다 
//		Substitution Failure Is Not An Error 혹은 줄여서 SFINAE 라고 합니다.
// 
//		템플릿 인자 치환에 실패할 경우(위 같은 경우) 
//		컴파일러는 이 오류를 무시하고, 그냥 오버로딩 후보에서 제외하면 된다 라고 명시되어 있습니다.

//enable_if
//		SFINAE 를 잘 활용하는 툴들 중 가장 널리 쓰이는 것이 바로 enable_if
//		조건부로 존재하게 만드는 템플릿 도구
//		잘못된 타입/조건의 인스턴스화를 컴파일 타임에 차단하기 위해 사용


//-------------------------------------------------------------------------------------
#include <iostream>
#include <type_traits>

//enable_if의 템플릿 첫번째 인자로 boolean 타입을 넣어두고 해당 구문에서 판별을 요청하면, 
//결과값에 따라 type이 생기거나 생기지 않는 것을 이용할 수 있다.

	template <bool, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T> { typedef T type; };


// 정수 타입들을 받는 함수 (int, char, unsigned, etc.)
template <class T, 
	typename std::enable_if<std::is_integral<T>::value,T>::type* = nullptr>   //integral 계열이 아니라면,인스턴스화하지 않고 넘어간다.  
	void do_stuff(T& t) {		
	std::cout << "do_stuff integral\n";	
}

// 일반적인 클래스들을 받음
template <class T,
	typename std::enable_if<std::is_class<T>::value, T>::type* = nullptr>	//class 계열이 아니라면,인스턴스화하지 않고 넘어간다.  
	void do_stuff(T& t) {
	std::cout << "do_stuff class\n";
}

class A {};

int main()
{
	int a = 0;
	do_stuff(a);

	A aa;
	do_stuff(aa);
}

//C++14 -----------------------------------------

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;		//enable_if_t

// 정수 타입들을 받는 함수 (int, char, unsigned, etc.)
template <class T, typename std::enable_if_t<std::is_integral<T>::value>* = nullptr>		
	void do_stuff(T& t) { std::cout << "do_stuff integral\n";	}
// 일반적인 클래스들을 받음
template <class T, typename std::enable_if_t<std::is_class<T>::value>* = nullptr>
	void do_stuff(T& t) { std::cout << "do_stuff class\n";	}


//-------------------------------------------------------------------------------------
//	enable_if 없이는 템플릿 오버로딩 함수들이 무분별하게 오버로딩 되서 골치 아플 것입니다.

template <typename T>
class vector 
{
	vector( size_type n, const T val);

	template <class InputIterator>
	vector(InputIterator first, InputIterator last);
	
	//...	
}

int main() 
{
	// Create the vector {8, 8, 8, 8}
	std::vector<int> v1(4, 8);

	//문제는 v1(4, 8) 과 같이 생성자를 호출하였을 경우, 
	//프로그래머는 첫 번째 생성자를 의도한 것이기겠지만, 실제로는 두 번째 생성자가 호출됩니다.
	//왜냐하면 size_type 이 대개 unsigned 로 정의되어 있지만, 4 의 경우 그냥 signed 이므로 더 잘 맞는 후보군은 두 번째 것 
	// enable_if 필요

	// Create another vector {8, 8, 8, 8}
	std::vector<int> v2(std::begin(v1), std::end(v1));

	// Create the vector {1, 2, 3, 4}
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	std::vector<int> v3(arr, arr + 4);
}

/*
template <typename T>
class vector
{
	vector( size_type n, const T val);

	// enable_if 사용 ------------------------

	template <class _InputIterator>
	vector(
		_InputIterator __first,
		typename enable_if<__is_input_iterator<_InputIterator>::value &&
		!__is_forward_iterator<_InputIterator>::value &&
		// ... more conditions...  
		_InputIterator >::type __last);
}
*/
