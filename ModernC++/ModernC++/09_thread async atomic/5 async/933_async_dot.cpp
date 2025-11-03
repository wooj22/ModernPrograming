//inner_product 병렬처리 속도 측정 

#include <iostream>
#include <chrono>
#include <mutex>	
#include <utility>
#include <vector>	
#include <atomic>
#include <numeric>		// std::inner_product
#include <random>
#include <execution>	// parallel execution
#include <future>
#include <thread>

using namespace std;

mutex mtx;

void dotProductNaive(const vector<int>& v0, const vector<int>& v1,
	const unsigned int start, const unsigned int end, unsigned long long& sum)
{
	for (unsigned int i = start; i < end; ++i)
	{
		sum += (v0[i] * v1[i]);
	}
}

void dotProductLock(const vector<int>& v0, const vector<int>& v1,
	const unsigned int start, const unsigned int end, unsigned long long& sum)
{
	//cout << "Thread Start" << endl;
	for (unsigned int i = start; i < end; ++i)
	{
		std::scoped_lock lock(mtx);
		sum += (v0[i] * v1[i]);
	}
	//cout << "Thread End" << endl;
}

void dotProductAtomic(const vector<int>& v0, const vector<int>& v1,
	const unsigned int start, const unsigned int end, atomic<unsigned long long>& sum)
{
	for (unsigned int i = start; i < end; ++i)
	{
		sum += (v0[i] * v1[i]);
	}
}

auto dotProductFuture(const vector<int>& v0, const vector<int>& v1,
	const unsigned int start, const unsigned int end)
{
	int sum = 0;
	for (unsigned int i = start; i < end; ++i)
		sum += (v0[i] * v1[i]);
	return sum;
}


int main()
{
	const long long numData = 100'000'000;
	const unsigned int numThread = 4;
	// thread 개수 늘린다고 degree of multithreading이 높아지지는 않음

	vector<int> vec0, vec1;
	vec0.reserve(numData);
	vec1.reserve(numData);

	std::random_device seed;
	std::mt19937_64 makerand(seed());
	std::uniform_int_distribution<> range(1, 10);

	for (long long i = 0; i < numData; ++i)
	{
		vec0.push_back(range(makerand));
		vec1.push_back(range(makerand));
	}

	cout << "실험 1번 - std::inner_product\n";
	{
		const auto sta = std::chrono::steady_clock::now();		// 시간 측정 시작
		const auto sum = std::inner_product(vec0.begin(), vec0.end(), vec1.begin(), 0ull);
		// 두 벡터의 개수가 같다고 가정하므로 vec1은 begin만 있어도 되며 ull은 unsigned long long의 약자
		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << "연산에 소요된 시간 = " << dur.count() << '\n';
		cout << "결과값 = " << sum << '\n';
		cout << '\n';
	}

	cout << "실험 2번 - Naive\n";
	{
		const auto sta = std::chrono::steady_clock::now();

		unsigned long long sum = 0;

		vector<std::thread> threads;
		threads.resize(numThread);

		const unsigned int numPerThread = numData / numThread;
		for (unsigned int t = 0; t < numThread; ++t)
			threads[t] = std::thread(dotProductNaive, std::ref(vec0), std::ref(vec1),
				t * numPerThread, (t + 1) * numPerThread, std::ref(sum));
		for (unsigned int t = 0; t < numThread; ++t)
			threads[t].join();

		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << "연산에 소요된 시간 = " << dur.count() << '\n';
		cout << "결과값 = " << sum << '\n';
		cout << '\n';
	}

	cout << "실험 3번 - Lockguard\n";
	{
		const auto sta = std::chrono::steady_clock::now();

		unsigned long long sum = 0;

		vector<std::thread> threads;
		threads.resize(numThread);

		const unsigned int numPerThread = numData / numThread;
		for (unsigned int t = 0; t < numThread; ++t)
			threads[t] = std::thread(dotProductLock, std::ref(vec0), std::ref(vec1),
				t * numPerThread, (t + 1) * numPerThread, std::ref(sum));
		for (unsigned int t = 0; t < numThread; ++t)
			threads[t].join();

		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << "연산에 소요된 시간 = " << dur.count() << '\n';
		cout << "결과값 = " << sum << '\n';
		cout << '\n';
	}

	cout << "실험 4번 - Atomic\n";
	{
		const auto sta = std::chrono::steady_clock::now();

		atomic<unsigned long long> sum = 0;

		vector<std::thread> threads;
		threads.resize(numThread);

		const unsigned int numPerThread = numData / numThread;
		for (unsigned int t = 0; t < numThread; ++t)
			threads[t] = std::thread(dotProductAtomic, std::ref(vec0), std::ref(vec1),
				t * numPerThread, (t + 1) * numPerThread, std::ref(sum));
		for (unsigned int t = 0; t < numThread; ++t)
			threads[t].join();

		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << "연산에 소요된 시간 = " << dur.count() << '\n';
		cout << "결과값 = " << sum << '\n';
		cout << '\n';
	}

	cout << "실험 5번 - Future\n";
	{
		const auto sta = std::chrono::steady_clock::now();

		unsigned long long sum = 0;

		vector<std::future<int>> futures;
		futures.resize(numThread);

		const unsigned int numPerThread = numData / numThread;
		for (unsigned int t = 0; t < numThread; ++t)
			futures[t] = std::async(dotProductFuture, std::ref(vec0), std::ref(vec1),
				t * numPerThread, (t + 1) * numPerThread);
		for (unsigned int t = 0; t < numThread; ++t)
			sum += futures[t].get();

		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << "연산에 소요된 시간 = " << dur.count() << '\n';
		cout << "결과값 = " << sum << '\n';
		cout << '\n';
	}
	// TODO : Future의 divide and conquer 방식은 thread에서도 구현해보자.
	// async 대신에 thread와 promise를 사용해서 future을 사용해보자.

	cout << "실험 6번 - promise\n";
	{
		const auto sta = std::chrono::steady_clock::now();

		vector<std::promise<int>> prom;
		vector<std::future<int>> future;
		vector<std::thread> threads;
		prom.resize(numThread);
		future.resize(numThread);
		threads.resize(numThread);

		unsigned long long sum(0);
		unsigned numPerThread = numData / numThread;
		for (unsigned i = 0; i < numThread; ++i)
		{
			future[i] = prom[i].get_future();
			unsigned long long tempSum(0);
			threads[i] = std::thread([&](std::promise<int>&& prom)
				{
					std::scoped_lock lock2(mtx);

					for (unsigned int j = 0; j < numPerThread; ++j)
						tempSum += (vec0[j] * vec1[j]);
					prom.set_value(tempSum);
				}, std::move(prom[i]));
			threads[i].join();
		}
		for (unsigned int t = 0; t < numThread; ++t)
			sum += future[t].get();

		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << "연산에 소요된 시간 = " << dur.count() << '\n';
		cout << "결과값 = " << sum << '\n';
		cout << '\n';
	}

	cout << "실험 7번 - std::transform_reduce\n";
	{
		const auto sta = std::chrono::steady_clock::now();
		const auto sum = std::transform_reduce(std::execution::par, vec0.begin(), vec0.end(), vec1.begin(), 0ull);
		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << "연산에 소요된 시간 = " << dur.count() << '\n';
		cout << "결과값 = " << sum << '\n';
		cout << '\n';
	}
}

/*
//https://blog.naver.com/leeinje66/221580959555

1 std::inner_product ⭕, 빠름
2 순진한 멀티 쓰레딩 ❌, 빠름		//레이스 컨디션으로 값이 부정확하게 나온다.
3 Lock guard ⭕, 느림			//lock, unlock 과정 때문에 느리다.
4 atomic ⭕, 느림				//atomic의 연산은 느린 편이다.
5 Task - based parallelism(std::async) ⭕, 빠름
6 Task - based parallelism(std::thread, std::promise) ⭕, 빠름
7 std::transform_reduce ⭕, 빠름

*/

//transform_reduce : Map-Reduce에 해당하는 알고리즘, 병렬 버전도 있다. C++17