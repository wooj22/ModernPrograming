//std::generate
//  범위 내에 원소들을 인자로 전달된 함수에서 생성된 값으로 채운다
//  컨테이너의 요소들을 특정 값으로 채우거나, 생성 함수를 사용하여 값을 채우는 데 사용
//  #include <algorithm>

#include <algorithm>
#include <iostream>
#include <vector>

int f() {
    static int i = 1;
    return i++;
}

int main() {
    std::vector<int> v(5);
    std::generate(v.begin(), v.end(), f);

    std::cout << "v: ";
    for (auto iv : v) {
        std::cout << iv << " ";
    }
    std::cout << "\n";

    // 참고로 아래와 같이 lambda 의 capture 에서 객체를 생성하는 경우, 해당 람다
    // 객체와 함께 생성된 것이라 간주하면 되고, 람다가 소멸 되기 전 까지 계속
    // 유지됩니다. 물론 해당 capture 역시 값을 캡쳐하는 것이므로 mutable 람다가
    // 아니면 해당 값을 수정할 수 없습니다.
    //
    // std::iota(v.begin(), v.end(), 0); 와 동일한 문장.
    std::generate(v.begin(), v.end(), [n = 0]() mutable { return n++; });

    std::cout << "v: ";
    for (auto iv : v) {
        std::cout << iv << " ";
    }
    std::cout << "\n";
}


//관련 함수 : std::generate_n - 고정된 개수만큼 값을 생성

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v(10);

    // 처음 5개 요소만 특정 값으로 채우기
    std::generate_n(v.begin(), 5, []() { return 99; });

    for (int n : v) {
        std::cout << n << " ";
    }
    return 0;
}