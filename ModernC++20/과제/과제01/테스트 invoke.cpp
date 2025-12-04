//invoke 활용

#include <iostream>
#include <functional>  

struct S
{
	const int j = 0;
	int do_something(const int i) { return j + i; }
};

int main()
{
	S s;
	std::cout << s.do_something(5) << std::endl;

	// do_something() 함수를 invoke 함수를 이용해 호출하세요.
	std::invoke(&S::do_something, s, 5);

	int (S:: * fptr1)(const int) = &S::do_something;
	std::invoke(fptr1, s, 7);

	std::function<int(S&, const int)> fptr2 = &S::do_something;
	std::invoke(fptr2, s, 9);

	auto fptr3 = &S::do_something;
	std::invoke(fptr3, s, 10);
}