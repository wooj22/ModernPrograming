#include <iostream>
#include <functional>

void printMessage() {
    std::cout << "Hello, world!" << std::endl;
}

int main() {
    // std::function 객체 생성
    std::function<void()> func = printMessage;

    // 호출 가능한 상태
    if (func) {
        func();  // 출력: Hello, world!
    }

    // 비활성화 ***
    func = nullptr;  // std::function을 빈 상태로 설정 


    // 빈 상태 확인 ***
    if (func) {
        std::cout << "func is active" << std::endl;
    }
    else {
        std::cout << "func is not active" << std::endl;  // 이 줄이 출력됩니다.
    }

    return 0;
}
