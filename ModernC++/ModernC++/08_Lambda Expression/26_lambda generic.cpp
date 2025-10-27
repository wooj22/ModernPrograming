// lambda expressions	//캡처블럭 사용 정리

#include <iostream>
#include <functional>
using namespace std;


auto multipleValue(int x)
{
	return [x] {return 2 * x; }; // 람다 형식 리턴
}

int main()
{
	// 1. 가장단순한 형식
	auto lambda = [] { cout << "01 : lambda" << endl; };
	lambda();

	// 2. 파라미터를 받는 람다
	auto lambda2 = [](int arg) { cout << "02 : " << arg << endl; };
	lambda2(10);

	// 3. 리턴값이 있는 람다
	auto lambda3 = [](int val1, int val2) -> int {return val1 + val2; };
	// lamdba return 생략하면 컴파일러가 리턴타입을 유추해서 결정
	auto lambda3_2 = [](int val1, int val2) {return val1 + val2; };

	auto sum1 = lambda3(10, 20);
	auto sum2 = lambda3_2(10, 20);
	cout << "03 sum1 : " << sum1 << endl;
	cout << "03 sum2 : " << sum2 << endl;


	// 4. 캡처블럭 사용 (Value)
	int value = 10;
	auto lambda4 = [value] { cout << "04 : " << value << endl; };
	lambda4();

	// 5. 캡쳐블럭 사용 (Const value) : 디폴트로 Const이다. ***
	const int value2 = 20;
	auto lambda5 = [value2] { cout << "05 : " << value2 << endl; };
	lambda5();

	// 6. 캡쳐블럭은 Default가 Const인데 이를 무시하고 값을 변경 하고자 할 때
	int value3 = 30;
	auto lambda6 = [value3]() mutable { value3 += 10; cout << "06 : " << value3 << endl; };
	lambda6();
	cout << "06 : value3 " << value3 << endl;


	// 7. 캡처블럭 사용 (레퍼런스)
	int value4 = 40;
	auto lambda7 = [&value4] { value4 += 10; cout << "07 : " << value4 << endl;  };
	//lambda7();	// 실행되어야 변경됨 //지연 실행
	cout << "07 : " << value4 << endl;

	// 람다의 특성성 레퍼런스가 사라지지 않도록 주의해야 한다.


	// 8. 리턴타입으로써의 람다형식 // lambda를 function pointer처럼 사용가능    

	// ex1)
	function<int(void)> fn = ::multipleValue(10);
	cout << "fn() : " << fn() << endl;
	// ex2)
	auto fn2 = ::multipleValue(20);
	cout << "fn2() : " << fn2() << endl;


	// 9. 제너릭 람다 형식 (C++14, 파라미터 i를 auto로 가능) ***	// C++14
	int value5 = 50;
	auto lambda8 = [](auto i) { return i > 100; };
	cout << lambda8(value5) << endl;

	auto Add = [](auto a, auto b) { return a + b; };
	int		iResult = Add(2, 4);
	float	fResult = Add(2.f, 4.f);


	// 10. 캡쳐블럭 값 초기화 (init capture) ***		// C++14
	int value6 = 60;
	auto lambda9 = [myValue = "My Value :", value6]{ cout << myValue << ", value: " << value6 << endl; };
	lambda9();

	//람다는 캡쳐 절에서 임시 변수를 생성하고 초기화 할 수 있습니다.임시 변수의 타입은 자동 추론 됩니다.
	//init capture는 일반화된 람다 캡쳐(generalized lambda capture) 라고도 한다.


	// 10-1. unique_ptr은 value로는 기본적으로 복사가 되지 않지만... move로 가능'
	auto valuePtr = make_unique<int>(70);
	auto lambda9_2 = [p = std::move(valuePtr)]{ cout << *p << endl; };
	lambda9_2();
}

//제너릭 람다 (Generic Lambda)
//		람다 매개변수 타입에 auto를 쓸 수 있는 람다입니다.

//C++17부터는 auto 반환 타입도 추론되므로, 완전히 제너릭한 함수 형태로 사용 가능합니다.
{
	auto add = [](auto a, auto b) {
		return a + b;
		};

	std::cout << add(2, 3) << '\n';       // int + int
	std::cout << add(2.5, 4) << '\n';     // double + int → double
}

//제너릭 람다 + STL 알고리즘

	#include <algorithm>
	#include <vector>
	#include <iostream>

	int main() {
		std::vector<int> v = { 1, 2, 3, 4, 5 };

		std::for_each(v.begin(), v.end(), [](auto x) {
			std::cout << x * 2 << ' ';
			});
	}
	
//제너릭 람다 + Perfect Forwarding(C++14 이상)

	#include <utility>
	#include <iostream>

	auto forwarder = [](auto&& arg) {
		using T = decltype(arg);
		std::cout << "Forwarded type: " << (std::is_lvalue_reference_v<T> ? "Lvalue" : "Rvalue") << '\n';
		return std::forward<decltype(arg)>(arg);
		};

	int main() {
		int x = 10;
		forwarder(x);          // Lvalue
		forwarder(42);         // Rvalue
	}


// init capture ------------------------------------------------------------------
//		일반화된 람다 캡쳐(generalized lambda capture)
//		람다의 캡처 구문 안에서 변수 선언과 초기화를 동시에 진행
// 
//		[변수명 = 초기화식] 형태로 캡처하면
//		람다 내부에서 그 변수를 자유롭게 사용할 수 있습니다.

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>
#include <iostream>
using namespace std;

int main() {

	{
		int x = 5;
		int y = 10;

		auto f = [sum = x + y, str = std::string("Hello")]() {
			std::cout << str << " " << sum << '\n';
			};

		f();		// Hello 15
	}
	
	//move 캡처	

	//람다는 캡쳐 절에서 임시 변수를 생성하고 초기화 할 수 있습니다. 임시 변수의 타입은 자동 추론 됩니다.
	{
		std::string a = { "wolf" };
		[tstr = std::move(a)] {
			cout << tstr;
		}();    // move 로 a 를 가져와 wolf를 출력하고 삭제함 ( tstr은 임시변수라 삭제 됨! )

		int x = 4;
		auto y = [&r = x, x = x + 1]()->int
		{
			r += 2;    // r == 6
			return x * x;
		}();	// 스코프 바깥에있는 x는 6으로 업데이트 되고, y는 25가 됨
	}

	//std::unique_ptr 객체를 std::move 를 통해 캡쳐하여, 이를 람다에 쓸 수 있는 점이 이점.
	{
		vector<int> nums = {1, 2, 3};
		unique_ptr pNums = make_unique<vector<int>>(nums);
		auto a = [ptr = move(pNums)]()
		{
			// ptr
		};
	}
}
