// basic_string<T>
// 
//		std::string 은 basic_string 이라는 클래스 템플릿의 인스턴스화 버전
//      using string = basic_string<char, char_traits<char>, allocator<char>>;
// 
//      <T> 타입의 객체들을 메모리에 연속적으로 저장하고, 여러가지 문자열 연산들을 지원해주는 클래스 
//      <T> 자리에 char 이 오게 된다면, 우리가 생각하는 std::string

//5 가지 종류의 인스턴스화 된 문자열
//std::string		std::basic_string<char>
//std::wstring	    std::basic_string<wchar_t>	// wchar_t 의 크기는 시스템 마다 다름. 윈도우에서는 2 바이트, 유닉스 시스템에서는 4 바이트
//std::u8string	    std::basic_string<char8_t>	// char8_t 는 1 바이트;  UTF - 8 문자열을 보관할 수 있음 (C++ 20 에 새로 추가)
//std::u16string	std::basic_string<char16_t>	// char16_t 는 2 바이트; UTF - 16 문자열을 보관할 수 있음
//std::u32string	std::basic_string<char32_t>	// char32_t 는 4 바이트; UTF - 32 문자열을 보관할 수 있음


//char_traits<T>
// 
//      Traits 는 주어진 CharT 문자들에 대해 기본적인 '문자열 연산'들을 정의해놓은 클래스 
//      문자열들을 어떻게 보관하는지 에 대한 로직과 문자열들을 어떻게 연산하는지 에 대한 로직을 분리
//      전자는 basic_string 에서 해결하고, 후자는 Traits 에서 담당

//숫자들이 다른 문자들 보다 우선순위가 낮은 문자열 만들기

#include <cctype>
#include <iostream>
#include <string>

// char_traits 의 모든 함수들은 static 함수 입니다.
struct my_char_traits : public std::char_traits<char> {
    static int get_real_rank(char c) {        
        if (isdigit(c)) {
            return c + 256;         // 숫자면 순위를 엄청 떨어트린다.
        }
        return c;
    }

    static bool lt(char c1, char c2) {
        return get_real_rank(c1) < get_real_rank(c2);
    }

    static int compare(const char* s1, const char* s2, size_t n) {
        while (n-- != 0) {
            if (get_real_rank(*s1) < get_real_rank(*s2)) { return -1; }
            if (get_real_rank(*s1) > get_real_rank(*s2)) { return 1; }
            ++s1;
            ++s2;
        }
        return 0;
    }
};

int main() 
{
    std::string s1 = "1a";
    std::string s2 = "a1";
    std::cout << "일반 문자열 : " << std::boolalpha << (s1 < s2) << std::endl;

    std::basic_string<char, my_char_traits> my_s1 = "1a";
    std::basic_string<char, my_char_traits> my_s2 = "a1";
    std::cout << "숫자의 우선순위가 더 낮은 문자열 : " << std::boolalpha
        << (my_s1 < my_s2) << std::endl;
}


//짧은 문자열 최적화 (SSO)
//      basic_string 이 저장하는 문자열의 길이는 천차 만별. 
//      짧은 길이 문자열의 경우 따로 문자 데이터를 위한 메모리를 할당하는 대신에 그냥 객체 자체에 저장    
//      짧은 문자열 최적화(SSO - short string optimization)

// Release 로 실행해서 메모리 할당 여부를 확인해보세요.

#include <iostream>
#include <string>

// 이와 같이 new 를 전역 함수로 정의하면 모든 new 연산자를 오버로딩 해버린다.
// (어떤 클래스의 멤버 함수로 정의하면 해당 클래스의 new 만 오버로딩됨)
void* operator new(std::size_t count) {
    std::cout << count << " bytes 할당 " << std::endl;
    return malloc(count);
}

int main() {
    std::cout << "s1 생성 --- " << std::endl;
    std::string s1 = "this is a pretty long sentence!!!";
    std::cout << "s1 크기 : " << sizeof(s1) << std::endl;

    std::cout << "s2 생성 --- " << std::endl;
    std::string s2 = "short sentence";      //짧은 문자열인 s2 의 경우에는 메모리 할당이 발생하지 않았습니다.
    std::cout << "s2 크기 : " << sizeof(s2) << std::endl;     
}


// 리터럴 연산자(literal operator) 
// 
//  사용자 정의 리터럴(User-defined literal, UDL) 을 만드는 기능
//  숫자나 문자열 뒤에 **_suffix (접미사)**를 붙여 새로운 타입이나 동작을 정의하는 문법
//  
//  std::string operator"" s(const char* str, std::size_t len);

#include <iostream>
#include <string>
using namespace std::literals;

int main() {

    auto str = "hello";

    auto s1 = "hello"s;     // ""s

    std::cout << "s1 길이 : " << s1.size() << std::endl;

    std::string str = "hello";     // char[]
    std::wstring wstr = L"hello";  // wchar_t[]

}

//Raw String Literal (원시 문자열 리터럴)
// 
//      R"()" 안에 오는 문자들은 모두 문자 그대로 char 배열 안에 들어가게 됩니다.

#include <iostream>
#include <string>

int main() 
{
    std::string str = R"(asdfasdf
이 안에는 어떤 것들이 와도
// 이런것도 되고
#define hasldfjalskdfj
\n\n <--- Escape 안해도 됨
)";

    std::cout << str;
}

//C++ 에서 한글 다루기
//전세계 모든 문자들을 컴퓨터로 표현할 수 있도록 설계된 표준이 바로 '유니코드(Unicode)'

//인코딩(Encoding) 방식
//  UTF-8  : 문자를 최소 1 부터 최대 4 바이트로 표현한다. (즉 문자마다 길이가 다르다!)
//  UTF-16 : 문자를 2 혹은 4 바이트로 표현한다.
//  UTF-32 : 문자를 4 바이트로 표현한다.

//웹 상에서 많이 사용되는 UTF-8 인코딩 방식

#include <iostream>
#include <string>

int main() {
        
    std::u8string str = u8"UTF-8 문자열 입니다";
    std::cout << str.size() << std::endl;

    std::u32string u32_str = U"UTF-32 문자열 입니다";
    std::cout << u32_str.size() << std::endl;
}

//문제는 string 단에서 각각의 문자를 구분하지 못하기 때문에 불편함이 이만 저만이 아니라는 점
#include <iostream>
#include <string>

int main() {
    //                   1 234567890 1 2 34 5 6
    std::u8string str = u8"이건 UTF-8 문자열 입니다";
    size_t i = 0;
    size_t len = 0;

    while (i < str.size()) {
        int char_size = 0;

        if ((str[i] & 0b11111000) == 0b11110000) { char_size = 4; }
        else if ((str[i] & 0b11110000) == 0b11100000) { char_size = 3; }
        else if ((str[i] & 0b11100000) == 0b11000000) { char_size = 2; }
        else if ((str[i] & 0b10000000) == 0b00000000) { char_size = 1; }
        else { std::cout << "이상한 문자 발견!" << std::endl;            char_size = 1; }

        std::cout << str.substr(i, char_size) << std::endl;  //처리못함

        i += char_size;
        len++;
    }
    std::cout << "문자열의 실제 길이 : " << len << std::endl;
}

//Windows에서 UTF-8 출력
#include <iostream>
#include <string>
#include <Windows.h> // Windows 전용

int main() {
    // UTF-8 코드 페이지 설정
    SetConsoleOutputCP(CP_UTF8);

    std::u8string u8str = u8"안녕하세요, UTF-8!";
    std::cout << std::string(u8str.begin(), u8str.end()) << std::endl;

    return 0;
}

//일반적인 문자들만 수록되어 있는 텍스트를 다루신다면 u16string 을 사용하는 것 만큼 좋은 것이 없습니다.
//단. 이모지는 4바이트 사용  (window키 + .)

//한글의 초성만 분리해내는 코드

#include <iostream>
#include <string>

int main() {
    std::u16string u16_str = u"안녕하세요 오신 것을 환영합니다";
    std::string jaum[] = { "ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ",
                          "ㅂ", "ㅃ", "ㅅ", "ㅆ", "ㅇ", "ㅈ", "ㅉ",
                          "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ" };

    for (char16_t c : u16_str) {
        // 유니코드 상에서 한글의 범위
        if (!(0xAC00 <= c && c <= 0xD7A3)) {
            continue;
        }
        // 한글은 AC00 부터 시작해서 한 초성당 총 0x24C 개 씩 있다.
        int offset = c - 0xAC00;
        int jaum_offset = offset / 0x24C;
        std::cout << jaum[jaum_offset];
    }
}

//UTF-16 역시 때론 4 바이트로 문자를 인코딩
//i 번째 문자를 str[i] 와 같이 접근할 수 있는 것은 아닙니다. 

#include <iostream>
#include <string>

int main() {
    std::u16string u16_str = u"🍑🍒";
    std::cout << u16_str.size() << std::endl;
}


//C++ 17 에서 문자열을 편리하게 처리하기 위한 string_view 클래스 등장
// 
//      소유하지 않고 읽기만 한다!
//      const cha*, string 모두 받아서 처리가능

#include <iostream>
#include <string>

void* operator new(std::size_t count) {
    std::cout << count << " bytes 할당 " << std::endl;
    return malloc(count);
}

bool contains_very(std::string_view str)            //string_view
{
    return str.find("very") != std::string_view::npos; // 문자열에 "very" 라는 단어가 있으면 true 를 리턴함
}

int main() {
    // string_view 생성 시에는 메모리 할당이 필요 없다.
    std::cout << std::boolalpha << contains_very("c++ string is very easy to use")
        << std::endl;

    std::cout << contains_very("c++ string is not easy to use") << std::endl;

    std::string str = "some long long long long long string";
    std::cout << "--------------------" << std::endl;
    std::cout << contains_very(str) << std::endl;
}

/*

C++11	사용자 정의 리터럴의 기본 형태 도입(operator"" _suffix)
        정수·실수·문자·문자열 리터럴에 접미사 정의 가능
C++14	constexpr 리터럴 연산자 지원 → 컴파일 타임 평가 가능
        리터럴 연산자를 템플릿화할 수 있음(ex. template<char...> 형태)
C++17	constexpr 개선 및 표준 리터럴(예: std::string_view용 UDL) 추가
C++20	consteval 지원 → 반드시 컴파일 타임에 평가되는 리터럴 가능

*/