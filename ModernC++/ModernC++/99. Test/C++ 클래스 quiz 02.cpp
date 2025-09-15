//아래 코드에서 컴파일 오류가 나는 곳을 모두 쓰시오. (2점)   

#include<iostream> 
using namespace std;

class Base
{
private:
	int num1;
protected:
	int num2;
public:
	int num3;
};

class Drived : protected Base
{
public:
	void Show() {
		cout << num2 << endl;		//(1) x
		cout << num3 << endl;		//(2) x
	}
};

int main()
{
	Drived obj;
	cout << obj.num2 << endl;		//(3) o
	cout << obj.num3 << endl;		//(4) x
}
