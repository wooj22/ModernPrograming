//CRTP 활용 예시

//특정 클래스형의 객체가 얼마나 많이 생성됐는지 추적하기

//모든 생성자에서 정수형 정적 데이터 멤버를 증가시키고 소멸자에서는 그 값을 감소시킨다
//하지만 그런 코드를 모든 클래스에 제공하는 것은 반복되는 작업이다.

//objectcounter.hpp -------------------------------------------------------

#include <stddef.h>

template <typename Type>
class ObjectCounter {
private:
    static size_t count;    // 존재하는 객체 수

protected:
    // 기본 생성자
    ObjectCounter() {
        ++ObjectCounter<Type>::count;
    }

    // 복사 생성자 
    ObjectCounter(ObjectCounter<Type> const&) {
        ++ObjectCounter<Type>::count;
    }

    // 소멸자
    ~ObjectCounter() {
        --ObjectCounter<Type>::count;
    }

public:
    // 존재하는 객체 수를 반환 
    static size_t live() {
        return ObjectCounter<Type>::count;
    }
};

// 카운터를 0으로 초기화
template <typename CountedType>
size_t ObjectCounter<CountedType>::count = 0;

// main.cpp -------------------------------------------------------------

//#include "objectcounter.hpp" 
#include <iostream>
using namespace std;

template <typename T>
class MyString : public ObjectCounter<MyString<T> > {
};

int main()
{
    MyString<char> s1, s2;
    MyString<wchar_t> ws;

    std::cout << "number of MyString<char>: "
        << MyString<char>::live() << std::endl;

    std::cout << "number of MyString<wchar_t>: "
        << ws.live() << std::endl;
}