// mutex  lock(), unlock() -----------------------------------------------------------

// mutex 를 사용하기  ---------------------------------------------------------

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>                                // mutex 를 사용하기 위해 필요 

void worker(int& result, std::mutex& m)         // mutex 전달
{
    for (int i = 0; i < 10000; i++) {
        m.lock();
        result += 1;    //임계 영역(critical section) //한 쓰레드만이 유일하게 실행할 수 있는 코드 부분
        m.unlock();
    }
}

int main() {
    int counter = 0;
    std::mutex m;                               //mutex 객체 ***

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));  
    }

    for (int i = 0; i < 4; i++)
        workers[i].join();

    std::cout << "Counter 최종 값 : " << counter << std::endl;     //최종값 보장
}

// std::lock_guard<> ---------------------------------------------------
// 
//      lock(), unlock() 를 편하게 사용 ***
//      자신의 영역을 벗어나면 자동으로 unlock()을 호출
//      scope 종료 시 알아서 unlock

void worker(int& result, std::mutex& m)
{
    for (int i = 0; i < 10000; i++)
    {
        // lock 생성 시에 m.lock() 을 실행한다고 보면 된다.

        //m.lock()
        std::lock_guard<std::mutex> lock( m );
        result += 1;
        // scope 를 빠져 나가면 lock 이 소멸되면서 m 을 알아서 unlock 한다.
        //m.unlock() 
    }
}


//아래 코드를 mutex 를 사용하여 수정하세요 ----------------------------------------

#include <iostream>
#include <thread>
//#include <mutex>
using namespace std;

int main()
{
    auto work_func = [](const string& name)     //람다 사용
    {
        for (int i = 0; i < 5; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            cout << name << " " << std::this_thread::get_id() << " is working " << i << endl;
        }
    };
    std::thread t1 = std::thread(work_func, "Jack");
    std::thread t2 = std::thread(work_func, "Dash");

    t1.join();
    t2.join();
}

//아래 코드를 mutex 를 사용하여 수정하세요 ------------------

#include <iostream>
#include <thread>
using namespace std;

int main()
{
    int shared_memory(0);

    auto count_func = [&]()
        {
            for (int i = 0; i < 1000; ++i) {               
                shared_memory++;
            }
        };

    std::thread t1 = std::thread(count_func);
    std::thread t2 = std::thread(count_func);

    t1.join();
    t2.join();

    cout << "After" << endl;
    cout << shared_memory << '\n';
}

/*
#include <iostream>
#include <thread>
//#include <mutex>
using namespace std;

int main()
{
    int shared_memory(0);

    //mutex mtx;
    auto count_func = [&]()
    {
        for (int i = 0; i < 1000; ++i) {
            //std::lock_guard<mutex> lock(mtx);		// unlock을 해주지 않아도 자동으로 해줌!
            shared_memory++;
        }
    };

    std::thread t1 = std::thread(count_func);
    std::thread t2 = std::thread(count_func);

    t1.join();
    t2.join();

    cout << "After" << endl;
    cout << shared_memory << '\n';
}
*/

// std::scoped_lock --------------------------------------------------------------
//      스마트 포인터처럼 자신의 영역을 벗어나면 자동으로 unlock()을 호출해준다
//      C++17 에서 사용 가능하며 std::lock_guard 함수보다 권장된다

#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
#include <string>

void PrintMessage(const std::string& message)
{
    static std::mutex sMutex;
    std::scoped_lock<std::mutex> lock(sMutex); //

    std::cout << message << std::endl;
}

int main()
{
    std::thread thread(PrintMessage, "Message from a child thread.");
    PrintMessage("Message from a main thread.");

    thread.join();
    return 0;
}

//scoped_lock 이 lock_guard 보다 더 유용한 점은 주로 
// 
//    '여러 락'을 동시에 안전하게 관리하고, 데드락 방지를 돕는 기능에 있습니다. 
//    매개변수로 전달된 뮤텍스들을 내포하는 개체를 만듭니다.
//    개체 생성시에 뮤텍스를 잠그고 범위를 벗어나 소멸될 떄 풀어줍니다. 즉, 데드락을 방지합니다.
// 
//    C++14 의 경우, std::lock_gurad를 사용할 수 있습니다. 
//    그러나 이떄는 뮤텍스는 하나만 전달 가능합니다.
//
//      std::mutex m1, m2;
// 
//      std::lock_guard<std::mutex> lock(m1);
//      std::lock_guard<std::mutex> lock(m2);
// 
//      std::scoped_lock lock(m1, m2);              //객체소멸시 역방향으로 해제