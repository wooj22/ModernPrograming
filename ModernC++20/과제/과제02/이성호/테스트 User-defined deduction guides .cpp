// 클래스 템플릿 인수 추론을 이용해서 
// 기본 생성의 경우에도 Vector<int> 객체가 생성되도록 코드를 수정하세요.

#include <iostream>
#include <type_traits>
using namespace std;

template<typename T> class Vector
{
	T* buff;
public:
	Vector() {};// 타입 추론이 불가능 할경우 유저 정의 추론 가이드 필요
	Vector(int sz, T initValue) {}

};

Vector() -> Vector<int>;

int main()
{
	Vector v1(10, 3);       // 생성자 매개변수로 추론가능 
	Vector v2;              // 가이드를 통해서 추론 가능
}