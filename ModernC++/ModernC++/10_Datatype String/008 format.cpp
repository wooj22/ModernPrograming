// std::format
// 
//		문자열을 포맷팅할 수 있게 해줍니다. C++20
//		C++17 이전의 sprintf/snprintf, std::ostringstream보다 안전하고 편리
//		타입 안전, 가독성, 유연한 포맷
//		C++20에서는 std::format이 UTF-8 문자열과 호환

#include <iostream>
#include <format>			//C++20 //C++ 버전은 latest로 변경

int main()
{
	std::string world{ "world" };
	std::cout << "hello" << world << std::endl;


	std::string s = std::format("Hello, {}!", "World");   // {} 자리 표시자 (positional placeholder)
	std::cout << s << std::endl;  // Hello, World!


	const std::string str1{ std::format("{}, {}!", "hello", "world") };	//첫 번째 인수로 서식 문자열, 값, 값 ...
	const std::string str2{ std::format("{1}, {0}!", "world", "hello") }; //argument id 
	const std::string str3{ std::format("he{0}{0}o, {1}!", "l", "world") };
	std::cout << str1 << std::endl;
	std::cout << str2 << std::endl;
	std::cout << str3 << std::endl;


	//연습) 결과는?

	std::string str4 = std::format("{} {}!", "Hello", "world", "something");
	std::cout << str4 << std::endl;		// not an error // OK, produces "Hello world!"


	//연습) "5+5=10" 출력해 보세요.

	std::string str5 = std::format("{0}+{0}={1}", 5, 10);


	//연습) 소수점 둘째 자리까지 출력

	double pi = 3.14159;
	std::string st = std::format("pi = {:.2f}", pi);
	std::cout << st << std::endl;
	// 출력: x = 42, pi = 3.14
	
}
