//튜플 전체 요소를 출력하기

#include <iostream>
#include <tuple>
using namespace std;

//튜플과 index_sequence를 받아서 튜플 전체 요소를 출력
template<typename TP, size_t ... I>
void print_tuple_imp(const TP& tp, const index_sequence<I...>&)
{
	int x[] = { get<I>(tp)... };

	for (auto& n : x)
		cout << n << ", ";
}
// 튜플 사이즈를 구해서 index_sequence를 생성하여 print_tuple_imp에 전달
template<typename TP>
void print_tuple(const TP& tp)
{	
	print_tuple_imp(tp, make_index_sequence<tuple_size<TP>::value>());
}

int main()
{
	tuple<int, int, int> tp(1, 2, 3);

	print_tuple(tp);
}

//----------------------------------------------------------------------

#include <iostream>
#include <tuple>
#include <string>

// helper function to print a tuple of any size
template<class Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple& t)
    {
        TuplePrinter<Tuple, N - 1>::print(t);
        std::cout << ", " << std::get<N - 1>(t);
    }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};

template<class... Args>
void print(const std::tuple<Args...>& t)
{
    std::cout << "(";
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    std::cout << ")\n";
}

int main()
{
    std::tuple<int, std::string, float> t1(10, "Test", 3.14);
    int n = 7;
    auto t2 = std::tuple_cat(t1, std::make_pair("Foo", "bar"), std::tie(n));
    n = 10;
    print(t2);
}

//----------------------------------------------------------------------

#include <iostream>
#include <tuple>
#include <string>

template<class TupType, size_t... I>
void print(const TupType& _tup, std::index_sequence<I...> is)
{
    std::cout << "(";
    (..., (std::cout << (I == 0 ? "" : ", ") << std::get<is.size() - I - 1>(_tup)));  //역순 
    std::cout << ")\n";
}

template<class... T>
void print(const std::tuple<T...>& _tup)
{
    print(_tup, std::make_index_sequence<sizeof...(T)>());
}

int main()
{
    auto a = std::make_tuple(5, "Hello", -0.1);
    print(a);
}


