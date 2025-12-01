//함수 템플릿을 구현하였을 때, 함수 내부에서 값의 타입이 필요할 경우에
// 
//      T::value_type 이용
//      auto 사용도 가능

//함수 템플릿에서 '컨테이너의 데이터 타입' 사용하기.

#include <iostream>
#include <vector>
#include <list>
using namespace std;

template<typename T>
void print_first_element(T& v)  //T는 list<double> 
{
    T n = v.front();  //이렇게 쓸 수 없다.

    //typename T::value_type n = v.front();   // 1.값의 데이터 타입이 필요한 경우.
    //auto n = v.front();                   // 2.값의 데이터 타입 대신 auto 사용도 가능.

    cout << n << endl;
}

int main()
{
    list<double> v = { 1,2,3 };
    double n = v.front();

    print_first_element(v);   
}

// list<double>::value_type 이 어떻게 정의되어 있는지 살펴 보자.

//typedef 키워드 ---------------------------------------------------
// 
//      타입의 새로운 별칭을 정의하는 키워드

//typedef는 클래스 안에서 타입의 새로운 별칭을 지을 수 있습니다

//using 참고

#include <iostream>

class MyTypeClass
{
public:
    typedef int Type1;
private:
    typedef double Type2;
};
int main()
{
    MyTypeClass a;
    MyTypeClass::Type1 b;
    MyTypeClass::Type2 c;  //에러 private
    return 0;
}

//예시 --------------------------------------------
class MyTypeClass
{
public:
    typedef int Type1;
    
    void f() {
        Type2 c;
    }
private:
    typedef double Type2;
};

int main()
{
    MyTypeClass a;
    MyTypeClass::Type1 b;
    return 0;
}

//typedef 로 새로운 이름을 만들 때 원래 그 멤버 이름과 똑같이 짓는 것이 관례입니다

//------------------------------------------------------------------
//템플릿 파라미터로 받은 데이터 타입이 필요할 때가 있다

#include <iostream>

template<typename T>
class MyTempClass
{
public:
    typedef T TempType;                     //타입의 새로운 별칭을 정의
};

int main()
{
    MyTempClass<int> a;
    MyTempClass<int>::TempType b;           //int
    MyTempClass<double> c;
    MyTempClass<double>::TempType d;        //double
    return 0;
}

//템플릿에서 클래스이름::xx 로 접근 가능한 요소들
//      값   : enum 상수, static 멤버 변수
//      타입 : typedef, using


//------------------------------------------------------------------
//의존 타입 이름

//  템플릿 매개변수에 종속된 것을 '의존 이름(dependent name)'이라 한다.
//  정확히 하면, 클래스 안에 타입이 있으니, 중첩 의존 타입 이름(nested dependent type name)
//
//  의존타입이름 일 때는  typename 키워드로 타입임을 알려야 한다. ***
//  템플릿 내부에서는 이름이 나오면 기본적으로 값(Value)으로 인식하기 때문.

template <class T>
inline void PRINT_ELEMENTS(const T& coll, const char* optcstr = "")
{
    typename T::const_iterator pos;    //const_iterator 는 타입매개변수 T 에 의존 // typename 키워드 사용 

    std::cout << optcstr;
    for (pos = coll.begin(); pos != coll.end(); ++pos) {
        std::cout << *pos << ' ';
    }
    std::cout << std::endl;
}