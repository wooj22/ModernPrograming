/*
동시에 실행을 시키기

프로세스

    프로세스란, 운영체제에서 실행되는 프로그램의 최소 단위
    // 우리가 1 개의 프로그램을 가리킬 때 보통 1 개의 프로세스를 의미
    // CPU 의 경우 1 개의 코어. 즉, CPU 가 한 번에 한 개의 연산을 수행한다.

    컨텍스트 스위칭(Context switching): 여러개의 일을 처리할때 테스트간의 전환이 이루어짐
    // 어떤 프로그램을 실행시키고, 얼마 동안 실행 시키고,
    // 또 다음에 무슨 프로그램으로 스위치 할지는 
    // '운영체제'의 스케쥴러(scheduler)가 알아서 결정

쓰레드

    CPU 코어에서 돌아가는 프로그램 단위를 쓰레드(thread)라고 한다.
    CPU 의 코어 하나에서는 한 번에 한 개의 쓰레드의 명령을 실행.

    // 근래 들어서는 CPU 의 발전 방향이 코어 하나의 동작 속도를 높이기 보다는,
    // CPU 에 장착된 코어 개수를 늘려가는 식으로 발전 -> 쓰레드 중요

프로세스와 쓰레드의 차이

    한 개의 프로세스는 최소 한 개 쓰레드로 이루어져 있으며, 여러 개의 쓰레드로 구성될 수 있다.
    여러개의 쓰레드로 구성된 프로그램을 '멀티쓰레드(multithread) 프로그램' 이라 한다.

    프로세스와 쓰레드의 차이는 자원(메모리)의 공유 여부.
    한 프로세스 안에 쓰레드 1 과 쓰레드 2 가 있다면, 서로 같은 메모리를 공유.

어떤 경우에 프로그램을 멀티 쓰레드로 만드는 것이 유리할까?

    1.병렬 가능한 (Parallelizable) 작업들
    
    어떠한 연산 (연산 A) 을 수행하기 위해 다른 연산 (연산 B)의 결과가 필요한 상황을 
    A 가 B 에 의존(dependent)한다 라고 합니다.
    프로그램 논리 구조 상에서 연산들 간의 의존 관계가 많을수록 병렬화가 어려워지고, 
    반대로, 다른 연산의 결과와 관계없이 독립적으로 수행할 수 있는 구조가 많을수록 병렬화가 매우 쉬워집니다.

    2.대기시간이 긴 작업들

    CPU 시간을 낭비하지 않고 효율적으로 작업을 처리
*/

//C++ 11 에서부터 표준에 쓰레드가 추가

#include <iostream>
#include <thread>                   //#include
using std::thread;

void func1() {
    for (int i = 0; i < 10; i++) { std::cout << "쓰레드 1 작동중! \n"; }
}
void func2() {
    for (int i = 0; i < 10; i++) { std::cout << "쓰레드 2 작동중! \n"; }
}
void func3() {
    for (int i = 0; i < 10; i++) { std::cout << "쓰레드 3 작동중! \n"; }
}

int main()
{
    std::thread t1(func1);          //std::thread(함수)
    std::thread t2(func2);
    std::thread t3(func3);

    t1.join();                      //join //쓰레드 실행을 종료하면 리턴
    t2.join();
    t3.join();

    std::cout << "메인 함수 종료 \n";
}


//join 되거나 detach 되지 않는 쓰레드들의 소멸자가 호출된다면 예외를 발생시킴

int main()
{
    thread t1(func1);
    thread t2(func2);
    thread t3(func3);

    //t1.detach();        // 쓰레드 종료될 때 까지 기다리지 않는다.
    //t2.detach();
    //t3.detach();

    std::cout << "메인 함수 종료 \n";
}

// detach()
//      말 그대로, 해당 쓰레드를 실행 시킨 후, 잊어버리는 것 이라 생각하시면 됩니다. 
//      대신 쓰레드는 알아서 백그라운드에서 돌아가게 됩니다. 
// 메인종료와 상관없이 모두 실행 후 종료.


//스레드에게 -------------------------------------------------------------------
//      할 일을 '함수(포인터)', '함수객체(std::function)', '람다 함수' 를 통해 알려줄 수 있다

#include <iostream>
#include <thread>
using namespace std;

int main()
{
    cout << std::thread::hardware_concurrency() << endl;    //내 컴퓨터의 논리프로세서 갯수

    cout << std::this_thread::get_id() << endl;             //스레드의 id를 리턴

    std::thread t1 = std::thread( [] {
        cout << std::this_thread::get_id() << '\n';
        //while (true);
        } );

    t1.join();		// t1이 끝날 때까지 기다린다.
}


//연습) "Hello world" 출력하는 프로그램을 3개의 쓰레드로 작동되도록 작성하세요.
//      각 쓰레드의 아이디를 출력하세요.



//std::thread::hardware_concurrency()                           //내 컴퓨터의 논리프로세서
//      하드웨어의 스레드 컨텍스트 수를 반환한다.
//      사용할 수 없는 경우라면 0 을 반환
//      CPU에 따른, 프로그램에서의 효율적 스레드의 수 (하드웨어 스레드 컨텍스트 수 * 2) + 1
 
//std::this_thread::get_id()                                    //스레드의 id

//std::this_thread::sleep_for(std::chrono::milliseconds(100));  //스레드 지연

