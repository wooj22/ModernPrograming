//range를 반환하는 알고리즘
// 
//	range factories (래인지 팩토리) : 
//			range를 취하지 않고, range를 반환하는 알고리즘 
// 
//	range adaptors (래인지 어댑터) : 
//			기본적으로 하나 이상의 range를 취하고, '특정 작업을 적용한' range를 반환하는 알고리즘

//view_interface -----------------------------------------------------------------------------
// 
//		공통 부분의 구현을 단순화하기 위해 view_interface라는 클래스를 상속하고 있습니다.
//		'empty(), data(), size(), front(), back(), operator[]' 같은 
//		컨테이너들의 함수를 제공하고, 참조할 수 있습니다.

/*
	template<class D>
		requires is_class_v<D> && same_as<D, remove_cv_t<D>>
	class view_interface : public view_base {
		// impl
	};

	// D는 클래스 타입이며 const/volatile 키워드가 제거된 타입이어야 한다
	// 직접 view 를 정의할 때 사용되는데, 이것을 상속하면 std::ranges::enable_view가 자동으로 true가 됩니다.
	// view_base는 단순하게, view가 될 수 있는 클래스를 식별하기 위한 것
*/

//range factories ---------------------------------------------------------------------------
// 
//		std::ranges::filter_view 를 사용하지 않고 std::views::filter 를 사용한 것 처럼,
//		std::views의 네임스페이스에 view 객체들 중 몇몇을 'range factory' 라고 합니다.
// 
//		empty_view, single_view, iota_view, istream_view

//empty_view
//		단순히 T 타입의, 빈 시퀀스를 나타내는 view 입니다.
//		비어있는(empty) range를 제공할 때 사용됩니다.

#include <iostream>
#include <cassert>
#include <ranges>

int main()
{
	std::ranges::empty_view<int> sv;
	for (int n : sv) {
		assert(false);
	}

	for (int n : std::views::empty<int> ) {
		assert(false);
	}
}


//single_view
//		T 타입의 요소를 1개만 가지는 시퀀스를 나타내는 view입니다.
//		range를 가지고 알고리즘에 대해 1개 요소만 넣고 싶을 경우 등에 사용

#include <iostream>
#include <ranges>

int main() {
	std::ranges::single_view<int> sv{ 20 };

	for (int n : sv) {
		std::cout << n;
	}
}

//직접 생성자를 불러 구축할 수 있음
int main() {

	std::ranges::single_view<std::string> sv(std::in_place, "in place construct", 8);

	for (auto& str : sv) {
		std::cout << str; // in place
	}
}
// range factories를 사용
int main() {

	for (auto& str : std::views::single(std::string{ "in place construct", 8 })) {
		std::cout << str;
	}
}


//iota_view
//		iota_view는 건네받은 2 개의 값을 시작점과 끝점으로 사용하여, 
//		일정하게 증가하는 시퀀스를 나타내는 view 입니다.

//정수에 한정한다면, init, bound 두 값을 전달하면[init, bound) 의 범위에서 1씩 증가하는 수열을 생성합니다.
#include <iostream>
#include <ranges>
int main() {
	std::ranges::iota_view iv{ 1, 10 };

	for (int n : iv) {
		std::cout << n; // 123456789
	}
}

//또한 bound를 제공하지 않으면, '무한한 수열'을 생성합니다.
#include <iostream>
#include <ranges>
int main() {
	std::ranges::iota_view iv{ 1 };

	for (int n : iv) {
		std::cout << n;     // 1234567891011121314151617181920
		if (n == 20) break; // 20번째에서 빠져나오기 위해..
	}
}

//증가 가능하며 거리를 정의할 수만 있다면 어떤 형태든 가능합니다. //std::weakly_incrementable 에 의해 제한
#include <ranges>
#include <iostream>
#include <list>

int main() {

	int array[] = { 2, 4, 6, 8, 10 };
	// array 포인터 시퀀스
	std::ranges::iota_view iva{ std::ranges::begin(array), std::ranges::end(array) };

	for (int* p : iva) {
		std::cout << *p;  // 246810
	}
	std::cout << '\n';


	std::list list = { 1, 3, 5, 7, 9 };
	// list 컨테이너의 iterator를 사용한 시퀀스
	std::ranges::iota_view ivl{ std::ranges::begin(list), std::ranges::end(list) };

	for (auto it : ivl) {
		std::cout << *it; // 13579
	}
}

//std::weakly_incrementable 이 만족하려면 다음과 같아야 합니다.
//	++i 또는 i++ 같은 연산자를 통해 증가가 가능해야 합니다.
//	i가 증가 가능한 경우, ++i와 i++는 i의 다음 요소가 제공되어야 합니다. (즉 i + 1 은 i 다음의 요소가 제공되어야 함)
//	i가 증가 가능한 경우, addressof(++i)와 addressof(i)는 등치 상태입니다.

//iota_view 같은 경우 lazy operation 이므로, 이터레이터가 증가됨에 따라 1 개씩 요소가 계산됩니다.
#include <iostream>
#include <ranges>

int main() {
	std::ranges::iota_view iv{ 1, 10 }; // 이 때는 어떤 행동도 하지 않습니다.

	auto it = std::ranges::begin(iv); // 이 때는 어떤 행동도 하지 않습니다.

	int n1 = *it; // 1이라는 숫자를 이 때 계산합니다.
	++it;         // 2라는 숫자를 이 때 계산합니다.
	it++;         // 3이라는 숫자를 이 때 계산합니다.
	int n2 = *it; // 3이라는 숫자를 얻어낼 수 있습니다.
}

//range factories를 사용
#include <iostream>
#include <ranges>

int main() {
	for (int n : std::views::iota(1, 10)) {
		std::cout << n;   // 123456789
	}

	std::cout << '\n';

	for (int n : std::views::iota(1)) {
		std::cout << n;   // 1234567891011121314151617181920
		if (n == 20) break;
	}
}

//istream_view
//		istream이 나타내는 입력 스트림에 있는 T 값의 시퀀스를 생성하는 view 입니다.
//		이는 std::istream_iterator를 view로 재설계한 것입니다.
//		사실 view 클래스가 아니라, range factory 함수

#include <iostream>
#include <ranges>

int main() {
	for (int n : std::ranges::istream_view<int>(std::cin)) {
		std::cout << n; // 123456
	}
}

//------------------------------------------------------------------------------------------------------
//range adaptors는 range factories와는 다릅니다.
// 
//	range adaptors : 
//			기본적으로 하나 이상의 range를 취하고, '특정 작업을 적용한' range를 반환하는 알고리즘
//	range factories : 
//			range를 취하지 않고, range를 반환하는 알고리즘

//이전까지의 empty_view, single_view, iota_view, istream_view는 range factories 였습니다.
//하지만 아래부터는 range adaptors 입니다.

/*

//범위 팩토리(범위를 반환하지만 입력으로 범위가 없는 알고리즘)
//Range Factories
	empty_view
	single
	iota
	istream_view

//범위 어댑터(기본적으로 하나 이상의 범위를 가져와서 새로운 "적응된" 범위를 반환하는 알고리즘)
//Range Adaptors
	filter
	transform
	take
	take_while
	drop
	drop_while
	join
	split
	common
	reverse
	elements, keys, and values
*/

//---------------------------------------------------------------------------------------
//take_view
//		시퀀스의 시작 위치에서, 지정된 수만큼 요소를 꺼낸 시퀀스를 생성하는 view 입니다.
//		dangling 처럼 순서의 길이보다 긴 수를 지정하는 것을 대비해, 대책이 되어 있습니다.

#include <iostream>
#include <ranges>
#include <vector>

int main() {
	std::vector<int> numbers{ 1, 2, 3, 4, 5, 6 };

	// 앞의 3개 요소만 선택
	auto first_three = numbers | std::views::take(3);

	for (int n : first_three) {
		std::cout << n << " ";
	}

	return 0;
}

//dangling 처럼 순서의 길이보다 긴 수를 지정하는 것을 대비해, 대책이 되어 있습니다.

#include <ranges>
#include <iostream>
#include <list>
#include <ranges>
#include <forward_list>

int main() {
	using namespace std::string_view_literals;

	// 문자열의 크기보다 긴 길이를 지정한다. (random_access_iterator)
	std::ranges::take_view tv1{ "str"sv, 10 };

	int count = 0;
	for ([[maybe_unused]] char c : tv1) {		// 안전, 3번만 돕니다.		
		++count;
	}
	std::cout << "loop : " << count << '\n';	// loop : 3

		
	// list의 크기보다 긴 길이를 지정한다. (1.2의 std::counted_iterator)
	std::list li = { 1, 2, 3, 4, 5 };
	std::ranges::take_view tv2{ li, 10 };
	
	count = 0;	
	for ([[maybe_unused]] int n : tv2) {		// 안전, 5번만 돕니다.
		++count;
	}
	std::cout << "loop : " << count << '\n';	// loop : 5
}

//range adaptors를 사용 - view 들의 조작을 하는 함수를 'Adaptor' 라고 합니다.
 
// std::views::take

#include <iostream>
#include <ranges>

int main() {

	for (int n : std::views::take(std::views::iota(1), 5)) {
		std::cout << n;
	}

	std::cout << '\n';

	for (int n : std::views::iota(1) | std::views::take(5)) {
		std::cout << n;
	}
}

// std::views::take_while

#include <iostream>
#include <ranges>
#include <vector>

int main() {
	std::vector<int> numbers{ 1, 2, 3, 4, 5 };

	// 4보다 작은 값들만 선택
	auto result = numbers | std::views::take_while([](int n) { return n < 4; });	// predicate

	for (int n : result) {
		std::cout << n << " ";
	}

	return 0;
}


//--------------------------------------------------------------------------------------
// std::views::filter
//		어떠한 view가 들어왔을 때, 조건에 맞는 원소들만으로 새로운 view를 구축합니다.

//예를 들어, [0, 100] 사이의 값들 중 짝수만 출력하고 싶다면 다음과 같이 가능합니다.

#include <iostream>
#include <ranges>

int main()
{
	auto even = [](int elem) { return elem % 2 == 0; };

	for (int i : std::views::iota(0, 100) | std::views::filter(even))
	{
		std::cout << i << std::endl;
	}
}

//--------------------------------------------------------------------------------------
// std::views::drop
//		std::views::drop, std::views::drop_while 은 
//		Functor 을 받아 true 라면, view를 한칸 뒤로 밀게 됩니다.

#include <iostream>
#include <ranges>
#include <vector>

int main() {
	std::vector<int> numbers{ 1, 2, 3, 4, 5, 6 };

	// 3보다 작은 값 건너뛰고, 나머지 값을 2배로 변환
	auto result = numbers
		| std::views::drop_while([](int n) { return n < 3; })
		| std::views::transform([](int n) { return n * 2; });

	for (int n : result) {
		std::cout << n << " ";
	}

	return 0;
}

//--------------------------------------------------------------------------------------
//std::views::elements
//		C++20의 <ranges> 라이브러리에서 제공되는 범위 어댑터
//		튜플과 같은 복합 데이터 구조에서 특정 요소를 추출하는 데 사용
//		std::get<I>와 동일한 동작을 범위 뷰와 함께 사용하도록 설계

#include <iostream>
#include <ranges>
#include <vector>
#include <utility> // std::pair

int main() {
	std::vector<std::pair<int, std::string>> data = {
		{1, "Alice"},
		{2, "Bob"},
		{3, "Charlie"}
	};

	// 첫 번째 요소(정수)만 추출
	auto first_elements = data | std::views::elements<0>;

	for (int id : first_elements) {
		std::cout << id << " ";
	}

	return 0;
}