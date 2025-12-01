//클래스 템플릿 상속

#include <iostream>
#include <string>

template <class T>
struct Empty {
	typedef T type;					// 템플릿의 매개변수로 제공하는 타입을 선언
	virtual void Display() = 0;
};

// 위 클래스 템플릿을 상속받는 Optimized 클래스 템플릿을 선언
template <class T>
class Optimized : public Empty<T> {
private:
	typename Empty<T>::type data;	// Empty 클래스 템플릿이 제공하는 타입을 사용하기 위해 typename 지정자를 사용

public:
	Optimized(typename Empty<T>::type dataValue) : data(dataValue) { }

	typename Empty<T>::type GetData() const { return data; }

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
}

//-----------------------------------------------------------------------

#include <iostream>
using namespace std;

template <class T>
struct Empty {
	typedef T type;				// 템플릿의 매개변수로 제공하는 타입에 접근하기 위한 선언
	virtual void Display() = 0;
};

// 위 클래스 템플릿을 상속받는 Optimized 클래스를 선언
template <class T>
class Optimized : public Empty<T> {
private:
	typename Empty<T>::type data;	// Empty 클래스 템플릿의 타입을 사용하기 위해 typename 지정자를 사용 //의존 타입
	//typedef Empty<T>::type type;	// 다시 별칭 선언 // type으로 간략히 사용

public:
	Optimized(typename Empty<T>::type dataValue) : data(dataValue) { }

	typename Empty<T>::type GetData() const {
		return data;
	}

	virtual void Display() final;
};

template <class T>
void Optimized<T>::Display() {
	std::cout << "Optimized : " << data << std::endl;
}

int main() 
{
	Optimized<int> optimized(100);
	std::cout << "Empty Object : " << optimized.GetData() << std::endl;
	optimized.Display();

	//아래 표현을 별칭 템플릿을 이용해 간략히 변경하세요.

	Empty<std::string>::type str = "문자열";  //string str
	std::cout << str << std::endl;
}

/*
	template<typename T>
	using Empty_t = typename Empty<T>::type;	//using //별칭 선언

	int main()
	{
		Empty_t<string> str = "문자열";  //string str
		std::cout << str << std::endl;
	}

*/