#include <iostream>
#include <vector>
using namespace std;

class A {};

void foo(A& a) { std::cout << "A& a" << std::endl; }
void foo(const A& a) { std::cout << "const A& a" << std::endl; }
void foo(A&& a) { std::cout << "A&& a" << std::endl; }

template <typename T>
void wrapper(T&& u) 
{
	foo(std::forward<T>(u));
}

int main() {
	A a;
	const A ca;

	wrapper(a);
	wrapper(ca);
	wrapper(A());
}
