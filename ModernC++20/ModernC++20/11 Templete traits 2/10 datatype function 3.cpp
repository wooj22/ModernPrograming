//데이터형 함수
//      데이터형 함수는 데이터형 인자를 받아 결과로 데이터형이나 상수를 생성한다

//데이터형의 승격 특질 -------------------------------------------------------------------------------
//      연산자 템플릿을 작성할 때 매우 유용하게 쓰이는 데이터형 승격 특질

//두 Array 컨테이너를 더하는 함수 템플릿

    template<typename T1, typename T2>
    Array< ??? > operator+ (Array<T1> const&, Array<T2> const&);	//반환형은 뭔지 몰라서 ??? 표기


    template<typename T1, typename T2>
    typename Promotion<Array<T1>, Array<T2> >::ResultT				//데이터형 승격 특질을 만들자.
    operator+ (Array<T1> const&, Array<T2> const&);


//두 데이터형 파라미터 중 하나를 선택하기 위해 불리언 형의 값을 템플릿 파라미터로 받는 특별한 템플릿인 IfThenElse를 사용

#include <type_traits>
#include <iostream>


// 기본 템플릿 첫번째 인자에 따라 두번째나 세번째 선택 
template<bool C, typename Ta, typename Tb>
class IfThenElse;

// 부분 특수화 : true이면 두번째 선택
template<typename Ta, typename Tb>
class IfThenElse<true, Ta, Tb> {
public:
    typedef Ta ResultT;
};

// 부분 특수화 : false이면 세번째 선택
template<typename Ta, typename Tb>
class IfThenElse<false, Ta, Tb> {
public:
    typedef Tb ResultT;
};


//데이터형 승격이 필요한 데이터형의 크기에 따라 T1, T2와 void 중 하나를 선택 ***

template<typename T1, typename T2>
class Promotion {
public:
    typedef typename
        IfThenElse<(sizeof(T1) > sizeof(T2)),
        T1,
        typename IfThenElse<(sizeof(T1) < sizeof(T2)),
        T2,
        void
        >::ResultT
        >::ResultT ResultT;
};

//전체적인 로직을 보면
//sizeof(T1) > sizeof(T2) 이면 T1, sizeof(T1) < sizeof(T2) 이면 T2, sizeof(T1) == sizeof(T2) 이면 void 를 선택한다는 뜻이다

// 동일한 데이터형을 위한 부분 특수화
template<typename T>
class Promotion<T, T> {
public:
    typedef T ResultT;
};


//기초 데이터형의 데이터형 승격을 기록하려면 많은 특수화가 필요하다

//매크로를 사용해서 소스 크기를 줄여보자
#define MK_PROMOTION(T1,T2,Tr)        \
template<> class Promotion<T1, T2> {  \
public:                               \
    typedef Tr ResultT;               \
};                                    \
template<> class Promotion<T2, T1> {  \
public:                               \
    typedef Tr ResultT;               \
};

//데이터형 승격은 매크로로 추가하자
MK_PROMOTION(bool, char, int)
MK_PROMOTION(bool, unsigned char, int)
MK_PROMOTION(bool, signed char, int)
//...

//기초 데이터형에 대해 정의 되었으니 Array형을 보자

template<typename T1, typename T2>
class Promotion<Array<T1>, Array<T2> > {
public:
    typedef Array<typename Promotion<T1, T2>::ResultT> ResultT;
};

template<typename T>
class Promotion<Array<T>, Array<T> > {
public:
    typedef Array<typename Promotion<T, T>::ResultT> ResultT;
};