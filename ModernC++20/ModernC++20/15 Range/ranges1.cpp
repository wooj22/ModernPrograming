
//Ranges는 view, action, algorithm 이렇게 세 가지를 기반으로 합니다.

// view 는 
//		lazy operation입니다. ranges의 범위를 나타냅니다.
// action 은 
//		컨테이너나 배열같은 객체의 모음을 제자리에서 변경하고, 
//		추가 처리를 하는 컨테이너에 algorithm을 적용하는 것입니다. (C++20에 namespace는 없음) 
// algorithm 은 
//		STL과 동일하지만, 알고리즘에 iterator를 사용하는 함수 뿐만 아니라 
//		ranges를 사용하는 함수 또한 오버로딩 되어 있습니다. 

//Ranges Algorithm vs 기존 STL 알고리즘
//
//특징			STL 알고리즘							Ranges Algorithm
// 
//입력			Iterator 범위 사용					Range 객체 지원
//직관성			여러 인자 필요						컨테이너나 뷰 직접 전달 가능
//결과 반환		void 또는 iterator 반환				결과 Range 반환 가능
//연결 가능		불가능								뷰와 함께 파이프라인 사용 가능
//제약 조건		느슨한 개념 사용						강력한 개념과 제약 조건 사용

//std::ranges::actions란 ?
//	std::ranges::actions는 데이터 조작을 쉽게 하기 위해 제공되는 범위 기반의 알고리즘 모음입니다.
//	기존 STL 알고리즘(std::sort, std::transform 등)과는 다르게 즉시 적용 가능한 조작(pipeline) 기능을 제공합니다.
//
//	주요 특징 :
//	지연 평가 : Action은 뷰(View)처럼 즉시 실행하지 않고, 필요할 때 데이터를 조작합니다.
//	체인식 사용 가능 : 여러 Action을 파이프(| ) 연산자를 통해 연결하여 코드의 가독성을 높입니다.
//	컨테이너 변환 : 기존 컨테이너 데이터를 변형하거나 필터링할 수 있습니다.

//actions와 algorithm 차이점 요약 (VC 20++ actions은 없음)
// 
//특징			actions								algorithm
// 
//주요 목적		컨테이너 직접 수정					범위(뷰) 기반 알고리즘
//결과 반환		없음(수정된 컨테이너 자체 사용)		수정된 범위 또는 뷰를 반환
//체이닝			가능(파이프라인 사용)					체이닝을 위해서는 중간 변수 필요
//예시			std::ranges::actions::sort(v)		std::ranges::sort(v)
//용도			데이터의 직접적인 수정				데이터 조회 및 변환

//현재 MSVC에서는** std::ranges::actions** 를 사용할 수 없고, 대신** std::ranges::algorithm** 을 활용해야 합니다.


//예시) 3으로 나누어 떨어지는 수의 제곱을 추려내기 ----------------------------

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <ranges>		//
using namespace std;

void main()
{
	// stl <algorithm> 

	std::vector<int> input = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> intermediate, output;

	std::copy_if(input.begin(), input.end(), std::back_inserter(intermediate), [](const int i) { return i % 3 == 0; });
	std::transform(intermediate.begin(), intermediate.end(), std::back_inserter(output), [](const int i) {return i * i; });

	for (auto e : output) cout << e << " ";


	// ranges  // requires /std:c++20

	std::vector<int> input2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	auto output2 = input2
		| std::views::filter([](const int n) {return n % 3 == 0; })
		| std::views::transform([](const int n) {return n * n; });

}

// 파이프 구문과 지연 연산 ----------------------------------------------------

//F11 로 디버그 하며 따라가 봅시다. 지연 연산되고 있음을 알 수 있다.

#include <ranges>
#include <vector>
#include <iostream>

int main()
{
	std::vector<int> input = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	auto divisible_by_three = [](const int n) {return n % 3 == 0; };
	auto square = [](const int n) {return n * n; };

	auto x = input
		| std::views::filter(divisible_by_three)
		| std::views::transform(square);

	for (int i : x)
	{
		std::cout << i << '\n';
	}
	return 0;
}