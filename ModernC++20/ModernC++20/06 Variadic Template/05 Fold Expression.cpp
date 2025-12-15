//재귀 함수 호출을 종료하기 위해 베이스 케이스를 꼭 만들어줘야 한다는 점이 불편
// 
//하지만 C++ 17 에 새로 도입된 'Fold 형식'을 사용한다면 이를 훨씬 간단하게 표현


// Fold expressions (C++17) -----------------------------------------------------
//
//    Variadic Template의 parameter들을 unpack 하는 새로운 방식
// 
//    recursion을 끝내기 위한 종료자 함수들 만들어야하는 불편 해소 
//    VisualStudio에서는 2017 15.5 버전 이후부터 /std:c++17 옵션

/*

// 이항 연산자를 사용해서 parameter pack안에 있는 요소에 연산을 수행하는 문법

// parameter pack의 이름에서 ... 붙이지 않고 사용
		pack expansion  : args...          // args ...
		fold expression : args + ...       // args 연산자 ...

// Fold 방식의 종류

	(args op ...)           단항 우측 Fold  ( unary right fold )
	(... op args)           단항 좌측 Fold  ( unary left fold )
	(args op ... op Init)	이항 우측 Fold  ( binary right fold )
	(Init op ... op args)	이항 좌측 Fold  ( binary left fold )

	// Init 는 초기값
	// op 자리에는 대부분의 이항 연산자들이 포함될 수 있습니다. 예를 들어서 +, -, <, <<, ->, , 등등
	// Fold 식을 쓸 때 꼭 () 로 감싸줘야 한다

// Fold 방식 4가지 형태 예시 (args : 1, 2, 3, 4)

	unary right fold  : (args op ...)			// (args + ...)        // 1 + ( 2 + ( 3 + 4 ) )
	unary left fold   : (... op args)			// (... + args)        // ( ( 1 + 2 ) + 3 ) + 4
	binary right fold : (args op ... op init)   // (args + ... + 10)   // 1 + ( 2 + ( 3 + ( 4 + 10 ) ) )
	binary left fold  : (init op ... op args)	// (10 + ... + args)   // ( ( ( 10 + 1 ) + 2 ) + 3 ) + 4
*/

#include <iostream>

// Unary RIGHT fold
template<typename... Args>
auto SumCpp1(Args... args) { return (args + ...); }

// Unary LEFT fold
template<typename... Args>
auto SumCpp2(Args... args) { return (... + args); }

// Binary RIGHT fold
template<typename... Args>
auto SumCpp3(Args... args) { return (args + ... + 1); } //init

// Binary LEFT fold
template<typename... Args>
auto SumCpp4(Args... args) { return (1 + ... + args); } //init

int main() {
	auto val1 = SumCpp1(3, 5, 7, 9);    // unpack 흐름 (3 + (5 + (7 + 9)))         // val = 24
	auto val2 = SumCpp2(3, 5, 7, 9);    // unpack 흐름 (((3 + 5) + 7) + 9)         // val = 24
	auto val3 = SumCpp3(3, 5, 7, 9);    // unpack 흐름 (3 + (5 + (7 + (9 + 1))))   // val = 25
	auto val4 = SumCpp4(3, 5, 7, 9);    // unpack 흐름 ((((1 + 3) + 5) + 7) + 9)   // val = 25
}



// func(1,2,3,4);  //Fold Expression  4가지 방식으로 빼기를 구현하세요. ----------------
// 
// (pack op ...)           (1) Unary right fold
// (...  op pack)          (2) Unary left fold
// (pack op ... op init)   (3) Binary right fold
// (init op ... op pack)   (4) Binary left fold

#include <iostream>
using namespace std;

template <typename... TArgs>
int UnaryRightFold(TArgs&&... args) { return (args - ...); }

template <typename... TArgs>
int UnaryLeftFold(TArgs&&... args) { return (... - args); }

template <typename... TArgs>
int binaryRightFold(TArgs&&... args) { return (args - ... - 10); }

template <typename... TArgs>
int binaryLeftFold(TArgs&&... args) { return (10 - ... - args); }

int main()
{
	cout << UnaryRightFold(1, 2, 3, 4) << endl;     // 1 - (2 - (3 - 4))
	cout << UnaryLeftFold(1, 2, 3, 4) << endl;      // (( 1 - 2) - 3) - 4
	cout << binaryRightFold(1, 2, 3, 4) << endl;    // 1 - (2 - (3 - (4 -10)))
	cout << binaryLeftFold(1, 2, 3, 4) << endl;     // (((10 - 1) - 2) - 3) - 4

	return 0;
}



//예시 sum_all ----------------------------------------------------------------

//임의의 가변 정수를 받아 합을 구하는 함수 작성하기

#include <iostream>

int main()
{
	std::cout << sum_all(1, 4, 2) << std::endl;
	// 1 + 4 + 2
	std::cout << sum_all(1, 4, 2, 3, 10) << std::endl;
	// 1 + 4 + 2 + 3 + 10  
}

/*
	template <typename... Ints>
	int sum_all(Ints... nums) {
		return (... + nums);				//단항 좌측 Fold (Unary left fold)
	}
*/

//예시 ---------------------------------------------------------------------

#include <iostream>

// 100 에서, 임의의 가변 데이타를 빼는 함수 구현하기 ***

int main()
{
	std::cout << diff_from(100, 1, 4, 2, 3, 10) << std::endl;		// 100 - 1 - 4 - 2 - 3 - 10
}

/*

template <typename Int, typename... Ints>
Int diff_from(Int start, Ints... nums) {
	return (start - ... - nums);		//이항 좌측 Fold
}

*/

//예시 ---------------------------------------------------------------------
//	, 연산자를 사용하면 각각의 인자들에 대해 원하는 식을 실행할 수 있습니다. ***

#include <iostream>

class A {
public:
	void do_something(int x) const {
		std::cout << "Do something with " << x << std::endl;
	}
};

template <typename T, typename... Ints>
void do_many_things(const T& t, Ints... nums)
{
	(t.do_something(nums), ...); // 각각의 인자들에 대해 do_something 함수들을 호출한다.
}

int main() {
	A a;
	do_many_things(a, 1, 3, 2, 4);
}

/*
#include <iostream>
using namespace std;

template < typename... Ints>
void print( Ints... nums)
{
	( (cout << nums << " "), ..., (cout << endl));
}

int main()
{
	print(1, 3, 2, 4);
}

*/
