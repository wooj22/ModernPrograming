// 함수를 객체로
// 
//      Callable 들을 객체의 형태로 보관할 수 있는 std::function 이라는 클래스를 제공
//      bind 예제, mem_fn 예제

// std::bind ----------------------------------------------------------------------------------
// 
//      함수 객체 생성 시에 인자를 특정한 것으로 지정가능
//      함수의 일부 매개 변수를 고정 값으로 세팅한 후, 한번 Wrapping 하여 사용할 수 있게 해주는 함수

#include <functional>
#include <iostream>

void add(int x, int y) {
    std::cout << x << " + " << y << " = " << x + y << std::endl;
}

void subtract(int x, int y) {
    std::cout << x << " - " << y << " = " << x - y << std::endl;
}

int main() {
    auto add_with_2 = std::bind(add, 2, std::placeholders::_1);
    add_with_2(3);              // add(2 + 3)

    add_with_2(3, 4);           // 두 번째 인자는 무시된다.

    auto subtract_from_2 = std::bind(subtract, std::placeholders::_1, 2);
    subtract_from_2(3);         // 3 - 2 를 계산한다.

    auto negate = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);
    negate(4, 2);               // 2 - 4 를 계산한다
}

//주의할 점은, 레퍼런스를 인자로 받는 함수들의 경우
//      명시적으로 레퍼런스를 전달해줘야 합니다.
//      ref 함수는 전달받은 인자를 복사 가능한 레퍼런스로 변환.


#include <functional>
#include <iostream>

struct S {
    int data;
    S(int data) : data(data) { std::cout << "일반 생성자 호출!" << std::endl; }
    S(const S& s) {        
        data = s.data; std::cout << "복사 생성자 호출!" << std::endl;
    }
    S(S&& s) {        
        data = s.data; std::cout << "이동 생성자 호출!" << std::endl;
    }
};

void do_something(S& s1, const S& s2) { s1.data = s2.data + 3; }

int main() {
    S s1(1), s2(2);

    std::cout << "Before : " << s1.data << std::endl;

    // s1 이 그대로 전달된 것이 아니라 s1 의 복사본이 전달됨!
    auto do_something_with_s1 = std::bind(do_something, std::ref(s1), std::placeholders::_1);
    do_something_with_s1(s2);

    std::cout << "After :: " << s1.data << std::endl;
}
