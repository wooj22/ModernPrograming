// move_if_noexcept
//
//      이동(move) 또는 복사(copy)될 수 있는 "X" 를 인자로 받아, 
//      이동 생성자가  noexcept 이면 std::move(X) 를 반환,  그렇지 않으면 X 를 반환한다.
// 
//      C++11(VS2015) 라이브러리(utility.h)
//      STL container들이 move semantics에 대한 strong exception guarantee를 요구할 때 사용

#include <iostream>
#include <utility>

struct Good
{
    Good() {}
    Good(Good&&) noexcept       // 예외를 던지지 않는다
    {
        std::cout << "Non-throwing move constructor called\n";
    }
    Good(const Good&) noexcept  // 예외를 던지지 않는다
    {
        std::cout << "Non-throwing copy constructor called\n";
    }
};

struct Bad
{
    Bad() {}
    Bad(Bad&&)          // 예외를 던질 수 있다
    {
        std::cout << "Throwing move constructor called\n";
    }
    Bad(const Bad&)     // 예외를 던질 수 있다
    {
        std::cout << "Throwing copy constructor called\n";
    }
};

int main()
{
    Good g;
    Bad b;

    // Good 이동 생성자는 예외를 던지지 않으므로, std::move(g)를 반환
    // 이동 생성자가 실행된다
    Good g2 = std::move_if_noexcept(g);

    // Bad 이동 생성자는 예외를 던질 수 있으므로, b를 반환
    // 복사 생성자가 실행된다
    Bad b2 = std::move_if_noexcept(b);
}