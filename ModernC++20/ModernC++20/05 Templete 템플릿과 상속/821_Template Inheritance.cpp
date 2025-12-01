//클래스 템플릿의 상속(Class Template Inheritance)
// 
//		일반클래스, 클래스 템플릿 모두 상속 가능

//일반클래스 상속
/*
	#include <iostream>
	#include <string>

	class Base {
	};

	template <class T>
	class Derived : public Base
	{
	};

	int main() {
		Derived<int> d;
	}
*/

//클래스 템플릿 상속

#include <iostream>
#include <string>

template <class T>
struct Empty {
	virtual void Display() = 0;
};

// 위 클래스 템플릿을 상속받는 Optimized 클래스 템플릿을 선언
template <class T>
class Optimized : public Empty<T>			//Empty<T>
{
private:
	T data;
public:
	Optimized(T dataValue) : data(dataValue) { }
	T GetData() const { return data; }
	virtual void Display() final;
};

template <class T>
void Optimized<T>::Display() {
	std::cout << "Optimized : " << data << std::endl;
}

int main()
{
	Optimized<int> optimized(100);
	std::cout << optimized.GetData() << std::endl;
	optimized.Display();

	Empty<int>& e = optimized;
	e.Display();
}

