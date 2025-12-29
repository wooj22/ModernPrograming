//데이터형 함수
//      데이터형 함수는 데이터형 인자를 받아 결과로 데이터형이나 상수를 생성한다

#include <iostream> 

template <typename T>                                   //메타프로그래밍 입장에서 보면 함수
class TypeSize {                
public:
    static size_t const value = sizeof(T);
};

template <typename T>
constexpr int typeSize() { return sizeof(T); };


int main()
{
    std::cout << TypeSize<int>::value << std::endl;     //템플릿클래스명<입력데이터>::리턴데이터
    std::cout << typeSize<int>() << std::endl;
}

//컨테이너 요소의 데이터형 결정 --------------------------------------------------------------------------------

//부분 특수화를 사용함으로써 컨테이너형이 데이터형 함수에 대해 알지 못하더라도 데이터형 함수를 구현할 수 있다.

#include <vector> 
#include <list> 
#include <stack> 
#include <iostream> 
#include <typeinfo> 

template <typename T>
class ElementT;                     // 기본 템플릿

template <typename T>
class ElementT<std::vector<T> > {   // 부분 특수화 
public:
    typedef T Type;
};

template <typename T>
class ElementT<std::list<T> > {     // 부분 특수화 
public:
    typedef T Type;
};

template <typename T>
class ElementT<std::stack<T> > {    // 부분 특수화 
public:
    typedef T Type;
};

//데이터형이 value_type이라는 멤버형을 정의한다면 다음과 같이 작성될 수 있다.

template <typename C>
class ElementT {
public:
    typedef typename C::value_type Type;
};

template <typename T>
void print_element_type(T const& c)
{
    std::cout << "Container of "
        << typeid(typename ElementT<T>::Type).name()
        << " elements.\n";
}

int main()
{
    std::stack<bool> s;
    print_element_type(s);
}

