#include <iostream>
#include <vector>
using namespace std;

//프로그래밍 패러다임
// 
//명령형 프로그래밍 : 무엇(What)을 할 것인지 나타내기보다 어떻게(How) 할 건지를 설명하는 방식
//	절차지향 프로그래밍 : 수행되어야 할 순차적인 처리 과정을 포함하는 방식 (C, C++)
//	객체지향 프로그래밍 : 객체들의 집합으로 프로그램의 상호작용을 표현 (C++, Java, C#)
// 
//선언형 프로그래밍 : 어떻게 할건지(How)를 나타내기보다 무엇(What)을 할 건지를 설명하는 방식
//	함수형 프로그래밍 : 순수 함수를 조합하고 소프트웨어를 만드는 방식 (클로저, 하스켈, 리스프)


//객체지향 프로그래밍 - OOP - 추상화, 캡슐화, 상속성, 다형성
// 
//  프로그래밍에서 필요한 데이터를 추상화시켜 상태와 행위를 가진 객체를 만들고 
//  그 객체들 간의 유기적인 상호작용을 통해 로직을 구성하는 프로그래밍 방법
// 
//	추상화(Abstraction), 캡슐화(Encapsulation), 정보은닉(Information Hiding), 
//  상속성(Inheritance), 다형성(Polymorphism) 등의 특징
//
//	1. f(o);	// 절차지향
//	2. o.f();	// 객체지향


//함수형 프로그래밍 - Functional Programing
// 
//  순수 함수(pure function)를 조합하고, 
//  공유 상태(shared state), 변경 가능한 데이터(mutable data) 및 부작용(side-effects)을 피하여 프로그래밍하는 패러다임
// 
//  순수 함수(Pure Function), 불변성(Immutable), 
//  참조 투명성(Referential Transparency), 게으른 평가(Lazy Evaluation)등의 특징 
// 
//	함수를 변수나 객체처럼 데이타로 다루는 방법 
// 
//	C++11 에서는 Lambda expression 도입하여 지원함.


//최근 언어들은 캡슐화나 상속같은 기능은 모두 지원하는 추세, 주목할 특징은 다형성, 참조투명성.
// 
//객체지향 프로그래밍: 
//		함수 호출의 다형성을 사용할 때, 호출자의 코드가 피호출자의 코드에 의존하지 않아도 되도록 하는 기술. 
//		강하게 비결합된(Strongly decoupled) 시스템을 만들어주는 장점, 유지보수와 개발이 편한 시스템.
// 
//함수형 프로그래밍: 
//		참조 투명성 – 값을 다시 할당하지 않는 것. f(a) == f(b) when a == b
//		시스템을 예상 가능하게 만들어주기 때문에 바람직, 
//		시스템을 이해하기 쉽고, 개발하기 쉽게 만들고. 스레드 경쟁상태 같은 동시성 관련 문제도 해결.

/*
// 자바스크립트 예제)

	function plus(a) {
		let localVar = a;
		return function(x) { return localVar + x; }
	}

	let plus3 = plus(3);		//3을 더해주는 함수 //클로저
	plus3(10)					//결과는 13
*/

//C++ 은 클래스로 이를 구현 (함수 객체 활용) ------------------------------

#include <iostream>
#include <vector>
using namespace std;

class Plus 
{
	int localVar;
public:
	explicit Plus(int a) : localVar{ a } {}
	int operator()(int x) const
	{
		return localVar + x;
	}
};

int main()
{
	Plus plus3{ 3 };						// 3을 더하는 함수
	Plus plus5{ 5 };

	std::cout << plus3(10) << std::endl;	//대입 없이 기능 호출
	std::cout << plus5(10) << std::endl;

	//람다로 간단히 표현 가능

	//auto addN = [](int N) { return [N](int a) { return a + N; }  }
	//auto add3 = addN(3);
	//auto add5 = addN(5);

	return 0;
}
