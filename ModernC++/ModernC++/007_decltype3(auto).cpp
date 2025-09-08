// 템플릿 함수에서 리턴 타입

#include <iostream>
#include <vector>
using namespace std;


//어떤 객체의 타입이 템플릿 인자들에 의해서 결정되는 경우 ----------------------------------------

template <typename T, typename U>
void add(T t, U u, ??? result) {					// 무슨 타입이 와야 할까요? 
	*result = t + u;
}

template <typename T, typename U>
void add(T t, U u, decltype(t + u)* result) {		//decltype 로 해결
	*result = t + u;
}

//어떤 객체의 타입이 템플릿 인자들에 의해서 결정되는 경우 //함수의 리턴값 있다면

template <typename T, typename U>
decltype(t + u) add(T t, U u) {					 // error	//앞에서 미리 알 수 없다.
	return t + u;
}

template <typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {			//C++11  //함수의 리턴값을 인자들 정의 부분 뒤에 추가 //후행 리턴타입
	return t + u;
}

template <typename T, typename U>
decltype(auto) add(T t, U u) {					//C++14  //decltype(auto)
	return t + u;
}

//template<typename T, typename U>
//decltype(auto) myFunc(T&& t, U&& u) { return forward<T>(t) + forward<U>(u); };



//C++14 에선 모든 람다와 모든 함수에서 리턴 타입을 추론할 수 있다. auto -------------------------

template<typename T, typename U>
auto Plus(T&& lhs, U&& rhs)			//보편참조 ***
{
	return (std::forward<T>(lhs) + std::forward<U>(rhs));
};

int main()
{
	string A("abc");
	string B("def");
	cout << Plus(A, B) << endl;     //abcdef
	cout << Plus(10, 20) << endl;   //30
}

// auto가 자동으로 리턴 타입을 결정해줍니다.
//		하지만 auto는 다른 키워드나 타입이 붙지 않을 시 복사본이 된다

	#include <iostream>
	using namespace std;

	class c {
		int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	public:
		int& operator[](int i) { return arr[i]; }
	};

	template<typename T>
	auto changearr(T& c, int index) {		//auto
		return c[index];
	};

	int main() {		
		c myclass;
		//changearr(myclass, 3) = 100;		// 이런, 복사값이기 때문에 변하지 않아요.
		auto i = changearr(myclass, 3);
		i = 100;
		cout << myclass[3];
	}

// decltype(auto) ------------------------------------------------------------------------------

//	 리턴 타입을  decltype(auto) 로 하면,
//   auto의 복사본을 반환형으로 하는게 아닌, c[index]를 가지고 반환 추론을 하기 때문에 int& 형으로 반환
//   T가 rvalue (임시객체) 로 들어올 가능성도 있기 때문에, 꼭 universal reference 로 받아야 합니다.

	#include <iostream>
	using namespace std;

	class c {
		int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	public:
		int& operator[](int i) { return arr[i]; }
	};

	template<typename T>
	decltype(auto) GetArr(T&& c, int index) {	//decltype(auto)
		return std::forward<T>(c)[index];
	};

	int main()
	{
		//auto i = GetArr(c(), 3);		// i는 int 형입니다.
		//cout << i << endl;			// 이러면 c의 3번째 배열인 4가 출력되겠죠?

		c myclass;
		GetArr(myclass, 3) = 100;
		cout << myclass[3];
	}


// auto가	     값에 상응하는 타입을 추론시켜주는 키워드라면,
// decltype은    값으로부터 타입을 추출해 낼 수 있는 키워드
//               템플릿 인자에 기반한 generic programming의 어려움을 해소하기 위해 도입

// auto 반환 ( C++14 )
//		후행 반환 형식을 지정해 주지 않아도, 컴파일 에러없이 반환 타입을 추론
//		하지만 auto 타입은 템플릿 타입 추론에 의해 결정된다
//		이를 방지하려면, decltype으로 (auto)를 감싸주는 것이 필요 ***

// decltype(auto)
//
//      템플릿을 설계하는데 있어, 
//      그냥 auto 값타입 리턴을 하고 decltype 으로 리턴타입을 명시하지 않게 되면, 위험한 코드가 발생할 수 있습니다.
//
//  실제 함수가 reference를 리턴할 떄 auto로 리턴값을 받으면, 
//			reference성이 사라져버리고 임시객체가 리턴되며, 
//
//	해당 함수 리턴값을 lvalue reference로 받는다면 
//			rvalue를 담을 수 없어 컴파일 에러가 발생합니다.
// 
//	auto&로 리턴 할 수도 있겠지만, 
//			이는 함수 stack내 변수에 생성된 객체를 리턴하는 경우에도 문제가 발생합니다.
// 
//	따라서 이런경우 decltype으로 리턴 타입을 명시해줘야 합니다.

*/

