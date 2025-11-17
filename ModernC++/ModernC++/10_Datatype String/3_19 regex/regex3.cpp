//패턴을 만족하는 문자열 일부 를 검색하는 작업 ----------------------------------------

//regex_search 
//      주어진 문자열에서 정규 표현식과 일치하는 sub-string들을 찾는다.

#include <iostream>
#include <regex>
using namespace std;

void SearchTest()
{
    regex pattern("(\\w+[\\w\\.]*)@(\\w+[\\w\\.]*)\\.([A-Za-z]+)"); //이메일
    string str("My email address is SooKkaRak@gmail.com");

    smatch m;
    if (regex_search(str, m, pattern))
    {
        for (size_t i = 0; i < m.size(); i++)
            cout << i << "번째 : " << m[i] << endl;
    }
    else
    {
        cout << "NOT MATCH" << endl;
    }    
}

//여러 개 포함되어 있는 경우엔 어떻게 처리해야 할까 ?

void SearchTest()
{
    regex pattern("(\\w+[\\w\\.]*)@(\\w+[\\w\\.]*)\\.([A-Za-z]+)");
    string str("Primary:SooKkaRak@gmail.com     Secondary:Sweeper@yahoo.com");

    smatch m;
    while (regex_search(str, m, pattern))
    {
        for (size_t i = 0; i < m.size(); i++)
            cout << i << "번째 : " << m[i] << endl;
        cout << endl;

        // 다음 sub match를 str로 셋팅
        str = m.suffix();
    }
}
int main() {
    SearchTest();
}



//------------------------------------------------------------------
#include <iostream>
#include <regex>

int main() {
    std::string html = R"(
        <div class="social-login">
            <div class="small-comment">다음으로 로그인 </div>
            <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
            </div>
        </div>
        <div class="manual">
            <div class="small-comment">
            또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
            </div>
            <input name="name" id="name" placeholder="이름">
            <input name="password" id="password" type="password" placeholder="비밀번호">
        </div>
        <div id="adding-comment" class="sk-fading-circle">
            <div class="sk-circle1 sk-circle">a</div>
            <div class="sk-circle2 sk-circle">b</div>
            <div class="sk-circle3 sk-circle">asd</div>
            <div class="sk-circle4 sk-circle">asdfasf</div>
            <div class="sk-circle5 sk-circle">123</div>
            <div class="sk-circle6 sk-circle">aax</div>
            <div class="sk-circle7 sk-circle">sxz</div>
        </div>
    )";

    std::regex re(R"(<div class="sk[\w -]*">\w*</div>)");
    std::smatch match;
    while (std::regex_search(html, match, re)) {
        std::cout << match.str() << '\n';
        html = match.suffix();
    }

/*
    //regex_iterator 

    std::regex re(R"(<div class="sk[\w -]*">\w*</div>)");
    std::smatch match;

    auto start = std::sregex_iterator(html.begin(), html.end(), re);
    auto end = std::sregex_iterator();

    while (start != end) {
        std::cout << start->str() << std::endl;
        ++start;
    }
*/
}


