#include <iostream>
using namespace std;

int main()
{
	const int v1 = 0;
	auto a = v1;				// a 의 자료형은? int

	const int v2 = 0;
	auto& b = v2;				// b 의 자료형은? const int&

	int* v3 = nullptr;
	auto c = v3;				// c 의 자료형은? int*

	const int* v4 = 0;
	auto d = v4;				// d 의 자료형은? const int* 

	const int v5 = 0;
	auto&& e = v5;				// e 의 자료형은? const int&

	auto v6 = std::move(v1);
	auto&& f = v6;				// f 의 자료형은? int&

	return 0;
}