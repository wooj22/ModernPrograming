//재정의 함수는 override로 선언하라.
//
//  virtual 함수와 같은 함수를 파생클래스가 정의하면, 자동 override. 
//  하지만 명시적으로 사용하자.

//override의 조건 ***
// 
//  기반 클래스 함수가 반드시 가상 함수이어야 한다.
//  기반 함수와 파생 함수의 이름이 반드시 동일해야 한다(단, 소멸자는 제외).
//  기반 함수와 파생 함수의 매개변수 타입들이 반드시 동일해야 한다.
//  기반 함수와 파생 함수의 반환 타입과 예외 지정(exception specification)이 반드시 호환되어야 한다.
//  기반 함수와 파생 함수의 const성이 반드시 동일해야 한다.
//  멤버 함수들의 참조 한정사(reference qualifier)들이 반드시 동일해야 한다. C++11

//파생 함수를 override로 선언하면, 컴파일러는 재정의 관련 문제점들을 모두 지적해준다. ***
//
//  파생 클래스들에서 override를 일관되게 적용했다면
//	기반 함수의 시그니처를 변경하고, 시스템을 다시 컴파일하고, 컴파일에 실패한 파생 클래스에 대해서만 판단하면 됨
//	아니라면, 상세한 단위테스트(unit test) 필요.


#include <iostream>

class Base {
public:
    virtual void mf1(void) const;
    virtual void mf2(int x);
    virtual void mf3(void)&;
    void mf4(void) const;
};

class Derived : public Base {
public:
    virtual void mf1(void);                  // const
    virtual void mf2(unsigned int x);        // unsigned 
    virtual void mf3(void)&&;                // 우측값
    void mf4(void) const;                    // virtual 선언 아님
};

int main()
{
    return 0;
}


// 실수한 경우도 컴파일 통과된다. ~~

// 연습) override 를 사용하여 제대로 컴파일해 보자.

/*
class Base {
public:
    virtual void mf1(void) const;
    virtual void mf2(int x);
    virtual void mf3(void) &;
    virtual void mf4(void) const;
};

class Derived: public Base {
public:
    virtual void mf1(void) const override;
    virtual void mf2(int x) override;
    virtual void mf3(void) & override;
    void mf4(void) const override;
};
*/

// 오버라이드, 오버로드, 하이딩, 객체잘림(Object Slicing), 
// 가상함수, 추상함수, 추상클래스, 인터페이스