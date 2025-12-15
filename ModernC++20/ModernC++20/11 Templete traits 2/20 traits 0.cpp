//특질(Trait)과 정책(Policy) 클래스
// 
//		C++ 프로그래밍 장치로 실질적인 템플릿을 설계하는 단계에서 제안된 것으로 
//		이들을 사용하면 추가 파라미터들을 쉽게 관리할 수 있다
//      Type의 다양한 속성들에 대해 조사할 수도, 프로퍼티를 변경할 수도 있다.

// 템플릿을 통해 특질과 정책을 구현하는 방법에 대한 코드 예시

#include <iostream> 

template <typename T>
inline T accum(T const* beg, T const* end)
{
    T total = T();  // T()가 실제로 0값을 생성한다고 가정 
    while (beg != end) {  total += *beg;  ++beg; }
    return total;
}

int main()
{
    
    int num[] = { 1,2,3,4,5 };                                      // 정수 배열 5개 생성    
    std::cout << "int " << accum(&num[0], &num[5]) / 5 << '\n';     // 정수 평균 출력 

        
    char name[] = "templates";                                      // 문자열 생성 
    int length = sizeof(name) - 1;

    // 문자의 평균을 출력하려고 시도 
    std::cout << "char " << accum(&name[0], &name[length]) / length << '\n';  
    
    //예상되는 출력은? 이유는?

}

// a는 97이고 z는 122이다. 평균은 97과 122의 사이일거라고 예상. 
// 하지만, char형 연산이라 범위 부족.
//
// accum() 호출되는 각 데이터형 T와 축적된 합을 저장하는 데이터형 사이의 관계를 생성하는 방법.
// 이 데이터형은 T의 특질이라고 할수 있다.
//
// 템플릿으로 표현해 보자.

template<typename T> class AccumulationTraits;

template<> class AccumulationTraits<char> {
public:
    typedef int AccT;           //char 일때 AccT 는 int
};

template <typename T>
inline
typename AccumulationTraits<T>::AccT accum(T const* beg, T const* end)
{
    // 요소 타입의 특질 타입 반환
    typedef typename AccumulationTraits<T>::AccT AccT;

    AccT total = AccT();  // // T()가 실제로 0값을 생성한다고 가정   
    while (beg != end) { total += *beg;  ++beg; }
    return total;
}
