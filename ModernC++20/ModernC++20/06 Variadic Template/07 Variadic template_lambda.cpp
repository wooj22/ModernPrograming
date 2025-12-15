//예시 - 상속과 가변 템플릿

#include <iostream>

using namespace std;

template<class... Ts> struct overload : Ts...           //상속
{
    using Ts::operator()...;                            //using operator()
};
//template<class... Ts> overload(Ts...) -> overload<Ts...>; //User-defined deduction guides 

int main()
{
    auto funcs = overload{
        []() { cout << "()" << endl; },
        [](int) { cout << "(int)" << endl; },
        [](float) { cout << "(float)" << endl; },
        [](int, int) { cout << "(int, int)" << endl; },
        //[](int, int) { },
    };

    funcs();
    funcs(1);
    funcs(1.1f);
    funcs(2, 2);

    return 0;
}

/*
//사용자 정의 템플릿 인자 추론 가이드가 없었다면 위 코드를 아래처럼 구현해야 했겠죠.

template<class... Ts> struct overload : Ts...
{
    overload(Ts&&...) { }
    using Ts::operator()...;
};

//전혀 쓸모 없는, 오직 꼼수만을 위한 생성자를 추가해줘야 합니다.
*/


/*
//상속 예시

#include <iostream>
using namespace std;

struct A { void func() { cout << "A::func" << endl; } };
struct B { void func() { cout << "B::func" << endl; } };

struct overload : A, B           //상속
{
    using A::func, B::func;
};

int main()
{
    A a;
    B b;
    auto funcs = overload{ a, b };
    funcs.A::func();
    funcs.B::func();

    return 0;
}

//가변 템플릿으로 변경하면

template<class... Ts> struct overload : Ts...           //상속
{
    using Ts::func...;
};

*/