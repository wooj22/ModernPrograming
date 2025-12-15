//함수의 리턴타입, 인자타입 정보 구하기

// std::invoke_result  
// 
//      첫 번째 템플릿 인자로 호출 가능 객체의 타입을 넘겨줍니다.
//      두 번재 인자부터, 호출 가능 객체가 받아들이는 인자들의 타입들을 넘겨줍니다.
//      그러면 std::invoke_result 내부에 using 선언된 type이 곧 반환 타입이 됩니다.

#include <type_traits> 
#include <functional>

// 함수의 반환형 
typename std::invoke_result<int(double), double>::type A = 0;           // A의 타입은 int

// std::invoke_result는 '함수'외에도 '함수자'나 '람다'에도 적용할 수 있습니다.

// 함수자의 경우
typename std::invoke_result<std::function<bool()>>::type B = false;     // B의 타입은 bool

// 람다의 경우
auto lambda = [](int, int)->char { return '0'; };
typename std::invoke_result<decltype(lambda), int, int>::type C = '0';  // C의 타입은 char


// 멤버 함수 포인터에 대해서도 쓸 수 있습니다.
// 멤버 함수 포인터에 대해서는, 대상 객체의 타입을 두 번째 템플릿 인자로 넘겨주고,
// 세 번째 인자부터 멤버 함수가 받아들이는 인자들의 타입들을 넘겨줍니다.

struct SomeClass {};

typename std::invoke_result<
    double(SomeClass::*)(int), SomeClass, int
>::type D = 0.0;                                // D의 타입은 double


// std::invoke_result도 type_traits 헤더를 통해 더 사용하기 간편한 별칭 템플릿을 지원합니다.
//      invoke_result_t

std::invoke_result_t<int(char, double), char, double> E = 0;        // E의 타입은 int


//decltype --------------------------------------------------------------------

#include <iostream>
using namespace std;

int Function() {  
    return 0; 
}

int main()
{
    decltype(Function()) value = 0;         // value의 타입은 int

    cout << value << endl;
    cout << typeid(value).name() << endl;


    std::invoke_result_t<int()> E = 0;      // E의 타입은 int

    cout << E << endl;
    cout << typeid(E).name() << endl;

    return 0;
}

// 위 예제에서 Function() 이라는 표현식이 있지만 decltype 다음에 오는
// 괄호 안에 위치해서, 런타임에는 Function 함수가 전혀 실행되지 않습니다.

// 그리고 decltype은 Function 함수의 반환 타입을 컴파일 타임에 정확히 파악해 줍니다.


//decltype --------------------------------------------------------------------
//  함수(객체)의 타입만 알고 있는 경우

template <typename T>
T MakeT();

int main()
{
    decltype(MakeT<int(&)()>()()) A = 0;    // A의 타입은 int

    return 0;
}

// 여기에 사용된 MakeT 함수 템플릿은 심지어 정의가 없어도 됩니다.
// 왜냐하면 decltype 다음에 위치한 괄호 안의 호출문은,
// 런타임에서는 무시(호출되지 않음)되기 때문입니다.

// MakeT 함수 템플릿에 템플릿 인자 타입을 넘겨주고 호출하게 되면,
// 템플릿 인자로 넘겨받은 타입의 객체를 생성하여 반환하는 척(!)을 하게 됩니다.

// 따라서 MakeT 함수 템플릿에 함수 참조자 타입을 템플릿 인자로 넘겨주고
// 호출하면, MakeT 함수 템플릿은 넘겨받은 함수 참조자 타입의
// 객체를 반환하는 척(!)을 하게 됩니다.

// 이제 반환된 함수 참조자 타입의 객체를 호출하면,
// 함수 참조자 객체가 값을 반환하는 척(!)을 합니다.

// 마지막으로 decltype이 이 값의 타입을 알려주게 되는 것이죠.

// 이 모든 과정이 컴파일 타임에 이루어지며, 다시 말하지만
// 런타임에는 이런 과정들이 이루어지지 않습니다.