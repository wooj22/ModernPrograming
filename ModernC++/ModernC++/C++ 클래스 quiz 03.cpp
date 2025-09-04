
// [가상함수, 가상 테이블]
// 문제: 다음 코드에서 vtable이 존재하는 객체는 ?

struct Base { virtual void f() {} };
struct Derived : Base { void f() override {} };

A) Base
B) Derived
C) 모두 o
D) 없음
