//쓰레드에 인자 전달하기 연습

// 정수를 전달하면, 1부터 그 정수까지 더하는 함수를 작성하고, 
// 쓰레드로 실행해서 결과를 출력하세요.

#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void sum(int length)
{
    int rt = 0;
    for (size_t i = 1; i <= length; i++)
        rt += i;
    cout << rt << endl;
}
void sum2(int length, int* sum)
{
    for (size_t i = 1; i <= length; i++)
        *sum += i;
}

int main()
{
    vector<int> data = { 1,2,3,4,5,6,7,8,9,10};
   
    thread t1(sum, 100);                // 함수, 매개변수 전달
    t1.join();

    int sums = 0;
    thread t2(sum2, 100, &sums);        // 함수, 매개변수 전달
    t2.join();
    std::cout << "전체 합 : " << sums << std::endl;
}