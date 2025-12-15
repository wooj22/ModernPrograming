//std::apply
//      apply( F&& f, Tuple&& t );
//          f : 호출 할 객체
//          t :	f 의 인수로 사용될 요소를 가진 튜플
//      튜플 인수로 Callable 객체 f 를 호출합니다

//std::tuple 일 필요가 없으며 대신 std::get 및 std::tuple_size 를 지원하는 모든 것일 수 있습니다.
//특히 std::array 및 std::pair 를 사용할 수 있습니다.

#include <iostream>
#include <tuple>
#include <utility>

int add(int first, int second) { return first + second; }

template<typename T>
T add_generic(T first, T second) { return first + second; }

auto add_lambda = [](auto first, auto second) { return first + second; };

template<typename... Ts>
std::ostream& operator<<(std::ostream& os, std::tuple<Ts...> const& theTuple)
{
    std::apply
    (
        [&os](Ts const&... tupleArgs) {
            os << '[';
            std::size_t n{ 0 };
            ((os << tupleArgs << (++n != sizeof...(Ts) ? ", " : "")), ...);
            os << ']';
        }, theTuple
    );
    return os;
}

int main()
{
    // OK
    std::cout << std::apply(add, std::pair(1, 2)) << '\n';

    // 오류 : 함수 유형을 추론 할 수 없습니다.
    // std::cout << std::apply(add_generic, std::make_pair(2.0f, 3.0f)) << '\n';

    // OK
    std::cout << std::apply(add_lambda, std::pair(2.0f, 3.0f)) << '\n';

    // 고급 예
    std::tuple myTuple{ 25, "Hello", 9.31f, 'c' };
    std::cout << myTuple << '\n';
}