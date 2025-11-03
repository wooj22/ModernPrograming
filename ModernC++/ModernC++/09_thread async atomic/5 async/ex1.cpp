//출력순서를 확인하세요.

#include <iostream>
#include <future>
using namespace std;

int main()
{
	auto f1 = std::async([] {
		cout << "1";
		this_thread::sleep_for(chrono::seconds(2));
		cout << "2";
		});

	std::async([] {
		cout << "3";
		this_thread::sleep_for(chrono::seconds(1));
		cout << "4";
		});

	cout << "5";
}