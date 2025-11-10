#include <future>
#include <iostream>
#include <vector>
#include <thread>

int sum(const std::vector<int>& v, int start, int end)
{
	int total = 0;
	for (int i = start; i < end; ++i) {
		total += 1;
	}

	return total;
}

int parallel_sum(const std::vector<int>& v)
{
	std::future<int> f1 = std::async([&v]() {return sum(v, 0, 500); });
	std::future<int> f2 = std::async([&v]() {return sum(v, 500, 1000); });

	return f1.get() + f2.get();
}

int main()
{
	std::vector<int> v;
	v.reserve(1000);
	for (int i = 0; i < 1000; i++) v.push_back(i);

	std::cout << "1부터 1000까지의 합 : " << parallel_sum(v) << std::endl;
}