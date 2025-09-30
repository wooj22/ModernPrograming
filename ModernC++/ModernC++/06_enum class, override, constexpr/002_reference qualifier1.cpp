//멤버 함수 참조 한정자 (reference qualifier)    //C ++ 11
// 
//      this 함수 참조 한정자를 지정하여
//      암시적 개체 매개변수가 lvalue인지 rvalue 인지에 따라, 
//      비정적 멤버함수를 '오버로드' 할 수 있다.

   
#include <iostream>
#include <vector>
using namespace std;

struct myStruct {

    //void func() const {}

    void func() & { std::cout << "lvalue\n"; }
    void func() && { std::cout << "rvalue\n"; }
    void func() const& { std::cout << "const lvalue\n"; }
};

int main() 
{

    myStruct s;
    s.func();               // prints "lvalue"

    myStruct().func();      // prints "rvalue"

    std::move(s).func();    // prints "rvalue"

    const myStruct s2;
    s2.func();              // const lvalue
}

/*
//C++의 멤버 함수에 대한 const &, & 및 && 지정자

    T const& operator*() const&;
    T&       operator*() &;
    T&&      operator*() &&;

    // const& 는 오버로드가 const, non-const 및 lvalue 객체에만 사용된다는 것을 의미합니다.
    const A a = A();
    *a;

    // & 는 오버로드가 상수가 아닌 객체에만 사용된다는 것을 의미합니다.
    A a;
    *a;

    // && 즉, 이 오버로드는 rvalue 객체에만 사용됩니다.
    * A();

*/



/*
//참조 한정자

#include <iostream>
#include <string>
using namespace std;

struct A {
    std::string abc = "abc";
    std::string& get() & { std::cout << "1";  return abc; }
    std::string get() && { std::cout << "2"; return std::move(abc); }
    std::string const& get() const& { std::cout << "3"; return abc; }
    std::string get() const&& { std::cout << "4"; return abc; }
};

// 1234 가 나오도록 호출하세요.

int main()
{
    A a; a.get();
    A().get();
    const A a2{}; a2.get();
    const A a3{}; std::move(a3).get();
}
*/