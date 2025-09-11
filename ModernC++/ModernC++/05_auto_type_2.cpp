// auto 활용 //명시적 타입 선언보다는 auto 쓰면 좋은 이유

//auto 변수는 반드시 초기화해야 하며, 
//		이식성 또는 효율성 문제를 유발할 수 있는 타입 불일치가 발생하는 경우가 거의 없으며, 
//		대체로 변수의 타입을 명시적으로 지정할 때보다 타자량도 더 적다.


#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main()
{
	// auto는 반드시 초기화 해야 한다.

	int x1;						// 문맥에 따라서는 초기화되지 않을 수 있음
	auto x2;                    // 오류! 초기치가 꼭 필요함
	auto x3 = 0;                // x3의 값이 잘 정의됨


	// "타입 단축(type shortcut)" 문제 회피

	std::vector<int> v;
	unsigned int sz = v.size();	// 64비트 Windows에서는 unsigned 는 32비트인 반면 std::vector<int>::size_type은 64비트
	auto sz = v.size();         // sz의 타입은 std::vector<int>::size_type  // 타입단축 안 일어남


	// 타자량도 더 적다

	std::unordered_map<std::string, int> m;
	for (const std::pair<std::string, int>& p : m) { }
	for (const auto& p : m)	{ }

	/*
	// b에서 e까지의 구간에 있는 모든 요소에 대해 dwim("do what I mean") 알고리즘을 수행한다.
	template <typename It>	 
	void dwim(It b, It e) {
		for (; b != e; ++b) {
			typename std::iterator_traits<It>::value_type  currValue = *b;
		}
	}

	template <typename It>
	void dwim(It b, It e)
	{
		for (; b != e; ++b) {
			auto currValue = *b;
		}
	}
	*/

	return 0;
}

/*
	// auto는 타입 추론을 사용하므로, 예전에는 컴파일러만 알던 타입을 지정할 수 있다.

	auto derefUPLess =      // std::unique_ptr들이 가리키는 Widget 객체들을 비교하는 함수 ( 람다 타입 )
		[](const std::unique_ptr<Widget>& p1, const std::unique_ptr<Widget>& p2)
		{ return *p1 < *p2; }


	// C++14에서는 람다 표현식의 매개변수에도 auto를 적용할 수 있어서 더욱 편리해진다.

	auto derefUPLess =      // 그 어떤 것이든 포인터처럼 작동하는 것들이 가리키는 값들을 비교하는 함수
		[](const auto& p1, const auto& p2)
		{ return *p1 < *p2; }
*/

/*
	//클로저를 담는 변수를 선언할 때, 굳이 auto를 사용할 필요는 없다는 생각이 들지도 모르겠다.
	// 그냥 std::function 객체를 사용하면 되지 않을까?

	// std::function을 사용하는 것이 훨씬 장황
	//    대체로 std::function 객체는 auto로 선언된 객체보다 메모리를 더 많이 소비한다.

	// std::function 객체를 통해서 클로저를 호출하는 것은 
	//    인라인화(inlining)를 제한하고 간접 함수 호출을 산출하는 구현 세부사항 때문에,
	//    거의 항상 auto로 선언된 객체를 통해 호출하는 것보다 느리다.
*/

