//특질(Trait)과 정책(Policy) 클래스
//		C++ 프로그래밍 장치로 실질적인 템플릿을 설계하는 단계에서 제안된 것으로 
//		이들을 사용하면 추가 파라미터들을 쉽게 관리할 수 있다

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

//템플릿 파라미터를 추가하되 특질 템플릿으로 추가된 파라미터 기본값을 정하는 방식으로, 클래스 템플릿 작성
template <typename T, typename AT = AccumulationTraits<T> >
class Accum {
public:
    static typename AT::AccT accum(T const* beg, T const* end) {
        typename AT::AccT total = AT::zero();
        while (beg != end) { total += *beg; ++beg; }
        return total;
    }
};

//인터페이스를 단순화 하기 위해 편의 함수를 도입

template <typename T>
inline typename AccumulationTraits<T>::AccT accum(T const* beg, T const* end)
{
    return Accum<T>::accum(beg, end);
}

template <typename T, typename Traits >  // 다른 특질을 위한 편의함수
inline typename Traits::AccT accum(T const* beg, T const* end)
{
    return Accum<T, Traits>::accum(beg, end);
}

int main()
{
    // int 배열 5개 생성
    int num[] = { 1,2,3,4,6 };
    std::cout << "int " << accum(&num[0], &num[5]) / 5 << '\n';

    // int 배열 5개 생성
    int num3[] = { 1,2,3,4,6 };
    std::cout << "int " << Accum<int, AccumulationTraits<float>>::accum(&num3[0], &num3[5]) / 5 << '\n';

    // float 배열
    float num2[] = { 1.5f, 2.0f, 3.0f};
    std::cout << "float " << accum<float, AccumulationTraits<int>>(&num2[0], &num2[3]) / 3 << '\n';
}
