//https://modoocode.com/271
// 
//메모리는 엄청 느리다.
//   이를 보완하기 위해 캐시(Cache) 라는 것을 도입. 읽기 / 쓰기 속도가 매우 빠르다.
//   L1,L2,L3,L4

//Cache hit
//   CPU 가 특정한 주소에 있는 데이터에 접근하려 한다면, 
//   일단 캐시에 있는지 확인한 후, 캐시에 있다면 해당 값을 읽고, 없다면 메모리 까지 갔다 오는 방식으로 진행됩니다.
// 
//   이렇게 캐시에 있는 데이터를 다시 요청해서 시간을 절약하는 것을 Cache hit 이라과 하며 
//   반대로 캐시에 요청한 데이터가 없어서 메모리 까지 갔다 오는 것을 Cache miss 라고 부릅니다.


//보통 CPU 에서 캐시가 작동하는 방식은 다음과 같습니다.
//    메모리를 읽으면 일단 캐시에 저장해놓는다.
//    만일 캐시가 다 찼다면 특정한 방식에 따라 처리한다.

//캐시 크기가 1 KB 밖에 안되고 LRU 방식을 사용하는 CPU 가 있다고 했을 때 
//LRU 방식: 가장 최근에 쓴(LRU - Least Recently Used) 캐시를 날려버리고 그 자리에 새로운 캐시를 기록하는 방식

    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < 10000; j++) {
            s += data[j];
        }
    }
    for (int j = 0; j < 10000; j++) {
        for (int i = 0; i < 10000; i++) {
            s += data[j];                //data[0] 을 10000 번 연속으로 접근, Cache hit 이 되어서 빠르다
        }
    }


//CPU 캐시로 인해
//	CPU 에서 아래 코드가 실행될 때, b = 1; 가 a = 1; 보다 먼저 실행될 수 있습니다.

int a = 0;
int b = 0;
void foo() {
    a = b + 1;
    b = 1;
}


//CPU 파이프라이닝(pipelining)
//	컴파일러는 우리가 어떠한 최대한 CPU 의 파이프라인을 효율적으로 활용할 수 있도록 명령어를 재배치하게 됩니다.
//	문제는 컴파일러가 명령어를 재배치 할 때, 다른 쓰레드들을 고려하지 않는다는 점입니다.
//	멀티 쓰레드 환경에서는 예상치 못한 결과가 나올 수 도 있습니다.


//명령어를 읽어야 하고          (fetch), 
//읽은 명령어를 해석해야 하고   (decode), 
//해석된 명령어를 실행하고     (execute), 
//마지막으로 결과를 써야 하지요 (write)

//  1        2        3        4         5        6
//fetch - decode - execute - write
//        fetch  - decode  - execute - write
//                 fetch   - decode  - execute - write


//수정 순서(modification order)
//  C++ 의 모든 객체들은 수정 순서(modification order) 라는 것을 정의할 수 있습니다
//  모든 쓰레드에서 변수의 수정 순서에 동의만 한다면 문제될 것이 없습니다.
//  C++ 에서 모든 쓰레드들이 수정 순서에 동의해야만 하는 경우는 
//  바로 모든 연산들이 원자적 일 때.

//원자성(atomicity)
//	CPU 가 명령어 1 개로 처리하는 명령으로, 중간에 다른 쓰레드가 끼어들 여지가 전혀 없는 연산을 말합니다.
//	즉, 이 연산을 반 정도 했다 는 있을 수 없고, 이 연산을 했다 혹은 안 했다 만 존재할 수 있습니다.
//	마치 원자처럼 쪼갤 수 없다 해서 원자적(atomic) 이라고 합니다.


//	C++ 에서는 몇몇 타입들에 원자적인 연산을 쉽게 할 수 있도록 여러가지 도구들을 지원하고 있습니다.
//	또한 이러한 원자적 연산들은 올바른 연산을 위해 굳이 뮤텍스가 필요하지 않습니다! 
//  즉 속도가 더 빠릅니다. ***

//std::atomic
//  정수형 또는 포인터 타입에 대해 산술 연산들을 atomic 하게 수행할 수 있도록 해 주는 템플릿 클래스.
//  멀티스레드 환경에서 lock을 사용하지 않고 한 줄의 명령으로 방해받지 않고 실행 시킬 수 있음.

#include <iostream>
#include <vector>
#include <atomic>
#include <thread>

void worker(std::atomic<int>& counter) {
    for (int i = 0; i < 10000; i++) {
        counter++;
    }
}

int main()
{
    std::atomic<int> counter(0);

    std::vector<std::thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.push_back(std::thread(worker, ref(counter)));
    }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
    }

    std::cout << "Counter 최종 값 : " << counter << std::endl;


    // is_lock_free()
    //  해당 atomic 객체의 연산들이 과연 정말로 원자적으로 구현될 수 있는지 확인

    std::atomic<int> x;
    std::cout << "is lock free ? : " << boolalpha << x.is_lock_free() << std::endl;
}


//memory_order
//  atomic 객체들의 경우 원자적 연산 시에 메모리에 접근할 때 어떠한 방식으로 접근하는지 지정할 수 있습니다.
//  memory_order_relexed - 가장 느슨한 조건,메모리에서 읽거나 쓸 경우, 주위의 다른 메모리 접근들과 순서가 바뀌어도 무방
//  memory_order_acquire - 해당 명령 뒤에 오는 모든 메모리 명령들이 해당 명령 위로 재배치 되는 것을 금지 
//  memory_order_release - 해당 명령 이전의 모든 메모리 명령들이 해당 명령 이후로 재배치 되는 것을 금지
//  memory_order_acq_rel - acquire 와 release 를 모두 수행
//  memory_order_seq_cst - 메모리 명령의 순차적 일관성(sequential consistency) 을 보장


//두 개의 다른 쓰레드들이 같은 변수의 release 와 acquire 를 통해서 동기화 (synchronize) 를 수행

    #include <atomic>
    #include <iostream>
    #include <thread>
    #include <vector>
    using std::memory_order_relaxed;

    std::atomic<bool> is_ready;
    std::atomic<int> data[3];

    void producer() {
        data[0].store(1, memory_order_relaxed);
        data[1].store(2, memory_order_relaxed);
        data[2].store(3, memory_order_relaxed);
        is_ready.store(true, std::memory_order_release);
    }

    void consumer() {
        // data 가 준비될 때 까지 기다린다.
        while (!is_ready.load(std::memory_order_acquire)) {
        }

        std::cout << "data[0] : " << data[0].load(memory_order_relaxed) << std::endl;
        std::cout << "data[1] : " << data[1].load(memory_order_relaxed) << std::endl;
        std::cout << "data[2] : " << data[2].load(memory_order_relaxed) << std::endl;
    }

    int main() {
        std::vector<std::thread> threads;

        threads.push_back(std::thread(producer));
        threads.push_back(std::thread(consumer));

        for (int i = 0; i < 2; i++) {
            threads[i].join();
        }
    }

//  memory_order_acq_rel 
//      acquire 와 release 를 모두 수행하는 것입니다. 
//      이는, 읽기와 쓰기를 모두 수행하는 명령들, 예를 들어서 fetch_add 와 같은 함수에서 사용될 수 있습니다.
//  memory_order_seq_cst
//      memory_order_seq_cst 는 메모리 명령의 순차적 일관성(sequential consistency) 을 보장해줍니다.
//      순차적 일관성이란, 메모리 명령 재배치도 없고, 모든 쓰레드에서 모든 시점에 동일한 값을 관찰할 수 있다.

    #include <atomic>
    #include <iostream>
    #include <thread>
    using std::memory_order_seq_cst;
    using std::thread;

    std::atomic<bool> x(false);
    std::atomic<bool> y(false);
    std::atomic<int> z(0);

    void write_x() { x.store(true, memory_order_seq_cst); }

    void write_y() { y.store(true, memory_order_seq_cst); }

    void read_x_then_y() {
        while (!x.load(memory_order_seq_cst)) {
        }
        if (y.load(memory_order_seq_cst)) {
            ++z;
        }
    }

    void read_y_then_x() {
        while (!y.load(memory_order_seq_cst)) {
        }
        if (x.load(memory_order_seq_cst)) {
            ++z;
        }
    }

    int main() {
        thread a(write_x);
        thread b(write_y);
        thread c(read_x_then_y);
        thread d(read_y_then_x);
        a.join();
        b.join();
        c.join();
        d.join();
        std::cout << "z : " << z << std::endl;
    }

//C++ atomic 객체들의 경우 따로 지정하지 않는다면 
// 기본으로 memory_order_seq_cst 로 설정되는데, 이는 일부 CPU 에서 매우 값비싼 명령 입니다.
// 만약에 제약 조건을 좀 더 느슨하게 할 수 있을 때 
// 더 약한 수준의 memory_order 을 사용한다면 프로그램의 성능을 더 크게 향상 시킬 수 있습니다.
 
//https://modoocode.com/271