//다음 중 컴파일 에러가 나지 않는 코드는 ?

#include <iostream>

class Test {
	int n = 0;
public:
	void set(int a) { n = a; }
	int get() { return n; }
};

void main() {
	Test a;
	Test& b = a;
	std::cout << b.get() << std::endl;		//1
	Test* p = b;	            			//2
	std::cout << *p << std::endl;		    //3
	std::cout << p.get() << std::endl;		//4
}

// ① 1    ②  2     ③  3     ④  4
