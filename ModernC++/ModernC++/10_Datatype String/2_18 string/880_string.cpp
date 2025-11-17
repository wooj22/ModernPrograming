#include <iostream>
#include <tchar.h>
#include <string>
using namespace std;

int main()
{
	char arr[] = "Hello";
	const char* str = "Hello";

	string s1("Hello");			// string 생성자
	cout << s1 << endl;			// cout

	string src = "I am source :)";
	string dst;
	dst = src;					// =
	cout << dst << endl;

	string a = "hello";
	string b = " world!";
	string c = a + b;			// +
	cout << c << endl;

	if (a == b)	cout << "T";	// ==
	else 		cout << "F";
	return 0;
}

/*
// 표준 string 클래스의 분석 -------------------------------

1. 문자열을 인자로 전달받는 생성자의 정의
2. 생성자, 소멸자, 복사 생성자, 대입 연산자의 정의
   생성자 내에서 문자열 저장을 위한 메모리의 동적 할당이 이루어지므로..
3. 결합된 문자열로 초기화된 객체를 반환하는 + 연산자의 오버로딩
   string str3 = str1 + str2;   str1+str2의 반환 값으로 두 객체의 문자열을 모두 포함하는 string 객체가 반환되도록
4. 문자열을 덧붙이는 += 연산자의 오버로딩
5. 내용비교를 진행하는 == 연산자의 오버로딩
6. 콘솔 입출력을 가능하게 하는 <<, >> 연산자의 오버로딩
*/

/*
// 문자열 입력받기 -----------------------------------------

#include <iostream>
#include <string>
using namespace std;

int main()
{
	const int arSize = 20;
	char buf[arSize]; //char buf[20] 과 같음
	cout << "Enter answer: ";
	cin.getline(buf, arSize);
	cout << "Answer is : " << buf << endl;
}

#include <string>
using namespace std;

int main()
{
	string answer;
	cout << "Enter answer: ";
	getline(cin, answer);
	cout << "Your answer is: " << answer << endl;
}
*/