//enum class

#include <iostream>
#include <vector>
using namespace std;

vector<size_t> foo(size_t x) { 
    vector<size_t> v; 
    return v; 
}

int main()
{
    // 1. 범위 있는 enum은 이름 누수가 발생하지 않는다.  
    //      이름공간(namespace) 오염을 줄임

    enum class Color { black, white, red };   // black, white, red는 // Color 범위에 속함

    Color c1 = Color::white;            // OK
    auto c2 = Color::white;

    //Color c = white;                  // 오류!
    auto white = false;                 // OK //변수
    
    
    // 2. 열거자들에 타입이 훨씬 강력하게 적용된다는 장점도 있다.

    // 범위 없는 enum 은 암묵적으로 정수 타입 (암묵적으로 부동소수점)

    enum Fruit { apple, banana, mango };    

    Fruit c = apple;
    if (c < 14.5) {
        auto factors = foo(c);
    }

    // 범위 있는 enum 은 다른 타입으로 변환되지 않음

    enum class Fruit { apple, banana, mango };

    Fruit c = Fruit::apple;

    if (c < 14.5) {                 //error
        auto factors = foo(c);      //error
    }

    //if (static_cast<double>(c) < 14.5) {
    //    auto factors = foo(static_cast<size_t>(c));
    //}

    return 0;
}

/*

문제의 근원은 기존 enum의 타입이 때에 따라 달라진다는 것이다. ***

    enum Color { black, white, red };    
    //필요 표현량이 적으므로 complier는 Color를 char로 취급한다.

    enum Status {
        good = 0,
        failed = 1,
        incomplete = 100,
        corrupt = 200,
        indeterminate = 0xFFFFFFFF
    };                                  
    //필요 표현범위가 0~0xFFFFFFFF 이므로 Status는 int타입으로 취급한다.


enum class는 그 타입을 '고정'시켜서 사용하기 때문에, 
    전방선언이 가능하며, 내용을 바꿔도 다시 컴파일해야 되는 문제가 없다.

    enum class Status;      //기본적으로 int형을 사용한다. 전방선언에 문제 없다. ***

    메모리 최적화를 포기한 대신, 편리하게 사용할 수 있게 한다.
    물론 이런 경우를 대비하여 만약 사용자가 원한다면, 직접 내부 타입을 설정할 수 있다.

    enum class Status : std::uint32_t;      //enum의 내부 타입을 std::uint32_t로 직접 설정

    //열거자의 타입은 int, short, char 같은 정수 계열 형식이어야 한다. ***
    //bool 형도 가능하지만 형을 강제한다는 경고가 뜬다.


이제는 unscoped enum(일반 enum)도 내부 타입을 명시할 수 있게 바뀌었기 때문에

    enum Status : std::uint8_t;         //이렇게 전방선언이 가능하다.

*/