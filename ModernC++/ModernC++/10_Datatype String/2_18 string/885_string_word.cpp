//문자열 입력 // 단어수 구하기

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool is_alphabet(char ch)
{
    if ((0x41 <= ch && ch <= 0x5A) || (0x61 <= ch && ch <= 0x7A))
        return true;
    else
        return false;
}

bool is_space(char ch)
{
    if (ch == ' ')  return true;
    else            return false;
}

int main()
{
    // 성능최적화
    ios_base::sync_with_stdio(false);   // C 표준 stream과 C++ 표준 stream의 동기화를 끊습니다. //동기화가 비활성화됐기 때문에 멀티 쓰레드 환경에서는 주의
    cin.tie(NULL);                      // cin과 cout의 묶음을 풀어줍니다

    char ch;
    int count = 0, n = 0;
    string s;
    getline(cin, s);   //문자열 입력 

    //단어수 구하기
    for (size_t i = 0; i < s.size(); i++) {
        ch = s.c_str()[i];				//C 문자열로 변환

        if (is_alphabet(ch) == true && n == 0) { count++; n = 1; }
        if (is_space(ch) == true && n == 1) { n = 0; }
    }
    cout << count << endl;

    return 0;
}


/*
//4 + 125 + 4 + 77 + 102 등으로 표현된 덧셈식을 문자열로 입력받아 계산하는 프로그램 작성하라

#include <iostream>
#include <string>
using namespace std;

int main()
{

	string s;
	cout << "7+23+5+100+25와 같이 덧셈 문자열을 입력하세요." << endl;
	getline(cin, s, '\n'); // 문자열 입력

	int sum = 0;
	int startIndex = 0; // 문자열 내에 검색할 시작 인덱스
	while (true) {
		int fIndex = s.find('+', startIndex);
		if (fIndex == -1) { // '+' 문자 발견할 수 없음
			string part = s.substr(startIndex);
			if (part == "") break; // "2+3+", 즉 +로 끝나는 경우
			cout << part << endl;
			sum += stoi(part); // 문자열을 수로 변환하여 더하기
			break;
		}
		int count = fIndex - startIndex; // 서브스트링으로 자를 문자 개수
		string part = s.substr(startIndex, count); // startIndex부터 count 개의 문자로 서브스트링 만들기
		cout << part << endl;
		sum += stoi(part); // 문자열을 수로 변환하여 더하기
		startIndex = fIndex + 1; // 검색을 시작할 인덱스 전진시킴
	}
	cout << "숫자들의 합은 " << sum;
}

// &가 입력될 때까지 여러 줄의 영문 문자열을 입력 받고,
// 찾는 문자열과 대치할 문자열을 각각 입력받아 문자열을 변경하라

#include <iostream>
#include <string>
using namespace std;
int main()
{
	string s;
	cout << "여러 줄의 문자열을 입력하세요. 입력의 끝은 &문자입니다." << endl;
	getline(cin, s, '&');		// 문자열 입력
	cin.ignore();				// enter키 제거

	string f, r;
	cout << endl << "find: ";
	getline(cin, f, '\n');		// 검색할 문자열 입력
	cout << "replace: ";
	getline(cin, r, '\n');		// 대치할 문자열 입력

	int startIndex = 0;
	while (true) {
		int fIndex = s.find(f, startIndex); // startIndex부터 문자열 f 검색
		if (fIndex == -1)
			break;				// 문자열 s의 끝까지 변경하였음
		s.replace(fIndex, f.length(), r); // fIndex부터 문자열 f의 길이만큼 문자열 r로 변경
		startIndex = fIndex + r.length();
	}
	cout << s << endl;
}
*/