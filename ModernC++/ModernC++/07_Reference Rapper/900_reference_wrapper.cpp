//reference_wrapper
//		reference_wrapper<Ty>는 Ty 형식의 개체 또는 함수에 대한 '참조'를 래핑하며, (참조를 값처럼 저장)
//		해당 형식의 개체를 가리키는 포인터가 포함된 복사본을 생성/할당 가능하게 합니다.

//		도우미 함수 std::ref 및 std::cref를 사용하여 reference_wrapper 개체를 만들 수 있습니다.

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Base
{
public:
	int m_i = 0;
	virtual void print() { cout << "I'm Base" << endl; }
};

class Derived : public Base
{
public:
	int m_j = 1;
	virtual void print() override { cout << "I'm Derived" << endl; }
};

void doSomething(Base& b)
{
	b.print();
}

int main()
{
	// 호출되는 함수는?
	{
		Derived d;
		Base& b = d;			// 업캐스팅
		b.print();				// virtual 선언을 해줬기 때문에 "I'm Derived" 출력
	}
	{
		Derived d;
		Base b = d;				// 참조가 아니라면 Base 로 형변환되면서 '객체 잘림' (자식 클래스의 멤버들을 다 받지 못하는 것)
		b.print();				// 객체 잘림이 발생하여 Base 클래스의 print 함수 호출
	}

	//vector 의 경우
	{
		Base b;
		Derived d;

		std::vector<Base> my_vec;		//객체 잘림 현상 //타입을 &로 받지 않는다.
		my_vec.push_back(b);
		my_vec.push_back(d);

		for (auto& e : my_vec)
			e.print();
	}
	{
		Base b;
		Derived d;

		std::vector<Base*> my_vec;		// 그래서, 포인터를 사용해야 한다.
		my_vec.push_back(&b);
		my_vec.push_back(&d);

		for (auto& e : my_vec)
			e->print();
	}

	//포인터를 사용하지 않고 객체 잘림 현상을 해결할 수 있는 방법이 있는데, 
	//		그게 바로 reference_wrapper
	// 
	//vector는 referece를 자료형으로 받지 않기 때문에 이런 상황에는 reference_wrapper를 사용 ***
	//		C++에서는 참조(T&) 자체를 컨테이너에 저장하거나 복사할 수 없습니다.
	//		STL 컨테이너에 “참조”를 저장하고 싶을 때 std::reference_wrapper를 사용.
	{
		Base b;
		Derived d;

		std::vector<std::reference_wrapper<Base>> my_vec;	//<functional> 라이브러리에 포함된 기능
		my_vec.push_back(b);
		my_vec.push_back(d);

		for (auto& e : my_vec)
			e.get().print();								// get()을 꼭 사용
	}
	return 0;
}