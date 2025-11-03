#include <iostream>
#include <vector>
#include <thread>
#include <Windows.h>
using namespace std;

void worker(vector<int>::iterator start, vector<int>::iterator end, int* result)
{
	int sum = 0;
	
	for (auto itr = start; itr < end; ++itr)
	{
		sum += *itr;
	}

	*result = sum;
}

int main()
{
	// 합계를 구할 데이터
	vector<int> data(10000);
	for (int i = 0; i < 10000; i++) data[i] = i + 1;

	// 구간합을 저장할 벡터
	vector<int> resultPart(4);
	int sums = 0;

	// thread
	vector<thread> workers;

	for (int i = 0; i < 4; i++)
		workers.push_back(thread(worker, data.begin() + i * 2500, data.begin() + i * 2500 + 2500, &resultPart[i]));

	// works
	for (int i = 0; i < 4; i++)
		workers[i].join();

	// result
	for (int i = 0; i < 4; i++)
		sums += resultPart[i];

	cout << sums;
}
