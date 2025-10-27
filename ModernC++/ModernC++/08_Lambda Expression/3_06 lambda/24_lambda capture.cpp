// lambda expressions - late evaluation (지연실행)		//캡처 매카니즘 ***

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	int val = 5;
	auto func = [val]() mutable { val *= 5; return val; };
	std::cout << "val: " << val << std::endl;			//실행 결과는? //참조 캡쳐면? (지연실행)

	val = 10;
	std::cout << "val*5: " << func() << std::endl;		//실행 결과는? //참조 캡쳐면?

	// 10으로 바꾼 뒤에 func()가 실행이 됐지만 결과는 50이 아닌 25가 나온다. 
	// 
	// 캡처는 람다식이 쓰인 위치에서 바로 캡처한 값으로 유지 (value capture)
	// 기본적으로 상수캡쳐이므로 변경하려면  mutable 사용
}


//static(lexical) binding

/*
	#include <iostream>
	#include <functional>
	using namespace std;

	int main()
	{
		int a = 1, b = 2;

		// 외부 변수 a와 b를 복사 캡쳐하고, int x를 파라미터로 받는 lambda 함수
		auto closureFunc = [a, b](int x) { cout << a + b + x << endl; };
		//auto closureFunc = [&a, &b](int x) { cout << a + b + x<< endl; };

		closureFunc(3);		// 1 + 2 + 3 = 6 를 출력

		a = 10, b = 20;		// 여기에서 a 와 b 를 변경

		closureFunc(3);		// 지금의 closureFunc(3) 는	// 1+2+3 = 6 일까? 10+20+3 = 33 일까?

		return 0;
	}

	//static(lexical) binding
	//  closureFunc 함수는 a 와 b 의 값에 "Closed over(Closure)" 되었다

	//late evaluation (지연실행)
	//	Closure 특성이 유용한 이유는 late evaluation 이 가능하다는 것
	//	즉, closure 함수는 바뀐 주변 환경과 관계없이 자신이 정의될 때의 환경에 따라 행동한다.
	//	이러한 closure 의 특징은
	//	하나의 환경 하에서 여러 개의 코드 블록을 정의하여, 이후 해당 함수들이 필요할 때 실행시킬 수 있는 
	//	이른바 multiple function 의 사용을 가능하게 한다.

*/



// 람다 캡처 변수의 범위  -------------------------------------
//		람다에서 캡처는 오직 
//	    람다가 만들어지는 범위에서 볼 수 있는 non-static 지역변수에 대해서만 가능하다.

#include <algorithm>
#include <vector>
using namespace std;

int g_evenCount = 0;        //바깥쪽 범위의 변수가 아님, 범위를 벗어난 전역에 위치

int main()
{
	vector<int> v;
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}

	// 람다 캡처 변수는 바깥쪽 함수(main) 범위에 속해야 한다. //error
	for_each(v.begin(), v.end(), [&g_evenCount](int n) {
			if (n % 2 == 0) { g_evenCount++; }
		});

	//for_each(v.begin(), v.end(), [&](int n) {
	//    if (n % 2 == 0) { g_evenCount++; }		//캡처 변수가 아님
	//    });
}
