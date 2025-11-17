//https://learn.microsoft.com/ko-kr/cpp/cpp/string-and-character-literals-cpp?view=msvc-170

//String and character literals (C++)

//#include <iostream>
//using namespace std;

#include <string>
using namespace std::string_literals; // enables s-suffix for std::string literals

int main()
{
    // Character literals
    auto c0 = 'A';                  // char
    auto c1 = u8'A';                // char8_t  //C++20
    auto c2 = L'A';                 // wchar_t
    auto c3 = u'A';                 // char16_t
    auto c4 = U'A';                 // char32_t

    // Multicharacter literals
    auto m0 = 'abcd';               // int, value 0x61626364

    // String literals
    auto s0 = "hello";              // const char*
    auto s1 = u8"hello";            // const char* before C++20, encoded as UTF-8, (const char8_t* in C++20)
    auto s2 = L"hello";             // const wchar_t*
    auto s3 = u"hello";             // const char16_t*, encoded as UTF-16
    auto s4 = U"hello";             // const char32_t*, encoded as UTF-32

    // Raw string literals containing unescaped \ and "
    auto R0 = R"("Hello \ world")";     // const char*
    auto R1 = u8R"("Hello \ world")";   // const char* before C++20, encoded as UTF-8, (const char8_t* in C++20)
    auto R2 = LR"("Hello \ world")";    // const wchar_t*
    auto R3 = uR"("Hello \ world")";    // const char16_t*, encoded as UTF-16
    auto R4 = UR"("Hello \ world")";    // const char32_t*, encoded as UTF-32

    // Combining string literals with standard s-suffix
    auto S0 = "hello"s;                 // std::string
    auto S1 = u8"hello"s;               // std::string before C++20, std::u8string in C++20
    auto S2 = L"hello"s;                // std::wstring
    auto S3 = u"hello"s;                // std::u16string
    auto S4 = U"hello"s;                // std::u32string

    // Combining raw string literals with standard s-suffix
    auto S5 = R"("Hello \ world")"s;    // std::string from a raw const char*
    auto S6 = u8R"("Hello \ world")"s;  // std::string from a raw const char* before C++20, encoded as UTF-8, // std::u8string in C++20
    auto S7 = LR"("Hello \ world")"s;   // std::wstring from a raw const wchar_t*
    auto S8 = uR"("Hello \ world")"s;   // std::u16string from a raw const char16_t*, encoded as UTF-16
    auto S9 = UR"("Hello \ world")"s;   // std::u32string from a raw const char32_t*, encoded as UTF-32
}

int main()
{
    //문자 리터럴 - 5 가지
    //    char 형식의 일반 문자 리터럴                            (예:) 'a'
    //    wchar_t 형식의 와이드 문자 리터럴                       (예:) L'a'   
    //    char 형식의 의 UTF-8 문자 리터럴(char8_t C++20)입니다.  (예:) u8'a'    // 
    //    char16_t 형식의 UTF-16 문자 리터럴                      (예:) u'a'
    //    char32_t 형식의 UTF-32 문자 리터럴                      (예:) U'a'

    //Encoding
    //    문자 리터럴은 접두사를 기반으로 다르게 인코딩됩니다.
    //    접두사 없는 문자 리터럴은 일반 문자 리터럴
    //    접두사로 L 시작하는 문자 리터럴은 와이드 문자 리터럴
    //    접두사로 u8 시작하는 문자 리터럴은 UTF - 8 문자 리터럴
    //    접두사로 u 시작하는 문자 리터럴은 UTF - 16 문자 리터럴
    //    접두사로 u 시작하는 문자 리터럴은 UTF - 16 문자 리터럴

    //유니버설 문자 이름
    char u1 = 'A';          // 'A'
    char u2 = '\101';       // octal, 'A'
    char u3 = '\x41';       // hexadecimal, 'A'
    char u4 = '\u0041';     // \u UCN 'A'
    char u5 = '\U00000041'; // \U UCN 'A'


    //좁은 문자열 리터럴  
    const char* narrow = "abcd";    
    const char* escaped = "yes\\no";    // represents the string: yes\no


    //UTF-8로 인코딩된 문자열

    // Before C++20
    const char* str1 = u8"Hello World";
    const char* str2 = u8"\U0001F607 is O:-)";
    // C++20 and later
    const char8_t* u8str1 = u8"Hello World";
    const char8_t* u8str2 = u8"\U0001F607 is O:-)";


    //와이드 문자열 리터럴

    const wchar_t* wide = L"zyxw";
    const wchar_t* newline = L"hello\ngoodbye";


    //char16_t 및 char32_t(C++11)
      
    auto s3 = u"hello"; // const char16_t*
    auto s4 = U"hello"; // const char32_t*


    //원시 문자열 리터럴 (C++11)

    // represents the string: An unescaped \ character
    const char* raw_narrow = R"(An unescaped \ character)";
    const wchar_t* raw_wide = LR"(An unescaped \ character)";
    const char* raw_utf8a = u8R"(An unescaped \ character)"; // Before C++20
    const char8_t* raw_utf8b = u8R"(An unescaped \ character)"; // C++20
    const char16_t* raw_utf16 = uR"(An unescaped \ character)";
    const char32_t* raw_utf32 = UR"(An unescaped \ character)";

    const char* bad_parens = R"()")";           // error C2059
    const char* good_parens = R"xyz()")xyz";

    //줄 바꿈(이스케이프된 문자가 아님)이 포함된 원시 문자열 리터럴을 생성
    const wchar_t* newline = LR"(hello
goodbye)";


    //std::string 리터럴 (C++14)

    //#include <string>
    //using namespace std::string_literals;
    string str{ "hello"s };
    wstring str3{ L"hello"s };
    string str2{ u8"Hello World" };     // Before C++20
    u8string u8str2{ u8"Hello World" }; // C++20
    u16string str4{ u"hello"s };
    u32string str5{ U"hello"s };

    //s 접미사는 원시 문자열 리터럴에서도 사용
    u32string str6{ UR"(She said "hello.")"s };


    //문자열 리터럴의 크기

    //ANSI char* 문자열 및 기타 단일 바이트 인코딩( UTF-8 아님)의 경우 
    //    문자열 리터럴의 크기(바이트)는 종료되는 null 문자에 1을 더한 문자 수입니다.
    // 
    //다른 모든 문자열 형식의 경우 크기는 문자 수와 엄격하게 관련되지 않습니다.

    const wchar_t* str = L"Hello!";
    const size_t byteSize = (wcslen(str) + 1) * sizeof(wchar_t);


    //인접 문자열 리터럴 연결

    char str1[] = "12" "34";     
    
    char str2[] = "1234";

    char str3[] = "12\
34";

    //ASCII 5 문자와 f, i, v 및 e 문자가 포함된 문자열 리터럴을 만들려고 합니다.

    "\x05five"     // wow

    "\005five"     // Use octal literal.
    "\x05" "five"  // Use string splicing.

    auto x1 = "hello" " " " world"; // OK
    auto x2 = U"hello" " " L"world"; // C2308: disagree on prefix
    auto x3 = u8"hello" " "s u8"world"z; // C3688, disagree on suffixes


    //유니버설 문자 이름(UCN)을 가진 문자열 리터럴
    //      문자를 직접 입력하기 어려운 경우, 유니코드 코드 포인트를 직접 표현하는 방법
    // 
    //      EX) 이모지(Emoji)는 유니코드 문자 체계의 일부로, SMP 영역 (U+1F000 ~ U+1FAFF 등)
    //      Windows 키 + 마침표(.) 또는 Windows 키 + 세미콜론(;)

    // ASCII smiling face
    const char* s1 = ":-)";

    // UTF-16 (on Windows) encoded WINKING FACE (U+1F609)
    const wchar_t* s2 = L"😉 = \U0001F609 is ;-)";

    // UTF-8  encoded SMILING FACE WITH HALO (U+1F607)
    const char* s3a = u8"😇 = \U0001F607 is O:-)"; // Before C++20
    const char8_t* s3b = u8"😇 = \U0001F607 is O:-)"; // C++20

    // UTF-16 encoded SMILING FACE WITH OPEN MOUTH (U+1F603)
    const char16_t* s4 = u"😃 = \U0001F603 is :-D";

    // UTF-32 encoded SMILING FACE WITH SUNGLASSES (U+1F60E)
    const char32_t* s5 = U"😎 = \U0001F60E is B-)";

}

//이스케이프 시퀀스
// 
//  8진수	\ooo      //8진수가 아닌 첫 번째 문자에서 종료
//  16진수	\xhhh     //x가 뒤에 하나 이상의 16진수 숫자 시퀀스입니다. 앞에 오는 0은 무시

#include <iostream>
using namespace std;

int main() {
    char newline = '\n';
    char tab = '\t';
    char backspace = '\b';
    char backslash = '\\';
    char nullChar = '\0';

    cout << "Newline character: " << newline << "ending" << endl;
    cout << "Tab character: " << tab << "ending" << endl;
    cout << "Backspace character: " << backspace << "ending" << endl;
    cout << "Backslash character: " << backslash << "ending" << endl;
    cout << "Null character: " << nullChar << "ending" << endl;
}