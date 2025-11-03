//벡터를 전달해서 총합을 구하는 코드를  쓰레드를 활용해서 작성하세요.

#include <future>
#include <iostream>
#include <thread>
#include <vector>

// std::accumulate 와 동일
int sum(const std::vector<int>& v, int start, int end)
{
    int total = 0;
    for (int i = start; i < end; ++i) {
        total += v[i];
    }
    return total;
}

int parallel_sum(const std::vector<int>& v) 
{
    // lower_half_future 는 1 ~ 500 까지 비동기적으로 더함 
    std::future<int> lower_half_future =
        std::async(std::launch::async, sum, cref(v), 0, v.size() / 2);    //cref - wrapper

    //std::future<int> lower_half_future =
    //    std::async([&v]() { return sum(v, 0, v.size() / 2); });       //람다 함수

    // upper_half 는 501 부터 1000 까지 더함
    int upper_half = sum(v, v.size() / 2, v.size());

    return lower_half_future.get() + upper_half;
}


int main() 
{
    std::vector<int> v; v.reserve(1000);

    for (int i = 0; i < 1000; ++i) { v.push_back(i + 1); }

    std::cout << "1 부터 1000 까지의 합 : " << parallel_sum(v) << std::endl;
}
