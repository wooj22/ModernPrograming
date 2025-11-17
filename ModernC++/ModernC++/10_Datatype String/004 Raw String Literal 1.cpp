// User defined Literal     // C++11

//C++에는 코드 가독성이나 자료형의 표현에 대한 보조 수단으로 각종 리터럴들이 존재한다.
//    float   : f
//    2진수   : 0b (Binary Literal)
//    8진수   : 0
//    16진수  : 0x
//    wchar_t : L
//    unicode : u8 / u / U ( Unicode )
//    raw string : R ( Raw string Literals)

#include <iostream>
using namespace std;

int main()
{

    //" ... " : const char 타입의 null-terminated 문자열 생성
    //L" ... " : const wchar_t 타입의 null-terminated 문자열 생성

    cout << sizeof("가나abc") << endl;
    cout << sizeof(L"가나abc") << endl;

    cout << "\u0065" << endl;

    //Unicode string literal
    //u8" ... " : UTF8 인코딩된 const char 타입의 null-terminated 문자열 생성
    //u" ... " : UTF16 인코딩된 const char16_t 타입의 null-terminated 문자열 생성
    //U" ... " : UTF32 인코딩된 const char32_t 타입의 null-terminated 문자열 생성

    auto s1 = u8"I'm a UTF-8 string.";
    auto s1 = u"This is a UTF-16 string.";
    auto s1 = U"This is a UTF-32 string.";

    const char16_t* s16 = u"u00DA";
    const char32_t* s32 = U"u00DA";

    //Raw string literal
    //      R"(c:\a.txt)" 
    //      "c:\\a.txt"

    cout << R"(c:\a.txt)" << endl;
    cout << "c:\\a.txt" << endl;

    // R"( ... )"
    // This is raw string
    auto s1 = R"(This is raw string)";

    // R"delimeter( ... )delimeter"
    // Example: R"(This is raw string)"
    auto s2 = R"DEL(Example: R"(This is raw string)")DEL";

    //delimeter는 
    //  최대 16글자의 길이를 가질 수 있으며, 다음 문자는 포함할 수 없다.
    //  space, \ 


}

//------------------------------------------------------------------------

int main()
{
    /* s1과 s2는 같다 */
    const char* s1 =
        R"(
Hello
World
)";

    const char* s2 = "Hello\nWorld\n";

    /* s3와 s4는 같다*/
    const char* s3 = R"("How old are you?")";
    const char* s4 = "\"How old are you\?\"";

    /* s5와 s6은 같다 */
    const char* s5 =
        R"(<cmd action=CMD_InsertCharacterInfo version=2.0>
    <param>
        <uid v=123 />
        <gameCodeId v=18204 />
        <serverId v=2 />
        <charName v="가갸거겨" />
    </param>
</cmd>)";

    const char* s6 =
        "<cmd action=\"CMD_InsertCharacterInfo\" version=\"2.0\">\n"
        "\t<param>\n"
        "\t\t<uid v=\"123\"/>\n"
        "\t\t<gameCodeId v=\"18204\"/>\n"
        "\t\t<serverId v=\"2\"/>\n"
        "\t\t<charName v=\"가갸거겨\"/>\n"
        "\t</param>\n"
        "</cmd>";
}
