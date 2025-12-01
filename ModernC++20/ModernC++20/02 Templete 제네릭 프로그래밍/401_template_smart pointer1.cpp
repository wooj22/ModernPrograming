// 스마트 포인터 구현하기 - 알아서 소멸되는 편리한 포인터.

#include <iostream>
using namespace std;

class Pos
{
private:
	int xpos, ypos;
public:
	Pos(int x = 0, int y = 0) : xpos(x), ypos(y) {  }
	~Pos() {  }
	void SetPos(int x, int y) { xpos = x; ypos = y; }
	friend ostream& operator<<(ostream& os, const Pos& pos) {
		os << '[' << pos.xpos << ", " << pos.ypos << ']' << endl;
		return os;
	}
};

class SmartPtr
{
private:
	Pos* rawptr;
public:
	SmartPtr(Pos* ptr) : rawptr(ptr) {  	}	 // raw 포인터 할당	
	Pos& operator*() const { return *rawptr; }   // 연산자 정의 
	Pos* operator->() const { return rawptr; }   // raw 포인터 반환
	~SmartPtr() { delete rawptr; }			     // 알아서 자동으로 소멸 //RAII
};

int main()
{
	SmartPtr sptr1(new Pos(1, 2));  //선언할때 생성하면 사라질 때 자동 소멸
	SmartPtr sptr2(new Pos(2, 3));
	cout << *sptr1;
	cout << *sptr2;

	sptr1->SetPos(10, 20);
	sptr2->SetPos(30, 40);
	cout << *sptr1;
	cout << *sptr2;

	return 0;
}


//템플릿 참고
// http://tcpschool.com/cpp/cpp_template_smartPointer

//스마트 포인터 기능은 c++11이후 부터  추가되었다. memory 헤더파일을 include해야 사용 가능하다.
//	unique_ptr
//	shared_ptr 
//	weak_ptr
//	auto_ptr은 C++11 표준부터 삭제