#include <iostream>

// noexcept 로 선언해야하는 경우 
//
//      noexcept는 이동 연산들과 swap, 메모리 해제 함수들, 그리고 소멸자들에 특히나 유용하다. ***


//이동 연산
    //  C++11의 이동 연산을 통해 최적화를 하면 push_back은 강력한 예외 안전성을 보장할 수 없게 된다.
    //  이동 연산이 예외를 방출하지 않음이 확실한 경우에는 복사를 이동으로 대체해도 안전하다.    
    //  std::vector::push_back 같은 함수는 std::move_if_noexcept를 호출
    //  즉, 이동 연산의 이점을 얻으려면 noexcept 를 지원하라. ***
 

//swap 함수들
    //  noexcept가 특히나 바람직한 또 다른 예로 swap 함수들. noexcept를 통해서 최적화할 가치가 크다
    //  표준 라이브러리에 있는 swap들의 noexcept 여부는 
    //  사용자 정의 swap들의 noexcept 여부에 어느 정도 의존한다.

    /*
        template <class T, size_t N>
        void swap(T(&a)[N], T(&b)[N]) noexcept(noexcept(swap(*a, *b)));

        template <class T1, class T2>
        struct pair {
            void swap(pair& p) noexcept(noexcept(swap(first, p.first)) &&  noexcept(swap(second, p.second)));
        };
    */

//메모리 해제 함수들
    //  noexcept로 선언하는 것이 아주 중요한 일부 함수들은 기본적으로 noexcept로 선언된다. 
    //  기본적으로 모든 메모리 해제 함수(operator delete와 operator delete[] 등)와 
    //  모든 소멸자는 암묵적으로 noexcept이다. ***

int main()
{
	return 0;
}

// 주의) 대부분의 함수는 noexcept가 아니라 예외에 중립적이다.
//
//  noexcept는 함수의 인터페이스의 일부이다.
//  따라서 함수의 구현이 예외를 방출하지 않는다는 성질을 오랫동안 유지할 경우에만 
//  함수를 noexcept로 선언해야 한다. ***

//  만일 함수를 noexcept로 선언하고는 나중에 마음을 바꾼다면, 딱히 흡족한 수습 방안이 없다.
//  함수의 인터페이스가 변경(noexcept를 제거)되면 클라이언트 코드가 깨질 위험이 생긴다.
// 
//  넓은 계약(wide contract)들을 가진 함수와 좁은 계약(narrow contract)들을 가진 함수를 구분하는 사람들은 
//  넓은 계약을 가진 함수(전제조건 없는 경우)들에 대해서만 noexcept를 사용하는 경향이 있다.

//% 넓은 계약 vs 좁은계약
//  std::vector<int> s;  s[0]       //좁은 (index 범위라는 제약)
//  std::vector<int> s;  s.at(0);   //넓음 (예외 처리)
//  std::vector<int> s;  s.size()   //광범위한 계약 (조건없음)


//C++11에서도 함수 구현과 예외 지정 사이의 비일관성을 파악하는 데 컴파일러가 별 도움을 주지 않는다. ***
/*
    void setup(void);            // 다른 어딘가에 정의된 함수들
    void cleanup(void);

    void doWork(void) noexcept
    {
        setup();                // 필요한 준비 작업을 수행 
        cleanup();              // 정리 작업을 수행            
    }

    //setup(),cleanup() 은 예외를 던질까 ???
    //noexcept 보장이 없는 코드에 의존하는 경우가 있으므로, C++은 이런 코드를 허용한다.
*/



