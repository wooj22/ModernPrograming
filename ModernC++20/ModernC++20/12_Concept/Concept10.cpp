//concepts + thread_local + template 혼합 설계 문제

//문제. 타입이 산술 타입(int, float, double)일 때만 
//	thread - local 카운터를 제공하는 TypeSafeCounter를 구현하라.
// 
//요구 조건 :
//	TypeSafeCounter<T>::next()는 산술 타입에만 사용 가능해야 함
//	산술 타입이 아닌 경우, 컴파일 타임에 명확히 에러 발생
//	각 타입별로 thread_local 카운터 유지
//	concepts와 inline static thread_local 조합 사용

#include <concepts>
#include <iostream>
#include <thread>

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;   //산술 타입(arithmetic type)

template<Arithmetic T>
class TypeSafeCounter {
public:
    static T next() {
        return ++counter;
    }

private:
    inline static thread_local T counter = 0;
};

int main() {
    std::cout << TypeSafeCounter<int>::next() << "\n";     // OK
    std::cout << TypeSafeCounter<int>::next() << "\n";     // OK
    std::cout << TypeSafeCounter<double>::next() << "\n";  // OK
    // TypeSafeCounter<std::string>::next(); // 컴파일 타임 오류
}


//산술 타입(arithmetic type)
/*
정수 타입
    bool
    char, signed char, unsigned char
    short, int, long, long long
    각종 unsigned
부동소수점 타입
    float
    double
    long double
*/

//is_integral_v	            정수 타입만
//is_floating_point_v	    실수 타입만
//is_arithmetic_v	        정수 + 실수
