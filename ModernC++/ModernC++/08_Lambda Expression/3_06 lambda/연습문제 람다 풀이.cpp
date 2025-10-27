
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
// 람다함수로 표현하세요 ---------------------------

	std::string GetHello()	{
		return "Hello ";
	}

	//[]() -> string { return "Hello "; }
*/

int main()
{
	// "Hello World" 를 리턴하는 함수를 람다로 만들고, 실행하여 출력하여 보세요
	
		cout << []() { return "Hello World"; }();


	//변수 level 입력값이 10보다 크면 "ok" 아니면 "fail" 을 출력하기
	int level; 
	cin >> level;

		[](int a) {
			if (a > 10) cout << "ok" << endl;
			else		cout << "fail" << endl;
		}(level);


	// 정수 number 를 입력받고, "10보다 크면 출력"하도록 람다로 표현하세요.  // [] 캡쳐사용.
	int number;
	cin >> number;

		[number]() {if (number > 10) cout << number; }();


	//다음 코드의 출력값은?
	function<int(int)> func = [](int a)->int {return a + 1; };
	cout << func(1) << endl;


	//다음 벡터값 중 3의 배수 만 출력하세요.					// for_each		//요소 하나를 받아 함수 실행
	vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

		for_each(begin(v), end(v), [](const int& i) { if (i % 3 == 0) cout << i; }); 
		cout << endl;


	// vec1 에서 값을 두배하여 vec2에 추가하세요.				// transform	//요소를 받아 함수 실행한 결과를 저장
	std::vector<int> vec1 = { 5, 3, 1, 12, 4, 24, 8 };
	std::vector<int> vec2(7);

		std::transform(vec1.begin(), vec1.end(), vec2.begin(),  //std::back_inserter(vec2)
			[](int n) { return n * 2; });
		for (auto e : vec2) { cout << e << " "; }

	// 벡터에서 홀수인 원소 지우고, 지운 갯수를 출력하라.		//erase, remove_if		// [] 캡쳐사용.
	std::vector<int> vec{ 5, 3, 1, 2, 3, 4 };

		int num_erased = 0;
		vec.erase(std::remove_if(vec.begin(), vec.end(),
			[&num_erased](int i) {
				if (i % 2 == 1) { num_erased++; return true; }
				return false;
			}),
			vec.end());
		std::cout << "erase num : " << num_erased << std::endl;
		for (auto e : vec)	std::cout << e << std::endl;
	
	// 문자열의 소문자를 대문자로 변경하는 함수 를 만들어 보세요. 
	
	// 문자열과 위 함수를 매개변수로 전달받아,  그 함수로 변경된 값을 리턴하는 함수를 작성하라.
	
}

/*
	#include <iostream>
	#include <functional>
	#include <algorithm>
	using namespace std;

	string StrToUpper(string s)
	{
		std::transform(s.begin(), s.end(), s.begin(),
			[](unsigned char c) { return std::toupper(c); } // correct
		);
		return s;
	}

	int main() {

		string s = [](string s, function<string(string)> fn) { return fn(s); } ("abcASD", StrToUpper);
		std::cout << s;
	}
*/