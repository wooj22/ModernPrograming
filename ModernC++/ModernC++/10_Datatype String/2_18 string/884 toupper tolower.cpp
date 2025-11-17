// C언어 : <ctype.h>  // C++ : <cctype>
 
// tolower : 대문자를 소문자로 변환
// toupper : 소문자를 대문자로 변환

// isdigit : 문자가 숫자인지 판별
// isupper : 문자가 대문자인지 판별
// islower : 문자가 소문자인지 판별

#include <string>
#include <iostream>
using namespace std;

int main()
{
	//---------------------------------------------

	string str = "Hello World";

	for (int i = 0; i < str.length(); i++)
		str[i] = toupper(str[i]);

	//---------------------------------------------

	string str2 = "123ABCabc 123ABC abc";

	for (int i = 0; i < str2.size(); i++)
	{
		if (isdigit(str2[i])) {
			cout << str2[i] << endl;
		}
		else if (isupper(str2[i])) {
			cout << str2[i] << endl;
		}
	}
	return 0;
}


/*
1) 문자 판단 함수
isalnum(문자): 영문자 또는 숫자인 경우만 참을 리턴
isalpha(문자): 문자가 영문자인 경우만 참을 리턴
isdigit(문자): 문자가 숫자인 경우만 참을 리턴
islower(문자): 문자가 영어 소문자인 경우만 참을 리턴
isupper(문자): 문자가 영어 대문자인 경우만 참을 리턴
ispunct(문자): 문자가 기호문자인 경우에만 참을 리턴
isspace(문자): 문자가 스페이스인 경우에만 참을 리턴
isascii(int c): c가 ASCII이면 참값을 리턴
iscntrl(int c): c가 control 문자이면 참값을 리턴
isprint(int c): c가 인쇄 가능한 문자이면 참값을 리턴

2) 문자 변경 함수
toascii(char c): 문자를 아스키 코드 값으로 변경
tolower(char c): c를 소문자로 변환하는 함수
toupper(char c): c를 대문자로 변환하는 함수
*/
