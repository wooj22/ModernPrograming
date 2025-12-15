//Variadic Template
//      필요한 parameter 수 경우 만큼의 함수를 overload 해주는 불편함 해소

//C++17 이전
//"sum", "all" 성격의 recursive variadic template를 구현할 때엔 여전히 종료자 함수 요구

    // example1 - sum

    #include <iostream>

    auto SumCpp() { return 0; }                 // 'zero(0)' recursion terminator

    template <typename T1, typename... T>
    auto SumCpp(T1 s, T... ts) {
        return s + SumCpp(ts...);               // recursive function call
    }

    // example2 - print all

    void printCpp() { std::cout << '\n'; }      // recursion terminator

    template<typename A0, typename... ARGS>
    void printCpp(A0 a1, ARGS&&... rest) {
        std::cout << a1;    
        printCpp(std::forward<ARGS>(rest)...);  // recursive function call
    }

    int main()
    {
        std::cout << SumCpp() << std::endl;
        std::cout << SumCpp(1) << std::endl;
        std::cout << SumCpp(1,1) << std::endl;

        printCpp();
        printCpp(1);
        printCpp(1, 1);
    }

//C++17에서 recursive 방식을 사용안해도 되는 "Fold expression"이 등장 ***
//Fold expression
//      parameter들을 unpack 하는 새로운 방식

// (pack op ...)           (1) Unary right fold
// (... op pack)           (2) Unary left fold
// (pack op ... op init)   (3) Binary right fold    //초기값 줄 때 사용
// (init op ... op pack)   (4) Binary left fold     //초기값 줄 때 사용

/*
    op : 다음의 32가지 operator를 포함한다.
         참고로, binary fold일 경우 2항의 op가 동일해야 한다
        +   -   *   /   %   ^   &   |   =   <   >   <<  >>
        +=  -=  *=  /=  %=  ^=  &=  |=  <<= >>=
        ==  !=  <=  >=  &&  ||  ,   .*  ->*
*/

//Unary simple examples -----------------------------------------------------

#include <iostream>
    using namespace std;

    // Unary RIGHT fold
    template<typename... Args> auto SumCpp1(Args... args) { return (args + ...); }
    // Unary LEFT fold
    template<typename... Args> auto SumCpp2(Args... args) { return (... + args); }
    // Binary RIGHT fold
    template<typename... Args> auto SumCpp3(Args... args) { return (args + ... + 1/*init*/); }
    // Binary LEFT fold
    template<typename... Args> auto SumCpp4(Args... args) { return (1/*init*/ + ... + args); }

    int main()
    {
        auto val1 = SumCpp1(3, 5, 7, 9);        //(3 + (5 + (7 + 9)))   // val = 24
        auto val2 = SumCpp2(3, 5, 7, 9);        //(((3 + 5) + 7) + 9)   // val = 24
        auto val3 = SumCpp3(3, 5, 7, 9);        //(3 + (5 + (7 + (9 + 1/*init*/))))     // val = 25
        auto val4 = SumCpp4(3, 5, 7, 9);        //((((1/*init*/ + 3) + 5) + 7) + 9)     // val = 25
    }

//Fold expressions operator 우선순위 --------------------------------------------

template<typename... Args>
auto SumCpp7(Args... args)
{
    return ((1 * 2) + ... + args);          // ()로 감싸야 한다. ***
}


// printCPP 예제 -------------------------------------------------------------

//stream operator << 를 사용한 Binary LEFT fold expression ***

#include <iostream>
using namespace std;

template<typename ...Args>
void printCPP(Args&&... args)
{
    (std::cout << ... << args) << '\n';     
}

int main() {
    printCPP(1,'A',"abc");
    //unpack 흐름 //((std::cout << args1) << args2) << args3 …) << std::endl;
}


// vector push_back 예제 -----------------------------------------------------

#include <iostream>
#include <vector>

template<typename T, typename... Args>
void push_back_vec(std::vector<T>& v, Args&&... args)
{
    (v.push_back(std::forward<Args>(args)), ...);
}

int main()
{
    std::vector<int> v;
    push_back_vec(v, 6, 2, 45, 12);

    for (int i : v)
        std::cout << i << ' ';

    return 0;
}
//operator comma( , ... )의 경우는 parameter unpack 과정에서 앞선 문장을 반복 실행하는 형태 ***
 
//unpack 흐름
//  v.push_back(args_0); v.push_back(args_1); v.push_back(args_2); v_push_back(args_3);


// 람다 실행 callback 예제 ---------------------------------------------------

#include <iostream>

template<typename Func, typename... Args>
void my_call(Func func, Args&&... args)
{
    (func(std::forward<Args>(args)), ...);
}

int main()
{
    my_call(
        [](auto v) { std::cout << v << " "; },
        "The num", 69, "is < than", 3.33
    );
    std::cout << std::endl;

    return 0;
}

//cppreference.com - fold expression(기본)
//modernesscpp.com - fold expressions(기본)
//baptiste - wicht.com - fold expressions(기본)
//http://filipjaniszewski.com - folding expressions (심화)
//Exploding tuples with fold expressions(심화)