//type_traits 라이브러리 //SFINAE 활용 예시
 
//std::void_t 를 이용해 클래스에 특정 멤버가 있는지 확인하기
//		"타입이 존재하는지"를 검사하기 위한 SFINAE 전용 도구, 존재성 검사(detection idiom)에 특화.

#include <iostream>
#include <type_traits>

template<typename, typename = void>
struct has_member_foo : std::false_type { };

template<typename T>
struct has_member_foo<T, std::void_t<decltype(std::declval<T>().foo)>> : std::true_type { };

class Bar {
public: int bar;
};

class Foo {
public:
	explicit Foo(int); int foo;
};

int main()
{
	using namespace std;
	cout << std::boolalpha <<
		has_member_foo<int>::value << " " <<
		has_member_foo<Bar>::value << " " <<
		has_member_foo<Foo>::value <<
		endl;
	return 0;
}

//T를 int라고 가정합니다.
//	has_member_foo<int>는 has_member_foo<int, void>
//특수화 버전이 있는지 찾아봐야
//	has_member_foo<T, std::void_t<decltype(std::declval<T>().foo)>>

//std::void_t<decltype(std::declval<T>().foo)> 에서
//  std::declval<T>는 T&를 반환하는 녀석입니다.
//  (&T).foo가 되는데 T가 뭐랬죠 ? int. int에 foo가 있나요 ? 없죠. 컴파일러도 그 사실을 여기서 알게 됩니다.
//  그럼 컴파일 에러를 띄울까요 ?

//SFINAE 규칙에 의해, 템플릿 특수화를 찾는 과정에서 이런 에러가 발생해도 컴파일 에러를 띄우지 않는다.
//  에러를 띄우지 않는 대신 에러가 난 특수화 버전을 무시.
//  고로 남은건 처음의 녀석, std::false_type를 상속하는 녀석뿐입니다.
//  컴파일러는 해당 버전을 선택하고 has_member_foo<int>::value는 false가 됩니다

//이번엔 T를 Foo라고 가정합니다
//  has_member_foo<Foo, std::void_t<decltype(std::declval<T>().foo)>> 는
//  has_member_foo<Foo, void> 가 됩니다. 특수화 버전을 찾았습니다.
//  이 버전은 std::true_type를 상속받고 있으므로 has_member_foo<Foo>::value는 true가 됩니다.


//연습) 다음 코드의 출력은 ?

#include <iostream>
#include <type_traits>
#include <vector>

template <typename, typename = std::void_t<>>
struct has_value_type : std::false_type {};

template <typename T>
struct has_value_type<T, std::void_t<typename T::value_type>> : std::true_type {};

int main()
{
	std::cout << has_value_type<std::vector<int>>::value << "\n";   //??? 
	std::cout << has_value_type<int>::value << "\n";                //??? 
}

