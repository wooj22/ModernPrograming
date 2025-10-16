// 함수를 객체로
//      Callable 들을 객체의 형태로 보관할 수 있는 std::function 이라는 클래스를 제공
//      std::function, std::mem_fn, std::bind

// std::bind
//      함수 객체 생성 시에 인자를 특정한 것으로 지정가능
//      함수의 일부 매개 변수를 고정 값으로 세팅한 후, 한번 Wrapping 하여 사용할 수 있게 해주는 함수

//      std::function< 함수의 형태> 변수명 = bind( 함수명, 인자1, 인자 2, ...);

#include <iostream>
#include <functional>

using namespace std;

int test(string name, int a, int b) {
    cout << name << " " << a + b << endl;
    return a + b;
}

int main() {
    function<int()> f = bind(test, "hello", 1, 2);
    f();                                    // function 사용

    auto g = bind(test, "hello", 1, 2);
    g();                                    // auto를 사용
}


// bind시 인자를 변수로 변경하는 방법
//      bind함수 호출 시 고정 값 인자 대신 std::placeholders::_1을 사용하면 
//      wrapping 한 함수에 인자 값을 사용자가 입력 수 있다. 

#include <iostream>
#include <functional>

using namespace std;

int test(string name, int a, int b) {
    cout << name << " " << a << " " << b << endl;
    return a * b;
}

int main() {
    std::function<int(int)> f = bind(test, "hello", std::placeholders::_1, 2);
    f(10);                  //placeholders::_1 전달

    auto g = bind(test, "hello", placeholders::_1, 2);
    g(20);

    auto g2 = bind(test, "hello", std::placeholders::_2, 2);
    g2(10, 20);             //placeholders::_2 전달
}

// std::placeholders::_1을 사용시 _1을 건너뛰고 _2를 사용했다면 
// 
//  auto g = bind(test, "hello", std::placeholders::_2, 2);
//  g() 함수 호출 시 무조건 2개의 인자를 넘겨야 합니다.  g(1, 2)
//  이렇게 인자 2개를 넘기지 않으면, 2번째 인자를 찾지 못하여 컴파일 시 에러 납니다.



// bind 함수에서  cref 사용 ---------------------------

#include <functional>
#include <iostream>

void print_sum(int a, int b) {
    std::cout << (a + b) << '\n';
}

int main() {
    int n = 5;
    auto bound = std::bind(print_sum, std::cref(n), 10);    
    //n = 6;
    bound(); // 15
}
