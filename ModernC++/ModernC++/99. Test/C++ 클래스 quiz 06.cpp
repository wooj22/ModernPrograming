//static //잘못된 코드에 X 표시하세요.

#include <iostream>
using namespace std;

class CTest
{
	int count = 0;                      //1 (  )
	static int g_count = 0;             //2 (  )
public:
	void func1() { count++; }           //3 (  )
	void func2() { g_count++; }         //4 (  )
	static void func3() { count++; }    //5 (  )
	static void func4() { g_count++; }  //6 (  )
};
