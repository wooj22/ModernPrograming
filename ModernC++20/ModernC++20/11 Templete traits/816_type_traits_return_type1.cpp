//함수의 리턴타입, 인자타입 정보를 구하는 traits 만들기
//
//      메인 템플릿(Main template)을 만들고 
//          typedef T type 제공 (C++11 using 동일)
// 
//      부분 특수화(Partial specialization)를 통한 원하는 타입을 얻을 수 있도록 T 타입 분할
//          함수 타입 T(double(short, int))를 리턴타입 double과 인자타입(short, int)로 분리
//          T(double(short, int))->R(A1, A2)
// 
//      메인 템플릿의 활용도가 없을 경우 내부 type은 제거 해도 됨


#include <iostream>
using namespace std;

double hoo(short a, int b) { return 0; }

// 반환 타입에 대한 메인 템플릿
template<typename T>
struct result_type
{
    typedef T type;
};

// 함수타입에 대한 부분 특수화
template<typename T, typename A1, typename A2>
struct result_type<T(A1, A2)>
{
    typedef T type;
};

// 인자는 복수개이므로 N 파라미터 추가로 필요
template<typename T, size_t N>
struct argument_type
{
    typedef T type;
};

// 첫번째 인자에 대한 부분 특수화
template<typename R, typename A1, typename A2>
struct argument_type<R(A1, A2), 0>          //리턴타입(인자타입) 으로 분리
{
    typedef A1 type;
};

// 두번째 인자에 대한 부분 특수화
template<typename R, typename A1, typename A2>
struct argument_type<R(A1, A2), 1>
{
    typedef A2 type;
};

template<typename T> void foo(T& t)
{
    // T : double(short, int)
    typename result_type<T>::type ret_type;
    typename argument_type<T, 0>::type arg_type0;
    typename argument_type<T, 1>::type arg_type1;

    cout << typeid(ret_type).name() << endl; // double
    cout << typeid(arg_type0).name() << endl; // short
    cout << typeid(arg_type1).name() << endl; // int
}

int main()
{
    foo(hoo);
}


//C++11 표준의 함수 리턴 타입 구하기 -----------------------------------
//
//  result_of(C++17 미만)
//  invoke_result(C++17 이상)
//  decltype 사용해서 구현(일반함수, 함수 객체, 람다표현식등의 모든 callable object 고려)
