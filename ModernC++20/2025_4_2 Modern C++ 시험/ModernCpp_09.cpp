// Range
// 
// Range 코드입니다. 코드를 분석하고 아래 질문에 답하세요.

#include <iostream>
#include <vector>
#include <ranges>

int main() {
    auto v = std::vector{ 1,2,3,4,5 };

    auto even = v
        | std::views::filter([](int x)
            {
                std::cout << "filter called for " << x << std::endl;
                return x % 2 == 0;
            });

    for (int x : even) {
        std::cout << x << std::endl;
    }
}

//질문
//1. 다음 코드에서 "filter called for " 는 언제 출력이 수행되는가 ?
even의 요소를 출력할 때 출력합니다.


//2. 코드 위치와 그 이유를 설명하세요.
for (int x : even) {
    std::cout << x << std::endl;    // 이곳에서 출력됩니다.
}

std::cout << "filter called for " << x << std::endl;
은 조건(짝수)에 관계 없이 v의 모든 요소에 대해 출력되기 때문입니다.
