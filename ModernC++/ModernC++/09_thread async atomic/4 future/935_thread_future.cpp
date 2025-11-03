// std::promise 와 std::future
//
//   결국 비동기적 실행으로 하고 싶은 일을, 어떠한 데이터를 다른 쓰레드를 통해 처리해서 받아내는 것.
//   내가 어떤 쓰레드<T> 를 사용해서, 비동기적으로 값을 받아내겠다 라는 의미는, 
//   미래에(future) 쓰레드<T> 가 원하는 데이터를 돌려 주겠다 라는 약속(promise)라고 볼 수 있다.

// 100 이라는 결과를 리턴하는 함수를 쓰레드로 구현하기  ( promise, future 사용 )

#include <future>
#include <iostream>
#include <string>
#include <thread>
using std::string;

void worker(std::promise<int>* p)
{	
	p->set_value(100);				        // 5.약속을 이행하는 모습. 해당 결과는 future 에 들어간다.
}

int main() {

	std::promise<int> p;					// 1.promise 선언
	std::future<int> f = p.get_future();    // 2.future에 할당, 미래에 string 데이터를 돌려 주겠다는 약속.

	std::thread t(worker, &p);				// 3.promise 전달	

	f.wait();	                            // 4.기다린다 // 참고로 wait 없이 그냥 get 해도 wait 한 것과 같다. ***
	std::cout << "받은 데이터 : " << f.get() << std::endl;	//6. 결과 획득

	t.join();
}



// packaged_task 를 사용하게 된다면  ------------------------------------------------
//    쓰레드에 굳이 promise 를 전달하지 않아도
//    알아서 packaged_task 가 함수의 '리턴값을 처리' 해줘서 매우 편리합니다.

	#include <future>
	#include <iostream>
	#include <thread>

	int some_task(int x) {  return 10 + x; }                    //함수 int 결과 리턴 ***

	int main() 
	{
		// int(int) : int 를 리턴하고 인자로 int 를 받는 함수. (std::function 참조)
		std::packaged_task< int(int) > task( some_task );
		std::future<int> f = task.get_future();                 //task.get_future() 

		std::thread t(std::move(task), 5);

		std::cout << "결과값 : " << f.get() << std::endl;

		t.join();
	}

//Example with exceptions ----------------------------------------------------------
//    promise 와 future 를 이용하는 것이
//    조건 변수를 사용한 것 보다 훨씬 더 깔끔하고 더 이해하기도 쉽다.
//    또한 더 우수한 점은 future 에 예외도 전달할 수 있기 때문입니다

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

    std::condition_variable cv;
    std::mutex m;
    bool done = false;
    std::string info;

    void worker() {
        {
            std::lock_guard<std::mutex> lk(m);
            info = "some data";  // 위의 p->set_value("some data") 에 대응
            done = true;
        }
        cv.notify_all();
    }

    int main() {
        std::thread t(worker);

        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] { return done; });  // 위의 data.wait() 이라 보면 된다.
        lk.unlock();

        std::cout << "받은 데이터 : " << info << std::endl;

        t.join();
    }

//예외도 전달

#include <exception>
#include <future>
#include <iostream>
#include <string>
#include <thread>
    using std::string;

    void worker(std::promise<string>* p) {
        try {
            throw std::runtime_error("Some Error!");
        }
        catch (...) {            
            p->set_exception(std::current_exception());     // set_exception 에는 exception_ptr 를 전달해야 한다.
        }
    }
    int main() {
        std::promise<string> p;

        // 미래에 string 데이터를 돌려 주겠다는 약속.
        std::future<string> data = p.get_future();

        std::thread t(worker, &p);

        // 미래에 약속된 데이터를 받을 때 까지 기다린다.
        data.wait();

        try {
            data.get();
        }
        catch (const std::exception& e) {
            std::cout << "예외 : " << e.what() << std::endl;
        }
        t.join();
    }

//exception

#include <thread>
#include <iostream>
#include <future>

    int main()
    {
        std::promise<int> p;
        std::future<int> f = p.get_future();

        std::thread t([&p] {
            try {
            // code that may throw
            throw std::runtime_error("Example");
        }
        catch (...) {
            try {
                // store anything thrown in the promise
                p.set_exception(std::current_exception());
            }
            catch (...) {} // set_exception() may throw too
        }
            });

        try {
            std::cout << f.get();
        }
        catch (const std::exception& e) {
            std::cout << "Exception from the thread: " << e.what() << '\n';
        }
        t.join();
    }


// wait_for

#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <string>
#include <thread>

    void worker(std::promise<void>* p) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        p->set_value();
    }

    int main() {
        // void 의 경우 어떠한 객체도 전달하지 않지만, future 가 set 이 되었냐
        // 안되었느냐의 유무로 마치 플래그의 역할을 수행할 수 있습니다.
        std::promise<void> p;

        // 미래에 string 데이터를 돌려 주겠다는 약속.
        std::future<void> data = p.get_future();

        std::thread t(worker, &p);

        // 미래에 약속된 데이터를 받을 때 까지 기다린다.
        while (true) {
            std::future_status status = data.wait_for(std::chrono::seconds(1));

            // 아직 준비가 안됨
            if (status == std::future_status::timeout) {
                std::cerr << ">";
            }
            // promise 가 future 를 설정함.
            else if (status == std::future_status::ready) {
                break;
            }
        }
        t.join();
    }

//shared_future
//      future 의 경우 딱 한 번만 get 을 할 수 있습니다.
//      왜냐하면 get 을 호출하면 future 내부의 객체가 이동되기 때문이지요.
//      하지만, 종종 여러 개의 다른 쓰레드에서 future 를 get 할 필요성이 있습니다.


#include <chrono>
#include <future>
#include <iostream>
#include <thread>
using std::thread;

    void runner(std::shared_future<void> start) {
        start.get();
        std::cout << "출발!" << std::endl;
    }

    int main() {
        std::promise<void> p;
        std::shared_future<void> start = p.get_future();

        thread t1(runner, start);
        thread t2(runner, start);
        thread t3(runner, start);
        thread t4(runner, start);

        // 참고로 cerr 는 std::cout 과는 다르게 버퍼를 사용하지 않기 때문에 터미널에
        // 바로 출력된다.
        std::cerr << "준비...";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cerr << "땅!" << std::endl;

        p.set_value();

        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }



//https://en.cppreference.com/w/cpp/thread/promise
//https://en.cppreference.com/w/cpp/thread/future

// future from -------------------------------------------------------------------

#include <iostream>
#include <future>
#include <thread>

    int main()
    {
        // 1. future from a packaged_task
        std::packaged_task<int()> task([] { return 7; }); // wrap the function
        std::future<int> f1 = task.get_future();  // get a future
        std::thread t(std::move(task)); // launch on a thread

        // 2. future from a promise
        std::promise<int> p;
        std::future<int> f2 = p.get_future();
        std::thread([&p] { p.set_value_at_thread_exit(9); }).detach();

        // 3. future from an async()
        std::future<int> f3 = std::async(std::launch::async, [] { return 8; });


        std::cout << "Waiting..." << std::flush;
        f1.wait();
        f2.wait();
        f3.wait();
        std::cout << "Done!\nResults are: "
            << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
        t.join();
    }