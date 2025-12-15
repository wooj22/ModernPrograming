//tuple C++11 표준
//서로 다른 타입의 객체를 N개 보관하는 템플릿
/*
    #include <iostream>
    #include <tuple>
    using namespace std;

    int main()
    {
        tuple<> t0;
        tuple<int> t1(1);
        tuple<int, double, int, char> t4(1, 3.4, 2, 'A');

        get<2>(t4) = 15; // 참조 리턴으로 값 변경 가능

        cout << get<2>(t4) << endl; // 2
    }
*/

//tuple 만들기 -----------------------------------------------
// 
//  가변인자 템플릿을 사용해서 메인 템플릿(Main template)을 만듬
//  1개의 요소를 보관할 수 있도록 부분 특수화 구현
//  상속을 사용해서 N개를 보관할 수 있게 구현
//  생성자등 필요한 멤버 추가

#include <iostream>
using namespace std;

// tuple 메인 템플릿
template<typename ... Types> struct xtuple
{
    static constexpr int N = 0;
};

// tuple 부분 특수화
template<typename T, typename ... Types>
struct xtuple<T, Types...> : public xtuple<Types...> // 타입을 상속을 통해 재귀 저장 효과
{
    T value;
    xtuple() = default; // 기본 생성자
    xtuple(const T& v, const Types& ... args)
        : value(v), xtuple<Types...>(args...) {} // Pack expansion으로 가변인자 전달

    static constexpr int N = xtuple<Types...>::N + 1;
};

int main()
{
    xtuple<> t0;
    xtuple<int> t1(3);
    xtuple<int, double, char> t4(1, 3.4, 'A');
}