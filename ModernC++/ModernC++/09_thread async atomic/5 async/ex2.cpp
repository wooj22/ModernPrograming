// 벡터를 전달해서 총합을 구하는 코드를 람다로 작성하고, 
// 쓰레드를 활용해서 벡터의 합을 구해 출력하세요.

#include <iostream>
#include <vector>
#include <thread>
#include <future>
using namespace std;

int main()
{
    vector<int> v = { 1,2,3 };

    //벡터를 전달해서 총합을 구하는 코드
    auto addvector = [](vector<int> v) {
        int sum = 0;
        for (auto& e : v) sum += e;
        return sum;
        };

    //쓰레드를 활용해서 벡터의 합을 구해 출력
    std::future<int> f = std::async(addvector, v);
    std::cout << f.get();
}