//템플릿 타입 생략 ( Templete Deduction )

//템플릿 인수 타입 추론(Template Argument Type Deduction)
//      사용자가 템플릿 인자를 명시적으로 지정하지 않은 경우 
//      컴파일러가 인자를 보고 추론(deduction)하는 것
// 
//      타입을 결정하는 방식(type deduction rule)

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;

    template<typename T> T square(T a) {
        return a * a;
    }

    int main()
    {
        square<int>(3);

        square(3);          // 인수 타입 추론 (int)
        square(3.3);        // 인수 타입 추론 (double)
    }

//클래스 템플릿 인수 추론(CTAD) - Class template argument deduction
// 
//      템플릿 인수 추론은 익숙한 문법이지만,  C++17부터 기능이 더 확장
//      템플릿 함수 뿐 아니라, 템플릿 클래스의 경우도 추론.
//      템플릿 클래스가 '객체 생성'의 타입으로 사용되는 경우에도 추론을 수행한다. ***

    template <typename T> class Foo
    {
    public:
        Foo(const T& data) : data(data) { }
        T data;
    };

    int main()
    {
        Foo<int> foo1(1);
        Foo      foo2(1);           //타입 생략    

        Foo a = 42;                 //Foo<int>

        auto f = Foo{ a.data };     //Foo<int>
        cout << f.data << endl;
    }


//이런 간단한 표현이 가능해 짐 -----------------------------------------

    #include <iostream>
    #include <algorithm>
    #include <array>
    #include <vector>
    #include <list>

    using namespace std;

    int main()
    {
        std::pair p(2, 4.5);

        std::tuple t(4, 3, 2.5);

        std::vector v1{ 1, 2, 3 };
        std::vector v2{ 0 };

        std::copy_n(v1.begin(), 3, std::back_insert_iterator(v2));
        for (auto e : v2) { cout << e << " "; }

        std::for_each(v1.begin(), v1.end(), [&](int i) {});

        //auto lck = std::lock_guard(foo.mtx);     
        //std::lock_guard lck2(foo.mtx, ul);

        // array ------------------------------------------------------------

        //std::array<int, 10> arr = { 1,2,3,4,5,6,7,8,9,10 };
        std::array arr = { 1,2,3,4,5,6,7,8,9,10 };

        //list<int> s = { 1,2,3 };
        std::list ls = { 1,2,3 };             //C++17

        //C++20
        for (std::array a{ 1,2,3,4,5,6,7,8,9,10 }; int n : a)
            std::cout << n << ' ';
        std::cout << endl;


        //basic_string, tuple 등에서 가능 ------------------------------------

        std::pair p2{ 2467368, "esdjkvhwjhjl"s };
        std::cout << p2.first << " " << p2.second << std::endl;

        auto&& [n, s] = p2;                         // 구조적 바인딩 (Structured binding)
        n = 3;                                      // n은 int 타입
        s = "3";                                    // s는 string 타입        


        // C# (7+) tuple : (n, s) = (3, "3"); 
        // C++ 에서는:

        int n1; string s1;
        std::tie(n1, s1) = std::tuple{ 3, "3" };    // tuple의 템플릿 인자를 생략했습니다.

        auto [n2, s2] = std::tuple{ 3, "3" };       // auto 활용 //구조화된 바인딩
        std::cout << n2 << " " << s2 << std::endl;

        return 0;
    }

// 클래스 템플릿 인수 추론의 장점
//        간결한 코드 : 템플릿 인수를 명시적으로 지정할 필요 없이, 코드가 간결하고 읽기 쉬워집니다.
//        자동 추론 : 코드 작성자가 템플릿 인수를 직접 지정할 필요가 없어 코드의 유지보수성이 향상됩니다.


// 사용자 정의 템플릿 인수 추론 가이드(User-defined deduction guides) ----------------------------------
//      C++ 17부터 지원
//      컴파일러가 자동으로 수행하는 템플릿 인자 추론 대신, 사용자가 가이드 제공가능
//      -> 를 사용해 반환형을 명시하는 함수 선언 문법 
// 
//      템플릿 클래스를 함수 이름으로 사용한다. 생성자를 통한 타입 결정.

    #include <iostream>
    #include <type_traits>
    using namespace std;

    template<typename T> class Vector
    {
        T* buff;
    public:
        Vector() {}             // 타입 추론이 불가능 할경우 유저 정의 추론 가이드 필요
        Vector(int sz, T initValue) {}

    };
    Vector()->Vector<int>;      // Vector 기본 생성자 호출 시, int로 타입 추론하도록 가이드 ***

    int main()
    {
        Vector v1(10, 3);       // 생성자 매개변수로 추론가능 
        Vector v2;              // 가이드를 통해서 추론 가능
    }
