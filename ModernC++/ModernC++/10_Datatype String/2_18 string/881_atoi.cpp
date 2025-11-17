//문자열 변환 //C

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

int main()
{
	int i;
	char buffer[256];
	printf("Enter a number: ");
	fgets(buffer, 256, stdin);
	i = atoi(buffer);								//
	printf("The value entered is %d.\n", i);

	//int i;
	//char buffer[33];
	printf("Enter a number: ");
	scanf_s("%d", &i);
	_itoa(i, buffer, 10);	printf("decimal: %s\n", buffer);
	_itoa(i, buffer, 16);	printf("hexadecimal: %s\n", buffer);
	_itoa(i, buffer, 2);	printf("binary: %s\n", buffer);

	return 0;
}
