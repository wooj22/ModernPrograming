// 정규표현식 - 텍스트를 빠르게 처리하기 위한 방법, 별도의 문법과 함수 표현

#include <iostream>
#include <regex>
#include <vector>
//#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main()
{  
    regex re("\\d");                        //숫자    // 입력테스트    1,  a,  3,  1a,  12 
    //regex re(R"(\d)");                    //숫자    // R"( )"
    //regex re(R"(\d{1,3})");               //숫자 1~3 
    //regex re(R"([0-9]{1,})");             //숫자 1회 이상
    //regex re(R"([a-z][0-9]{1,})");        //소문자 숫자 1회 이상
    //regex re(R"([A-Za-z]@[0-9]{1,})");    //영문자 @ 숫자 1회 이상

    string str;

    while (true)
    {
        getline(cin, str);

        // regex_match() 함수
        if (std::regex_match(str, re))  cout << "Match" << endl;
        else                            cout << "No Match" << endl;


        // 반복자를 이용하여 검사한 후 매치하는 부분만 출력
        auto begin = std::sregex_iterator(str.begin(), str.end(), re);
        auto end = std::sregex_iterator();
        for (auto itr = begin; itr != end; ++itr) {
            std::smatch match = *itr;
            cout << match.str() << " ";
        }
        cout << endl;

    }

    return 0;
}


//특정 문자열에서 정규 표현식에 부합하는 요소만 추출해서 출력하는 예
#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main()
{
    std::string s = "123 456 789";
    std::regex number("([0-9])([0-9])([0-9])");

    std::sregex_iterator it(s.begin(), s.end(), number);
    std::sregex_iterator end;

    while (it != end)
    {
        std::smatch m = *it;
        std::cout << m.str() << std::endl;
        ++it;
    }
    return 0;
}
