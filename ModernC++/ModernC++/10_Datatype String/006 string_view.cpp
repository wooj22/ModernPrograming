//string_view 
//		c++ 17에서 추가
//		다양한 문자열 타입을 전달 받을 수 있는 안전하면서 효과적인 방법을 제공
// 
//		내부적으로 문자열에 대한 'pointer'와 '길이'만 가지며, '임시객체를 생성하지 않고' 문자열을 사용 할 수 있다.
//      string_view는 내부적으로 'null 종료 문자'를 가지지 않는다.
//      string_view 타입들을 내부적으로 std::basic_string_view<T>로 구현.

//문자열을 다루는 함수를 만든다고 해보면 매개변수를 
//      const char* 혹은 const std::string& 으로 만드는 것이 보통이다.
//
//두가지 장점을 모두 가져가기 위해 추가된 것이 std::string_view 이다.
//      std::string_view는 내부에 포인터와 길이정보를 가진다.
//      그래서 문자열 포인터를 바로 받을 수 있으면서, std::string 의 기능을 제공해준다. ***
//      포인터와 길이 정보만 가지고 있기 때문에 보통 레퍼런스가 아닌, 값을 전달하는 방식으로 구현한다.

//string_view 객체생성
// 
//  다양한 문자열 타입을 전달 받을 수 있는 안전하면서 효과적인 방법을 제공
//  문자열 데이터를 복사하지 않고 참조하여 성능을 높이는 데 유용합니다. (경량 문자열 객체)

#include <iostream>
#include <string>
#include <string_view>
using namespace std;

int main()
{
    std::string cppstr = "Foo";
    std::string_view cppstr_sv(cppstr);                     //std::string
    std::string_view cppstr_v(&cppstr[0], cppstr.size());   //* , size
    std::cout << cppstr_v << '\n';

    const char* cstr = "Hello";
    std::string_view cstr_v(cstr);                          //const char*
    std::cout << cstr_v << '\n';

    char array[3] = { 'B', 'a', 'r' };                      //array[]
    std::string_view array_v(array, std::size(array));      //* , size


    std::wstring_view wcstr_v = L"xyzzy";                   //wstring_view
    std::cout << array_v << '\n' << wcstr_v.size() << '\n';
}

//string_view 사용하기
//
//  std::string 이 지원하는 다양한 멤버함수를 std::string_view 도 지원한다

int main()
{
    // 전체 문자열 전달
    std::string_view sv1("123456789");
    copy(sv1.begin(), sv1.end(), ostream_iterator<char>(cout));     // 123456789 출력
    cout << '\n';

    // data() - 원본 포인터 얻기
    cout << sv1.data() << '\n';         // 123456789 출력


    // 부분 문자열 전달
    std::string_view sv2("123456789", 2);  // 2
    copy(sv2.begin(), sv2.end(), ostream_iterator<char>(cout));     // 12 출력
    cout << '\n';

    cout << sv2.data() << '\n';         // 출력 ?

    // data함수를 사용하면 const char *를 리턴하기 때문에 '\0' 까지 출력
    // 부분 문자열을 사용하려면 begin(), end()형태로 사용 필요
}


// string 을 사용하는 경우와 string_view 를 사용하는 경우를 다른점을 비교하자. -----------------------

#include <iostream>
#include <string>
using namespace std;

// c++ 14버전
std::string GetString(const std::string& str)
{
    if (str.size() < 5) return str;
    return str.substr(0, 5);
}

// c++ 17 string_view  
std::string_view GetStringView(const std::string_view str)
{
    if (str.size() < 5) return str;
    return str.substr(0, 5);
}

int main()
{
    auto val1 = GetString("123456789");       // std::string       val1 = "12345"    
    auto val2 = GetStringView("123456789");   // std::string_view  val2 = "12345"
}

// string_view를 사용하면 string 객체의 '복사'가 발생하지 않습니다. ***
// string_view로 받아서 string& 처럼 사용.



//사용시에 주의 할 점은 ---------------------------------------------------------------------------
//      원본 데이터에 대한 객체의 수명을 제어 할 수 없기 때문에
//      호출하는 주체가 원본 데이터의 안정성을 보장해 줘야 합니다. 

//string_view 자체는 원본 데이터를 수정 할 수 없지만
//      바라보고 있는 원본 데이터가 수정되면, string_view 문자열 데이터도 수정됩니다. ***

void CallerOriginStringObject(std::string_view str_v, std::string& str)
{
    std::cout << "[origindata] str_v = " << str_v.data() << " Size = " << str_v.size() << std::endl;

    str = "modify";
    // 원본데이터가 변경되면 string_view의 데이터가 변경됩니다.
    // 문자열 : "modify", size = 15     // 남아있는 빈 공간에는 이전 데이터가 들어 있습니다. 

    std::cout << "[origindata modify] str_v = " << str_v.data() << " Size = " << str_v.size() << std::endl;
}

int main()
{
    std::string str("original string");
    CallerOriginStringObject(str, str);
}


// string_view 리터럴 -----------------------------------------------------------------
// 
//      참고로 using namespace std::string_view_literals; 를 추가하면
//      문자열 뒤에 sv를 붙여줌으로써 string_view 리터럴을 사용할 수 있다.

using namespace std::string_view_literals;

void StringViewTest(std::string_view strv)
{
    std::cout << "str : " << strv.data() << " length : " << strv.length() << std::endl;
}

int main() {

    StringViewTest("abcdefg");          //

    std::string testStr("Test");
    StringViewTest(testStr);            //

    auto sv = "My Test String View"sv;  // "sv
    StringViewTest(sv);
}


//basic_string_view
// 
//  클래스 템플릿 basic_string_view 는 연속된 문자의 나열의 시작점을 가리키는 객체를 만들어줍니다.
//  basic_string_view는 내부적으로 문자열 포인터와 사이즈를 저장하는 변수만을 가집니다.
//  문자나 std::string 타입보다 '가볍게' 동작할 수 있습니다.
//  const_point 형태로 보유하기 때문에 원본 데이터를 수정할 수 없고 '읽기 전용'으로만 사용 가능합니다.

//std::string_view는 기본적으로 referencing을 위해 만들어진 type이기 때문에 
//  "반드시" heap use after free 문제에 대해 인지하고 써야 합니다.


//굳이 basic_string_view 를 사용하냐면, 
// 
//  일반적인 const char* 과 같은 포인터와는 달리, 
//  basic_string_view 는 가리키는 대상의 길이도 기억하고 있기 때문에, 사용이 매우 편리합니다. ***
// 
//      복사 비용 절감 - 문자열 전체 복사 없이 '포인터 + 길이' 만 전달
//      문자열 일반화 - const char*, std::string, 리터럴 모두 받을 수 있음
//      부분 문자열 뷰 가능 - .substr() 대신 뷰로 바로 접근 가능, 메모리 추가 할당 없음
//      표현력 - 범위 기반 알고리즘, 슬라이싱 등 편리 
// 
//  이름에서도 알 수 있듯이 string 을 볼 수만 있기 때문에, 가리키고 있는 문자열을 수정할 수는 없습니다.
//  또한 주의할 점으로 가리키고 있는 문자열이 메모리에서 소멸되지 않도록 해야만 합니다.

const char* func() 
{
    string s = "abc";
    return s.c_str();
}

int main()
{    
    std::string_view good("a string literal");  // OK. static 배열을 가리키고 있음

    std::string_view bad(func());               // BAD. 이미 소멸된 string 을 가리킴
}

