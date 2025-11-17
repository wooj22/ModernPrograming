#include <iostream>
#include <string>
using namespace std;

void main()
{
	string base = "hello world!";
	//base.at(0); // 'h'							//at(0)
	//base.at(1); // 'e'

	if (base.find("world!") != string::npos)		//find, string::npos
	{
		std::cout << "find" << endl;	// "world!"라는 문자열을 찾았을 때의 동작
	}

	string s1("Hello"); 
	string s2(" World ");
	s1 += " Wow! ";									// +=
	s2 += " ^.^ ";
	std::cout << s1 << endl;
	std::cout << s2 << endl;

	s1.append(s2);									//append   s1에 s2를 덧붙임	
	std::cout << s1 << endl;
	std::cout << s2 << endl;

	//for (auto iter = s1.begin(); iter != s1.end(); ++iter)	
	//	s2.push_back(*iter);  // s2에 s1를 덧붙임

	string a = "I am string one! ;)";
	string b = "string";
	if (a.compare(b) == 0)							//compare  // 두 문자열이 같을 때	
	{ }
	else if (a.compare(b) < 0) // a가 b보다 사전순으로 앞일 때 
	{ }
	else if (a.compare(b) > 0) // a가 b보다 사전순으로 뒤일 때 
	{ }


}
