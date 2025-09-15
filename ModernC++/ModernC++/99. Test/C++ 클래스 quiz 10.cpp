
// 다음 코드의 출력 결과는?  

#include <iostream>
using namespace std;

struct Player {
	int& r;
	Player(int& n) : r(n) { }
};

int main(void) 
{
	int n = 0;

	Player p1(n);
	Player p2(p1);
	p1.r = 1;
	p2.r = 2;
	n = 3;

	cout << p1.r << endl;

	return 0;
}
