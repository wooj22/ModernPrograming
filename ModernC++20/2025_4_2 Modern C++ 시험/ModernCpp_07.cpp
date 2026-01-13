// Concept
// 
// 아래 Printable 컨셉은 반환 타입 제약이 없어서 side-effect 표현이 불분명합니다. 
// 더 정확하게 수정하세요.


#include <iostream>

template <typename T>
concept Printable = requires(T a) {
	std::cout << a;
};

template <Printable T>
void Log(const T& v) {
	std::cout << v << std::endl;
}

int main() {
	Log(2017);       // ok
	Log(3.14f);      // ok
	Log("Hello");    // ok
	//log(std::vector<int>{1,2,3}); // error
	return 0;
}