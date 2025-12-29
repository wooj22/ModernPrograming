//range 변환

#include <ranges>
#include <iostream>
#include <algorithm>
#include <vector>

template<class Rng>
	requires std::ranges::range<Rng>
auto toVector(Rng& rng)
{
	std::vector<std::ranges::range_value_t<decltype(rng)>> v;

	if constexpr (std::ranges::sized_range<decltype(rng)>) {
		v.reserve(std::ranges::size(rng));
	}

	std::ranges::copy(rng, std::back_inserter(v));
	return v;
}

int main()
{
	//vector -> ranges

	std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	auto r = std::ranges::views::all(v);


	//ranges -> vector

	std::vector<int> v1;
	for (int i : r) v1.push_back(i);

	auto common = std::views::common(r);					//std::views::common
	auto v2 = std::vector(common.begin(), common.end());

	auto v3 = toVector(v);									//custum template

	auto v4 = std::ranges::to<std::vector>(r);				//std::ranges::to

	for (auto e : v4) std::cout << e << " "; std::cout << std::endl;
	
}

//ranges::to ----------------------------------------------------------------------

#include <vector>
#include <ranges>
#include <iostream>
#include <algorithm>
using namespace std;

using IntMatrix = vector<vector<int> >;

int count_evens(const vector<int>& number_line) {
	return ranges::count_if(number_line, [](int num) {return num % 2 == 0; });
}

vector<int> count_all_evens(const IntMatrix& numbers)
{
	auto r = numbers | ranges::views::transform(count_evens);
	return ranges::to<vector<int>>(r);
}

int main()
{
	IntMatrix m{ {1, 2, 3}, {4, 5, 6} };

	//IntMatrix 의 각 행의 짝수 갯수를 가진 배열(vector<int>)을 반환하는 함수.
	// 1 2

	for (auto item : count_all_evens(m)) {
		std::cout << item << " ";
	}
	std::cout << std::endl;
	return 0;
}


//the "pipe" syntax -----------------------------------------------------------------

#include <iostream>
#include <ranges>

int main()
{
	auto const ints = { 0, 1, 2, 3, 4, 5 };
	auto even = [](int i) { return 0 == i % 2; };
	auto square = [](int i) { return i * i; };

	// a traditional "functional" composing syntax:
	for (int i : std::views::transform(std::views::filter(ints, even), square))
		std::cout << i << ' ';

	// the "pipe" syntax of composing the views:
	for (int i : ints | std::views::filter(even) | std::views::transform(square))
		std::cout << i << ' ';

	std::cout << '\n';
}