//연습) Integer 컨셉 구현 -----------------------------------------------------------------------

#include <iostream> 
#include <type_traits>
using namespace std;

template<typename T>
concept Integer = is_convertible_v<T, int>;

template<Integer T>
T add_int(T t1, T t2) { return t1 + t2; }

decltype(auto) getval(auto s) {
    return s;
}

int main()
{
    cout << add_int(int{ 1 }, int{ 2 }) << endl;    //Integer 타입

    [[maybe_unused]] Integer auto x = getval(3);    //Integer 로 추론되는지 확인

    auto var1 = getval(string{ "abc" });    cout << "var1: " << var1 << endl;

    Integer auto var2 = getval(string{ "abc" });    cout << "var2: " << var2 << endl;
    //제약조건이 false로 표시됩니다.
}


//연습) 축약 함수 템플릿 ----------------------------------------------------------
//  Abbreviated Function Templates - C++20
//  Constrained Auto (제한된 auto)

#include <iostream>
using namespace std;

class Animal {
};

//C++17 
//template <class T>
//void give_head_scratches(T const& the_animal) { }

//C++20 
//void give_head_scratches(auto const& the_animal) { }

//C++20 concept 
template <class T>
concept animal = is_same<T, Animal>::value;

//Constrained Auto - 특정 컨셉만 자동으로 템플릿 구현
void give_head_scratches(animal auto const& the_animal) { }

int main()
{
    give_head_scratches(Animal());
    give_head_scratches(42);

    return 0;
}
