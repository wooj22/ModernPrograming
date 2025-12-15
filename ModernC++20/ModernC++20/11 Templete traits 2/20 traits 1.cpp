//특질(Trait)과 정책(Policy) 클래스
//		C++ 프로그래밍 장치로 실질적인 템플릿을 설계하는 단계에서 제안된 것으로 
//		이들을 사용하면 추가 파라미터들을 쉽게 관리할 수 있다

#include <iostream> 

//주요 데이터형에 대해 부가적인 데이터형 정보를 제공하는 특질

template<typename T> class AccumulationTraits;

template<> class AccumulationTraits<int> { 
public:
    typedef long AccT;
};

template<> class AccumulationTraits<char> {
public:
    typedef int AccT;
};

template <typename T>
inline
typename AccumulationTraits<T>::AccT accum(T const* beg, T const* end)
{
    // 요소 타입의 특질 타입 반환
    typedef typename AccumulationTraits<T>::AccT AccT;

    AccT total = AccT();    // T()가 실제로 0값을 생성한다고 가정   
    while (beg != end) { total += *beg;  ++beg; }
    return total;
}

int main()
{

    // 정수 배열 5개 생성
    int num[] = { 1,2,3,4,5 };
    // 정수 평균 출력 
    std::cout << "int " << accum(&num[0], &num[5]) / 5 << '\n';

    // 문자열 생성 
    char name[] = "templates";
    int length = sizeof(name) - 1;
    // 문자의 평균을 출력하려고 시도 
    std::cout << "char " << accum(&name[0], &name[length]) / length << '\n';  
    
}

//그런데
//Acct() 합 계산 루프를 시작하기에 좋은 값을 반환할거란 보장은 없으며 
//심지어 AccT형에 기본 생성자가 없을 수도 있다.

//AccumulationTrait에 값 특질을 추가한다.


template<typename T> class AccumulationTraits;

template<> class AccumulationTraits<int> {
public:
    typedef long AccT;
    static AccT const zero = 0;     //
};

template<> class AccumulationTraits<char> {
public:
    typedef int AccT;
    static AccT const zero = 0;     //
};
