//https://modoocode.com/221

//템플릿 메타 프로그래밍 (Template Meta programming)
//		컴파일 타임에 생성되는 코드로 프로그래밍을 하는 것을 메타 프로그래밍(meta programming)
// 
//		템플릿 메타 프로그래밍(TMP)으로 작성된 코드는 
//		모두 컴파일 타임에 모든 연산이 끝나기 때문에 
//		프로그램 실행 속도를 향상 시킬 수 있다는 장점이 있다. ***
// 
//		컴파일 시간은 늘어남. 구현이 어렵고 복잡함, 디버깅이 불가능, 오류가 길고 복잡. 

//C++에서, 템플릿 메타프로그래밍은 
//		튜링 완전성. 표현 가능한 어떤 계산도 템플릿 메타프로그램에 의해서도 가능하다. 
// 
//하지만, C++과는 다른 함수형 프로그래밍 형태로 나타난다.
//		이 기법으로 작성된 프로그램은 변수 값을 바꿀 수 없다. 일단 초기화된 값은 바꿀 수 없다는 뜻 *** 
//		즉, 상수식을 사용하고, if 문 같은 실행할 때 이루어지는 코드 사용이 안 됨.
//  	메타프로그램에서의 if 대신, '템플릿 특수화', SFINAE 등의 방법을 사용한다. *** 
//		메타프로그램에서의 순서 제어는 for 대신, '재귀'를 통해 이루어진다.	*** 
//		메타프로그램에서의 함수는 컴파일 타임에 호출할 수 있는 함수여야 한다.	   ***
//		C++ 에선 '클래스'와 '클래스 템플릿'이 '메타 함수'이다.	 *** 


// 템플릿만으로 더하기를 구현하자. ***
//		변수할당, if, for, 함수 사용 불가.


//특정 타입 정의하기 -----------------------------------------------------------

#include <iostream>

template <int N>		//템플릿 인자에는 타입뿐만 아니라 데이터 역시 사용이 가능
struct Int {
	static const int num = N;				//템플릿 Int  //변수 ***
};

template <typename T, typename U>			//템플릿 add  //메타 함수 ***
struct add {
	typedef Int<T::num + U::num> result;	
};

int main() {

	typedef Int<1> one;						//one::num ?
	typedef Int<2> two;						//two::num ?

	//one a;								//one 과 two 는 객체가 아닌 타입
	//two b;

	typedef add<one, two>::result three;	//타입을 이용해 변수처럼 활용 (변수 대입 X) 

	//Int< Int<1>::num + Int<2>::num >

	std::cout << "Adddition result : " << three::num << std::endl;

}


//컴파일 타임에 비교하기 (if X) -----------------------------------------------------------

// is_same_type 구현				- // 특수화 활용 ***

template <typename T1, typename T2>
struct is_same_type	{ enum { value = false };};		// 상수식, enum 활용

template <typename T>								// 부분 특수화를 이용해 구현 
struct is_same_type<T, T> { enum { value = true }; };		

int main()
{
	cout << is_same_type<int, double>::value << endl;
	cout << is_same_type<int, int>::value << endl;
}


// 컴파일 타임에 반복하기 -----------------------------------------------------------------
 
// 컴파일 타임 팩토리얼 계산하려면  - 재귀를 활용 ( for X ) ***

/*
	int factorial(int n) {
		if (n == 0)	return 1;
		return n * factorial(n - 1);
	}
	int main()
	{
		factorial(4);
	}
	//이 경우 factorial(4)의 값은 실행 시점에 계산된다.
*/

#include <iostream>

template <int N>
struct Factorial {
	static const int result = N * Factorial<N - 1>::result;		//재귀
};

template <>
struct Factorial<1> {
	static const int result = 1;
};

int main()
{
	std::cout << "6! = 1*2*3*4*5*6 = " << Factorial<6>::result << std::endl;

	//반복문이 필요 없고, 상당히 최적화된 코드를 얻을 수 있어 좋다.
}

/*
//두 수의 최대공약수  -----------------------------------------------------------

	int gcd(int a, int b) {
		if (b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}

// TMP 로 바꿔보면 아래와 같다 ----------------

	#include <iostream>

	template <int X, int Y>
	struct GCD {
		static const int value = GCD<Y, X % Y>::value;
	};

	template <int X>
	struct GCD<X, 0> {
		static const int value = X;
	};

	int main() {
		std::cout << "gcd (36, 24) :: " << GCD<36, 24>::value << std::endl;
	}
*/


//C++11 이후 부터는 enum 대신 constexpr을 사용할 수 있다. ---------------------------------------

#include <iostream>
#include <type_traits>
using namespace std;

template<int N> struct Factorial
{
	//enum { value = N * Factorial<N-1>::value };
	static constexpr int value = N * Factorial<N - 1>::value;
};
template<> struct Factorial<1>		// 재귀의 종료를 위해 특수화(Specialization)
{
	//enum { value = 1 };
	static constexpr int value = 1;
};

int main()
{
	int n = Factorial<5>::value; // 5 * 4 * 3 * 2 * 1 => 120
	// 5 * Factorial<4>::value
	// 4 * Factorial<3>::value
	// 3 * Factorial<2>::value
	// 2 * Factorial<1>::value
	// 1

	cout << n << endl;
}

//if constexpr ---------------------------------------------------------------------------
//		if 문은 템플릿 특수화, 템플릿 타입 유추를 통해 구현.
//		C++17 이후   if constexpr 로 처리 가능. ***


//constexpr 함수 ---------------------------------------------------------------------------
//
//		함수앞에 constexpr 붙이면, 
//		파라미터가 컴파일 타임 상수일 경우, 함수를 컴파일 시간에 연산(성능 이점)
//		일반 변수 파라미터 입력시, 일반 함수처럼 동작

#include <iostream>
#include <type_traits>
using namespace std;

template<int N> struct Check
{
};

constexpr int add(int a, int b)		// constexpr 함수(c++11)
{
	return a + b;
}

int main()
{
	int n1 = 1, n2 = 2;

	int n = add(n1, n2);   // OK(일반 변수 파라미터 입력 시 일반 함수처럼 동작)
	int m = add(1, 2);     // OK(컴파일 타임 상수 파라미터 입력 시 컴파일 타임에 연산)

	Check<add(1, 2)> c;    // OK(컴파일 타임에 연산됨으로 템플릿 파라미터로 사용 가능) ***
	Check<add(n1, n2)> c2; // Error(일반 함수처럼 동작하므로 템플릿 파라미터로 사용 불가)
}
