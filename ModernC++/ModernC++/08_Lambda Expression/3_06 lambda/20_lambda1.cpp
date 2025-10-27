// lambda_expressions

//람다 함수 Lambda
//		익명 함수(Anonymous functions), 함수를 보다 단순하게 표현하는 방법.
//		코드(람다식)를 데이타처럼 사용 (매개변수로 전달, 리턴이 가능)
// 
//		장점 
//		코드의 간결함, 지연 연산을 통한 퍼포먼스 향상, 
//		이터레이션 관련 코드를 구현하는 데 있어 불필요한 부분들을 제거할 수 있다.

//람다 함수 형식
//		[capture list](받는 인자) -> 리턴 타입 { 함수 본체 }   //trailing return type(후행(후위) 리턴 타입)
// 
//리턴 타입을 생략할 경우
//		[capture list](받는 인자) {함수 본체}					//리턴 타입은 추론된다

/*
//예제 //람다로 표현하세요

	void Print() { cout << "Hello World" << endl; };		
	void Show() { cout << "hello" << endl; };				
	void PrintNum(int x) { cout << x << endl; };			
	int Abs(int x) {	if(x<0) return -x; return x; };		
	bool isEven(int x) {	return x % 2; };				
	int Add(int x, int y) {	return x + y; };				

//   []()-> void { cout << "Hello World" << endl; };
//   [] { cout << "hello" << endl; };
//   [](int x)-> void { cout << x << endl; };
//   [](int x)-> int {	if(x<0) return -x; return x; }
//   [](int x)-> bool {	return x % 2; }
//   [](int x, int y) { return x + y; }


//람다 함수 실행 하기 

	[](int i) { return i % 2 == 1; }
	[](int i) { return i % 2 == 1; }(3);					// true

    auto func = [](int i) { return i % 2 == 1; };  
	func(4);												// false;

*/

#include <functional>
#include <iostream>
using namespace std;

//함수를 변수 처럼 정의해서 사용하기 //람다식으로 변경해보자.
int Add(int x, int y) 
{
	return x + y; 
};

int main()
{
	// 1.함수 호출
	cout << Add(1, 2) << endl;


	// 2.람다 표현식
	cout << [](int x, int y)-> int { return x + y; } (1, 2) << endl;
	//cout << [](int x, int y) { return x + y; } (1, 2) << endl;

	// 3.람다식으로 변수처럼 정의해서 사용
	auto f1 = [](int x, int y) { return x + y; };		//auto 활용 가능
	cout << f1(1, 2) << endl;


	// function<> 형식으로 람다를 전달하기 --------------------------------

	// 함수 객체  //function object  // 특정 형식의 코드를 정의 (매개변수로 활용)
	function<int(int, int)> f2 = Add;
	cout << f2(3, 4) << endl;

	// 4.함수 객체에 맞는 람다식을 전달하기
	function<int(int, int)> f3 = [](int x, int y) { return x + y; };
	cout << f3(3, 4) << endl;
}

// [capture list](받는 인자) {함수 본체} (실행인자)
// 
//  []   // lambda capture 영역
//  ()   // parameter list 영역
//  {}   // body 영역
// 
//  ()   // lambda 함수를 명시적으로 호출할 때

//장점 : 코드 간결성, 지연 연산으로 인한 성능 향상
//단점 : 셀프 난독화 가능, 디버깅시 콜스택 추적 hard
