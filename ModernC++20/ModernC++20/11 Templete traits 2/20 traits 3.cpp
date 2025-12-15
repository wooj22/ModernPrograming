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


template <typename T>
inline
typename AccumulationTraits<T>::AccT accum(T const* beg,
    T const* end)
{
    // 반환형이 요소형의 특질이다.
    typedef typename AccumulationTraits<T>::AccT AccT;

    AccT total = AccumulationTraits<T>::zero();     //
    while (beg != end) {
        total += *beg;
        ++beg;
    }
    return total;
}

int main()
{
    // int 배열 5개 생성
    int num[] = { 1,2,3,4,5 };
    std::cout << "int " << accum(&num[0], &num[5]) / 5 << '\n';

    // char 배열 
    char name[] = "templates";
    int length = sizeof(name) - 1;
    std::cout << "char " << accum(&name[0], &name[length]) / length << '\n';  

    // float 배열
    float num2[] = { 1.5f, 2.0f, 3.0f};
    std::cout << "float " << accum(&num2[0], &num2[3]) / 3 << '\n';
}

//특질 사용이 고정되어 있다. 데이터형과 분리된 특질이 정의 되면 알고리즘 내에서 사용할 수 없다.
//템플릿 파라미터를 추가하되, 특질 템플릿으로 추가된 파라미터 기본값을 정하는 방식으로 하자
//함수 템플릿은 기본 템플릿 인자를 가질 수 없다. 그래서 클래스 템플릿으로 만든다.

//  Accum<char>::accum(&name[0], &name[length])