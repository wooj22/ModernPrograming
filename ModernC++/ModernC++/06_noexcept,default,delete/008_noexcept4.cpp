//noexcept 연산자
//
//  noexcept 연산자는 컴파일 타임에 해당 표현식이 예외를 던지지 않는 표현식인지 체크하여, true/false를 반환한다.

//표현식이 다음의 경우 중 하나라도 포함하고 있으면, noexcept는 false를 반환하며, 그렇지 않은 경우엔 true를 반환한다.
//  상수 표현식이 아닌 함수가 noexcept 키워드를 가지지 않을 경우
//  런타임 체크가 필요한 dynamic_cast 등의 RTTI가 포함된 경우
//  typeid 표현식에 포함된 타입이 상속 관계에 있는 클래스나 구조체일 경우


//다음의 함수들은 기본적으로 noexcept를 가진다. ***
//  
//  암시적으로 생성되는 기본 생성자, 복사 생성자, 대입 연산자, 이동 생성자, 이동 연산자, 소멸자
//
//  유저가 명시적으로 noexcept(false)로 선언하거나, 부모의 소멸자가 그러하지 않은 경우를 제외한 
//  모든 유저 정의 소멸자 operator delete 함수들 (할당 해제 함수들)

//  이 중 암시적으로 생성되는 복사/이동 생성자나 대입/이동 연산자는 
//      '자신의 멤버들'이 복사나 이동시 noexcept를 보장해야만
//       이들의 생성자나 연산자가 기본적으로 noexcept를 가질 수 있다.      ***


#include <iostream>
#include <utility>
#include <vector>


void may_throw();                   // 예외를 던질 수 있음
void no_throw() noexcept;           // 예외를 던지지 못함

auto lmay_throw = [] {};            // 예외를 던질 수 있는 람다
auto lno_throw = []() noexcept {};  // 예외를 던지지 않는 람다

class T
{
public:
    // 명시적인 소멸자 선언으로 인해 이동생성자/이동연산자 암시적 생성 금지
    // 하지만 복사생성자/대입연산자는 noexcept로 암시적 생성
    ~T() {}
};

class U
{
    std::vector<int> mv;
public:
    // 명시적인 소멸자 선언으로 인해 이동생성자/이동연산자 암시적 생성 금지
    // 하지만, 복사생성자/대입연산자는 noexcept(false)로 암시적 생성
    // vector<int> mv 의 복사생성자/대입연산자가 noexcept가 아니기 때문...
    ~U() {}
};

class V
{
public:
    // 복사생성자/대입연산자는 noexcept(false)로 암시적 생성
    // 이동생성자/이동연산자는 noexcept로 암시적 생성
    // vector<int> mv의 복사생성자/대입연산자가 noexcept가 아니기 때문...
    std::vector<int> mv;
};

int main()
{
    T t;
    U u;
    V v;

    noexcept(may_throw());      // false
    noexcept(no_throw());       // true
    noexcept(lmay_throw());     // false       
    noexcept(lno_throw());      // true

    noexcept(std::declval<T>().~T());   // true  (기본적으로 유저 정의 소멸자는 noexcept)

    noexcept(T(std::declval<T>()));     // true  (T(rvalue t)는 이동생성자가 없으므로 복사생성자가 noexcept)
    noexcept(T(t));                     // true  (T(lvalue t) 복사생성자가 noexcept)

    noexcept(U(std::declval<U>()));     // false (U(rvalue u)는 이동생성자가 없으므로 복사생성자가 noexcept(false))
    noexcept(U(u));                     // false (U(lvalue u)는 복사생성자가 noexcept(false))

    noexcept(V(std::declval<V>()));     // true  (V(rvalue v)는 이동생성자가 noexcept)
    noexcept(V(v));                     // false (V(lvalue v)는 복사생성자가 noexcept(false))
}
