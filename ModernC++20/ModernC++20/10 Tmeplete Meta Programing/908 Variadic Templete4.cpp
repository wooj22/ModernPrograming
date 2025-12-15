/*
함수의 인자 타입을 구하는 traits 만들기

메인 템플릿(Main template)만들고 typedef T type 제공

함수 타입인 T 안에 있는 함수 인자 타입을 얻을 수 있도록 부분 특수화
    T->R(A1, A2), T->R(A1, Types...)

N번째 인자 타입 구하는 방법
    0번째 인자의 타입을 구하는 부분 특수화 작성
    N번째 인자의 타입을 구하는 부분 특수화 작성
    N == 0이 될때까지 Recursive 사용
    Recuresive 사용시, 함수의 0번째 인자를 제거하고 N - 1 사용
    argument_type < 3, R(A1, A2, A3, A4))::type
        argument_type < 2, R(A1, A2, A3, A4))::type
            argument_type < 1, R(A1, A2, A3, A4))::type
                argument_type < 0, R(A1, A2, A3, A4))::type
*/

#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;

// 메인 템플릿
template<size_t N, typename T> struct argument_type
{
    typedef T type;
};

// 0번째 인자의 타입을 구하는 부분 특수화 작성
template<typename T, typename A1, typename ... Types>
struct argument_type<0, T(A1, Types ...)>
{
    typedef A1 type;
};

// N번째 인자의 타입을 구하는 부분 특수화 작성
template<size_t N, typename R, typename A1, typename ... Types>
struct argument_type<N, R(A1, Types ...)>
{
    typedef typename argument_type<N - 1, R(Types...)>::type type;  //
};

template<typename T> void foo(const T& t)       // T : double(short, int, double)
{    
    typename argument_type<0, T>::type ret;
    cout << typeid(ret).name() << endl;
}

// 함수 hoo 의 인자타입을 출력하자.

double hoo(short a, int b, double c) { return 0; }

int main()
{
    foo(hoo);
}

