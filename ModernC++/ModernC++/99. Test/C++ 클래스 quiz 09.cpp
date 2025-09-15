//다음 프로그램을 실행하면 화면에 출력되는 값은 ?

#include <iostream>
#include <string>

class A {
protected:
	std::string val;
public:
	void Set(std::string v) { val = "A" + v; }
	virtual std::string Get() { return val + "A"; }
};
class B : public A {
public:
	virtual void Set(std::string v) { val = "B" + v; }
	std::string Get() { return val + "B"; }
};
int main()
{
	B b;
	A* p = &b;	p->Set("_");  std::cout << p->Get();
}

// ① A_A    ② A_B     ③ B_A     ④ B_B
