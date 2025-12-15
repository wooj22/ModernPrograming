//C++ 가변인자 템플릿(Variadic template) tuple을 위한 get 구현

/*
//기반 클래스의 멤버에 접근하는 방법(기반 지식)

//기반 클래스의 멤버와 파생클래스의 멤버의 이름이 동일할때는 자신(파생 클래스)의 멤버가 우선
//기반 클래스의 멤버에 접근하는 방법
//    d.Base::value
//    static_cast<Base&>(d).value;
//값 캐스팅과 참조 캐스팅
//    static_cast<Base>(d): 임시객체 생성. lvalue가 될 수 없음
//    static_cast<Base&>(d): 임시객체를 생성 안함. lvalue가 될 수 있음

    #include <iostream>
    using namespace std;

    struct Base
    {
        int value = 10;
    };

    struct Derived : public Base
    {
        int value = 20;
    };

    int main()
    {
        Derived d;

        cout << d.value << endl;            // 20
        cout << d.Base::value << endl;      // 10

        cout << static_cast<Base>(d).value << endl;     // 10 임시객체 생성
        cout << static_cast<Base&>(d).value << endl;    // 10 참조

        //static_cast<Base>(d).value = 30;          // Error
        static_cast<Base&>(d).value = 30;           // OK

    }
*/

//Tuple_element --------------------------------------------------------
// 
//  tuple이 가진 N번째 요소의 타입을 구하는 템플릿
//  메인 템플릿(Main template) 생성, 구현은 불필요하므로 생략
//  0번째 요소를 구하는 부분 특수화 구현
//  N번째 요소를 구하는 부분 특수화 구현(Recursive)

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


// 메인 템플릿
template<size_t N, typename TP> struct xtuple_element;

// 요소의 타입을 구할 수 있도록 부분 특수화
template<typename T, typename... Types> 
struct xtuple_element<0, xtuple<T, Types...>>
{
    typedef T type;
    typedef xtuple<T, Types...> tupleType;
};

// 요소의 타입을 구할 수 있도록 부분 특수화 ( 재귀 )
template<size_t N, typename T, typename... Types>
struct xtuple_element<N, xtuple<T, Types...>>
{
    typedef typename xtuple_element<N - 1, xtuple<Types...>>::type type;
    typedef typename xtuple_element<N - 1, xtuple<Types...>>::tupleType tupleType;
};

// xtuple 요소를 꺼내는 함수
template<size_t N, typename TP>
typename xtuple_element<N, TP>::type& xget(TP& tp)
{
    return static_cast<typename xtuple_element<N, TP>::tupleType&>(tp).value;
}

int main()
{
    xtuple<int, double, char> t3(1, 3.4, 'A'); // 1

    cout << xget<1>(t3) << endl; // 3.4
    xget<1>(t3) = 1.1;
    cout << xget<1>(t3) << endl; // 1.1
}

/*

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
            cout << n << ", ";
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

//출처: https://www.devoops.kr/149?category=691976 [데브웁스]
// 템플릿 패턴
// 템플릿 디자인 패턴
*/