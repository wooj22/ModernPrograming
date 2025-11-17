//printf() -> std::format()

#include <iostream>
#include <format>			//C++20 //C++ 버전은 latest로 변경

int main() 
{
	std::string world{ "world" };

	std::cout << "hello" << world << std::endl;


	const std::string str1{ std::format("{}, {}!", "hello", "world") };	//첫 번째 인수로 서식 문자열, 값, 값 ...

	const std::string str2{ std::format("{1}, {0}!", "world", "hello") };	//argument id 

	const std::string str3{ std::format("he{0}{0}o, {1}!", "l", "world") };
	
	std::cout << str1 << std::endl;
	std::cout << str1 << std::endl;
	std::cout << str1 << std::endl;

	// "5+5=10" 출력해 보세요.
	std::string str = std::format("{0}+{0}={1}", 5, 10);

}
