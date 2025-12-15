//가변 템플릿 //Fold Expression 활용

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

//배열을 이용한 Pack Expansion을 하여 그 값을 다 더한 결과를 반환, 출력하는 예제 -----------

template<typename ... Types>
int foo(Types ... args)
{
    int vals[] = { args... };
    int sum = 0;
    for (int v : vals) { sum += v; }
    return sum;
}
int main()
{
    std::cout << foo(1, 2, 3, 4) << std::endl;
}

//연습) Fold Expression 으로 변경하세요.

    template<typename ... Types>
    int goo(Types ... args)
    {
        int sum = (args + ...);
        return sum;
    }
    int main()
    {
        std::cout << goo(1, 2, 3, 4) << std::endl;
    }


//초기값 부분에 객체를 넣고 연산자 오버로딩을 통해 원하는 바를 구현하는 예제 ----------------

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

template<typename ... Types>
void foo(Types ... args)
{
    (std::cout << ... << args);      // std::cout 을 초기값으로  // init + ... + args
}

int main()
{
    foo(1, 2.3, "456");
}

/*
template<typename T>
void do_something(T x) { std::cout << x << " "; }

template<typename ... Types>
void foo(Types ... args) { (do_something(args), ...); } //Parameter Pack
*/

//콤마도 이항 연산자이다. 이를 이용하여 전역 변수인 g_v 벡터에 값을 넣는 예제 --------------

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

std::vector<int> g_v;

template<typename ... Types>
void foo(Types ... args)
{
    (g_v.push_back(args), ...);     //Parameter Pack을 사용하는 패턴 가능
}

int main()
{
    foo(1, 2, 3, 4);
    for (int v : g_v)
    {
        std::cout << v << std::endl;
    }
}