//가변인자 함수 - C
//		void func(int num_args, ...);

//printf 함수의 원형
//		int printf(const char* format, ...)		//가변 파라미터  //포인터 기반

#include <iostream>
#include <vector>
#include <cstdarg>			//#include <stdarg.h>
using namespace std;

int sum(int num_args, ...); //함수 프로토타입 선언 

int main()
{
	printf("%d\n", 1);                     //인자 2개
	printf("%d, %d\n", 1, 2);              //인자 3개 
	printf("%d, %d, %s\n", 1, 2, "HELLO"); //인자 4개

	cout << sum(1, 2) << endl;
	cout << sum(2, 2, 3) << endl;
	cout << sum(3, 6, 7, 8) << endl;
}

int sum(int num_args, ...)		//첫 번째 고정인수에 총 개수
{	
	va_list ap;							// va_list 는 가변 인수들에 대한 정보를 담기 위한 타입 				
										// 추후 인자리스트에서 추출하고 싶은 인자의 주소를 가리키는 포인터 역할. 
	va_start(ap, num_args);				// va_start 는 ap가 맨 첫 번째 가변인수를 가리킬 수 있도록 초기화! 
	int arg = 0, result = 0;
	for (int i = 0; i < num_args; i++)  // 반복문 돌리면서 인자값 한 개 한 개씩 뽑기!
	{
		arg = va_arg(ap, int);			// va_arg 는  ap포인터가 위치한 부분의 데이터를 읽어 반환 
		result += arg;
	}

	va_end(ap);							// va_end 가변인자 사용 끝!

	return result;
}

/*
//평균 출력하는 가변인자 함수를 만들어 보세요.

	//#include <stdio.h>
	//#include <stdarg.h>
	#include <iostream>
	#include <cstdarg>
	using namespace std;

	double avg(double value, ...);	

	int main()
	{
		printf("result :%.3lf", avg(1.01, 34.02, 7.45, 0.0));
		return 0;
	}

	double avg(double value, ...)
	{
		double sum = 0; int num = 0;
		va_list ap;								//va_list
		va_start(ap, value);					//va_start
		while (value != 0.0) {
			sum += value; num++;
			value = va_arg(ap, double);			//va_arg
		}
		va_end(ap);								//va_end
		return (sum / num);
	}
*/

// vsprintf
//		다양한 타입의 가변 인자들을 %d, %s, %c 등의 형식을 읽어서 알아서 예쁘게 포장해주는 함수
//		int vsprintf(char* dest, const char* format, va_list args)
//		int vsnprintf(char* dest, size_t maxCount, const char* format, va_list args)

	#include <stdio.h>
	#include <stdarg.h>
	#include <string.h>

	void errorPrintf(char* fmt, ...)
	{
		char buf[512] = {0,};
		va_list ap;

		strcpy(buf, "[ERROR] ");
		va_start(ap, fmt);
		vsprintf(buf + strlen(buf), fmt, ap);
		va_end(ap);

		puts(buf);
	}

	int main()
	{
		int a = 10, b = 0;

		if(b != 0)
			printf("%d\n", a / b);
		else
			errorPrintf("Don't divide by %d\n", b);

		return 0;
	}

*/

/*
//다양한 자료형의 가변 인자 처리하기.

	#include <iostream>
	#include <cstdarg>
	using namespace std;
	//#include <stdio.h>
	//#include <stdarg.h>    // va_list, va_start, va_arg, va_end가 정의된 헤더 파일

	void printValues(const char* types, ...)    // 가변 인자의 자료형을 받음, ...로 가변 인자 설정
	{
		va_list ap;						// 가변 인자 목록
		int i = 0;
		va_start(ap, types);			// types 문자열에서 문자 개수를 구해서 가변 인자 포인터 설정
		while (types[i] != '\0')		// 가변 인자 자료형이 없을 때까지 반복
		{
			switch (types[i])			// 가변 인자 자료형으로 분기
			{
			case 'i':                                // int형일 때
				printf("%d ", va_arg(ap, int));      // int 크기만큼 값을 가져옴 // ap를 int 크기만큼 순방향으로 이동
				break;
			case 'd':                                // double형일 때
				printf("%f ", va_arg(ap, double));   // double 크기만큼 값을 가져옴 // ap를 double 크기만큼 순방향으로 이동
				break;
			case 'c':                                // char형 문자일 때
				printf("%c ", va_arg(ap, char));     // char 크기만큼 값을 가져옴 // ap를 char 크기만큼 순방향으로 이동
				break;
			case 's':                                // char *형 문자열일 때
				printf("%s ", va_arg(ap, char*));    // char * 크기만큼 값을 가져옴 // ap를 char * 크기만큼 순방향으로 이동
				break;
			default:
				break;
			}
			i++;
		}
		va_end(ap);						// 가변 인자 포인터를 NULL로 초기화
		printf("\n");					
	}

	int main()
	{
		printValues("i", 10);                                       // 정수
		printValues("ci", 'a', 10);                                 // 문자, 정수
		printValues("dci", 1.234567, 'a', 10);                      // 실수, 문자, 정수
		printValues("sicd", "Hello, world!", 10, 'a', 1.234567);    // 문자열, 정수, 문자, 실수
		return 0;
	}
*/