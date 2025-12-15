//가변인자 템플릿을 활용
 
//함수 정보를 구하는 traits 만들기
//      메인 템플릿(Primary template)을 만들고 typedef T type 제공
//      함수 타입의 T안에 있는 리턴 타입을 얻을 수 있도록 부분 특수화 구현
//      부분 특수화를 할 때 가변인자 템플릿을 활용

#include <iostream>
#include <type_traits>
using namespace std;

double hoo(short a, int b) { return 0; }        //이 함수 정보를 출력하자. ***

// 메인 템플릿
template<typename T>
struct result_type
{
    typedef T type;             //double(short, int)  //함수형식
};

// 함수 타입에 대한 부분 특수화, 가변인자 활용
template<typename T, typename ... Types>
struct result_type< T(Types ... args) >    //함수로 추론 // foo< double(short, int) >
{
    typedef T type;             //double    //함수반환형식
};

template<typename T> void foo(const T& t)
{
    // T : double(short, int) 함수 모양
    typename result_type<T>::type ret;
    cout << typeid(ret).name() << endl;
}

int main()
{
    foo(hoo);           //함수의 형식 추론  // foo<double(short, int)>
}


//traits 잘못 사용할때 처리 방법 ---------------------------------------------------------------
// 
//  메인 템플릿에서 typedef T type을 제공하지 않는 방법
//  메인 템플릿에서 static_assert()를 사용해서 명시적 에러 메시지 출력
//  메인 템플릿의 선언만 구현

#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;

// 1. typedef T type 미제공
template<typename T>
struct result_type
{
};

// 2. static_assert()를 사용해서 에러 메시지 출력
template<typename T>
struct result_type
{
    static_assert(is_function<T>::value, "Not supported type");
};

// 3. 선언부만 제공
template<typename T>
struct result_type;


// 함수 타입에 대한 부분 특수화
template<typename T, typename ... Types>
struct result_type<T(Types ... args)>
{
    typedef T type;
};


template<typename T> void foo(const T& t)
{    
    typename result_type<T>::type ret;      // T : double(short, int) 함수의 result_type
    cout << typeid(ret).name() << endl;
}

double hoo(short a, int b) { return 0; }

int main()
{
    foo(hoo);
}