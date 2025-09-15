// 템플릿 타입 추론 규칙 --------------------------------------------

// T에 대한 타입 추론, 또 하나는 ParamType에 대한 타입 추론. 이 둘은 다른 경우가 많다.
// ParamType에 흔히 const나 참조 한정사(&나&& 를 말한다) 같은 수식어들이 붙은 경우가 있음

// 템플릿 타입 추론 도중에, 참조 타입의 인수들은 비참조로 취급된다.
// 즉, 일반적으로 추론이 auto 와 같다 ***

#include <iostream>
#include <vector>
using namespace std;


template<typename T>		//T
void foo(const T& param)    //const T&		//ParamType 이 다른 경우
{
	// T, param 의 타입은 ???
}

int main()
{
	int x = 0;
	foo(x);				// param 은 const int&로 추론, T는 int로 추론
	

	const int cx = x;
	foo(cx);			// param -  const int&      T- int

	const int& rx = x;
	foo(rx);			// param -  const int&		T- int

	return 0;
}


//-----------------------------------------------------------------------------
//경우 1: ParamType이 포인터도 아니고 참조도 아님		- & c v 무시
// 
//		param은 주어진 인수의 복사본, 즉 완전히 새로운 객체이다.
//		expr의 타입이  참조, const, volatile 이면  무시한다

	template <typename T>
	void f(T param);					// param이 값으로 전달된다	-> T는 &, const, volatile 무시

	int main()
	{
		// 그리고 이런 변수 선언들이 있다고 하자.
		int x = 27;						// x는 int
		const int cx = x;				// const int
		const int& rx = x;				// const int&
		
		f(x);							// T와 param의 타입은	둘 다 int
		f(cx);							// T와 param의 타입은	둘 다 int
		f(rx);							// T와 param의 타입은	둘 다 int

		// cx와 rx가 const 값을 지정하지만, 그래도 param은 const가 아님을 주목하자.
		// param은 cx나 rx의 복사본이므로, 다시 말해 param은 완전히 독립적인 객체이므로, 이는 당연한 결과이다.
		// 여기서 명심할 것은, const가(그리고 volatile이) 값 전달 매개변수에 대해서만 무시된다는 점이다.
	}

//-----------------------------------------------------------------------------
//경우 2: ParamType이 포인터 또는 참조 타입이지만 보편 참조(universal reference)는 아닌 경우 
// 
//		만일 expr이 참조 타입이면 참조 부분을 무시한다.			

	// 함수 템플릿이 다음과 같다고 하자.
	template <typename T> 
	void f(T& param)					// param은 T&	 -> T는 & 무시,  const, volatile 반영
	{
	}
	int main()
	{
		int x = 27;						// 이전과 동일
		const int cx = x;				// 이전과 동일
		const int& rx = x;				// 이전과 동일
				
		f(x);							// param의 타입은 int&      , T는 int,		  
		f(cx);							// param의 타입은 const int&, T는 const int, 
		f(rx);							// param의 타입은 const int&, T는 const int, 

		// 둘째, 셋째 호출에서 cx와 rx에 const 값이 대입되었기 때문에 T는 const int로 추론된다.
		// 셋째 호출에서, 비록 rx의 타입이 참조이지만 T는 비참조로 추론되었음을 주목하자.
	}

	// f의 매개변수의 타입을 T&에서 const T&로 바꾸면 상황이 조금 달라진다.

	template <typename T>
	void f(const T& param);				// param은 const T&	 -> T는 &, const 무시 
	int main()
	{
		int x = 27;						// 이전과 동일
		const int cx = x;				// 이전과 동일
		const int& rx = x;				// 이전과 동일

		f(x);							// param의 타입은 const int&, T는 int 
		f(cx);							// param의 타입은 const int&, T는 int
		f(rx);							// param의 타입은 const int&, T는 int

		// 이전처럼, 타입 추론 과정에서 rx의 참조성은 무시된다.
	}

	// param이 참조가 아니라 포인터 (또는 const를 가리키는 포인터) 라도, 
	// 타입 추론은 본질적으로 같은 방식으로 진행된다.

	template <typename T>
	void f(T* param);					// 이번에는 param이 포인터	-> T는 * 무시
	int main()
	{
		int x = 27;						// 이전과 동일
		const int* px = &x;				// px는 const int로서의 x를 가리키는 포인터

		f(&x);							// param의 타입은 int *		 , T는 int,       
		f(px);							// param의 타입은 const int * , T는 const int, 
	}

//-----------------------------------------------------------------------------
//경우 3: ParamType이 보편 참조(universal reference) 인 경우
// 
//		보편 참조(universal reference)가 관여하는 경우에는
//		좌측값 인수와 우측값 인수에 대해 서로 다른 추론 규칙들이 적용된다.
// 
//		만일 expr이 좌측값이면, T 와 ParamType 둘 다 좌측값 참조로 추론된다.  ***
//		만일 expr이 우측값이면, '정상적인' 규칙들이 적용

//		보편 참조(universal reference)가 아닌 매개변수들에 대해서는 그런 일이 절대 발생하지 않는다.

	template<typename T>
	void f(T&& param);				// 이번에는 param이 보편 참조(universal reference)
	int main()
	{
		int x = 27;						// 이전과 동일
		const int cx = x;				// 이전과 동일
		const int& rx = x;				// 이전과 동일
		f(x);							//  x는 좌측값, 따라서 T는 int&,       param의 타입도 int&
		f(cx);							// cx는 좌측값, 따라서 T는 const int&, param의 타입도 const int&
		f(rx);							// rx는 좌측값, 따라서 T는 const int&, param의 타입도 const int&
		f(27);							// 27은 우측값, 따라서 T는 int, 그러므로 param의 타입은 int&&
	}



//-----------------------------------------------------------------------------
// expr이 const 객체를 가리키는 const 포인터이고 param에 값으로 전달되는 경우는 어떨까 ???
// 이런 예를 보자.

	template <typename T>
	void f(T param);					// 인수는 param에 여전히 값으로 전달된다.
	int main()
	{
		const char* const ptr = "abc";	// ptr는 const 객체를 가리키는 const 포인터
		f(ptr);							// const char * const 타입의 인수를 전달
	}

	// 이 경우 포인터 자체(ptr)는 값으로 전달된다. 따라서 ptr의 상수성은/ 무시된다.
	// 하지만, ptr이 가리키는 객체 (여기서는 문자열)의 상수성은/ 여전히 보존된다.
	// 그 결과 T와 param의 타입은 둘 다 const char*로 추론된다.


//-----------------------------------------------------------------------------
// 
//템플릿 타입 추론 과정에서 배열이나 함수 이름에 해당하는 인수는 포인터로 붕괴(decay)한다.
//단, 그런 인수가 참조를 초기화하는 데 쓰이는 경우에는 포인터로 붕괴(decay)하지 않는다.

	//void myFunc(int param[]);  ->  void myFunc(int* param);   로 해석

	template<typename T>
	void f(T param);
	int main()
	{
		const char name[] = "abc";
		f(name);					// name은 배열이지만 T와 param은 const char*로 추론된다.

	}

	//배열에 대한 참조로 선언할 수는 있다.
	template<typename T>
	void f(T& param);
	int main()
	{
		const char name[] = "abc";
		f(name);					// 배열을 f에 전달
	}

//배열 예제 -------------------------------------------------------------------------------

	//함수를 constexpr로 선언하면 함수 호출의 결과를 컴파일 도중에 사용할 수 있게 된다.
	template <typename T, std::size_t N>
	constexpr std::size_t arraySize(T(&)[N]) noexcept   
	{                                                   
		return N;                                       
	}

	//그러면 다음 예처럼, 배열과 같은 크기(원소 개수)의 새 배열을 선언하는 것이 가능해진다.
	{
		int keyVals[] = { 1, 3, 7, 9, 11, 22, 35 };            // keyVals의 원소 개수는 7
		int mappedVals[arraySize(keyVals)];                    // mappedVals의 원소 개수 역시 7

		// 물론 현대적인 C++ 개발자라면 당연히 내장 배열보다 std::array를 선호할 것이다.
		std::array<int, arraySize(keyVals)> mappedVals;        // mappedVals의 크기는 7
	}

/*
	//배열의 주소 ---------------------------------------------------

	#include <iostream> 
	int main() { 
		int i = 1; 
		int *px = &i; 

		int x[3] = { 1, 2, 3 }; 
		int *p1 = x;		// 일반적으로 생각하는 배열의 주소 (묵시적으로 첫번째 요소의 주소로 형변환 됨) 
		int(*p2)[3] = &x;	// 정확한 배열의 주소 (요소가 모두 포함된 전체 컨테이너의 주소) 

		printf("%p, %p\n", p1, p1 + 1); // 배열의 첫번째 요소의 주소에서 데이터 사이즈인 4바이트 증가 
		printf("%p, %p\n", p2, p2 + 1); // 요소가 3개인 배열의 주소에서 데이터 사이즈인 12바이트 증가 
	}
*/

//함수 예제 ------------------------------------------------------------------------------------

	void someFunc(int, double);		// someFunc는 하나의 함수; // 타입은 void(int, double)

	template <typename T>
	void f1(T param);               // f1의 param은 값 전달 방식

	template <typename T>
	void f2(T& param);              // f2의 param은 참조 전달 방식

	int main()
	{
		f1(someFunc);               // param은 함수 포인터로 추론됨;	// 타입은 void (*)(int, double)
		f2(someFunc);               // param은 함수 참조로 추론됨;   // 타입은 void (&)(int, double)
	}

/* 출력은?
	#include <iostream>
	using namespace std;

	template <typename T>			//???    //const int
	void f(T* param)				//???    //const int*
	{
		cout << typeid(T).name() << endl;			//const int -> int
		cout << typeid(param).name() << endl;
	}

	int main()
	{
		const int a = 0;
		f(&a);
	}
*/