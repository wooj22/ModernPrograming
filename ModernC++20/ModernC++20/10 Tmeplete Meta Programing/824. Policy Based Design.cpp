//C++ 템플릿 디자인 //Policy Based Design
// 
//  클래스가 사용하는 정책을 '템플릿 인자'를 통해서 교체할 수 있게 만드는 디자인
//  성능 저하 없이 정책을 교체 할 수 있음
// 
//  대부분의 정책은 담은 "단위 전략 클래스"는 지켜야 하는 규칙이 있음
//      규칙을 표현하는 코딩 방식은 없음(인터페이스 사용시 가상 함수이므로 약간의 오버헤드 발생), C++20 concept 문법
//      템플릿 기반 라이브러리, 특히 STL에서 널리 사용되는 디자인 기법


//예시) 싱글 쓰레드 or 멀티 쓰레드 선택하기
//  우리가 만들 동기화 정책클래스는 "lock/unlock" 함수가 필요함

#include <iostream>
using namespace std;

// 1개의 클래스로 정책 템플릿 인자를 통해서 다르게 구현 할 수 있도록 디자인
template<typename T, typename ThreadModel> 
class List
{
    ThreadModel tm;             //정책 //싱글 쓰레드 or 멀티 쓰레드 선택하기 위한 인자 추가.
public:
    void push_front(const T& a)
    {
        tm.lock();
        // 구현부 코드
        tm.unlock();
    }
};

// 싱글 쓰레드 기반 환경용
class NoLock
{
public:
    inline void lock() {};
    inline void unlock() {}
};

// 멀티 쓰레드 기반 환경용
class MutexLock
{
public:
    inline void lock() {};
    inline void unlock() {}
};


// 환경에 따라서 클래스 생성 시 전략을 선택 할 수 있음

// 싱글 쓰레드용 생성
//List<int, NoLock> s;
 
// 멀티 쓰레드용 생성
List<int, MutexLock> s;

int main()
{
    s.push_front(10);
}

//https://www.devoops.kr/153

