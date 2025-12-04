//common_type 사용

#include <iostream>
#include <type_traits>

struct Base {};
struct Derived : Base {};

int main()
{
	// Base, Derived 의 common_type 을 출력하는 코드를 작성하세요.
	std::common_type_t<Base, Derived> commonType;
	std::cout << typeid(commonType).name() << std::endl;

	return 0;
}