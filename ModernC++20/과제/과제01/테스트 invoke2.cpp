//invoke 활용

#include <iostream>
#include <type_traits>
#include <functional>

class S
{
public:
	int v = 999;
	std::function<void(S&)> obj_print_hello = [](auto) {std::cout << "Hello" << std::endl; };
} s;

int main()
{
	s.obj_print_hello(s);

	// invoke 함수를 이용해 호출하세요.
	std::invoke(s.obj_print_hello, s);
}