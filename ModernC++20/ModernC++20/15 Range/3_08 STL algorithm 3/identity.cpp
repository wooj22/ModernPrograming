//std::identity
//  C++20부터,함수 객체(Function Object)로, 전달된 값을 그대로 반환하는 역할
//  즉, "자신"을 반환하는 간단한 유틸리티
//  함수 호출 연산자 operator()가 정의되어 있어, 함수 객체처럼 동작


//1. 기본 반환 함수로 사용

#include <iostream>
#include <functional>

int main() {
    std::identity id;

    int x = 42;
    std::cout << "Identity: " << id(x) << std::endl; // 42 그대로 반환

    return 0;
}

//2. STL 알고리즘과 함께 사용

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    std::vector<int> numbers = { 3, 1, 4, 1, 5, 9 };

    // 정렬하면서 값 자체를 비교(즉, 변환 없이)
    std::sort(numbers.begin(), numbers.end(), std::less<>());

    // 값 그대로 출력 (std::identity 사용)
    std::for_each(numbers.begin(), numbers.end(), [](int x) {
        std::cout << x << " ";
        });

    return 0;
}

//3. 키 선택 함수로 활용
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    std::vector<int> numbers = { 3, 1, 4, 1, 5, 9 };

    // std::identity를 사용해 값 그대로 출력
    std::transform(numbers.begin(), numbers.end(),
        std::ostream_iterator<int>(std::cout, " "),
        std::identity{});

    return 0;
}

//4. 사용자 정의 타입과 함께 사용
#include <iostream>
#include <functional>
#include <string>

struct Person {
    std::string name;
    int age;
};

int main() {
    Person p{ "Alice", 30 };
    std::identity id;

    // 값 그대로 반환
    auto& original = id(p);

    std::cout << "Name: " << original.name << ", Age: " << original.age << std::endl;

    return 0;
}

//주의사항
//std::identity는 값 전달만 수행하며, 추가적인 변환이나 처리 로직이 없습니다.
//C++17 이전에는 std::identity가 없으므로 비슷한 동작을 하려면 람다 함수나 별도의 함수 객체를 작성해야 합니다.
//
//요약
//기본 기능 : 전달된 값을 그대로 반환.
//사용 용도 : STL 알고리즘에서 기본 동작으로 활용하거나, 값 자체를 반환하는 함수로 사용.
//헤더 파일 : <functional>.



