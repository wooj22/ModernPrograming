 //Range Factories , Range Adapters 예시

// std::ranges::views
// std::views				//namespace views = ranges::views; 로 정의되어 있음 ***

#include <ranges>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

template<class Rng>
	requires std::is_base_of_v<std::ranges::view_interface<Rng>, Rng>
std::ostream& operator<<(std::ostream& os, Rng& rng) {
	auto it = std::ranges::begin(rng);
	const auto e = std::ranges::end(rng);
	if (it == e) return os << "[]";
	os << '[' << *it;
	while (++it != e) os << "," << *it;
	os << ']';
	return os;
}

int main()
{
	//views::single
	//		한 개의 값을 range 로 만들 때 사용한다.
	{
		auto r = std::ranges::views::single(1);
		//auto r = std::views::single(1);	//namespace views = ranges::views; 
		std::cout << r << std::endl;		// [1]


		//값이란, range 도 포함한다.
		std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		auto r1 = std::views::all(v);
		auto r2 = std::views::single(r1);
		std::cout << r2 << std::endl;		// [[1,2,3,4,5,6,7,8,9,10]]
	}

	//views::filter
	//		view 란, range 를 여러 모양으로 보는 방법을 제공한다.
	{
		std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		auto rng = std::views::all(v)
			| std::views::filter([](int a) { return a % 2 == 0; });	// 짝수만 필터링

		std::cout << rng << std::endl; // [2,4,6,8,10]

		// 원본은 수정되지 않음. ***
		auto orinRange = std::views::all(v);
		std::cout << orinRange << std::endl; // [1,2,3,4,5,6,7,8,9,10]
	}

	// | (bit OR) 연산자를 통해 결합(파이프라이닝)될 수 있다. ***
	//
	//	  기존의 C++ 함수 호출 방식은 다음과 같이, 호출의 순서와는 반대로 작성된다.
	//			filter( all(v) );
	//	  파이프라인을 사용하면, 호출의 순서와 동일하게 코드를 작성할 수 있다.
	//			all(v) | filter()


	//views::transform
	//		transform() 은 range의 내용을 변경하며 순회할 때 사용한다.
	{
		std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		auto rng = std::ranges::views::all(v)
			| std::ranges::views::filter([](int a) {return a % 2 == 0; })
			| std::ranges::views::transform([](int a) {	return a * a; });

		std::cout << rng << std::endl; // [4,16,36,64,100]
	}

	//views::take
	//		take() 는 range 중, 맨 앞에 n개만 골라서 별도의 range를 만들 때 사용한다.
	{
		std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		auto rng = std::ranges::views::all(v)
			| std::ranges::views::filter([](int a) { return a % 2 == 0; })
			| std::ranges::views::transform([](int a) { return a * a; })
			| std::ranges::views::take(3);

		std::cout << rng << std::endl; // [4,16,36]
	}

	//views::reverse
	//		range 를 거꾸로 순회할 때 사용한다.
	{
		std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		auto rng = std::ranges::views::all(v)
			| std::ranges::views::filter([](int a) { return a % 2 == 0; })
			| std::ranges::views::transform([](int a) {	return a * a; })
			| std::ranges::views::reverse
			| std::ranges::views::take(3);

		std::cout << rng << std::endl; // [100,64,36]
	}

	//views::drop
	//		range 내의 처음 n 개의 원소를 스킵할 때 사용한다.
	{
		std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		auto rng = std::ranges::views::all(v)
			| std::ranges::views::filter([](int a) { return a % 2 == 0; })
			| std::ranges::views::transform([](int a) {	return a * a; })
			| std::ranges::views::reverse
			| std::ranges::views::drop(1)
			| std::ranges::views::take(3);

		std::cout << rng << std::endl; // [64,36,16]
	}
}


//--------------------------------------------------------------------------------------
// std::views::drop_while 예시
//	
// 어떠한 문자열이 들어오면, 선행/후행 공백이 제거된 새 문자열을 구성하려고 합니다.

#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>
#include <ranges>

template <std::ranges::range R>
auto trimFront(R&& rng) {
	return std::forward<R>(rng) | std::views::drop_while(::isspace);
}

template <std::ranges::range R>
auto trimBack(R&& rng) {
	return std::forward<R>(rng) |
		std::views::reverse |
		std::views::drop_while(::isspace) |
		std::views::reverse;
}

std::string StringTrimming(const std::string_view& str) {
	auto view{ str | std::views::common };
	auto trimString{ trimBack(trimFront(view)) };
	return std::string{ trimString.begin(), trimString.end() };
}

int main() {
	std::string str{ "\n\t\r Hello World! \n\n" };
	std::cout << StringTrimming(str) << std::endl;	// Hello World!
}

//Adaptor를 구성하고, 파이프 연산을 할 수 있습니다.	 //간결한 표현 가능
/*
auto trimFront() {
	return std::views::drop_while(::isspace);
}

auto trimBack() {
	return
		std::views::reverse |
		std::views::drop_while(::isspace) |
		std::views::reverse;
}

std::string StringTrimming(const std::string_view& str) {
	auto trimString{
		str | trimFront() | trimBack()
	};
	return std::string{ trimString.begin(), trimString.end() };
}

int main() {
	std::string str{ "\n\t\r Hello World! \n\n" };
	std::cout << StringTrimming(str) << std::endl;	// Hello World!
}
*/

//--------------------------------------------------------------------------------------
// std::ranges::for_each 
// std::views::transform 예시

#include <algorithm>
#include <cstdio>
#include <iterator>
#include <ranges>
#include <string>

char rot13a(const char x, const char a) {
	return a + (x - a + 13) % 26;
}

char rot13(const char x) {
	if ('Z' >= x and x >= 'A')		return rot13a(x, 'A');
	if ('z' >= x and x >= 'a')		return rot13a(x, 'a');

	return x;
}

int main()
{
	auto show = [](const unsigned char x) { std::putchar(x); };

	std::string in{ "cppreference.com\n" };
	std::ranges::for_each(in, show);
	std::ranges::for_each(in | std::views::transform(rot13), show);

	std::string out;
	std::ranges::copy(std::views::transform(in, rot13), std::back_inserter(out));
	std::ranges::for_each(out, show);
	std::ranges::for_each(out | std::views::transform(rot13), show);
}