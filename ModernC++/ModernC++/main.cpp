#include <iostream>
using namespace std;

int main()
{
	const int v1 = 0;
	auto a = v1;				// a �� �ڷ�����? int

	const int v2 = 0;
	auto& b = v2;				// b �� �ڷ�����? const int&

	int* v3 = nullptr;
	auto c = v3;				// c �� �ڷ�����? int*

	const int* v4 = 0;
	auto d = v4;				// d �� �ڷ�����? const int* 

	const int v5 = 0;
	auto&& e = v5;				// e �� �ڷ�����? const int&

	auto v6 = std::move(v1);
	auto&& f = v6;				// f �� �ڷ�����? int&

	return 0;
}