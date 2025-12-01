//std::variant
//      C++17은 타입-세이프 한 공용체가 필요했고, 그것을 구현했습니다.
//      std::variant는 union 과 똑같이 행동하지만, 타입에 안전합니다.

//  std::variant는 값의 수명을 유지하고 관리합니다.
//  만약 variant가 값을 보유하고 있는 경우, 그 값의 유형은 템플릿 인수 유형 중 하나여야 합니다. (<T>)
//  주어진 시간에 variant는 객체 유형 중 하나의 값을 보유하거나 보유하지 않습니다.
//  variant 인스턴스가 T 타입의 값을 보유하면, 이는 T 타입의 값이 variant 저장소 내에 할당됨을 의미합니다.

//  T 타입을 보유하기 위해 동적 메모리 같은 추가 저장소를 사용하진 않습니다.
//  단순히 Types에 있는 모든 유형에 대해 적절히 정렬된 변형 저장소를 사용합니다.
//  모든 타입은 참조할 수 있습니다.


#include <variant>
#include <iostream>
#include <string>

int main() {
    std::variant<int, double, std::string> v; // 초기값: int 0

    v = 42;          // int
    v = 3.14;        // double
    v = "Hello"s;    // std::string
}

//초기값 미지정 시 첫 번째 타입으로 기본 초기화
//이후 대입하면 타입이 변할 수 있음


//--------------------------------------------------------------------------

#include <iostream>
#include <variant>
using namespace std;

int main() 
{
    {
        std::variant<int, double, std::string> vunion = 1;  // variant type = int
        
        cout << std::get<int>(vunion) << endl;              //1

        vunion = 3.5;                                       //variant type = double, int 객체는 삭제됨

        cout << std::get<double>(vunion) << endl;           //3.5               (타입 기반 접근)
        cout << std::get<1>(vunion) << endl;                //위와 같은 효과     (인덱스 기반 접근)
        
        auto t = std::get<double>(vunion);                  // t 에 값을 담음

        //auto i = std::get<int>(vunion);             // bad_variant_access 예외를 던짐
        //auto str = std::get<string>(vunion);        // bad_variant_access 예외를 던짐 
    }
    
    //값 접근을 위한 멤버, 비멤버 함수를 지원합니다.
    {
        std::variant<int, double, std::string> vunion = "abc"s;
        vunion.index();                                     // 2 //현재 variant 의 인덱스를 반환

        std::holds_alternative<int>(vunion);                // false //그 타입이 유효한지에 대해 bool 값을 반환

        std::holds_alternative<std::string>(vunion);        // true

        std::get_if<std::string>(&vunion);                  // string* //타입이 유효하다면 타입의 포인터형을 반환 (안전한 접근)

        //std::get_if<bool>(&vunion);                       // nullptr
        //타입이 유효하지 않다면 bad_variant_access 예외를 던지는 대신, nullptr을 반환
    }

}

//std::monostate
//  variant 에 아무 것도 들고 있지 않은 상태를 표현
//
//  사용법

//공용체(union) 과 비교
//  공용체가 현재 어떤 타입의 객체를 보관하고 있는지 알 수 없기 때문에 실제로 사용하기에는 매우 위험
//  variant 의 가장 큰 특징으로는 반드시 값을 들고 있어야 한다는 점


//std::variant
//  이러이러한 타입들 중 하나(one-of) 를 표현하기에 매우 적합한 도구
//  즉 컴파일 타임에 정해진 여러가지 타입들 중에 한 가지 타입의 객체를 보관할 수 있는 클래스 

//std::optional 과 비교
//  원하는 데이터를 가지거나 가지지 않는 객체

//std::tuple 과 비교
//  여러 서로다른 타입들의 모음
//  C++ 17 부터는 structured binding   

