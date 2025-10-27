// 여러 구현 방법들 

// 예시) level 이 10보다 크면 "yes" 아니면 "no" 를 출력하는 람다식, 실행 

#include<iostream>
#include<string>
using namespace std;

int main()
{
	int level = 1;	

	[](int a)-> void {
		if (a > 10) cout << "yes" << endl;
		else 		cout << "no" << endl;
	}(level);	

	[level]() {
		if (level > 10) cout << "yes" << endl;
		else 			cout << "no" << endl;
	}();

	[level]() {	level > 10 ? (cout << "yes" << endl) : (cout << "no" << endl);} ();

	cout <<
		[](int a)->string {
			if (a > 10) { return "yes"; }
			else		{ return "no"; }
		}(level)
	<< endl;

	return 0;
}