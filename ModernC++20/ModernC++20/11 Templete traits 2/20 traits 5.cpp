//특질(Trait)과 정책(Policy) 클래스
//		C++ 프로그래밍 장치로 실질적인 템플릿을 설계하는 단계에서 제안된 것으로 
//		이들을 사용하면 추가 파라미터들을 쉽게 관리할 수 있다


//정책과 정책 클래스
//      정책 클래스는 알고리즘에 하나 이상의 정책을 적용하는 인터페이스를 제공하는 클래스 이다.

//accumulation, summation 의 의미로 사용하지 않고 주어진 값의 수열을 곱할 수도 있다.

//정책 클래스를 추가하자.

#include <iostream> 

template<typename T> class AccumulationTraits;

template<> class AccumulationTraits<int> {
public:
    typedef long AccT;
    static AccT zero() { return 0; }
};

template<> class AccumulationTraits<char> {
public:
    typedef int AccT;
    static AccT zero() { return 0; }
};

template<> class AccumulationTraits<float> {
public:
    typedef double AccT;
    static AccT zero() { return 0; }
};

//덧셈 정책 클래스 --------------------------------------------
class SumPolicy {
public:
    template<typename T1, typename T2>
    static void accumulate(T1& total, T2 const& value) {
        total += value;
    }
};
//곱셈 정책 클래스 --------------------------------------------
class MultPolicy {
public:
    template<typename T1, typename T2>
    static void accumulate(T1& total, T2 const& value) {
        total *= value;
    }
};
//------------------------------------------------------------------
template <typename T,
    typename Policy = SumPolicy,    //정책 클래스를 담는 파라미터
    typename Traits = AccumulationTraits<T> >
    class Accum {
    public:
        typedef typename Traits::AccT AccT;
        static AccT accum(T const* beg, T const* end) {
            AccT total = Traits::zero();
            while (beg != end) {
                Policy::accumulate(total, *beg);
                ++beg;
            }
            return total;
        }
};

//인터페이스를 단순화 하기 위해 편의 함수를 도입
template <typename T>
inline typename AccumulationTraits<T>::AccT accum(T const* beg, T const* end)
{
    return Accum<T>::accum(beg, end);
}
// 다른 특질을 위한 편의함수
template <typename T, typename Traits >
inline typename Traits::AccT accum(T const* beg, T const* end)
{
    return Accum<T, Traits>::accum(beg, end);
}

int main()
{
    // create array of 5 integer values 
    int num[] = { 1,2,3,4,5 };

    // print product of all values 
    std::cout << "the product of the integer values is "
        << Accum<int, MultPolicy>::accum(&num[0], &num[5])
        << '\n';

    //결과는???                    // 0 //기본값이 0이기 때문

    //다양한 특질과 정책이 상호작용할 수 있으므로 템플릿 설계가 중요
    //모든것을 특질과 정책으로만 해결해야 하는 것은 아니다.
    //예를 들어 C++표준 라이브러리 accumulate()함수는 초기값을 세번째 인자로 받는다.
}

//특질과 정책의 차이점
// 
//특질 클래스 : 템플릿 파라미터의 자리에 사용되는 클래스. 
//      클래스이므로 유용한 데이터형과 상수를 수용할 수 있으며, 템플릿이기도 하므로 많은 문제를 해결할 수 있다.
//정책 : 정책은 특질과 여러모로 유사하지만 
//      이들은 데이터형보다 좀 더 행위에 초점을 맞춘다
//
//특질은 템플릿 파라미터에 자연스럽게 추가된 속성.
//정잭은 일반 함수와 데이터형에 따라 구성될 수 있는 행위.

//특질에 대해서
//      특질 파라미터는 대부분 매우 자연스러운 기본값을 가진다.
//      특질 파라미터는 하나 이상의 주요 파라미터에 긴밀히 종속돼 있곤 하다.
//      특질은 멤버 함수보다는 데이터형이나 상수와 결합된다.
//      특질은 특질 템플릿으로 모아지곤 한다.
//
//정책 클래스에 대해서
//      정책 클래스는 템플릿 파라미터로 전달되지 않을 경우 크게 기여하는 바가 없다.
//      정책 파라미터는 기본 값을 가질 필요가 없으며 일반적으로 외부에서 명시된다.
//      정책 파라미터는 템플릿의 다른 파라미터와 크게 관련이 없다.
//      정책 클래스는 대체로 멤버 함수와 결합 된다.
//      정책은 일반 클래스나 클래스 템플릿으로 모을 수 있다.

//두 용어 사이의 경계선은 뚜렷하지 않다. 특질로 기능을 정의하기도 하기도 한다. 
