//원하는 패턴 치환하기 ------------------------------------------
//regex_replace  

#include <iostream>
using namespace std;

int main() {
    string str1 = "aaa-bb";
    cout << str1.replace(0, 2, "zz") << endl; //zza-bb

    //문자열.replace(시작 위치, 길이, 치환 문자열)

    return 0;
}

//--------------------------------------------------------------
#include <iostream>
#include <regex>
using namespace std;

int main() {    
    string str1 = regex_replace("aaa-bba-ccd-daf", regex("a"), "z");
    cout << str1 << endl;

    //regex_replace.(대상 문자열, regex(정규식), 치환 문자열)

    return 0;
}

//--------------------------------------------------------------
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

    //sk-circle1 과 같은 문자열을 1-sk-circle 로 바꿔보는 정규 표현식

    std::regex re(R"r(sk-circle(\d))r");    //캡쳐 그룹을 이용
    std::smatch match;

    std::string modified_html = std::regex_replace(html, re, "$1-sk-circle");
    std::cout << modified_html;

    //치환된 문자열을 생성하지 않고 그냥 stdout 에 출력하고 싶다면;
    //std::regex_replace(std::ostreambuf_iterator<char>(std::cout), html.begin(), html.end(), re, "$1-sk-circle");
}


