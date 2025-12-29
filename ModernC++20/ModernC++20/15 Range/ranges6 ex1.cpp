//stl algorithm 연습 
//ranges 

#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    // 3으로 나누어 떨어지는 수의 제곱을 추려내기 

    // 벡터 v1에서 짝수인 원소들로만 필터링하고, 남은 원소들에 2를 곱한다.
    // result: 4 8 12 16 20
    vector<int> v1 = { 1,2,3,4,5,6,7,8,9,10 };

    vector<int> results;
    std::copy_if(v1.begin(), v1.end(), std::back_inserter(results),
        [](int n) { return n % 2 == 0; });
    std::transform(results.begin(), results.end(), results.begin(),
        [](int n) { return  n = n * 2; });
    /*
        auto results = v1
            | std::views::filter([](int n) {return n % 2 == 0; })
            | std::views::transform([](int n) {return n * 2; });
    */
    for (auto e : results) cout << e << " "; cout << endl;



    // 1. 0 ~ 99까지의 원소를 가진 뷰 생성
    // 2. 3의 배수인 원소로만 필터링
    // 3. 앞 원소 다섯개만 취한다.
    // result: 0 3 6 9 12

    std::vector<int> v2;
    for (size_t i = 0; i < 100; i++) v2.push_back(i);
    vector<int> temp;
    std::copy_if(v2.begin(), v2.end(), std::back_inserter(temp),
        [](int n) { return n % 3 == 0; });
    std::vector<int> out(temp.begin(), temp.begin() + 5);

    /*
        std::vector<int> out;

        for (int n : std::views::iota(0, 100) |
            std::views::filter([](int n) {return n % 3 == 0; }) |
            std::views::take(5))
        {
            out.push_back(n);
        }
    */
    for (auto e : out) cout << e << " "; cout << endl;
}