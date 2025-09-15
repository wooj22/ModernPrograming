//완벽한 전달과 std::forward<>
// 
//		문맥에 따라 & L-value Reference, && R-value Reference 을 구분하지 못하는 경우에
//		std::forward 를 통해 타입을 분명하게 해준다.
//
//		std::forward가 하는 일 
//		L-value 로 들어온거면 L-value 로 리턴해주고, R-value 로 들어온거면 R-value 로 리턴
//		조건부 캐스팅 함수, 불필요한 복사를 줄이고 최적화된 코드 실행
//		완벽한 전달(perfect forwarding) 구현에 필수적이다

#include <iostream>	
#include <vector>
#include <utility>
using namespace std;

struct myStruct {};

void func(struct myStruct& s) { cout << "Pass by L-ref\n"; }  // L-value Reference 오버로딩
void func(struct myStruct&& s) { cout << "Pass by R-ref\n"; }  // R-value Reference 오버로딩

template<typename T>			
void func_wrapper(T t)
{
	func(t);
}

int main()
{
	myStruct s;

	func(s);					// 적당한 것을 IDE가 잘 찾아서 연결해준다.
	func(myStruct());			// 적당한 것을 IDE가 잘 찾아서 연결해준다.
	cout << endl;

	func_wrapper(s);			// 둘 다 L-value Reference로 처리해버린다
	func_wrapper(myStruct());	// 둘 다 L-value Reference로 처리해버린다 ?

	//대입되는 타입이 T 템플릿화가 되면서 R-value, L-value 정보가 날아가버리기 때문
	//Move Semantics 를 사용하기 위해 어떻게든 R-value로 넘기고 싶다면 ???
}

// 문제) func_wrapper 를 std::forward 를 사용해서 수정하세요 -----------------------------

/*
	template<typename T>
	void func_wrapper(T&& t)
	{
		func( std::forward<T>(t) );
	}

	// t 가 rvalue면 &&, lvalue면 & 로 반환
*/