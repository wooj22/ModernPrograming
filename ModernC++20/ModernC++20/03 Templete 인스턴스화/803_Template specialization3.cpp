//Couple - 템플릿 특수화 활용
//
//  2개의 인자로 받은 데이터를 보관하는 컨테이너
//  인자로 Couple 타입도 전달 가능
//  부분 특수화(Partial specialization)를 할때 파라미터 수를 잘 선택해야함
//  파라미터로 자기 자신을 재귀로 입력 시 N 표현 방법 고려
//  1 번째 인자, 2번째 인자, 모든 인자가 Couple 일 경우 특수화 방법 고려


#include <iostream>
#include <type_traits>
using namespace std;

// 보관 데이터 수를 출력하는 함수
template<typename T> void printN(const T& cp)
{
    cout << T::N << endl;
}

// 2개의 인자를 보관하는 데이터(메인 템플릿)
template<typename T, typename U> struct Couple
{
    T v1;
    U v2;
    enum { N = 2 };
};

// 2번째 인자가 Couple일 경우
template<typename A, typename B, typename C>
struct Couple<A, Couple<B, C>>
{
    A v1;
    Couple<B, C> v2;
    enum { N = Couple<B, C>::N + 1 };
};

// 1번째 인자가 Couple일 경우
template<typename A, typename B, typename C>
struct Couple<Couple<A, B>, C>
{
    Couple<A, B> v1;
    C v2;
    enum { N = Couple<A, B>::N + 1 };
};

// 1번째, 2번째 모든 인자가 Couple일 경우
template<typename A, typename B, typename C, typename D>
struct Couple<Couple<A, B>, Couple<C, D>>
{
    Couple<A, B> v1;
    Couple<C, D> v2;
    enum { N = Couple<A, B>::N + Couple<C, D>::N };
};

int main()
{
    // 2개의 인자 데이터
    Couple<int, double> c2;

    // 2번째 인자에 Couple 데이터를 입력 할 경우(총 3개 보관)
    // 가변 영역의 데이터는 int, int, char 총 3개
    Couple<int, Couple<int, char>> c3;

    // 2번째 인자의 Couple 데이터의 2번째 인자에 다시 Couple 데이터를 입력 할 경우(총 4개 보관)
    // Couple 데이터를 중첩하여 사용하였으나 가변 영역은 동일하게 int, int, T로 총 3개
    Couple<int, Couple<int, Couple<int, char>>> c4;

    // 1번째, 2번째 인자 모두 Couple 데이터를 입력 할 경우(총 4개 보관)
    Couple<Couple<int, int>, Couple<int, int>> c5;

    // 보관 데이터 수 출력
    printN(c2);
    printN(c3);
    printN(c4);
    printN(c5);
}



//XTuple(Couple 선형화 구현) - 상속과 재귀 활용
//
//  Couple 재귀 호출 대신 선형 호출 할 수 있는 패턴 지원
//      Couple<int, Couple<int, double>...>->XTuple<int, int, double...> 형태로 개선
//  Null 클래스 활용(Empty class)
//      멤버 없는 클래스
//      크기는 항상 1(sizeof(Null))
//      멤버는 없지만 타입이므로 함수 오버로딩이나 템플릿 인자로 활용
//  상속 활용 기술
// 
//  개수의 제한을 없앨 수 없을까 ? C++ + Variadic template

#include <iostream>
#include <type_traits>
using namespace std;

template<typename T, typename U> struct Couple
{
    T v1;
    U v2;
    enum { N = 2 };
};

// 빈 파라미터로 활용하기 위한 empty class
struct Null {};

// 2개이상 5개 미만의 타입 전달
template<typename P1,
    typename P2,
    typename P3 = Null,
    typename P4 = Null,
    typename P5 = Null>
    class XTuple
    : public Couple<P1, XTuple<P2, P3, P4, P5, Null>>  //Couple<P2, XTuple<P3, P4, P5, Null>> ...
{

};

// XTuple 상속을 종료하기 위한 특수화
template<typename P1, typename P2>
class XTuple<P1, P2, Null, Null, Null>
    : public Couple<P1, P2>
{

};

int main()
{
    // Couple을 선형화하여 XTuple 형태로 사용
    XTuple<int, char, long, short, double> t5;
}

// <int, < char, <long, <short, double> > > >
