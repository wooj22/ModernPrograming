#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Person
{
public:
	Person(std::string name) : m_name{ std::move(name) } {}
	const std::string& getName() const { return m_name; }
private:
	std::string m_name;
};

int main()
{
	//리턴 타입 추론은 레퍼런스와 const를 지워버립니다. //리턴 타입은 string으로 추론
	auto lambda1 = [](const Person& person) { return person.getName(); };

	//후행 리턴 타입을 decltype(auto)처럼 혼합하여 사용하면 추론된 타입을 실제 getName()의 타입과 일치시킬 수 있습니다. ***
	auto lambda2 = [](const Person& person) -> decltype(auto) { return person.getName(); };


	// implicit return type
	auto foo = [] { return 3.14; };

	// explicit return type
	auto bar = []() -> float { return 3.14f; };

	// warning. double에서 float으로 암시적 형변환.
	float x = foo();

	// OK
	float y = bar();
}

/*
// lambda를 반환하는 함수 ***

	std::function<int(void)> multiplyBy2Lambda(int x)		//function
	{
		return [x] { return 2 * x; };
	}

	auto multiplyBy2Lambda(int x)							//함수 리턴 타입 추론을 활용
	{
		return [x] { return 2 * x; };
	}

	auto multiplyBy2Lambda(int x)	//x를 레퍼런스로 캡처하면
	{
		return [&x] { return 2 * x; };		// BUG! //int x 는 사라짐
	}

	int main()
	{
		int a = 1;

		auto fff = multiplyBy2Lambda(a);
		//std::function<int(void)>  fff = multiplyBy2Lambda(a);

		std::cout << fff();

		
	}
*/

//반환 형은 std::function 혹은 auto 사용
//반환 형을 적지 않으면 컴파일러가 추론한다. 방법은 일반 함수의 리턴 타입을 추론할때와 같다. ***


//변수를 캡처하지 않는 람다는 ([]의 안에 없음) 함수 포인터로 변환 할 수 있습니다.
//그러나 람다의 실제 유형은 함수 포인터가 아닙니다. 지정되지 않은 functor 유형입니다. ***


//컴파일러는 람다 표현식을 이름 없는 펑터(함수 객체)로 변환한다.
//캡처한 변수는 이 펑터의 데이터 멤버가 된다. 값으로 캡처한 변수는 펑터의 데이터 멤버로 복제 된다.
//펑터마다 함수 호출 연산자인 operator()가 구현돼 있다. 람다 표현식의 경우 이 연산자는 기본적으로 const로 설정.
//따라서 non-const 변수를 람다 표현식에 값으로 캡처해도 람다 표현식 안에서 이 값의 복제본을 수정 할 수 없다.