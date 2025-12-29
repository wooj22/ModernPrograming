//C++ 템플릿 패턴 // Thin template, 코드 메모리 최적화 기법

//thin template
//
//  템플릿의 단점 중 한가지는 코드 메모리의 증가, 최적화를 위해 템플릿 활용
//  모바일등 메모리가 부족한 환경에서 사용할 수 있는 기법


#include <iostream>
using namespace std;

template<typename T> class Vector
{
    T* buff;
    int sz;
public:
    int size() const {}
    bool empty() const {}
    void push_front(const T& a) {}          //
    T& front() {}                           //
};

int main()
{
    Vector<int> v1;
    Vector<short> v2;
    Vector<double> v3;
}
//4개의 함수 구성 * 3개의 타입 사용 = 총 12개의 함수 생성  --> 줄이자.

//'T를 사용하지 않는 모든 멤버'를 기반클래스에 정의하고 '상속'받아서 구현하면
//2개의 함수 구성 * 3개의 타입 사용 + 기반 클래스 함수 2개 = 총 8개의 함수 생성


//모든 T는 void* 로 변경, 
//void* 를 바로 사용하면 캐스팅이 불편하므로 캐스팅을 책임지는 파생 클래스를 템플릿으로 제공
//기반 클래스 멤버를 직접 호출 방지를 위해 private 상속으로 변경

#include <iostream>
using namespace std;

class VectorBase
{
protected:
    void* buff;
    int sz;
public:
    int size() const {}
    bool empty() const {}
    void push_front(const void* a) {}
    void* front() {}
};

// void*를 바로 사용하면 캐스팅의 불편함이 있음, 캐스팅을 책임지는 파생 클래스를 템플릿으로 제공
template<typename T> class Vector : private VectorBase
{
public:
    //int size() const { return VectorBase::size(); }
    //bool empty() const { return VectorBase::empty(); }
    inline void push_front(const T& a) { VectorBase::push_front(static_cast<void*>(a)); }
    inline T& front() { return static_cast<T&>(VectorBase::front()); }
};

int main()
{
    Vector<int> v1;
    Vector<short> v2;
    Vector<double> v3;
}


