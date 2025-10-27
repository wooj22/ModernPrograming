//벡터를 여러가지 방법으로 정렬해보자 ( 함수, 펑터, 람다 )

//펑터(functor)와 람다(lamda) 의 필요성      // 활용성, 속도, 편리
//      함수 포인터는 작성이 가장 단순하나, 상태를 가지지 못한다.
//      함수 객체는 상태를 가질 수 있으나, 클래스나 구조체를 정의해야 하는 번거로움이 있다.

#include<iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>       //시간
using namespace std;

bool function_sort(int& a, int& b)
{
    return a > b;
}

class functor_sort
{
public:
    bool operator()(int& a, int& b) { return a > b; }
};

int main(int argc, char* argv[])
{
    //정렬 시간을 비교해 보자.

    for (size_t i = 0; i < 3; i++)
    {
        vector<int> v;
        for (int i = 0; i < 1000000; ++i) {
            v.push_back(rand() % 2000);
        }

        auto StartTime = chrono::system_clock::now();

        if( i == 0) sort(v.begin(), v.end(), function_sort);                                // 함수를 이용한 벡터 정렬

        if (i == 1) sort(v.begin(), v.end(), functor_sort());                               // 펑터를 사용한 벡터 정렬

        if (i == 2) sort(v.begin(), v.end(), [](int& a, int& b)-> bool { return a > b; });  // 람다를 사용한 벡터 정렬

        auto EndTime = chrono::system_clock::now();

        chrono::milliseconds resultTime = chrono::duration_cast<chrono::milliseconds>(EndTime - StartTime);
        cout << resultTime.count() << "ms" << endl;
    }

    return 0;
}


//람다 함수를  vector에 저장 ---------------------------------------------------------------

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

int main() {
    std::vector<std::function<void(void)>> funcs;

    funcs.push_back([]() { std::cout << "Hello" << std::endl; });
    funcs.push_back([]() { std::cout << "lambda!" << std::endl; });

    for (auto& func : funcs) {
        func();
    }
}