//range 구현

#include <ranges>
#include <iostream>
#include <algorithm>
#include <vector>

//range 를 구현하려면, 가장 먼저 해야할 것은
//std::ranges::view_interface 를 상속받는 것이다.

//view_interface 는 CRTP 으로 구현되어 있으므로 구현할 클래스를 템플릿 파라미터로 전달
/*
	class iota_view : public std::ranges::view_interface<iota_view>
	{
		// To do...
	}
*/

//이제 필요한 것은 무엇일까 ?
//iota_view 는 range 이므로, std::ranges::range 컨셉을 만족해야 한다.
 
//range 컨셉은 다음과 같다.
/*
	// CONCEPT ranges::range
	template <class Rng>
	concept range = requires(Rng & r) {
		std::ranges::begin(r);
		std::ranges::end(r);
	};
*/

//그리고 begin(), end() 함수는 
//iota_view 가 생성될 때 인자로 전달받은
//begVale, endValue 를 가리키는 Iterator 를 리턴해야 한다.

class iota_view : public std::ranges::view_interface<iota_view>
{
	int begValue = 0;
	int endValue = std::numeric_limits<int>::max();

public:
	iota_view() = default;
	iota_view(int begValue, int endValue = std::numeric_limits<int>::max())
		: begValue(begValue), endValue(endValue)
	{}

	struct Iterator
	{
		using value_type = int;
		using difference_type = int;

		int pos;

		Iterator() = default;
		Iterator(int pos) : pos(pos) {}

		Iterator& operator++()	// 레퍼런스를 리턴해야 한다.
		{						// weakly_incrementable 컨셉
			++pos;
			return *this;
		}

		Iterator operator++(int)
		{
			int tmp = pos;
			++pos;
			return Iterator(tmp);
		}

		// indirectly_readable 및 forward_iterator 컨셉을 만족하려면
		// 아래 두 함수의 리턴타입은 같아야 함
		const int& operator *() const {
			return pos;
		}

		const int& operator *() {
			return pos;
		}

		bool operator==(const Iterator& _other) const
		{
			return this->pos == _other.pos;
		}
	};

	Iterator begin()
	{
		return Iterator(begValue);
	}

	Iterator end()
	{
		return Iterator(endValue);
	}
};

int main()
{
	auto rng = iota_view(0, 5);
	for (auto e : rng) std::cout << e << " "; std::cout << std::endl; // [0,1,2,3,4]

	auto rng2 = iota_view(0) | std::ranges::views::take(3);
	for (auto e : rng) std::cout << e << " "; std::cout << std::endl; // [0,1,2]
}


/*
iota_view 에는 operator | () 를 구현하지 않아도 된다.
이미 구현되어 있는 view 들과 파이프라이닝 될 수 있도록
operator| () 가 friend 함수로 구현되어 있다.

VS를 사용한다면, ranges 헤더파일에서 "operator|" 를 검색해보는 것이 이해에 도움이 될 것이다.

추가로, 파이프라이닝에는 views::take() 처럼 view 함수객체를 사용하는 것이 편한데,
간략하게 구현해서 사용하려면 다음과 같이 구현하면 된다.

namespace
{
	class iota_fn
	{
	public:
		iota_view operator()(
			int begValue,
			int endValue = std::numeric_limits<int>::max())
		{
			return iota_view(begValue, endValue);
		}
	};

	inline iota_fn iota; // 함수객체 선언
}

*/