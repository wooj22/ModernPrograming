//문제)

#include <iostream>
using namespace std;
int main()
{
	const int v1 = 0;
	auto a = v1;				// a 의 자료형은?

	const int v2 = 0;
	auto& b = v2;				// b 의 자료형은?

	int* v3 = nullptr;
	auto c = v3;				// c 의 자료형은?

	const int* v4 = 0;
	auto d = v4;				// d 의 자료형은?

	const int v5 = 0;
	auto&& e = v5;				// e 의 자료형은?

	auto v6 = std::move(v1);
	auto&& f = v6;				// f 의 자료형은?

	return 0;
}

/*
#include <iostream>
#include <array>
using namespace std;

int main()
{
	const int v1 = 0;
	auto v2 = std::move(v1);
	auto&& val1 = v2;		// val1 의 자료형은?
}

// val1 : int &


int main()
{
	const int* ca = 0;
	auto val1 = ca;				//???
	auto&& val2 = val1;			//???
}

// val1 : const int *
// val2 : const int *&

*/