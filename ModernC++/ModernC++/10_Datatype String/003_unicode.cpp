// OS에서 제공하는 유니코드 처리

#include <iostream>
#include <string>
#include <Windows.h>		//Windows API

int main() {
 
	//*유니코드->멀티바이트
	{
		wchar_t strUni[256] = L"유니코드";
		char strUtf8[256] = { 0, };
		int nLen = WideCharToMultiByte(CP_UTF8, 0, strUni, lstrlenW(strUni), NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_UTF8, 0, strUni, lstrlenW(strUni), strUtf8, nLen, NULL, NULL);
	}

	//*멀티바이트->유니코드
	{
		wchar_t strUnicode[256] = { 0, };
		char strMultibyte[256] = { 0, };
		wcscpy_s(strUnicode, 256, L"유니코드");
		int len = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, strMultibyte, len, NULL, NULL);
	}

	//*유니코드->UTF - 8
	{
		wchar_t strUnicode[256] = { 0, };
		char strMultibyte[256] = { 0, };
		strcpy_s(strMultibyte, 256, "멀티바이트");
		int nLen = MultiByteToWideChar(CP_ACP, 0, strMultibyte, strlen(strMultibyte), NULL, NULL);
		MultiByteToWideChar(CP_ACP, 0, strMultibyte, strlen(strMultibyte), strUnicode, nLen);
	}

	//*UTF - 8->유니코드
	{
		wchar_t strUnicode[256] = { 0, };
		char	strUTF8[256] = { 0, };
		strcpy_s(strUTF8, 256, "UTF-8글자"); // UTF-8 문자라고 가정하고..
		int nLen = MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), NULL, NULL);
		MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), strUnicode, nLen);
	}

	//*기본적으로 UTF - 8로 변형할땐 유니코드 상태에서만 변형을 시켜야 한다.
	//	- 멀티바이트->유니코드(UTF - 16)->UTF - 8
	//	- UTF - 8->유니코드(UTF - 16)->UTF - 8
}


//Unicode는 전 세계의 모든 문자를 고유한 코드 포인트(code point) 로 정의합니다.
//인코딩 방식(저장 / 전송 방식) 은 별도로 정의
 
//주요 인코딩 방식
//
//코딩		설명									특징
//UTF-8		가변 길이(1~4바이트).ASCII와 호환		웹 표준, 가장 널리 사용
//UTF-16	2바이트 또는 4바이트					Windows, Java 내부 표현
//UTF-32	고정 4바이트							단순하지만 메모리 비효율적

//std::string은 단순 바이트 배열이지, “문자” 단위가 아님 ***
//
//내부 문자열은 UTF-8 로 통일하는 것이 가장 실용적.
//입출력 시에는 파일 / 콘솔의 인코딩을 맞추거나 변환 사용.
//정규화, 비교, 대소문자 변환은 ICU, Boost.Text, fmtlib 같은 라이브러리 이용.

//유니티(Unity)의 유니코드 처리
//	C# 기반이므로.NET 문자열 시스템(System.String) 을 그대로 사용
//	C#의 string은 내부적으로 UTF-16 인코딩을 사용
//	즉, 유니티의 모든 문자열(string, TextMeshPro, UI.Text, JSON 등)은 자동으로 유니코드 호환

//언리얼 엔진(Unreal Engine)의 유니코드 처리
//	C++ 기반이지만 모든 문자열을 내부적으로 UTF-16(TCHAR)로 처리
//	플랫폼별 문자 크기 차이를 숨김
//	문자열 클래스(FString, FText, FName)는 모두 유니코드 지원








