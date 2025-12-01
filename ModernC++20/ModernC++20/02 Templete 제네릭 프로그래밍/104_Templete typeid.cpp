//RTTI(런타임 형식 정보)와 템플릿 메타프로그래밍 비교
// 
//      RTTI는 실행시간에 타입을 결정하는 것이고 
//      C++에서 RTTI를 제공하는 키워드는 dynamic_cast<>와 typeid가 있습니다. ***
//  
//      템플릿 메타프로그래밍은 
//      컴파일 타임에 타입계산이 이루어져 실행시간에서는 상수로 변해버리는 특성이 있다. 
//      템플릿 메타프로그래밍을 위해 decltype, constexpr 등 컴파일타임 키워드를 사용한다. ***


// typeid 는 실행시간에 객체의 클래스를 결정하는 경우에 사용된다.
// 즉, 템플릿에서 타입을 얻을 수 없음.

#include <iostream>
#include <typeinfo>  //typeid를 사용하기 위한 헤더

class BaseClass
{
public:
    virtual ~BaseClass() {}
};
class DerivedClass : public BaseClass
{
};

int main()
{
    BaseClass base;
    DerivedClass derived;
    BaseClass* ptr = &derived;
    BaseClass& ref = derived;

    std::cout << "typeid(base)    " << typeid(base).name() << std::endl;
    std::cout << "typeid(derived) " << typeid(derived).name() << std::endl;
    std::cout << "typeid(ptr)     " << typeid(ptr).name() << std::endl;
    std::cout << "typeid(*ptr)    " << typeid(*ptr).name() << std::endl;
    std::cout << "typeid(ref)     " << typeid(ref).name() << std::endl;

    return 0;
}

