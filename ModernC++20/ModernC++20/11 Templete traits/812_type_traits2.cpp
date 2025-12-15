// type_traits 함수 중 몇 가지를 직접 사용, 구현해 보자.

// is_same				//동일 타입 인지 
// is_integral			//정수 타입 인지 
// is_floating_point	//float 타입 인지 
// is_class				//클래스 인지 아닌지 확인하는 메타 함수 
// is_pointer			//데이터 멤버를 가리키는 포인터 (Pointer to Data member)
// remove_const			//const 제거
// enable_if			//true면 type을 정의
// void_t				//특정 타입에 특정 멤버가 있는지 컴파일 타임에 확인	
// ...


// type_traits 함수 사용 예시 --------------------------------------------------------
//		#include <type_traits>
//		https://en.cppreference.com/w/cpp/meta

//is_integral			// 정수 타입 확인하는 함수
//is_floating_point		// 실수 타입 확인하는 함수

#include <iostream>
#include <type_traits>

class A {};

template <typename T>
void only_integer(const T& t) {
	static_assert(std::is_integral<T>::value);  //static_assert 는 C++ 11 에 추가된 키워드
	std::cout << "T is an integer \n";
}

int main() 
{
	int n = 3;
	only_integer(n);

	A a;
	only_integer(a);

	std::cout << std::is_floating_point<float>::value << '\n';
	std::cout << std::is_floating_point<int>::value << '\n';
}
 
// remove_pointer

template<typename T>
void foo(T a) {
	std::remove_pointer_t<T> n;
}

// is_pointer

template<typename T>
void foo(T a) {
	bool b = std::is_pointer_v<T>;
}

// is_array

#include <iostream>
#include <type_traits>

template<typename T>
void foo(T& a) {
	if (std::is_array<T>::value)
	{
		std::cout << "Array" << std::endl;
		std::cout << std::extent<T, 0>::value << std::endl;
		std::cout << std::extent<T, 1>::value << std::endl;
	}
}
int main()
{
	int arr[4][3]{ 0,1,2,3,4,5,6,7,8,9,10,11 };
	foo(arr);
}
//std::extent<T, N> : 배열 유형인 경우 배열의 N번째 차원에 있는 요소 수와 동일한 T 멤버 상수 제공


// is_same

template<typename T, typename U>
void foo(T a, U b) {
	bool same = std::is_same<T, U>::value;
	std::cout << same << std::endl;
}

int main()
{
	foo(1, 2);
	foo(1, 2.0);
}

// remove_const			//const 제거
// remove_volatile		//volatile 제거
// remove_cv			//const,volatile 제거
// remove_reference		//reference 제거

//const int, int같이 const 속성이 있지만 둘 다 int이므로, 같은 타입으로 취급하려면 remove_const<T>::value 를 사용하고, 
//volatile을 제거하고 싶을 땐 remove_volatile<T>::value 을, 둘 다 제거하려면 remove_cv<T>::value를 사용하면 된다.

template<typename T, typename U>
void foo(T a, U b) {
	bool same = std::is_same<typename std::remove_cv<T>::type, typename std::remove_cv<U>::type>::value;
	std::cout << same << std::endl;
}

int main()
{
	foo<int, const int>(1, 2);
}

