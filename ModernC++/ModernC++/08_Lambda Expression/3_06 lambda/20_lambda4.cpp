// lambda expressions //벡터에서 람다 사용하기

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

	for_each(v.begin(), v.end(), [](int i) { cout << i; } ); cout << endl;


	// 출력
	for_each(begin(v), end(v), [&](const int& i) { cout << i; } ); cout << endl;
	// 짝수 출력
	for_each(begin(v), end(v), [&](const int& i) { if (i % 2 == 0) cout << i; }); cout << endl;

	// 벡터 내용을 변경 후 출력
	for_each(begin(v), end(v), [](int& i) { i++; cout << i; }); cout << endl;

	//for_each(v.begin(), v.end(), [](auto n) { cout << n; });  cout << endl;

	//for (auto n : v) cout << n;
}


//lambda 함수를 STL container에 저장 -------------------------------------------

	#include <iostream>
	#include <algorithm>
	#include <functional>
	#include <vector>
	using namespace std;

	int main()
	{
		vector< function<const char* ()> > v;			//vector 에 람다 저장

		v.push_back( [] { return "대한민국 "; } );
		v.push_back( [] { return "Korea"; } );

		printf("%s %s\n", v[0](), v[1]());


		vector< function<void (void)> > funcs;			//vector 에 람다 저장

		funcs.push_back( [](){ std::cout << "Hello" << std::endl; } );
		funcs.push_back( [](){ std::cout << "lambda!" << std::endl; } );

		for(auto& func : funcs) {
			func();
		}
	}


// lambda를 반환하는 함수 -----------------------------------------------

	// void 반환, 인자 없음의 함수타입을 반환한다
	function<void()> FunctionReturn() 
	{
		return [] { cout << "Korea" << endl; };
	}

	int main()
	{
		auto func = FunctionReturn();
		func();
		return 0;
	}

// lambda를 반환하는 함수 // auto 활용 -------------------------------

	std::function<int(void)> multiplyBy2Lambda(int x)
	{
		return [x] { return 2 * x; };
	}

	auto multiplyBy2Lambda(int x)	//함수 리턴 타입 추론을 활용
	{
		return [x] { return 2 * x; };
	}

	auto multiplyBy2Lambda(int x)	//x를 레퍼런스로 캡처하면
	{
		return [&x] { return 2 * x; };		// BUG! 주의
	}

	int main() {

		auto rf = multiplyBy2Lambda(2);		//rf 의 형식 확인하세요.
		int b = rf();
		std::cout << b;
	}


// 템플릿 함수의 인자로써 lambda를 사용 ---------------------------

	#include <iostream>
	#include <algorithm>
	#include <functional>
	using namespace std;

	template<typename TFunc>
	void TemplateFunc(TFunc func)
	{
		func();
	};

	int main()
	{
		auto func = [] { std::cout << "Hello World" << std::endl; };
		
		TemplateFunc(func);  // 람다를 전달받아 실행하는 템플릿 함수

		return 0;
	}