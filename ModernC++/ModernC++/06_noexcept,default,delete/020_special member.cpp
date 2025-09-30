/*
자동생성 in C++ 11 총정리 * **

default 생성자 :
	생성자 정의하면 자동 생성 안된다.C++ 98과 동일

소멸자 :
	부모가 virtual이면 자식도 virtual로 자동 생성.정의하면 자동생성 안된다.
	여기까지 C++ 98, C++ 11부터 바뀐점은 자동 생성된 소멸자가 noexcept로 만들어진다는 점.

copy 연산자들 :
	해당 함수가 선언되지 않았을 때, move 연산자들이 정의되지 않았을 때 자동 생성된다.***
	다른 copy연산자나, 소멸자가 있는 경우 자동 생성하는 것이 deprecated 되었다.
	비정적 멤버들에 대해서 해당 복사 연산자를 호출하는 방식으로 동작한다.

move 연산자들 :
	copy 연산자들, move 연산자들, 소멸자 모두가 정의되지 않았을 경우에만 자동 생성한다.***
	비정적 멤버들에 대해서 move 연산자를 호출하는 방식으로 동작한다.

특수 멤버함수가 템플릿 함수인 경우
	템플릿으로 짜여진 특수 멤버함수가 정의된 경우 자동생성을 방지하는 룰이 적용되지 않는다.

*/

//특수맴버 함수를 정의하세요.

class Base {
public:
	Base() = default;
	virtual ~Base(void) = default;                  // 소멸자를 가상으로

	Base(const Base&) = default;                    // 복사 지원
	Base& operator=(const Base&) = default;
	Base(Base&&) = default;                         // 이동 지원
	Base& operator=(Base&&) = default;
};

