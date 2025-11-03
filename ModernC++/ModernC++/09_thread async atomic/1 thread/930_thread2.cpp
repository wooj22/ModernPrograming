
//벡터의 합 구하기 //쓰레드를 활용하여 더 빠르게 처리하기

#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void worker(vector<int>::iterator start, vector<int>::iterator end, int* result)
{
    int sum = 0;
    for (auto itr = start; itr < end; ++itr) {
        sum += *itr;
    }
    *result = sum;

    thread::id this_id = std::this_thread::get_id();  // 쓰레드의 id 를 구한다.
    printf("쓰레드 %x 에서 %5d 부터 %5d 까지 계산한 결과 : %d \n",
        this_id, *start, *(end - 1), sum);
}

int main()
{
    vector<int> data(10000);
    for (int i = 0; i < 10000; i++) data[i] = i;

    vector<int> partial_sums(4);    // 각 쓰레드에서 계산된 부분 합들을 저장하는 벡터

    vector<thread> workers;
    for (int i = 0; i < 4; i++)
    {
        workers.push_back(
            //쓰레드에 인자 전달하기 //첫번째 인자로 함수, 뒤에 함수의 인자 전달
            thread( worker,
                data.begin() + i * 2500,
                data.begin() + (i + 1) * 2500,
                &partial_sums[i] )
        );
    }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
    }

    int total = 0;
    for (int i = 0; i < 4; i++) {
        total += partial_sums[i];
    }
    std::cout << "전체 합 : " << total << std::endl;
}