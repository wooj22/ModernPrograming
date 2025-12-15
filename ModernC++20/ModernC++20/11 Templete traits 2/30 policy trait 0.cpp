//속성 특질(property trait)
//		템플릿 파라미터의 속성을 결정하기 위해 사용
//		데이터형의 종류는 무엇인지, 혼합된 데이터형 연산에서 어떤 데이터형으로 데이터형 승격해야 할 것인지 등을 결정
// 
//정책 특질(policy trait)
//		특정 데이터형을 어떻게 취급해야하는지 정의 하는 것
//		정캑 클래스의 개념과 유사
//		속성 특질은 데이터형 함수로 구현될 수 있는데 정책 특질은 일반적으로 멤버 함수 내에 정책으로 캡슐화된다.


//읽기 전용 파라미터형
//C++에서 함수 호출 인자는 기본적으로 "값으로" 전달된다.
//큰 구조체는 const 참조자로 인자를 넘기는 것이 더 낫다.

template<typename T>
class RParam {
public:
    typedef typename IfThenElse<sizeof(T) <= 2 * sizeof(void*),
        T,
        T const&>::ResultT Type;
};

//컨테이너형의 복사 비용은 매우 클수 있다.
template<typename T>
class RParam<Array<T> > {
public:
    typedef Array<T> const& Type;
};

//성능 고려가 필요할 때 클래스 형을 선택적으로 추가하자 

template<typename T>
class RParam {
public:
    typedef typename IfThenElse<IsClassT<T>::No,
        T,
        T const&>::ResultT Type;
};

//클라이언트는 이들을 활용해 원하는 효과를 얻을 수 있다 ----------------------------
#include <iostream>
#include "rparam.hpp"

class MyClass1 {
public:
    MyClass1() { }
    MyClass1(MyClass1 const&) { }
};

class MyClass2 {
public:
    MyClass2() { }
    MyClass2(MyClass2 const&) { }
};

// MyClass2를 RRaram<>에게 값으로 전달
template<>
class RParam<MyClass2> {
public:
    typedef MyClass2 Type;
};


#include "rparam.hpp"
#include "rparamcls.hpp"

// 값으로 전달 또는 참조로 전달을 허용하는 함수
template <typename T1, typename T2>
void foo_core(typename RParam<T1>::Type p1,
    typename RParam<T2>::Type p2)
{
    //...
}

// 명시적 템플릿 파라미터 전달을 피하기 위한 래퍼(wrapper)
template <typename T1, typename T2>
inline
void foo(T1 const& p1, T2 const& p2)
{
    foo_core<T1, T2>(p1, p2);
}

int main()
{
    MyClass1 mc1;
    MyClass2 mc2;
    foo(mc1, mc2);  // foo_core<MyClass1,MyClass2>(mc1,mc2)와 동일
}