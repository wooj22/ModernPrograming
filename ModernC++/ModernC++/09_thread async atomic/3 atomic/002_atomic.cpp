#include <atomic>
using namespace std;

int main()
{
    //atomic 객체를 선언하고, 값을 대입
    atomic<int> intAtomic;
    intAtomic = 2;

    // atomic 객체간 복사생성 / 대입연산은 금지되어 있다. ***

    // 복사생성 시도 -> 컴파일 에러
    atomic<int> intAtomic2 = intAtomic;

    // 대입연산 시도 -> 컴파일 에러
    atomic<int> intAtomic2;
    intAtomic2 = intAtomic;

    // atomic<short>애 대입
    atomic<short> shortAtomic = intAtomic.load();

    // +,- 연산/논리 연산 --------------------------------------------------

    // 값 더하기 : 멤버 함수 fetch_add
    intAtomic.fetch_add(1);
    // 값 더하기 : 멤버 함수 operator++(), operator++(int)
    intAtomic++;
    // 값 더하기 : 일반 함수 atomic_fetch_add
    atomic_fetch_add(&intAtomic, 1);

    // 값 빼기 : 멤버 함수 fetch_sub
    intAtomic.fetch_sub(1);
    // 값 빼기 : 멤버 함수 operator--(), operator--(int)
    intAtomic--;
    // 값 빼기 : 일반 함수 atomic_fetch_sub
    atomic_fetch_sub(&intAtomic, 1);

    // and : 멤버 함수 fetch_and (0x10 & 0x10)
    intAtomic.fetch_and(2);
    // and : 멤버 함수 operator &= (0x10 & 0x10)
    intAtomic &= 2;
    // and : 일반 함수 atomic_fetch_add (0x10 & 0x01)
    atomic_fetch_add(&intAtomic, 1);

    // or : 멤버 함수 fetch_or (0x00 | 0x01)
    intAtomic.fetch_or(1);
    // or : 멤버 함수 operator |= (0x01 | 0x10)
    intAtomic |= 2;
    // or : 일반 함수 atomic_fetch_or (0x11 | 0x01)
    atomic_fetch_or(&intAtomic, 1);

    // xor : 멤버 함수 fetch_xor(0x11 ^ 0x01)
    intAtomic.fetch_xor(1);
    // xor : 멤버 함수 operator ^= (0x10 ^ 0x01)
    intAtomic ^= 1;
    // xor : 일반 함수 atomic_fetch_xor (0x11 ^ 0x01)
    atomic_fetch_xor(&intAtomic, 1);

    // 읽기/저장/교환/비교 교환 --------------------------------------------------

    // 값 로드 : 멤버 함수 load
    int value = intAtomic.load();
    // 값 로드 : 멤버 함수 Operator T
    value = intAtomic;
    // 값 로드 : 일반 함수 atomic_load
    value = atomic_load(&intAtomic);

    // 값 저장 : 멤버 함수 store
    intAtomic.store(3);
    // 값 저장 : 멤버 함수 operator= (T value)
    intAtomic = 3;
    // 값 저장 : 일반 함수 atomic_store
    atomic_store(&intAtomic, 3);

    // 값 교환 : 멤버 함수 exchange
    int oldValue = intAtomic.exchange(5);
    // 값 교환 : 일반 함수 atomic_exchange
    oldValue = atomic_exchange(&intAtomic, 3);

    int comparand = 5;
    int newValue = 10;

    // 값 비교 교환 : 멤버 함수 (value = 3, 5와 같다면, 10으로 value를 바꾸어라)
    // 수행 후 comparand는 원래 value인 3로 바뀐다.
    bool exchanged = intAtomic.compare_exchange_weak(comparand, newValue);
    // 값 비교 교환 : 일반 함수
    // 앞서 comparand가 3로 바뀌었기에, 값이 10으로 바뀐다
    exchanged = atomic_compare_exchange_weak(&intAtomic, &comparand, newValue);

    // VS2013에서는 compare_exchange_weak와 compare_exchange_strong 구현이 동일하다.
    // compare_exchange_weak가 compare_exchange_strong을 호출한다.


    /// 유틸 함수
    // std::atomic은 해당 오브젝트 크기가 8바이트 이하이면 atomic을 보장한다.
    // _ATOMIC_MAXBYTES_LOCK_FREE = 8
    bool is_lock_free = intAtomic.is_lock_free();

    return 0;
}

//메모리 가시성(memory visibility)과 메모리 장벽(memory barrier) 

//memory order
//http://en.cppreference.com/w/cpp/atomic/memory_order

//특별히 memory_order를 지정하지 않은 채 함수들을 호출하면 기본적으로 memory_order_seq_cst가 적용된다.
//(즉, sequential consistency를 보장한다)
