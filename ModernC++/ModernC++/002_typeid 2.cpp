//typeid 연산자를 사용하면, 
//		런타임에 개체의 형식을 확인할 수 있다.
//		자료형이나 변수 또는 식을 입력받아 const type_info& 형식의 객체를 반환해 주는 연산자

//C++에서 RTTI(Run Time Type Info)를 제공하는 키워드는 
//		RTTI(실행시간에 타입을 결정)
//		dynamic_cast<> 와 typeid 가 있습니다.


#include <iostream>
#include <typeinfo>

class Base {
public:
	virtual void vvfunc() {}
};

class Derived : public Base {};

using namespace std;
int main() {

	//식의 정적 형식을 결정할 때 가능할 경우  참조, const, volatile 가 무시됩니다

	cout << typeid(char).name() << endl;
	cout << typeid(int).name() << endl;
	cout << typeid(__int64).name() << endl;

	cout << typeid(char&).name() << endl;
	cout << typeid(const char).name() << endl;
	cout << typeid(volatile char).name() << endl;

	//포인터 형식을 결정할 때	 const, volatile 구분
	cout << typeid(char*).name() << endl;
	cout << typeid(const char*).name() << endl;
	cout << typeid(volatile char*).name() << endl;

	//클래스의 경우 출력할때 class 표시됨
	cout << typeid(Base).name() << endl;
	cout << typeid(Derived).name() << endl;


	//포인터를 역참조하지 않으면 포인터가 가리키는 것이 아니라 포인터에 대한 결과가 됩니다
	//부모 클래스에 virtual 함수가 있을 경우 자식 클래스를 구분할 수 있습니다.
	Derived* pd = new Derived;
	Base* pb = pd;
	cout << typeid(pb).name() << endl;		//prints "class Base *"
	cout << typeid(*pb).name() << endl;		//prints "class Derived"
	cout << typeid(pd).name() << endl;		//prints "class Derived *"
	cout << typeid(*pd).name() << endl;		//prints "class Derived"
	delete pd;
}
