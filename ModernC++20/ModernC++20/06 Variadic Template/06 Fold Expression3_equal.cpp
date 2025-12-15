//예시 // equal 함수를 가변으로 만들어 보기.

#include <iostream>
using namespace std;

template <typename T1, typename T2>
constexpr bool equal_two(T1 const& a1, T2 const& a2) {
	return (a1 == a2);
}

// parameter 1개 이상 필요
template <typename A0, typename... Args>
constexpr bool equal_var(A0 const& a0, Args const&... args) {
	return ((args == a0) && ...);				// && 연산자
}

int main()
{
	cout << boolalpha;		//print true or false

	cout << equal_two(1, 1) << '\n';			// true
	cout << equal_two(1.0, 1.1) << '\n';		// false
		
	cout << equal_var(1) << '\n';				// true
	cout << equal_var(0, 0, 0) << '\n';			// true
	cout << equal_var(1, 1, 1, 1, 1) << '\n';	// true
	cout << equal_var(1, 2, 3, 4, 5) << '\n';	// false
	// cout << equal_var() << '\n';	// compile error

	return 0;
}