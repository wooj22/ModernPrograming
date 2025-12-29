// Views
//		view는 '요소를 소유하지 않은 범위'라고 합니다.
// 
//	 조금 더 공식적으로, view는 다음과 같습니다.
// 
//		기본 생성 가능(is default constructible)
//		constant-time 의 이동 연산과, 파괴 연산(destruction operations)이 있습니다.
//		(만약 복사 가능한 경우) constant-time 의 복사 연산이 있습니다.

//https://en.cppreference.com/w/cpp/ranges/view

// Vewable ranges
//		views와 borrowed ranges는 'viewable ranges' 라고 불립니다. ( Range concepts )
//
// view 는 
//		constant-time 의 copy / move / destroy가 있으며 
//		view_base 를 상속했거나 enable_view 를 사용한 경우 입니다.
//
// borrowed ranges ( safe_range )
//		ranges가 스코프를 벗어나더라도 반복자가 살아있는 ranges를 뜻합니다.
//		(dangling 이 아니거나, 반복자를 역참조 즉, operator* 했을 때 객체가 살아 있는 경우) 
// 
//		borrowed ranges 에는 두 가지 경우가 있습니다.
// 
//		1. lvalue 참조(T&)에 대한 ranges는 항상 'borrowed ranges' 입니다.
//		   lvalue 참조는 값 자체가 아니므로, 소멸되어도 괜찮습니다.
//		2. 'enable_borrowed_range'가 
//		   borrowed 된 것으로 간주되도록 반드시 선택해야 하는 범위

/*
	template <class _Ty> 
	concept view = range<_Ty> && movable<_Ty> && enable_view<_Ty>;

	template<class R> 
	concept borrowed_range = ranges::range<R> && 
		(std::is_lvalue_reference_v<R> || ranges::enable_borrowed_range<std::remove_cvref_t<R>>);
*/

#include <ranges>

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

std::vector<int> getVector()
{
	std::vector<int> vec{ 5, 22, 88, -12, 14 };
	return vec;
}

std::span<int> getSpan() {
	std::vector<int> vec{ 5, 22, 88, -12, 14 };
	std::span<int> sp1(vec);			//std::span 은 연속 객체 순차열을 참조 하는 객체.
	return sp1;
}

int main()
{
	std::vector<int> vec{ getVector() };

	auto iter1{ std::min_element(vec.begin(), vec.end()) };		//STL algorithm

	auto iter2{ std::ranges::min_element(vec) };				//borrowed_iterator_t


	//모든 집합 들은 view로 변환이 가능합니다. ------------------------------------

	auto view{ std::views::all(vec) };		//ref_view 객체

	//반복자는 항상 값을 제대로 들고 있어야 합니다.

	//auto func = []() {};
	auto func = [](const int n) {return n * n; };

	auto v1{ vec | std::views::transform(func) };
	// OK: vec은 lvalue입니다.

	auto v2{ getSpan() | std::views::transform(func) };
	// OK : span은 borrowed 입니다. ( span은 보통 view 입니다. )

	auto v3{ std::ranges::subrange(vec.begin(), vec.end()) | std::views::transform(func) };
	// OK : subrange는 borrowed 입니다. ( view 입니다. )

	auto v4{ getVector() | std::views::transform(func) };
	// ERROR : getVector()는 rvalue vector입니다. 
	// view도 아니고, borrowed range도 아닙니다. 
	// Rvalue 컨테이너는 사라질 우려 - 수명관리가 필요. 
}


//view에 대한 또 하나의 예시를 봅시다. ---------------------------------------

#include <ranges>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

int main()
{
	{
		vector vec = { -2, -1, 0, 1, 2 };
		//auto vec = { -2, -1, 0, 1, 2 };						//	error
		std::transform(vec.begin(), vec.end(), vec.begin(),	[](int i) {return i * i; });
		auto sumsq{ std::accumulate(vec.begin(), vec.end(), 0) };
	}

	//view -----------------------
	{
		auto vec = { -2, -1, 0, 1, 2 };
		auto view{ std::views::transform(vec, [](int i) { return i * i; }) };
		auto sumsq{ std::accumulate(view.begin(), view.end(), 0) };
	}
	//view -----------------------
	{
		auto vec = { -2, -1, 0, 1, 2 };
		auto view{ vec
			| std::views::transform([](int i) { return i * i; })
			| std::views::common };
		auto sumsq{ std::accumulate(view.begin(), view.end(), 0) };
	}

	//views::common은 ranges의 iterator를 감시하는 역할이라고 보면 됩니다.
	//	iterator / sentinel 이 주어질 때, 다른 유형의 'view'가 존재 한다면, 
	//	그 'view'들을 동일한 유형으로 바꾸는 작업을 합니다.

	return 0;
}


//views::common --------------------------------------------------------
 
	//range를 받아 vector로 변경하는 함수 
	template <std::ranges::range R>
	auto toVector(R&& r) {
		auto r_common{ r | std::views::common };
		return std::vector(r_common.begin(), r_common.end());
	}

//views::common 은 
//
//	범위(view)의 공통화를 위해 사용됩니다.(C++20에서 도입된 Ranges 라이브러리)
//	이 함수는 범위를 순회할 때 모든 const와 volatile 수식어를 제거하고, 
//	기본적으로 변경 가능한 범위를 생성합니다.
// 
//	range 객체 하나를 받고 그것이 이미 
//	common_range라면 std::views::all(r)의 결과를 주고,
//	common_range가 아니라면 r를 토대로 common_view를 구축하고 반환합니다.
//  
//common_view는 
//	C++20 이후의 iterator를 C++17 이전의 iterator로 변환하는 작업을 합니다.


//C++20 이후 ranges/iterator 라이브러리에서는 
//		begin()으로 얻는 것을 iterator, 
//		end()로 얻는 것을 sentinel 이라고 합니다. ***
