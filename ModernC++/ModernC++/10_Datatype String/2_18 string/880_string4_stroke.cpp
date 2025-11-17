//문자열 분리하기 //strtok_s

#include <iostream>
#include <string>
using namespace std;

int main(void)
{
	char str1[] = "a b c d e f";
	char str2[] = "가,나,다,라,마,바";
	char str3[] = "1,2-3;4 5";
	char* context;

	char* tok1 = strtok_s(str1, " ", &context);
	while (tok1 != NULL) {
		cout << tok1 << endl;
		tok1 = strtok_s(context, " ", &context);
	}

	//str2 를 분리하여 출력하세요.
	char* tok2 = strtok_s(str2, ",", &context);
	while (tok2 != NULL) {
		cout << tok2 << endl;
		tok2 = strtok_s(context, ",", &context);
	}

	//str3 를 분리하여 출력하세요.
	char* tok3 = strtok_s(str3, ",-; ", &context);
	while (tok3 != NULL) {
		cout << tok3 << endl;
		tok3 = strtok_s(context, ",-; ", &context);
	}

	return 0;
}

