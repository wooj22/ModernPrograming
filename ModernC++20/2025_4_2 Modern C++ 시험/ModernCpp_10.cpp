// Range
// 
// Range 코드입니다. 코드를 분석하고 아래 질문에 답하세요.

#include <vector>
#include <ranges>
#include <iostream>

std::vector<int> make()
{
    return { 1,2,3,4,5 };
}

auto odds() {
    return make()       // { 1,2,3,4,5 }
        | std::views::filter([](int x) { return x % 2; })        // {1, 3, 5}
        | std::views::transform([](int x) { return x * x; });    // {1, 9, 15}
}

int main() {
    for (int v : odds()) { std::cout << v << " "; }
}

//질문
1. 이 코드는 올바르게 정의된 동작을 수행하는가 ?
출력 결과는 나오지만, 항상 잘 나온다고 보장할 수 없습니다.

2. 문제가 있다면 원인은 ?
R value 컨테이너는 범위의 작업이 끝나기 전에 소멸될 가능성이 있습니다.
파이프 연산자의 왼쪽에는 view 또는 borrowed_range가 와야 안전합니다.

3. 수정 방안을 기술하세요.
1) 변수에 저장하여 lvalue로 변환
2) std::ranges::owning_view 사용
3)  std::move를 사용하여 컨테이너를 전달