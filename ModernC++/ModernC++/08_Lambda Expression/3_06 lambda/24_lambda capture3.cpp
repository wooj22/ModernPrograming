//참조로 캡처할 때 주의점

#include <iostream>
#include <functional>
using namespace std;

int main()
{
	int* test = new int;
	*test = 10;

	auto fun1 = [&]() {	(*test)++;	cout << *test << endl;	};
	auto fun2 = [&]() {	(*test)++;	cout << *test << endl;	};

	cout << *test << endl;

	fun1();

	fun2();			//정상 출력
	delete test;

	delete test;	//만약 먼저 지워진다면
	fun2();
}

//참조로 캡처할 때 주의점은 참조로 캡처한 변수가 메모리상에 존재하고 있어야 한다는 것입니다. 
//스택에 있는 변수 같은 것을 참조로 캡처할 때는 특히나 주의해야 합니다.

//mutable 사용
//auto fun1 = [test2 = *test]() mutable {	test2++; cout << test2 << endl;	};
//auto fun2 = [test2 = *test]() mutable {	test2++; cout << test2 << endl;	}; //변경가능 하나 각각 다른 값

//shared_ptr 사용
//shared_ptr<int> test = make_shared<int>(10);
//메모리 어딘가에서 객체가 삭제되어도 완전히 삭제되는 것은 shared_ptr의 모든 참조가 해제되는 순간까지 보장받습니다.