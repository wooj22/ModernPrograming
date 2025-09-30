// 유니폼 초기화 (균일한 초기화) (중괄호 초기화)

#include <iostream>
#include <vector>
using namespace std;

struct T {
	int i;
	string v;
	bool b;
};

class C {
public:
	int a;
};

int main() 
{
	int a(0);			// 초기치를 괄호로 감산 예
	int b = 0;			// 초기치를 "=" 다음에 지정한 예
	int c{ 0 };			// 초기치를 중괄호로 감싼 예
	int d = { 0 };		// "="와 중괄호로 초기치를 지정한 예


	//구조체 //중괄호 초기화 활용 ------------------------------------
	T t{ 1, "hello", false };


	//클래스의 경우 ------------------------------------------------- 
	//		클래스의 생성자 인수를 () 소괄호에 넣는 대신 {} 중괄호에 넣어 초기화할 수 있다.
	//		이제부터는 함수 호출과 헷갈리지 않는 초기화가 가능

	C c1();
	C c2{}; c2.a = 0;


	// vector 객체 생성에 중괄호 사용하기 ------------------------------------
	std::vector<int> v{ 1, 3, 5 };

	//괄호와 중괄호의 선택이 의미있는 차이를 만드는 예는
	//		인수 두 개로 std::vector<수치 타입>을 생성하는 것이다.

	std::vector<int> v1(10, 20);    // std::initializer_list 생성자가 아님
									// 모든 요소의 값이 20인, 요소 10개짜리 std::vector가 생성됨

	std::vector<int> v2{ 10, 20 };  // std::initializer_list 생성자를 사용:
									// 값이 각각 10과 20인 두 요소를 담은 std::vector가 생성됨


	//복사할 수 없는 객체( 이를테면 std::atomic )는 
	//		중괄호나 괄호로는 초기화할 수 있지만, "="로는 초기화할 수 없다.
	//std::atomic<int> ai1{ 0 };		// OK
	//std::atomic<int> ai2(0);		// OK
	//std::atomic<int> ai3 = 0;		// 오류! - 이전 버전

	return 0;
}

/*
	// 비정적(non-static) 데이터 멤버의  기본 초기화 값을 지정할 때 사용 가능

	class Widget {
	private:
		int x = 0;		// OK
		int y{ 0 };		// OK, x의 기본값은 0
		//int z(0);		// 오류!
	public:
		Widget() {}
		Widget(int a) {}
	};

	int main()
	{
		Widget w1(10);	// 인수 10으로 Widget의 생성자를 호출
		Widget w2();	// 가장 성가신 구문 해석! Widget의 기본 생성자를 호출하는 것이 아니라,Widget을 돌려주는, w2라는 이름의 함수를 선언
		Widget w3{};	// 인수 없이 Widget의 생성자를 호출
	}
*/


 
//생성자 호출에서 std::initializer_list 매개변수가 관여하지 않는 한 괄호와 중괄호의 의미는 같다.
//  
//	그러나 생성자 중 하나 이상이 std::initializer_list 타입의 매개 변수를 선언한다면, 
//  중괄호 초기화 구문은 std::initializer_list 를 받는 오버로딩 버전을 "강하게" 선호한다. ***

	#include <iostream>
	using namespace std;

	class Widget {
	public:
		Widget(int i, bool b) { cout << "int, bool" << endl; }
		Widget(int i, double d) { cout << "int, double" << endl; }

		//Widget(std::initializer_list<long double> il) {cout << "initializer_list" << endl;}		// 추가됨
	};

	int main()
	{
		Widget w1(10, true);	// 첫 생성자를 호출
		Widget w2{ 10, true };	// 역시 첫 생성자를 호출		//추가 후 std::initializer_list 생성자 호출
		Widget w3(10, 5.0);		// 둘째 생성자를 호출
		Widget w4{ 10, 5.0 };	// 역시 둘째 생성자를 호출	//추가 후 std::initializer_list 생성자 호출
	}

//보통은 복사생성이나 이동생성이 일어났을 상황에서도 
//		std::initializer_list 생성자가 끼어들어서 기회를 가로챈다.  
//		VS, GCC, Clang에서 각각 컴파일 & 실행 결과를 비교해 봐여함 - VS는 복사생성자 호출됨

	#include <iostream>
	#include <string>
	#include <vector>
	using namespace std;

	class Widget {
	public:
		Widget(int i, double d) { cout << "int, double" << endl; }
		Widget(std::initializer_list<long double> il) { cout << "initializer_list" << endl; }
		Widget(const Widget& d) { cout << "const Widget&" << endl; }
		Widget( Widget&& d) { cout << "Widget&&" << endl; }
		//operator float(void) const { return 0.1f; }			// float 로
	};

	int main()
	{
		Widget w3{ 10 };			//std::initializer_list 우선
		Widget w4{ 10, 5.0 };		//std::initializer_list 우선

		Widget w5(w4);				// 괄호 사용, 복사 생성자 호출
		Widget w6{ w4 };			// 중괄호 사용, std::initializer_list 생성자 호출	// (w4가 float으로 변환되고 그 float이 long double로 변환됨)

		Widget w7(std::move(w4)); // 괄호 사용, 이동 생성자 호출
		Widget w8{ std::move(w4) }; // 중괄호 사용, std::initializer_list 생성자 호출 // (w6에서와 마찬가지의 변환들이 일어남)
	}


//컴파일러가 자신의 결심을 포기하고 보통의 오버로딩 해소로 물러나는 경우는 
//		중괄호 초기치의 인수 타입들을 std::initializer_list 타입으로 변환하는 방법이 '아예 없을 때' 뿐이다.

	#include <iostream>
	using namespace std;

	class Widget {
	public:
		Widget(int i, bool b) { cout << "int, bool" << endl; }
		Widget(int i, double d) { cout << "int, double" << endl; }

		// 이제는 std::initializer_list의 원소 타입이 std::string
		Widget(std::initializer_list<std::string> il) { cout << "initializer_list" << endl; }
	};

	int main()
	{
		Widget w1(10, true);   // 괄호 사용, 첫 생성자를 호출
		Widget w2{ 10, true }; // 중괄호 사용, 이제는 첫 생성자 호출
		Widget w3(10, 5.0);    // 괄호 사용, 둘째 생성자를 호출
		Widget w4{ 10, 5.0 };  // 중괄호 사용, 이제는 둘째 생성자 호출

		//int, bool, double을 std::string으로 암묵적으로 변환할 방법이 없기 때문이다.
	}


//빈 중괄호 부호를 사용하면 어떻게 받아들일까 ? 
//		표준에 따르면 기본 생성자가 호출된다. ***
//		즉 빈 중괄호 쌍은 빈 std::initializer_list가 아니라 '인수 없음'을 뜻한다.

	class Widget {
	public:
		Widget(void);
		Widget(std::initializer_list<int> il);    // std::initializer_list 생성자
	};

	{
		Widget w1;		// 기본 생성자를 호출
		Widget w2{};	// 역시 기본 생성자를 호출
		Widget w3();	// 가장 성가신 구문 해석! 함수 선언임!
	}

//빈 std::initializer_list로 std::initializer_list 생성자를 호출하고 싶다면,
//	다음처럼 빈 중괄호 쌍을 괄호로 감싸거나 빈 중괄호 쌍을 또 다른 중괄호 쌍으로 감싸면 된다.

		Widget w4({});
		Widget w5{ {} };

