//launch::async     비동기 실행
//launch::deferred  실행하지 않고 대기

//매개변수 전달하여 실행 시키기

#include <iostream>
#include <future>
using namespace std;

void for_print(char c) 
{
    for (int i = 0; i < 10; i++)
        printf("%c 번 Thread : %d\n", c, i);
}

int main() {
    std::future<void> a = std::async(std::launch::async, for_print, 'a');
    std::future<void> b = std::async(std::launch::deferred, for_print, 'b');
    std::future<void> c = std::async(for_print, 'c');       //std::launch::async

    for (size_t i = 0; i < 10000000; i++) {} 

    b.get();        // launch::deferred 실행

    return 0;
}

//std::launch::deferred 는 실행하지 않고 대기합니다.
//      그 후.get() or .wait()을 만나면 실행하게 됩니다.