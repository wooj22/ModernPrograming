//C++20 - std::format
https://blog.naver.com/kmc7468/221707892020
https://openmynotepad.tistory.com/98

//C - printf()
//  - 너무 간결, built-in type 들 (int, const char* 등..) 에 대해서만 작동.
// 
//C++에서 자주 사용하는 표준 <iostream>
//  - cin, cout
//  - 그러나 성능저하 잘못된 설계 너무 많은 'operator<<' 때문에 문제
// 
//std::format 은 이를 보완
//  - 편하게 문자열을 포매팅 할 수 있다. ***

#include <iostream>
#include <vector>
#include <format>  //

using namespace std;

int main(int argc, char* argv[])
{
    std::string str = std::format("{} + {} = {}", 16, 14, 30);
    cout << str << '\n';

    // {} 출력하기
    std::string str1 = std::format("{{}}");
    cout << str1 << '\n';

    std::string str2 = std::format("{{,}}");
    cout << str2 << '\n';

    //argument id - 몇 번째 포매팅할 값을 해당 자리에 replace할지 나타낸다.
    std::string str3 = std::format("{0}+{0}={1}", 5, 10);
    cout << str3 << '\n';
}

//<format> 은 세 가지 간단한 원칙을 기반으로 하는 텍스트 서식 지정 라이브러리
//	색인화된 인수 및 타입 지정에 대한 지원을 포함하는 자리 표시자(placeholder) 기반 형식 구문
//	가변 인자 지원을 위한 가변 템플릿을 사용하는 타입 안전 형식
//	사용자 정의 포매터(User-defined formatter)를 통한 사용자 정의 타입 지원

//인자가 std::string_view 또는 std::wstring_view 로 변환될 수 있는 경우에만 가능

#include <format>

int main()
{
    const std::string message{ std::format("{}, {}!", "hello", "world") };

    //std::format("{1}, {0}!", "world", "hello");
    //std::format("he{0}{0}o, {1}!", "l", "world");
}


//"{}" 를 replacement fields 라고 합니다. 형식은 다음과 같습니다.
//  1. { arg-id(optional) }
//  2. { arg-id(optional) : format_spec }
//
//arg-id : 인덱스를 지정하여 args 값을 사용하게 됩니다. 
//      생략하면 인자가 순서대로 사용됩니다.
//      만약 생략한 필드와 인덱싱을 추가한 필드가 둘 다 존재하다면 오류입니다.
//
//format_spec : 해당 인자에 대한 std::formatter specification 의해 정의된 사양입니다.
//      (1) built-in type 과 표준 문자열 타입들은 표준 사양으로 해석됩니다.
//      (2) std::chrono 유형의 경우 크로노 사양으로 해석됩니다.
//      (3) 그 외엔 사용자 정의 formatter specification에 의해 결정됩니다.


// 7가지 C++ 기본 데이터 유형(Primitive Built-in Types)
//      bool, char, int, float, double, void, wchar_t
// 
// 유형 한정자(type modifiers) 중 하나 이상을 사용하여 여러가지 기본 유형을 수정
//      signed, unsigned , short, long



//std::format_to()를 사용하여 
//  결과 문자열을 std::string에 직접 할당하는 대신 iterator를 가져다 쓸 수 있습니다.

#include <iostream>
#include <fstream>
#include <vector>
#include <format>
using namespace std;

int main(int argc, char* argv[])
{
    // format_to
    std::string buffer;
    std::format_to(
        std::back_inserter(buffer), //< OutputIt
        "Hello, {0}::{1}!{2}",      //< fmt
        "std",                      //< 인수 {0}
        "format_to()",              //< 인수 {1}
        "\n",                       //< 인수 {2}
        "extra param(s)...");       //< unused
    std::cout << buffer;

    // file input output
    std::ofstream file{ "format.txt" };
    std::format_to(std::ostream_iterator<char>{file}, "hello, {}!", "world");

    // container
    std::vector<char> buffer{};
    std::format_to(std::back_inserter(buffer), "hello, world");

    for (auto e : buffer) cout << e << " ";
}


//std::format은 사용할 수 있는 모든 종류의 형식을 지원합니다.

#include <chrono>
#include <format>
using namespace std;

int main(int argc, char* argv[])
{
    const std::string str{ std::format("Just {} days left for the release, right?", std::chrono::days(42)) };
    const std::string number{ std::format("Number is {}", 5) };
}


//포매터는 값의 문자열 표현을 반환할 뿐만 아니라 Formatting specifiers 를 통해 출력을 정의할 수 있습니다.

1개			        format("{}", 1)	//1
2개			        format("{} {}", 1, 2)	//1 2
3개			        format("{} {} {}", 1, 2, 3)	//1 2 3
순서 지정	        format("{2} {1} {0}", 1, 2, 3)	//3 2 1
문자(c는 생략 가능)	format("{:c}", 'C')	//C
문자열(s는 생략 가능)	format("{:s}", "C++")	//C++
bool		        format("{}", true)	//true
bool		        format("{}", false)	//false
정수(10진수, d생략 가능)	format("{:d}", 42)	//42
정수(8진수)	        format("{:o}", 042)	//42
정수(16진수)	        format("{:x}", 0xab)	//ab
정수(16진수) 대문자	format("{:X}", 0xab)	//AB
정수(16진수) 0x 붙음	format("{:#x}", 0xab)	//0xab
정수(16진수) 0X 붙음	format("{:#X}", 0xab)	//0XAB
정수(2진수)	        format("{:b}", 0b10101010)	//10101010
정수(2진수) 0b 붙음	format("{:#b}", 0b10101010)	//0b10101010
정수(2진수) 0B 붙음	format("{:#B}", 0b10101010)	//0B10101010
정수(정수에 + )	    format("{:+d}", 42) //+ 42
부동소수점수	        format("{:f}", 123.456789)	//123.456789
정도 지정	        format("{:6.3f}", 123.456789)	//123.457
지수 표기(e)	        format("{:e}", 123.456789)	//1.234568e+02
지수 표기(E)	        format("{:E}", 123.456789)	//1.234568E+02
최적의 표기를 자동 판정(g는 생략 가능)	format("{:g}", 123.456789)	//123.457
왼쪽 정렬	        format("{:<12}", "left")	//left
오른쪽 정렬	        format("{:>12}", "right")	//right
중앙 정렬	        format("{:^12}", "center")	//center
묻힐 문자 지정	    format("{:!^12}", "hello")	//!!!hello!!!!

// 문자열을 3자리 수까지만 저장합니다.
const std::string pi = std::format("{:.3f}", 3.141592654);

