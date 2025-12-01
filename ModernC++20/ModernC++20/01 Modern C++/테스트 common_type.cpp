#include <iostream>
#include <type_traits>

struct Base {};
struct Derived : Base {};

int main()
{
    // Base, Derived 의 common_type 을 출력하는 코드를 작성하세요.

/*
    std::common_type<Base, Derived>::type a;
    std::cout << typeid(a).name() << std::endl;


    typedef std::common_type<Base, Derived>::type ClassType;
    std::cout << std::boolalpha;
    std::cout << std::is_same<Base, ClassType>::value << std::endl;
*/

    return 0;
}