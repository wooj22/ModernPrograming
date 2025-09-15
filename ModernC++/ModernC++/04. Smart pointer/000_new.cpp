//메모리 관리와 메모리의 동적 할당  // new delete

#include <iostream>
using namespace std;

int main(void)
{
	//동적할당 //heap에 공간 할당하기

	char* pchar = new char;				//1바이트만큼 heap에 공간 할당
	*pchar = 'a';
	cout << "메모리주소 :" << (void*)pchar << "\t값 :" << *pchar << endl;  //void*로 형변환
	cout << "heap 크기: " << sizeof(*pchar) << endl;
	delete pchar;

	int* pnum = new int;				//4바이트만큼 heap에 공간 할당
	*pnum = 3;
	delete pnum;

	double* pdouble{ new double };		//8바이트만큼 heap에 공간 할당
	*pdouble = 3.141592;
	delete pdouble;


	//new 하면서 초기화하기 //new는 초기화가 가능하다. ***

	int* p = new int(10);				// int 10 으로 초기화
	cout << "*p:" << *p << endl;
	delete p;

	float* pfloat = new float(75.25f);
	cout << "*pfloat: " << *pfloat << endl;
	delete pfloat;

	int* pary1 = new int[3]{};			// 배열 new	// 0으로 초기화 
	cout << "pary1[0]: " << pary1[0] << endl;
	delete[] pary1;						// 배열 delete

	int* pary2{ new int[3]{} };
	delete[] pary2;

	char* pary3 = new char[20]{ "Hello World!" };		//문자열
	cout << "pary3: " << pary3 << endl;
	delete[] pary3;

	int* pary4{ new int[5]{ 1, 2, 3, 4, 5 } };
	delete[] pary4;

	/*
		// float형 보관하려고 합니다. 
		// 공간을 동적할당하여,  1.1, 2.2, 3.3, 4.4 데이타로 초기화하고, 출력하세요.

		int num = 4;
		
		auto* pary{ new float[num] { 1.1, 2.2, 3.1, 4.1 } };
		for (int i = 0; i < num; i++)
			cout << "pary[" << i << "]: " << pary[i] << "  ";
		cout << endl;

		delete[] pary;

		// 같은 변수에 2.2는 삭제하고, 5.5 데이타를 추가하여 다시 출력하세요.

		// 6.6 데이타를 추가하여 다시 출력하세요.
	*/

	return 0;
}

/*

//---------------------------------------------------------------------
동적 할당
	C++에는 C언어의 malloc free 함수이외에 new delete 연산자가 하나 더 있다.
	둘다 사용이 가능하지만 C++ 연산자가 더 쉽고 간단하기 때문에 더 많이 사용된다.
	특히 클래스의 경우는 '반드시' new delete 연산자를 사용한다. ***

	int *p = (int *)malloc(sizeof(int));
	int *p = new int;

	//주소를 저장할 포인터 선언 = new 할당하고 싶은 크기의 자료형;

배열을 사용하여 동일한 크기의 메모리를 동적 메모리를 할당 하려면 아래의 방법처럼 해주면 된다.

	int *p = (int *)malloc(sizeof(int)*10); // int[10]
	int *p = new int[10];

C언어에서 free를 해주 듯 new 연산자에서도 delete 연산자가 있다.
표현 방법은 아래와 같다.

	free(p);
	delete p;

하지만 delete 연산자에서는 주의해야 할 점이 있는데,
new 연산자와 같은 형태로 해제를 해 주어야 한다는 것이다. [] ***

	int *p = new int;
	delete p;

	int *p = new int[10];
	delete[] p;

*/

// 클래스 객체의 동적할당 ------------------------------------------------
/*
#include <iostream>
using namespace std;

class Test
{
	int num;
public:
	Test() : num(0) { cout << "Test(): " << num << endl; }
	Test(int num) : num(num) { cout << "Test(int): " << num << endl;; }
	void Print() { cout << num << endl; }
};

int main()
{
	Test* ptest1 = new Test;
	Test* ptest2 = new Test(10);
	delete ptest1;
	delete ptest2;

	Test* plist = new Test[3]{ Test(1), Test(2),Test(3) };
	for (size_t i = 0; i < 3; i++)
	{
		plist[i].Print();
	}
	delete[] plist;


	Test** plist2 = new Test*[3] { new Test(4), new Test(5), new Test(6) };
	for (size_t i = 0; i < 3; i++)
	{
		plist2[i]->Print();
	}
	delete plist2[0];
	delete plist2[1];
	delete plist2[2];
	delete[] plist2;

	return 0;
}

*/

/*

포인터의 문제점 ***

	포인터가 가리키는 주소의 값이 배열인지 하나의 객체인지 판별이 불가능  -> 포인터 선언의 타입  
	파괴하기 위해 어떤 방법을 써야할 지 알아낼 방법이 없다. delete를 써야할지, delete []를 써야할지
	포인터가 가리키는 대상을 내가 소유하고 있는지 아닌지 알 수 있는 방법이 없다.  -> 배타적 소유권
	댕글링 포인터(dangling pointer), 자원이 이미 해제된 자원인지 아닌지 판별할 수가 없다  - nullptr
	자원 해제는 정확히 한번만 해야한다  -> 중복 해제 방지 방법

해결책으로

	++ 11에서는 스마트 포인터라는 것이 도입, RAII

//memory leak ---------------------------------------------------------------

	//해제 누락
		delete 를 안하는 경우

	//재할당 
		delete 없이 new 를 두번 하는 경우 

		while (true)
		{
			int* ptr = new int;  //기존의 new int 영역은 미아가 되버린다
			cout << ptr << endl;
		}

	//중복 해제
		delete 를 두번 하는 경우 

//memory leak 을 방지하는 방법은 ???     - 스마트 포인터

*/