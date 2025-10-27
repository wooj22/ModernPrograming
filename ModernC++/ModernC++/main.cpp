#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;


int main()
{
	// 다음 벡터값 중 3의 배수 만 출력하세요.	
	// for_each
	vector<int> v1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	for_each(begin(v1), end(v1), [](const int& i) {if (i % 3 == 0) { cout << i << " "; }});
	cout << endl;


	// vec1 에서 값을 두배하여 vec2에 추가하세요.	
	// transform
	vector<int> v2 = { 5, 3, 1, 12, 4, 24, 8 };
	vector<int> v3(7);
	std::transform(v2.begin(), v2.end(), v3.begin(), [](int n) {return n * 2; });
	for (auto v : v3) cout << v << " ";
	cout << endl;


	// 벡터에서 홀수인 원소 지우고, 지운 갯수를 출력하라. 
	// erase, remove_if
	vector<int> v4 = { 5, 3, 1, 2, 3, 4 };

	int eraseCount = 0;
	v4.erase(remove_if(v4.begin(), v4.end(), [&eraseCount](int& i) {if (i % 2 == 1) { return true; }}), v4.end());
	cout << "erase count : " << eraseCount << endl;


	for (auto v : v4) cout << v << " ";

}