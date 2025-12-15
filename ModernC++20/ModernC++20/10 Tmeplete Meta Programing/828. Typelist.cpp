//C++ 템플릿 디자인 

//Typelist
// 
//		값이 아닌 타입의 리스트를 보관하는 데이터 타입
//		템플릿 인자가 1개라도 Typelist를 활용하면 복수의 타입을 만들 수 있음

#include <iostream>
using namespace std;

// 값을 보관하지 않음 // 타입 2개를 보관함
template<typename T, typename U> struct Typelist
{
    typedef T Head;
    typedef U Tail;
};

struct NullType {};

// 매크로 도입
#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, Typelist<T2, NullType>>
#define TYPELIST_3(T1, T2, T3) Typelist<T1, Typelist<T2, Typelist<T3, NullType>>>
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, Typelist<T2, Typelist<T3, Typelist<T4, NullType>>>>

template<typename T> class xtuple {};

int main()
{
    xtuple<int> t0;

    Typelist<int, NullType> t1;
    Typelist<int, Typelist<int, NullType>> t2;
    Typelist<int, Typelist<int, Typelist<char, NullType>>> t3;

    TYPELIST_1(int) u1;
    TYPELIST_2(int, int) u2;
    TYPELIST_3(int, int, int) u3;
}


//Typelist Length ----------------------------------------------------------
//
//      타입리스트의 요소 수 구하기

#include <iostream>
using namespace std;

// 값을 보관하지 않음 // 타입 2개를 보관함
template<typename T, typename U> struct Typelist
{
    typedef T Head;
    typedef U Tail;
};

struct NullType {};

// 매크로 도입
#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, Typelist<T2, NullType>>
#define TYPELIST_3(T1, T2, T3) Typelist<T1, Typelist<T2, Typelist<T3, NullType>>>
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, Typelist<T2, Typelist<T3, Typelist<T4, NullType>>>>

// 1. 사용하는 모습을 보고 메인 템플릿 생성
template<typename T> struct Length;
// 2. 갯수를 구할 수 있도록 부분 특수화
template<typename T, typename U> struct Length<Typelist<T, U>>
{
    enum { value = Length<U>::value + 1 };
};
// 3. 재귀를 종료하기 위한 특수화
template<> struct Length<NullType>
{
    enum { value = 0 };
};

template<typename T> void get_size()
{
    cout << Length<T>::value << endl; // 4
}

int main()
{
    get_size<TYPELIST_4(int, int, double, float)>();
}

//TypeAt ----------------------------------------------------------

#include <iostream>
using namespace std;

// 값을 보관하지 않음 // 타입 2개를 보관함
template<typename T, typename U> struct Typelist
{
    typedef T Head;
    typedef U Tail;
};

struct NullType {};

// 매크로 도입
#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, Typelist<T2, NullType>>
#define TYPELIST_3(T1, T2, T3) Typelist<T1, Typelist<T2, Typelist<T3, NullType>>>
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, Typelist<T2, Typelist<T3, Typelist<T4, NullType>>>>


// Typelist의 N번째 요소의 타입 구하기
// 메인 템플릿
template<typename T, int N> struct TypeAt
{
    //typedef ? type;
};

// 원하는 타입을 구할 수 있도록 부분 특수화
// N == 0
template<typename T, typename U> struct TypeAt<Typelist<T, U>, 0>
{
    typedef T type;
};

// 원하는 타입을 구할 수 있도록 부분 특수화
// N != 0
template<typename T, typename U, int N> struct TypeAt<Typelist<T, U>, N>
{
    typedef typename TypeAt<U, N - 1>::type type;
};

template<typename T> void test()
{
    typename TypeAt<T, 0>::type i; // int
    cout << typeid(i).name() << endl;

    typename TypeAt<T, 1>::type c; // char
    cout << typeid(c).name() << endl;

    typename TypeAt<T, 2>::type d; // double
    cout << typeid(d).name() << endl;

    typename TypeAt<T, 3>::type l; // long
    cout << typeid(l).name() << endl;
}

int main()
{
    test<TYPELIST_4(int, char, double, long)>();
}

//Append ----------------------------------------------------------

#include <iostream>
using namespace std;

// 값을 보관하지 않음 // 타입 2개를 보관함
template<typename T, typename U> struct Typelist
{
    typedef T Head;
    typedef U Tail;
};

struct NullType {};

// 매크로 도입
#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, Typelist<T2, NullType>>
#define TYPELIST_3(T1, T2, T3) Typelist<T1, Typelist<T2, Typelist<T3, NullType>>>
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, Typelist<T2, Typelist<T3, Typelist<T4, NullType>>>>

// Typelist 끝에 타입 추가하기
template<typename TL, typename T> struct Append;

// TL T
// 1. NullType, NullType => NullType
template<> struct Append<NullType, NullType>
{
    typedef NullType type;
};

// 2. NullType, 임의의 타입 => Typelist<임의의 타입, NullType>
template<typename T> struct Append<NullType, T>
{
    typedef Typelist<T, NullType> type;
};

// 3. NullType, Typelist<Head, Tail> = Typelist<Head, Tail>
template<typename Head, typename Tail> struct Append<NullType, Typelist<Head, Tail>>
{
    typedef Typelist<Head, Tail> type;
};

// 4. Typelist<Head, Tail>, NullType => Typelist<Head, Tail>
template<typename Head, typename Tail> struct Append<Typelist<Head, Tail>, NullType>
{
    typedef Typelist<Head, Tail> type;
};

// 5. Typelist<Head, Tail>, 임의의 타입 => Typelist<Head, Append<Tail, T>::type>
template<typename Head, typename Tail, typename T> struct Append<Typelist<Head, Tail>, T>
{
    typedef Typelist<Head, typename Append<Tail, T>::type> type;
};

template<typename T> void test()
{
    typename Append<T, int>::type t1;
    cout << typeid(t1).name() << endl; // int, char, double, int, NullType
}

int main()
{
    test<TYPELIST_3(int, char, double)>();
}

//Typelist 예제 -------------------------------------------------------------------------


#include <iostream>
using namespace std;

// 타입 2개를 보관함
template<typename T, typename U> struct Typelist
{
    typedef T Head;
    typedef U Tail;
};
// 값을 보관하지 않음
struct NullType { };

// 매크로 도입
#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, Typelist<T2, NullType>>
#define TYPELIST_3(T1, T2, T3) Typelist<T1, Typelist<T2, Typelist<T3, NullType>>>
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, Typelist<T2, Typelist<T3, Typelist<T4, NullType>>>>

// Holder : 임의 타입의 data 1개 보관
template<typename T> struct Holder
{
    T value;
};

// GenScatterHierachy => MakeCode
template<typename T, template<typename> class Unit>
class MakeCode : public Unit<T>
{
};

template<template<typename> class Unit>
class MakeCode<NullType, Unit>
{
};

template<typename Head, typename Tail, template<typename> class Unit>
class MakeCode<Typelist<Head, Tail>, Unit> : public MakeCode<Head, Unit>, public MakeCode<Tail, Unit>
{
    // int value;
    // double value;
};

int main()
{
    // MakeCode 의 1번째 인자가 Typelist 일 때
    MakeCode<TYPELIST_2(int, double), Holder> mc1;  // 기반 클래스 Holder<int> // Holder<int> 와 메모리 모양이 동일
    //mc1.Holder<int>::value;
    //mc1.Holder<double>::value;

    // MakeCode<int, Unit>, MakeCode<Typelist<double, NullType>, Unit>
    // Holder<int>        , MakeCode<double, Unit> , MakeCode<NullType, Unit>
    //                    , Holder<double>         , empty 

    MakeCode<double, Holder> mc2; // Holder<double>
    //mc2.value

    MakeCode<NullType, Holder> mc3; // Empty
}