// std::ref()
//    <functional> 에 있다.
//    reference_wrapper를 간편하게 생성하는 헬퍼 함수 
// 
//    특정 타입을 참조하는 객체를 만든다. 
//    auto r = std::ref(var)로 생성할 수 있다.
//    r.get() 또는 바로 r로 해당 변수로서 사용되어 진다.
// 
//    참조자와 다른점 : & 와 다르게, 타입만 같다면 참조대상을 바꿀 수 있다.

// 사용
//    주로 thread의 인자 또는 bind의 인자로 넘겨줄 때 사용한다.
//    또, 참조를 보유할 수 없는 표준 컨테이너(예: std::vector) 내부에 
//    참조를 저장하는 메커니즘으로 사용한다.



#include <iostream>
#include <functional>
using namespace std;

void print(int i) {
    std::cout << i << '\n';
}

int main() {
    int i = 10;

    auto f1 = std::bind(print, i);
    auto f2 = std::bind(print, std::ref(i));

    i = 20;

    f1(); // 10
    f2(); // 20
}

// std::ref 는 대부분 std::bind와 결합되어 사용됩니다.

#include <iostream>
#include <functional>
using namespace std;

void printNumber(int i) {
    cout << i << endl;
}

int main() {
    int n = 4;
    std::function<void()> print1 = std::bind(&printNumber, n);
    std::function<void()> print2 = std::bind(&printNumber, std::ref(n));

    n = 5;

    print1();    // 4 를 출력
    print2();    // 5 를 출력
}



//컨테이너에 참조 저장	    std::reference_wrapper(std::ref 사용)
//const 참조 저장	        std::cref
//참조 수명 보장 필요	        스마트 포인터 사용(shared_ptr, unique_ptr)


//std::reference_wrapper와 std::shared_ptr의 차이
//
//항목	            std::reference_wrapper<T>	    std::shared_ptr<T>
//목적	            참조 전달(Reference semantics)	소유권 공유(Ownership semantics)
//수명 관리	        안 함(원본이 살아있어야 함)	    참조 카운트 기반으로 자동 관리
//내부 구현	        단순히 T* 포인터 1개	            T* + 참조 카운트 블록
//복사 시	        참조만 복사(원본 동일)	        참조 카운트 증가
//컨테이너 저장	    가능(std::ref)	                가능(std::make_shared)
//원본이 삭제되면	    댕글링(dangling)	                마지막 소멸자에서 자동 삭제
//사용 예	        함수 인자, STL 컨테이너 내 참조	동적 객체 관리, 리소스 공유
//
//비유              주소만 빌려서 보는 사람           공동 소유자



