//함수 순차적으로 실행하기

#include <iostream>
#include <tuple>
#include <string>
using namespace std;

// helper function to print a tuple of any size
template<class Tuple, std::size_t N>
struct TupleCall {
    static void call_tuple(const Tuple& t) {
        TupleCall<Tuple, N - 1>::call_tuple(t);
        std::get<N - 1>(t)();
    }
};
template<class Tuple>
struct TupleCall<Tuple, 1> {
    static void call_tuple(const Tuple& t) {
        std::get<0>(t)();
    }
};

template<class... Args>
void call_tuple(const std::tuple<Args...>& t)
{
    TupleCall<decltype(t), sizeof...(Args)>::call_tuple(t);
}

int main()
{
    auto func1 = [] {cout << 1 << endl; };
    auto func2 = [] {cout << 2 << endl; };

    auto tp = make_tuple(func1, func2);
    call_tuple(tp);
}