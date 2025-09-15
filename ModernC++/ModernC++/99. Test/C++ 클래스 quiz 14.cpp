//코드의 실행결과로 올바른 것은 ?

#include <iostream>
using namespace std;

class Base {
	int n;
public:
	Base(int n) :n(n) {}
	Base& operator=(const Base& p) { if (this != &p) { n = p.n; } return *this; }
	void print() { cout << n; }
};

class Drived : public Base {
	int m;
public:
	Drived(int n, int m) : Base(n), m(m) {}
	Drived& operator=(const Drived& p) { if (this != &p) { m = p.m; } return *this; }
	void print() { Base::print();  cout << m; }
};

int main() {
	Drived d1(1, 2);  d1.print();
	Drived d2(0, 0);  d2 = d1;  d2.print();
	return 0;
}

//① 1212    ② 1200    ③ 1210    ④ 1202
