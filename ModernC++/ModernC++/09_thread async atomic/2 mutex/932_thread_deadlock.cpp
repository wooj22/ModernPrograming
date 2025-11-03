//데드락(deadlock) : 
//      뮤텍스를 취득한 쓰레드가 unlock 을 하지 않으면 대기함
//      쓰레드 상호간의 충돌로 인한 교착상태.

#include <iostream>
#include <mutex>  // mutex 를 사용하기 위해 필요
#include <thread>

void worker1(std::mutex& m1, std::mutex& m2) {
    for (int i = 0; i < 10000; i++) {
        std::lock_guard<std::mutex> lock1(m1);
        std::lock_guard<std::mutex> lock2(m2);
        // Do something
    }
}

void worker2(std::mutex& m1, std::mutex& m2) {
    for (int i = 0; i < 10000; i++) {
        std::lock_guard<std::mutex> lock2(m2);  //
        std::lock_guard<std::mutex> lock1(m1);  //
        // Do something
    }
}

int main() {
    int counter = 0;
    std::mutex m1, m2;  // mutex 객체

    std::thread t1(worker1, std::ref(m1), std::ref(m2));
    std::thread t2(worker2, std::ref(m1), std::ref(m2));

    t1.join();
    t2.join();

    std::cout << "끝!" << std::endl;
}

//데드락이 가능한 상황을 어떻게 해결할 수 있을까? 한 가지 방법으로는 한 쓰레드에게 우선권을 주는 것
//한 쓰레드가 다른 쓰레드에 비해 우위를 갖게 된다면, 
//      한 쓰레드만 열심히 일하고 다른 쓰레드는 일할 수 없는 기아 상태(starvation)가 발생할 수 있다.

//기아 상태(starvation)
//      한 쓰레드가 다른 쓰레드에 비해 우위를 갖게 되면, 
//      한 쓰레드만 열심히 일하고, 다른 쓰레드는 일할 수 없는 경우가 발생 가능하다.


//try_lock()
//      blocking없이 현재 수행 대상에서 lock을 얻기 위해 시도합니다.  //true : lock 획득
//      예외가 발생하면 lock을 획득하지 않습니다. 

#include <iostream>
#include <mutex>  
#include <thread>

void worker1(std::mutex& m1, std::mutex& m2) {
  for (int i = 0; i < 10; i++) {
    m1.lock();
    m2.lock();
    std::cout << "Worker1 Hi! " << i << std::endl;

    m2.unlock();
    m1.unlock();
  }
}

void worker2(std::mutex& m1, std::mutex& m2) {
  for (int i = 0; i < 10; i++) {
    while (true) {
      m2.lock();

      // m1 이 이미 lock 되어 있다면 m2.unlock() 를 수행하게 된다.
      if (!m1.try_lock()) {
        m2.unlock();
        continue;
      }

      std::cout << "Worker2 Hi! " << i << std::endl;
      m1.unlock();
      m2.unlock();
      break;
    }
  }
}

int main() {
  std::mutex m1, m2;  // mutex 객체

  std::thread t1(worker1, std::ref(m1), std::ref(m2));
  std::thread t2(worker2, std::ref(m1), std::ref(m2));

  t1.join();
  t2.join();

  std::cout << "끝!" << std::endl;
}


//데드락 상황을 피하기 위해 다음과 같은 가이드라인 ***
//      - C++ Concurrency In Action
//
//      중첩된 Lock 을 사용하는 것을 피해라.
//          모든 쓰레드들이 최대 1 개의 Lock 만을 소유. 
//          여러개의 Lock 을 필요로 한다면 정말 필요로 하는지 확인할 것.
// 
//      Lock 을 소유하고 있을 때 유저 코드를 호출하는 것을 피해라.
//          유저 코드에서 Lock 을 소유할 수 도 있기에 중첩된 Lock 을 얻는 것을 피하려면 
//          Lock 소유시 유저 코드를 호출하는 것을 지양해야
// 
//      Lock 들을 언제나 정해진 순서로 획득해라.


