//아래 코드의 출력 값을 기술하세요.

#include <iostream>
using namespace std;
class CTest
{
private:
	int num;
public:
	CTest(int n) : num(n) { }
	CTest(const CTest& copy) : num(copy.num) { cout << "0"; }
	CTest& Add(int n) { num += n; return *this; }
	CTest Show() { cout << num; return *this; }
};
CTest Func(CTest ob)
{
	return ob;
}
int main(void)
{
	CTest obj(0);
	Func(obj).Add(0).Show();
	return 0;
}
