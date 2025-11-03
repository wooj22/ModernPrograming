#include <iostream>
#include <thread>
using namespace std;

// 함수포인트를 사용한 Thread 에제  //유의 사항 : default Parametar는 사용 할 수 없다.
void func_type_thread(int count) {
    for (int i = 1; i <= count; i++) {
        cout << "func point type : count " << i << endl;
    }
}

// class 내부의 static 함수화 멤버 함수를 사용한 Thread 예제 
class thread_test
{
public:
    static void class_static_func_type_thread(int count) {
        for (int i = 1; i <= count; i++) {
            cout << "class static func type : count " << i << endl;
        }
    }

    void class_func_type_thread(int count) {
        for (int i = 1; i <= count; i++) {
            cout << "class func type : count " << i << endl;
        }
    }

};

int main() 
{
    // 1. C 스타일 thread 생성 (함수 포인트 활용)
    thread thread1 = thread(func_type_thread, 10);

    // 2. Class의 Static 함수를 사용한 Thread 생성
    thread thread2 = thread(thread_test::class_static_func_type_thread, 10);


    // 3. Class의 멤버 함수를 사용한 Thread 생성 ***
    thread thread3 = thread(&thread_test::class_func_type_thread, thread_test(), 10);

    // 4. lamda를 사용하여 Class의 멤버 함수를 Thread로 생성 ***
    thread thread4([](int count) {
        thread_test tt4;
        tt4.class_func_type_thread(count);
        }, 10);

    // 5. lambda 를 사용한 Thread 생성
    thread thread5([](int count) {
        for (int i = 1; i <= count; i++) {
            cout << "lambda type : count " << i << endl;
        }
        }, 10);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    return 0;
}

/*
1. thread관련 class는 무엇인가??
  1) 표준 체택 시기	- C++11 에서 표준으로 채택
  1) namesapce	    - std
  2) Header	        - #include <thread>
  3) class          - std::thread

2. thread 생성 방법 (4가지)
  1) C 스타일 thread 생성 (함수 포인트 활용)
      thread(thread로 돌릴 함수, 넘길 인자);

  2) Class의 Static 함수를 사용한 Thread 생성
      thread(Class명:thread로 돌릴 함수, 넘길 인자);

  3) Class의 멤버 함수를 사용한 Thread 생성 ***
      thread(Class명:thread로 돌릴 함수, Class 생성자, 넘길 인자);

  4) lambda 를 사용한 Class 멤버 함수 Thread 생성 ***
    - static이 아닌 클래스의 멤버함수를 Thread로 돌릴 수 있다.

  5) lambda 를 사용한 Thread 생성
    - Thread로 돌릴 내용을 바로 생성 한다.

3. 고급

  1) class안에서 Thread 실행 하기  ***

    - 1번 인자로 class에서 thread로 돌릴 함수의 주소를 넘긴다.
    - 2번 this 를 넘긴다. (현재 생성된 객체를 넘기는 것을 의미)

    #include <thread>

    void Test::runMultiThread()
    {
        std::thread t1(&Test::calculate, this,  0, 10);
        std::thread t2(&Test::calculate, this, 11, 20);
        t1.join();
        t2.join();
    }

  2) 비동기로 실행 결과 받기(async 사용)

    #include <future>

    void Test::runMultiThread()
    {
         auto f1 = std::async(&Test::calculate, this,  0, 10);
         auto f2 = std::async(&Test::calculate, this, 11, 20);
         auto res1 = f1.get();
         auto res2 = f2.get();
    }

*/