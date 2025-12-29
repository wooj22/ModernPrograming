
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

int main()
{
	auto func = [](const int n) {return n * n; };
	auto v4{ getVector() | std::views::transform(func) };
	// ERROR : getVector()는 rvalue vector입니다. 
	// view도 아니고, borrowed range도 아닙니다.


	//std::ranges::for_each(v4, [](auto a) { std::cout << a << " "; });
}


// C++20의 범위 라이브러리에서는 * *범위(ranges) * *의 개념에 기반하고 있으며, 
// 파이프 연산자의 왼쪽에는 std::ranges::range 컨셉을 만족하는 객체가 올 수 있습니다. ***
// 
// Rvalue 컨테이너의 문제 ***
//		범위 작업이 끝나기 전에 소멸될 가능성이 있습니다.
// 
// 해결 방법
// 
//1. 변수에 저장하여 lvalue로 변환
//
//	auto tempVec = getVector();
//	auto v4 = tempVec | std::views::transform(func);
//
//2. std::ranges::owning_view 사용
//	C++23에서는 **std::ranges::owning_view**를 사용하여 rvalue 컨테이너를 안전하게 사용할 수 있습니다.
// 
//	auto v4 = std::ranges::owning_view{getVector()} | std::views::transform(func);
//
//3. std::move를 사용하여 컨테이너를 전달
//
//  auto v4 = std::views::all(std::move(getVector())) | std::views::transform(func);
//
// 파이프 연산자(| )의 왼쪽에는 뷰 또는** borrowed_range** 가 와야 안전합니다.  ***









