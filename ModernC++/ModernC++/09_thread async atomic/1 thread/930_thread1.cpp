//쓰레드에 인자 전달하기 
//      첫번째 인자로 함수, 뒤에 함수의 인자 전달

//함수와 매개변수 전달하여 실행시키기 ----------------------------------------------------

#include <iostream>
#include <thread>                       //#include
using std::thread;

void func(int n) {
    for (int i = 0; i < 10; i++) { std::cout << "func " << n << "\n"; }
}

int main()
{
    std::thread t1(func, 10);           //std::thread(함수)

    t1.join();                          //join //쓰레드 실행을 종료대기

    std::cout << "메인 함수 종료 \n";
}

 
//벡터의 합 구하기 //쓰레드를 활용하여 처리하기 ------------------------------------

#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

// 벡터, 범위 전달
void worker(vector<int>::iterator start, vector<int>::iterator end, int* result)
{
    int sum = 0;
    for (auto itr = start; itr < end; ++itr) { sum += *itr; }
    *result = sum;

    thread::id this_id = std::this_thread::get_id();  // 쓰레드의 id 를 구한다.
    printf("쓰레드 %x 에서 %5d 부터 %5d 까지 계산한 결과 : %d \n",
        this_id, *start, *(end - 1), sum);
}

int main()
{
    vector<int> data(10000);
    for (int i = 0; i < 10000; i++) data[i] = i;

    int sums = 0;

    thread t1(worker, data.begin(), data.begin() + 10000, &sums);   // 함수, 매개변수 전달

    t1.join();

    std::cout << "전체 합 : " << sums << std::endl;
}