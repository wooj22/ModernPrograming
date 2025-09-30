// 0 과 NULL 보다  nullptr 를 선호하라.
//
//		NULL은 그냥 숫자 0이기 때문에 어떨 때는 int 타입이랑 비교가 되고, 
//		int 타입의 인자로 들어가서 함수를 호출하기도 하고
//		어떨때는 포인터 0으로 널을 가리키고 아주 애매모호함

#include <iostream>
#include <mutex>
using namespace std;

int main()
{
	int* p1 = 0;
	int* p2 = NULL;
	int* p3 = nullptr;

	//포인터 변수를 초기화하기 위해 기존의 방식대로 0,NULL을 사용해도 되지만, 
	//nullptr을 사용하는 것이 안전하고 코드의 가독성을 높일 수 있다.

	int* a = 0; //포인터	
	if (a == 0)					// a가 int 값의 0인지 포인터 타입인지 헷갈릴 수 있음.
	{
		cout << "a == 0" << endl;
	}
	if (a == nullptr)			// a가 포인터 타입인지 알 수 있음, 가독성
	{
		cout << "a == nullptr" << endl;
	}

	//nullptr 의 데이터 타입 --------------------------------------------
	//	std::nullptr_t
	//  0이 int 타입이고, 0.0이 double타입, 0.0f가 float 타입이듯이
	//  nullptr의 데이터 타입은 std::nullptr_t라는 타입이다. ***
	//  해당 std::nullptr_t 타입은 모든 타입의 포인터로 암시적 형변환이 가능합니다.

	int* ptr1 = nullptr;                    // int 포인터
	char* ptr2 = nullptr;                   // char 포인터
	double* ptr3 = nullptr;                 // double 포인터
	void (*func1) (int a, int b) = nullptr; // 함수 포인터1
	void (*func2) () = nullptr;             // 함수 포인터2


	// NULL, nullptr 비교 ---------------------------------------------
	int* pt1 = NULL;
	int* pt2 = nullptr;

	if (pt1 == NULL)	{ cout << "pt1 == NULL" << endl; }
	if (pt2 == NULL)	{ cout << "pt2 == NULL" << endl; }
	if (pt1 == nullptr) { cout << "pt1 == nullptr" << endl; }
	if (pt2 == nullptr) { cout << "pt2 == nullptr" << endl; }
	if (pt1 == pt2)	    { cout << "NULL == nullptr" << endl; }			

	//  0, NULL, nullptr 비교 
	int n = 0;
	if (n == NULL) { cout << "int 타입 0 == NULL" << endl; }
	//if (n == nullptr) { cout << "3-2. int 타입 0 == nullptr" << endl; }		//ERROR

	return 0;
}
