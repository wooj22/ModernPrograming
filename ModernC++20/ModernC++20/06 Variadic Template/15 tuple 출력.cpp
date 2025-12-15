//가변인자 템플릿(Variadic template)를 활용하여 tuple 전체 요소를 출력

#include <iostream>
#include <tuple>
using namespace std;

//튜플과 index_sequence를 받아서 튜플 전체 요소를 출력
template<typename TP, size_t ... I>
void print_tuple_imp(const TP& tp, const index_sequence<I...>&)
{
    int x[] = { get<I>(tp)... };

    for (auto& n : x)
        cout << n << " ";
}

template<typename TP>
void print_tuple(const TP& tp)
{
    // 튜플 사이즈를 구해서 index_sequence를 생성하여 print_tuple_imp에 전달
    print_tuple_imp(tp, make_index_sequence<tuple_size<TP>::value>());
}

int main()
{
    tuple<int, int, int> tp(1, 2, 3);
    print_tuple(tp);
}

/*
// index_sequence ------------------------------------

#include <iostream>
using namespace std;

template <typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
{
    std::cout << "The sequence of size " << int_seq.size() << ": ";
    ((std::cout << ints << ' '), ...);
    std::cout << '\n';
}

int main()
{
    //정수 시퀀스를 타입 형태로 컴파일 타임에 생성
    index_sequence is = make_index_sequence<3>();
    // index_sequence< unsigned long long,  0, 1, 2 >  인덱스를 타입으로 변환
    print_sequence(is);
}
*/