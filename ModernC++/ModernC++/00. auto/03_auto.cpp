//����)

#include <iostream>
using namespace std;
int main()
{
	const int v1 = 0;
	auto a = v1;				// a �� �ڷ�����?

	const int v2 = 0;
	auto& b = v2;				// b �� �ڷ�����?

	int* v3 = nullptr;
	auto c = v3;				// c �� �ڷ�����?

	const int* v4 = 0;
	auto d = v4;				// d �� �ڷ�����?

	const int v5 = 0;
	auto&& e = v5;				// e �� �ڷ�����?

	auto v6 = std::move(v1);
	auto&& f = v6;				// f �� �ڷ�����?

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
	auto&& val1 = v2;		// val1 �� �ڷ�����?
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