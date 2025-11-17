#include <iostream>
#include <string>
using namespace std;

void main()
{
	string* p = new string("C++");	// 스트링 객체  동적 생성
	cout << *p;						// "C++" 출력

	p->append(" Great!!");			// p가 가리키는 스트링이 "C++ Great!!"이 됨
	cout << *p;						// "C++ Great!!" 출력

	delete p;						// 스트링 객체  반환
}

// 스트링 생성

int main() 
{	
	string str;								// 빈 문자열을 가진 스트링 객체 생성
	cout << str << endl;					// 빈 스트링. 아무 값도 출력되지 않음

	char text[] = "Love C++";
	string title(text);						// 배열로 string 생성, "Love C++" 문자열을 가진 스트링 객체 생성
	cout << title << endl;

	string address("서울시 성북구 삼선동 389");	
	string copyAddress(address);			// 복사 생성, address의 문자열을 복사한 스트링 객체 생성
	cout << address << endl;
	cout << copyAddress << endl;

}
