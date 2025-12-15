//Tuple 구현 예시 코드

#include <iostream>
#include <type_traits>

// 기본 Tuple 클래스 템플릿 (재귀 기반)
template <typename Head, typename... Tail>
class Tuple {
private:
    Head head;
    Tuple<Tail...> tail;

public:
    // 생성자
    Tuple(const Head& h, const Tail&... t) : head(h), tail(t...) {}

    // 첫 번째 요소 접근
    Head& getHead() { return head; }
    const Head& getHead() const { return head; }

    // 나머지 요소 접근
    Tuple<Tail...>& getTail() { return tail; }
    const Tuple<Tail...>& getTail() const { return tail; }
};

// 단일 요소를 처리하기 위한 특수화 (재귀 종료 조건)
template <typename Head>
class Tuple<Head> {
private:
    Head head;

public:
    // 생성자
    Tuple(const Head& h) : head(h) {}

    // 첫 번째 요소 접근
    Head& getHead() { return head; }
    const Head& getHead() const { return head; }
};

// 헬퍼 함수: 특정 인덱스의 요소 가져오기
template <std::size_t Index, typename Head, typename... Tail>
struct TupleElement {
    using Type = typename TupleElement<Index - 1, Tail...>::Type;

    static Type& get(Tuple<Head, Tail...>& t) {
        return TupleElement<Index - 1, Tail...>::get(t.getTail());
    }

    static const Type& get(const Tuple<Head, Tail...>& t) {
        return TupleElement<Index - 1, Tail...>::get(t.getTail());
    }
};

// 인덱스 0의 요소 가져오기 (특수화)
template <typename Head, typename... Tail>
struct TupleElement<0, Head, Tail...> {
    using Type = Head;

    static Head& get(Tuple<Head, Tail...>& t) { return t.getHead(); }
    static const Head& get(const Tuple<Head, Tail...>& t) { return t.getHead(); }
};

// 인덱스를 사용하여 요소를 가져오는 함수
template <std::size_t Index, typename... Types>
typename TupleElement<Index, Types...>::Type& get(Tuple<Types...>& t) {
    return TupleElement<Index, Types...>::get(t);
}

template <std::size_t Index, typename... Types>
const typename TupleElement<Index, Types...>::Type& get(const Tuple<Types...>& t) {
    return TupleElement<Index, Types...>::get(t);
}

int main() {
    // Tuple 생성
    Tuple<int, double, std::string> myTuple(42, 3.14, "Hello");

    // 요소 접근
    std::cout << "First: " << get<0>(myTuple) << "\n";
    std::cout << "Second: " << get<1>(myTuple) << "\n";
    std::cout << "Third: " << get<2>(myTuple) << "\n";

    // 값 변경
    get<1>(myTuple) = 2.718;
    std::cout << "Updated Second: " << get<1>(myTuple) << "\n";

    return 0;
}