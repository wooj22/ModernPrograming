// User defined Literal     // C++11

//C++에는 코드 가독성이나 자료형의 표현에 대한 보조 수단으로 각종 '리터럴'들이 존재한다.
//    float   : f
//    long    : L
// 
//    2진수   : 0b (Binary Literal)
//    8진수   : 0
//    16진수  : 0x
//    
//    wchar_t    : L" "
//    unicode    : u8 / u / U  (Unicode  Literals)
//    raw string : R"( )"      (Raw string Literals)

//escape character
//   '\n'
//   '\t'
//   '\000'
//   '\x0000'
//   '\u0000'
//   '\U00000000'

//5 가지 종류의 인스턴스화 된 문자열

//  std::string		    std::basic_string<char>         // char    - 멀티바이트 표현   1 byte
//  std::wstring	    std::basic_string<wchar_t>	    // wchar_t - 유니코드 대응    2 byte이상
//  std::u8string	    std::basic_string<char8_t>	    // char8_t  는 UTF-8  문자열을 보관할 수 있음 (C++20)
//  std::u16string	    std::basic_string<char16_t>	    // char16_t 는 UTF-16 문자열을 보관할 수 있음
//  std::u32string	    std::basic_string<char32_t>	    // char32_t 는 UTF-32 문자열을 보관할 수 있음

// User defined Literal (UDL)
// 
//    C++11 부터는 프로그래머가 직접 정의하는 리터럴을 만들 수 있다. ***

http://en.cppreference.com/w/cpp/language/user_literal

#include <string>
using namespace std;

int main()
{
    auto s1 = "abc"s;   // char_t   //std::string  // "s 표준 라이브러리에 정의된 리터럴      
    auto s2 = L"abc"s;  // wchar_t
    auto s3 = u"abc"s;  // char16_t
    auto s4 = U"abc"s;  // char32_t
}

/*

VS2015에 포함된 다음의 표준 라이브러리들이 UDL을 사용함을 확인할 수 있다.

"" s (문자열, size_t) : std::string(X)
"" h                : std::chrono::hour
"" min              : std::chrono::min
"" s (숫자)         : std::chrono::second
"" ms               : std::chrono::milliseconds(x))
"" us               : std::chrono::microseconds(x))
"" ns               : std::chrono::nanoseconds(x))
"" i (= std::complex(0.0, 3.14))

*/

//-----------------------------------------------------------------------------------
// UDL(User defined Literal) 만들기  ***
// 
//      void operator "" _이름( 매개변수 ) {   }
//      선행밑줄은 꼭 필요, 
//      _ 가 없는 리터럴은 표준 라이브러리 리터럴 뿐.

/*
1. 숫자 타입

UDL을 만들 수 있는 숫자타입은 다음과 같다.

    정수형 : 매개변수가 unsigned long long
    실수형 : 매개변수가 long double

    위 타입 외 다른 숫자타입으로 UDL을 만들려 하면, 다음의 컴파일 에러가 발생한다.
    error C3684 : '연산자 ""_print' : 리터럴 연산자 선언에 잘못된 매개 변수 목록이 있습니다.

    void operator "" _print(unsigned long long num)
    {
        cout << num << endl;
    }
    int main()
    {
        123_print;
    }

2. 문자열 타입

문자열의 경우 일반적으로 '문자 포인터 인자'와 'size_t 길이 인자'를 같이 넘겨 받아야 한다.

    void operator "" _print(const char* str, size_t len)
    {
        cout << str << endl;
    }
    int main()
    {
        "aaa"_print;
    }
*/

#include <iostream>
using namespace std;

// #1 - 문자열 처리 UDL
void operator "" _print(const char* str, size_t len) { cout << str << endl; }

// #2 - 정수 처리 UDL
void operator "" _print(unsigned long long num) { cout << num << endl; }

// #3 - (숫자->문자열) 처리 UDL
void operator "" _print(const char* str) { cout << str << endl; }

int main()
{
    // #1 호출
    "aaa"_print;

    // #2 호출
    12345_print;

    // #3가 아닌 #2이 호출됨
    0x1234_print;
}

//----------------------------------------------------------------------
// #3 - (숫자->문자열) 처리 UDL, 원시 리터럴 연산자
//      매개변수가 size 없이 const char* 면, 앞의 숫자를 원시 문자열로 인식

#include <iostream>
using namespace std;

//원시 리터럴 연산자
string operator "" _print(const char* _str) { string str = _str; return str; }  

//unsigned long long operator "" _print(unsigned long long  _str) { unsigned long long str = _str; return str; }

int main()
{
    auto a =  0x12345_print;    //0x12345 문자열로 취급됨. 
    cout << a;
}


//----------------------------------------------------------------------

#include <iostream>
using namespace std;

long double operator ""_w(long double);
std::string operator ""_w(const char16_t*, size_t);
unsigned    operator ""_w(const char*);

int main()
{
    // 어떤 operator 함수가 사용될까요 ?

    1.2_w;                   // calls operator ""_w(1.2L)
    u"one"_w;                // calls operator ""_w(u"one", 3)
    12_w;                    // calls operator ""_w("12")
    "two"_w;                 // error: no applicable literal operator
}