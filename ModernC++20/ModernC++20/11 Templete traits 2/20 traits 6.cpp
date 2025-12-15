//정책 클래스를
//클래스 템플릿을 사용해서 정책클래스 인터페이스를 설계해 템플릿 템플릿 인자를 사용할 수도 있다.

//템플릿 템플릿 파라미터를 통해 
//템플릿 파라미터에 종속된 데이터형을 갖는 상태 정보를 정책클래스 내에 갖기 쉽게 된다.

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
template <typename T1, typename T2>                             //
class SumPolicy {
public:
    static void accumulate(T1& total, T2 const& value) {
        total += value;
    }
};
//곱셈 정책 클래스 --------------------------------------------
template<typename T1, typename T2>                             //
class MultPolicy {
public:
    static void accumulate(T1& total, T2 const& value) {
        total *= value;
    }
};

//------------------------------------------------------------------
template <typename T,
        template<typename, typename> class Policy = SumPolicy,      //
        typename Traits = AccumulationTraits<T> >   
class Accum {
    public:
        typedef typename Traits::AccT AccT;
        static AccT accum(T const* beg, T const* end) {
            AccT total = Traits::zero();
            while (beg != end) {
                Policy<AccT, T>::accumulate(total, *beg);       //
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
    std::cout 
        << Accum<int>::accum(&num[0], &num[5])
        << '\n';

}


//특질과 정책을 사용함으로써 파라미터 수를 사용자가 충분히 관리할 수 있을 정도로 줄일 수 있다.



/*
//C++ 표준 라이브러리는 반복자 특질 이라고 불리는 것을 제공. std::iterator_traits

//일반화된 반복자를 다룰수 있는 능력을 추가해보자. 

#include <iterator> 

template <typename Iter>
inline typename std::iterator_traits<Iter>::value_type 
accum(Iter start, Iter end)
{
    typedef typename std::iterator_traits<Iter>::value_type VT;

    VT total = VT();  //VT()가 실제로 0값을 생성한다고 가정
    while (start != end) {
        total += *start;
        ++start;
    }
    return total;
}

*/
