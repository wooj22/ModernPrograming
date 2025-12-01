#include <iostream>
#include <functional>   //

struct S
{
    const int j = 0;
    int do_something(const int i) { return j + i; }
};

int main()
{    
    S s;
    
    std::cout << s.do_something(5) << std::endl; // invoke 함수를 이용해 호출하세요.

    
    // std::cout << std::invoke(&S::do_something, s, 5) << '\n';  //맴버 함수
}