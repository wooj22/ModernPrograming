//사용자 정의 리터럴
//      주로 편의상 또는 컴파일 시간 형식 추론을 위해 사용

#include <iostream>
#include <complex>
#include <chrono>
using namespace std;

//std::string str = "hello"s + "World"s;                  // 표준 라이브러리인 <string> 의 리터럴
//complex<double> num = (2.0 + 3.01i) * (5.0 + 4.3i);     // 표준 라이브러리인 <complex> 의 리터럴
//auto duration = 15ms + 42h;                             // 표준 라이브러리인 <chrono> 의 리터럴
// 
//Distance d = 36.0_mi + 42.0_km;                         // Custom UDL (see below)

//사용자 정의 리터럴을 통해 호출자에게 명시적으로 입력을 지정하도록 장려하는 방법

struct Distance
{
private:
    explicit Distance(long double val) : kilometers(val) { }

    friend Distance operator"" _km(long double val);        //사용자 정의 리터럴
    friend Distance operator"" _mi(long double val);        //사용자 정의 리터럴

    long double kilometers{ 0 };
public:
    long double get_kilometers() const { return kilometers; }

    Distance operator+(const Distance& other) {
        return Distance(get_kilometers() + other.get_kilometers());
    }
};

Distance operator"" _km(long double  val) {
    return Distance(val);
}

Distance operator"" _mi(long double val) {
    return Distance(val * 1.6);
}

int main(int argc, char* argv[])
{
    // 오퍼레이터에 사용되려면 . 을 꼭 사용하셔야 합니다 (double 형이므로)

    Distance d{ 402.0_km };         // kilometer 와 매칭됩니다
    cout << "Kilometers in d: " << d.get_kilometers() << endl; // 402

    Distance d2{ 402.0_mi };        // mile 과 매칭됩니다.
    cout << "Kilometers in d2: " << d2.get_kilometers() << endl;  //643.2

    // 다른 타입에 대해서 +연산을 할 수도 있습니다. ***
    Distance d3 = 36.0_mi + 42.0_km;
    cout << "d3 value = " << d3.get_kilometers() << endl; // 99.6


    Distance d4(90.0);      // error, 맞는 사용자 리터럴이 없습니다. 
}


/*
//사용자 리터럴

ReturnType operator "" _a(unsigned long long int);   // int 형 사용자 리터럴
ReturnType operator "" _b(long double);              // double 형 사용자 리터럴

ReturnType operator "" _c(char);                     // char 형 사용자 리터럴
ReturnType operator "" _d(wchar_t);                  // char 형 사용자 리터럴
ReturnType operator "" _e(char16_t);                 // char 형 사용자 리터럴
ReturnType operator "" _f(char32_t);                 // char 형 사용자 리터럴

ReturnType operator "" _g(const     char*, size_t);  // 문자열(char* 또는 string) 형 사용자 리터럴
ReturnType operator "" _h(const  wchar_t*, size_t);  // 문자열(char* 또는 string) 형 사용자 리터럴
ReturnType operator "" _i(const char16_t*, size_t);  // 문자열(char* 또는 string) 형 사용자 리터럴
ReturnType operator "" _g(const char32_t*, size_t);  // 문자열(char* 또는 string) 형 사용자 리터럴

ReturnType operator "" _r(const char*);              // 원시 리터럴 연산자 ***
template<char...> ReturnType operator "" _t();       // 템플릿 리터럴 연산자

https://learn.microsoft.com/ko-kr/cpp/cpp/user-defined-literals-cpp?view=msvc-170

//선행밑줄은 꼭 필요, _가 없는 리터럴은 표준 라이브러리 리터럴 뿐.

//연산자 내에서 추가작업을 할 수도 있고, constexpr 로 선언할 수도 있습니다.

//사용자 정의 여부에 관계없이 모든 리터럴은 
//본질적으로 101, 54.7, "hello" 또는 true와 같은 영숫자 문자의 시퀀스입니다.
//
//컴파일러가 리터럴 값으로 할당 한 모든 형식을 입력으로 허용하는 사용자 정의 리터럴을 
//      비공식적으로 가공된 리터럴이라고 합니다.
//_r 및 _t를 제외한 위의 모든 연산자는 가공된 리터럴.
//_r 및 _t는 원시 리터럴을 정의하는 데 사용할 수 있습니다.

//원시 리터럴
//원시 사용자 정의 리터럴에서 정의하는 연산자는 리터럴을 char 값 시퀀스로 허용합니다. 
//해당 시퀀스를 숫자 또는 문자열 또는 다른 형식으로 해석하는 것은 사용자의 달려 있습니다.

*/

/*
//예제) 복소수 정의하기

#include <iostream>
using namespace std;

class MyComplex {
public:
    long double getS() { return s; }
    long double getH() { return h; }
private:
    
    friend MyComplex operator"" _i(long double val);
    friend MyComplex operator+(long double lhs, const MyComplex& rhs);

    MyComplex operator+(const MyComplex& rhs) const {
        return MyComplex(s + rhs.s, h + rhs.h);
    }

    explicit MyComplex(long double _s) : s(_s) { }
    explicit MyComplex(long double _s, long double _h) : s(_s), h(_h) { }

private:
    long double s;
    long double h;
};

MyComplex operator+(long double lhs, const MyComplex& rhs) {
    return MyComplex(lhs, rhs.h);
}
MyComplex operator"" _i(long double val) {
    return MyComplex(0, val);
}

int main() 
{
    MyComplex a = { 10.0 + 10.0_i };

    cout << a.getS() << " + " << a.getH() << 'i' << endl;

    // 10 + 10i 가 출력 됩니다!
}

*/