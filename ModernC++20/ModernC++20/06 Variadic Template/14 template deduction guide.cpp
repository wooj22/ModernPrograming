// Deduction Guide //가변템플릿 //C++20 이상 ----------------------------------------

#include <iostream>
#include <type_traits>
using namespace std;

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };     //상속
template<class... Ts> overload(Ts...) -> overload<Ts...>;     // 각각의 타입으로 추론 가이드

int main()
{
    auto a = overload{
        []() { cout << "()" << endl; },
        [](int) { cout << "(int)" << endl; },
        [](float) { cout << "(float)" << endl; },
    };

    a();
    a(42);
    a(42.0f);

    return 0;
}