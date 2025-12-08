#include <iostream>
#include <list>

using namespace std;


template<typename T>
class Foo
{
public:
	T data;
	explicit Foo(const T& a) : data(a) {}
	Foo(const T& a, const T& b) : data(a + b) {}
};

template<typename T1, typename T2>
Foo(const T1& a, const T2& b) -> Foo<std::common_type_t<T1, T2>>;

int main()
{
	Foo f1{ 42 };
	Foo f2{ 42, 77.7 };

	cout << f2.data << endl;

	return 0;
}