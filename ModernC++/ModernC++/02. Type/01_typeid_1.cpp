//typeid
//		자료형이나 변수 또는 식을 입력받아 const type_info& 형식의 객체를 반환해 주는 연산자
//		name 멤버함수는 해당 자료형에 대한 문자열 표현을 const char* 형태로 반환
//
//		typeid(변수이름).name()을 사용하면 '런타임'에 개체의 형식을 확인할 수 있다. 
//      RTTI (Runtime Type Information)라고도 함

#include <iostream>
using namespace std;

void main()
{
	cout << typeid(int).name() << endl;				//기본 자료형
	cout << typeid(type_info).name() << endl;		//클래스
	cout << typeid(main).name() << endl;			//함수
	cout << typeid(cout).name() << endl;			//객체

	//그밖에 enum, 사용자 정의 클래스, 멤버 함수, 람다 함수까지도 받을 수 있는 연산자
}

// typeid 관련 함수
// 
// raw_name()
//		해당 자료형의 압축된 형식의 문자열을 그대로 출력, 비교연산 등에서 좀 더 빠른 성능
// before() 
//		형식의 정렬된 순서에 따라 0 또는 1을 리턴, 부모 자식 클래스 간에서는 항상 같은 순서를 유지
// hash_code()
//		해쉬 코드를 리턴합니다. 해쉬 코드는 해쉬 테이블 등에 인덱스로 사용
// 비교 연산자 ==, !=


//부모 클래스에 virtual 함수가 있을 경우 자식 클래스를 구분할 수 있다. ***

class A {
public:
	virtual void vf() {}
};
class B : public A {};
class C : public A {};
class D : public A {};

int main() {
	B b;
	C c;
	D d;
	A* a[] = { &b, &c, &d };

	cout << typeid(*a[0]).name() << endl;
	cout << typeid(*a[1]).name() << endl;
	cout << typeid(*a[2]).name() << endl;
}

//-------------------------------------------------------------------------
//자식클래스로 형변환히 필요할 때
//사전에 해당 클래스가 맞는지 확인한 후 형 변환을 할 수 있어, 보다 안전한 부모자식간 형변환이 가능

class A {
public:
	virtual void vf() {}
};
class B : public A { public: bool b;};
class C : public A { public: int c;};

void memberPrint(A* a)			// 매개변수가 B 타입인지 C 타입인지 구분하기.
{
	if (typeid(B) == typeid(*a)) {			//B 클래스인지 검사
		B* b = (B*)a;						//자식클래스로 강제 형변환 이지만 안전이 보장됨
		cout << typeid(b->b).name() << endl;
	}
	else if (typeid(C) == typeid(*a)) {		//C 클래스인지 검사
		C* b = (C*)a;						//자식클래스로 강제 형변환 이지만 안전이 보장됨
		cout << typeid(b->c).name() << endl;
	}
}

int main() {
	B b;
	C c;
	A* a[] = { &b, &c };
	memberPrint(a[0]);
	memberPrint(a[1]);
}

//-------------------------------------------------------------------------
//typeid //템플릿에서 템플릿 매개 변수의 형식을 확인하는 데 사용

#include <typeinfo>

template < typename T >
T max(T arg1, T arg2) {
	cout << typeid(T).name() << endl;
	return (arg1 > arg2 ? arg1 : arg2);
}

//클래스의 이름을 문자열로 치환하는데 정해진 규칙이 없기 때문에 
//typeid(Widget).name() 이 동일한 문자열을 반환해 줄것이라고 기대해서는 안됩니다.
//컴파일러 제작사 마다 다릅니다 ***


//-------------------------------------------------------------------------
//typeid
//		자료형이나 변수 또는 식을 입력받아 const type_info& 형식의 객체를 반환해 주는 연산자
//		name 멤버함수는 해당 자료형에 대한 문자열 표현을 const char* 형태로 반환
//
//	식이 포인터가 아니고 개체의 기본 클래스에 대한 참조가 아닌 경우, 결과는 식의 정적 형식을 나타내는 참조입니다
//	식의 정적 형식은 컴파일 시간에 알려진 식의 형식을 나타냅니다. 
//	식의 정적 형식을 결정할 때 가능할 경우 참조가 무시됩니다 ***

#include <iostream>
#include <typeinfo>

int main()
{
	bool rt = typeid(int) == typeid(int&); // evaluates to true
	std::cout << rt << std::endl;;

	std::cout << typeid(int&).name() << std::endl;
}


//타입정보
//	(typeid, static_cast, dynamic_cast, const_cast, 멤버 포인터 변수)
//https://andjjip.tistory.com/295

