//스마트 포인터(smart pointer)
//		std 네임스페이스에 속해있고 <memory> 헤더파일에 속한 표준 포인터
//  
//		C++에서는 메모리 누수(memory leak)로부터 프로그램의 안전성을 보장하기 위해 스마트 포인터를 제공
// 
//		스마트 포인터(smart pointer)란 포인터처럼 동작하는 클래스 템플릿으로, 
//		사용이 끝난 메모리를 '자동으로' 해제해 줍니다 ***

//C++11부터는 다음과 같은 새로운 스마트 포인터를 제공한다.
//		unique_ptr	- 배타적 소유권
//		shared_ptr	- 공유 자원 관리
//		weak_ptr	- shared_ptr 보완

#include <iostream>
using namespace std;

class Foo {
public:
	Foo() { cout << "생성" << endl; }
	~Foo() { cout << "소멸" << endl; }
};

int main(void)
{
	// 동적할당 -------------------------------------
	
	Foo* ptr = new Foo();
	delete ptr;

	// 스마트 포인터 --------------------------------

	unique_ptr<Foo> sptr(new Foo());				//C++ 11 unique_ptr

	//unique_ptr<Foo> sptr = make_unique<Foo>();	//C++ 14 

	//해제하지 않아도 자동으로 소멸된다. ***


	//블럭 단위로 작동한다 ***
	cout << "before" << endl;
	{
		unique_ptr<Foo> ptr2 = make_unique<Foo>();
	}
	cout << "After" << endl;

	return 0;
}
