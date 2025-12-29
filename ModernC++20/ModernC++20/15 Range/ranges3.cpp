//투영 (Projection)
// 
//	view를 만드는 것과 vec이라는 변수를 만드는 것 자체도 멋져보이지 않을 수 있습니다.
//	이럴 땐 투영(Projection)을 사용합니다.
//	projection은 범위의 각 요소에 대해 변환을 적용할 수 있는 방식입니다.
// 
//	ranges algorithm 대부분은 projection을 지원합니다.
//	projection은 기본적으로 알고리즘을 스스로 호출합니다. projection은 callable 입니다.

#include <iterator>
#include <ranges>

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

template <std::input_iterator I, std::sentinel_for<I> S,	//들어오는 값이 iterator/sentinel 임을 제한
	typename Init = std::iter_value_t<I>,
	typename Op = std::plus<>,
	typename Proj = std::identity>
Init accumulate(I first, S last, Init init = Init{}, Op op = Op{}, Proj proj = Proj{}) {
	while (first != last) {
		init = std::invoke(op, std::move(init), std::invoke(proj, *first));
		++first;
	}
	return init;
}

template <std::ranges::input_range R,					//concept를 사용하여 들어오는 값이 range 임을 제한
	typename Init = std::ranges::range_value_t<R>,
	typename Op = std::plus<>,
	typename Proj = std::identity>						
Init accumulate(R&& range, Init init = Init{}, Op op = Op{}, Proj proj = Proj{})	//투영 (Projection)을 사용
{
	return accumulate(std::ranges::begin(range), std::ranges::end(range),			//begin, end
		std::move(init), std::move(op), std::move(proj));
}


std::vector<int> getInput() { return { -2, -1, 0, 1, 2 }; }

int main() {
	auto accsq{ accumulate(getInput(), {}, {}, [](int i) { return i * i; }) };
	std::cout << accsq << std::endl;
}