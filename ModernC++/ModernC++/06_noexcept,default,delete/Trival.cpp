// trivial / non-trivial

C++ 객체의 소멸자, 복사 생성자, 대입 연산자, 생성자가
얼마나 단순하게(즉, “컴파일러가 단순 메모리 복사 수준으로”) 작동하는가
성능, 메모리 배치, POD - like 타입 여부 등과 직접적으로 연결

//1. trivial의 의미

단순한, 기계적으로 가능한
컴파일러가 아무런 추가 동작 없이 단순히 메모리를 해제하거나 초기화 하는 정도만 수행하는 함수
호출해도 런타임 코드가 생성되지 않음(inline화 되어 사라짐)

//2. non-trivial이 되는 조건

사용자가 해당 함수를 직접 정의한 경우({} 포함)
해당 클래스가 기반 클래스(base) 를 가지거나
멤버가 non - trivial한 타입을 포함할 때
가상 소멸자, 가상 함수가 있을 때

//한 줄 요약
//  trivial : 컴파일러가 아무 동작도 안 하는 진짜 기본 형태.
//  non - trivial : 사용자가 무언가 개입한 형태. (직접 정의, 상속, 가상함수 등)


//3. 소멸자 기준으로 예시

#include <type_traits>
#include <iostream>

struct A {};                        // implicit destructor
struct B { ~B() = default; };       // explicitly defaulted
struct C { ~C() {} };               // user-defined (empty body)
struct D { virtual ~D() = default; }; // virtual destructor

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_trivially_destructible_v<A> << '\n'; // true
    std::cout << std::is_trivially_destructible_v<B> << '\n'; // true
    std::cout << std::is_trivially_destructible_v<C> << '\n'; // false
    std::cout << std::is_trivially_destructible_v<D> << '\n'; // false
}

//4. = default는 trivial을 유지할까 ?

    //유지하는 경우
    struct A {
        ~A() = default;             // 클래스 내부 선언 // trivial, noexcept(true)
    };

    //유지하지 않는 경우
    struct B {
        ~B();
    };
    inline B::~B() = default;       // 클래스 외부에서 default // non-trivial (하지만 noexcept는 true)
    
 
//5. 실무적 의미

관점	                trivial	        non - trivial
메모리 관리	        단순 스택 소멸	해제 코드 존재
성능	                빠름	            약간 느림
memcpy / memmove	가능      	    안전하지 않음
POD 여부	            가능	            불가능
복사 최적화	        가능	            제약 있음

