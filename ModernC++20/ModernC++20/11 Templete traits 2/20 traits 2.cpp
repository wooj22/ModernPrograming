//특질(Trait)과 정책(Policy) 클래스
//		C++ 프로그래밍 장치로 실질적인 템플릿을 설계하는 단계에서 제안된 것으로 
//		이들을 사용하면 추가 파라미터들을 쉽게 관리할 수 있다

#include <iostream> 

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

template <typename T>
inline
typename AccumulationTraits<T>::AccT accum(T const* beg,
    T const* end)
{
    // 반환형이 요소형의 특질이다.
    typedef typename AccumulationTraits<T>::AccT AccT;

    AccT total = AccumulationTraits<T>::zero;       //
    while (beg != end) {
        total += *beg;
        ++beg;
    }
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

// float 에 대해서도 추가햐려 한다.

template<>
class AccumulationTraits<float> {
public:
    typedef double AccT;
    static double const zero = 0.0;  // 에러: 정수 타입 아님 
    //C++ 클래스내 정적 상수 데이터 멤버 중 정수형이나 열거형 값에 대해서만 초기화를 허용합니다.
};

//인라인 함수로 만들자

template<>
class AccumulationTraits<float> {
public:
    typedef double AccT;
    static AccT zero() { return 0; }
};