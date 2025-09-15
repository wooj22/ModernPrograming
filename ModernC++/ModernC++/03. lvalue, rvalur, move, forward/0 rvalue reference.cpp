//Rvalue 참조 : 임시 객체(일시적인 값, rvalue)를 참조할 수 있도록 해주는 참조 타입
//			&& 기호를 사용 
//			주로 move semantics(이동 의미론)와 perfect forwarding(완벽한 전달)을 구현할 때 사용
//			함수 오버로딩에서 lvalue와 rvalue를 구분하여 호출.

#include<iostream>
#include <vector>
using namespace std;

int main()
{
	int a = 0;
	int& b = a;				// Lvalue 참조 // 복사(copy)
	int&& c = 0;			// Rvalue 참조 // 임시값이므로 이동(move)하여 사용, 효율적

	// const lvalue 참조

	const int& d1 = a;		// Lvalue 참조로 받아 변경 안하겠다.
	d1 = b;					// error
	const int& d2 = 0;		// const 이므로 Rvalue 가능 ***
	

	// Lvalue 를 이동하고 싶다 -------------------------------------------------------

	int&& e1 = a;			// error // 임시 객체, 리터럴 등 rvalue 만 바인딩 가능 
	int&& e2 = move(a);		// Lvalue 를 이동하려면 move()사용 //Xvalue  ***

	//이동 연산
	//	사라질 임시변수에 대하여, 복사를 하지 않고 주소를 이전하여 효율적으로 이동
	//	Lvalue도 더이상 사용하지 않을 경우라면, 복사보다는 이동이 효율적이다.
	//  Lvalue 이동을 하기 위해 move() 함수 사용, 
	//	std::move()를 사용하여 인자를 rValue참조자로 변환 (xvalue)


	// Lvalue, Rvalue 알아서 받았으면 좋겠다. ----------------------------------------
	 
	//보편 참조  ***
	auto&& f1 = 0;			// ok //int&&
	auto&& f2 = a;			// ok //int&

	//forward<T>(val) 사용하면, val에 따라 Lvalue, Rvalue 로 리턴
	//std::forward가 가장 많이 쓰이는 곳은 보편 참조 매개변수로 받아서 처리하는 로직
}


// Xvalue - 곧 소멸할 값 - 왼쪽(lvalue)처럼 보이지만, 우측(rvalue) 참조로만 바인딩할 수 있는 특이한 값
{
	int n = 1;			
	int&& rr = move(n);			// move(n) 은 Xvalue		// move(n)는 Lvalue 를 Xvalue 로 변환
	int&  lr = (int&)move(n);	// move(n) 은 Xvalue

}
