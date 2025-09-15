//C++17  임시 실체화(temporary materialization) 도입

//C++17 에서는 카테고리의 성격이 조금 변경되었는데, 각 카테고리의 성격 / 특징은 다음과 같습니다.
// 
// glvalue : 객체(object), 비트필드(bit-field), 또는 함수의 식별(identity)를 결정하는 표현식(주소를 갖는 실체를 결정하는)
// prvalue : 객체나 비트필드를 초기화하거나 연산자의 피연산자의 값을 계산하는 표현식
// xvalue(eXpiring  value) : 객체나 비트필드의 리소스가 재활용될 수 있는 glvalue
// lvalue : xvalue가 아닌 glvalue
// rvalue : xvalue나 prvalue인 표현식

//      int x = 3;
//      int y = x;
//      lvalue는 rvalue로 변환될 수 있는데, prvalue가 객체를 초기화하는 표현식이기 때문
//      이 변환( lvalue-to-rvalue )과 쌍을 이루는  prvalue-to-xvalue conversion  도입
//      임시 실체화(temporary materialization)

//C++17에서 prvalue로 초기화된 객체는 항상 '문맥'에 따라 결정됩니다.
//그 결과, 실제로 필요한 경우에만 임시 값이 생성됩니다.


// C++17 이전에는 prvalue(특히 클래스 타입)는 항상 임시 값을 의미했습니다.
// 아래 코드 error

#include <iostream>
using namespace std;

class N
{
public:
    N() {};
    N(N const&) = delete; // this class is neither copyable
    N(N&&) = delete;      // nor movable
};

N make_N() {
    return N{};
    // Always creates a conceptual temporary prior to C++17
    // In C++17, no temporary is created at this point
}

int main()
{
    auto n = make_N(); // ERROR prior to C++17 because the prvalue needs a conceptual copy.
    // OK since C++17, because n is initialized directly from the prvalue.
}


// C++17에서는 prvalue N 자체는 임시 값을 생성하지 않습니다.
// 대신 문맥에 따라 결정된 객체를 초기화합니다.위 예제 코드에서 그 객체가 바로 n 입니다.
// 여기에서 복사나 이동 연산이 고려되지 않으며(최적화가 아닌 언어 측면에서 보장된 동작),
// C++17에서는 위 예제 코드가 정상적으로 컴파일됩니다.


//예제 코드 - 값 카테고리의 다양한 상황

#include <iostream>
#include <vector>
using namespace std;

class X {
};

void f(X const&) { }    // accepts an expression of any value category
void f(X&&) { }         // accepts prvalues and xvalues only 
// but is a better match for those than the previous declaration

int main()
{
    X v;
    X const c;

    f(v);            // passes a modifiable lvalue to the first f()
    f(c);            // passes a non-modifiable lvalue to the first f()
    f(X());          // passes a prvalue (since C++17 materialized as xvalue) to the second f()
    f(std::move(v)); // passes an xvalue to the second f()
}
