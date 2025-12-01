//std::invoke
//		함수 뿐만 아니라 
//		네임스페이스에 포함되어 있는 함수 호출이나 펑터, 클래스 맴버의 인스턴스, 레퍼런스, 포인터 등을 넘겨 호출할 수도 있습니다.
//		즉, 모든 Callable 호출이 가능합니다.

/*
1) C++에서는 "함수처럼 호출될 수 있는 타입" 개념이 넓음

	함수
	함수 포인터
	함수 객체(functor)
	람다(lambda)
	operator() 오버로드한 임의 객체
	std::function

→ 모두 callable

2) 멤버 변수도 단순히 “그 타입의 인스턴스”
	그 타입이 callable 기능을 제공하면
	그 멤버 변수도 callable
*/

#include <type_traits>
#include <iostream>

class S {
public:
	int exponentiation(int i) {	return i * i; }
};

int main()
{
	S s;
	std::cout << std::invoke(&S::exponentiation, s, 4) << std::endl; // 16
	std::cout << std::invoke(&S::exponentiation, std::ref(s), 4) << std::endl; // 16

	S* p = &s;
	std::cout << std::invoke(&S::exponentiation, p, 4) << std::endl; // 16

 	std::unique_ptr<S> up(new S);
	std::cout << std::invoke(&S::exponentiation, up, 4) << std::endl; // 16
}


//---------------------------------------------------------------------------------
// function 객체를 맴버로 가지고 있는 클래스도 호출하는지 테스트

#include <iostream>
#include <type_traits>
#include <functional>

class S
{
public:
	void func_print_hello() { std::cout << "Hello" << std::endl; }
	std::function<void(S&)> obj_print_hello = &S::func_print_hello;		//
	int v = 999;
} s;

int main() {
	s.func_print_hello();				// Hello
	s.obj_print_hello(s);				// Hello

	std::invoke(&S::func_print_hello, s); // Hello
	std::invoke(&S::obj_print_hello, s);  // ?!			
	
	//std::invoke는 객체 레퍼런스 맴버로 대체합니다. 
	//따라서 invoke에 값을 할당하면 객체 레퍼런스의 맴버에 값을 할당하는 것과 같습니다. 
	//	std::invoke(&S::obj_print_hello, s)   --->    &S::func_print_hello
	//	std::invoke(std::invoke(&S::obj_print_hello, s), s);


	std::invoke(&S::v, s);				// s.v		//맴버에 값 v
	std::invoke(&S::v, s) = 1;			// s.v = 1
	int x = std::invoke(&S::v, s);		// int x = s.v
	//std::cout << s.v;
}


//---------------------------------------------------------------------------------

#include <iostream>
#include <type_traits>
#include <functional>

class S
{
public:
	int v = 999;
	std::function<void(S&)> obj_print_hello = [](auto) {std::cout << "Hello" << std::endl; };
} s;

int main() 
{
	s.obj_print_hello(s);							// Hello
	std::invoke(&S::obj_print_hello, s)(s);			// Hello
	std::invoke(std::invoke(&S::obj_print_hello, s), s);	//실행하기 위해서는 operator ()나 invoke로 한번 더 감싸줍니다
}
