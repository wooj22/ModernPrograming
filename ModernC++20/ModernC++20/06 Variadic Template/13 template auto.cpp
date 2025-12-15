//auto keyword in template   //c++17
// 
//      used to indicate a non-type parameter ( 비타입 파라미터 자동 추론 ) ***
//      the type of which is deduced at the point of instantiation.

/*

//For example,

    template <typename Type, Type value> constexpr Type constant = value;
    constexpr auto const IntConstant42 = constant<int, 42>;

//can now be written as

    template <auto value> constexpr auto constant = value;
    constexpr auto const IntConstant42 = constant<42>;

*/

#include <iostream>
#include <tuple>
using namespace std;

template <auto x> constexpr auto constant = x;

template<auto n> struct B {  };

int main()
{
    auto v1 = constant<5>;      // v1 == 5, decltype(v1) is int
    auto v2 = constant<true>;   // v2 == true, decltype(v2) is bool
    auto v3 = constant<'a'>;    // v3 == 'a', decltype(v3) is char

    B<5> b1;    // OK: template parameter type is int
    B<'a'> b2;  // OK: template parameter type is char
    B<2.5> b3;  // error: template parameter type cannot be double  //C++20 ok
}

//가변인자 템플릿 auto ----------------------------------------

#include <iostream>
#include <tuple>
using namespace std;

template<typename...Ts2>    //가변인자 템플릿
void foo(Ts2... args)
{
    tuple<Ts2...> tp(args...);
    cout << get<0>(tp) << endl;
    cout << get<1>(tp) << endl;
    cout << get<2>(tp) << endl;
}

template<auto... Ts>        //가변인자 템플릿 auto
struct C {
};

int main()
{
    foo<>('C', 0, 2L, nullptr);

    C<'C', 0, 2L, nullptr> x; // OK
}

//예시 ---------------------------------------------------------

#include <iostream>

// Template with auto non-type parameter
template <auto Value>
void printValue() {
    std::cout << "Value: " << Value << "\n";
}

int main() {
    printValue<42>();       // Non-type parameter is an int
    printValue<'A'>();      // Non-type parameter is a char
    printValue<3.14>();     // Non-type parameter is a double

    constexpr int x = 100;
    printValue<x>();        // Using a constexpr variable

    return 0;
}

//예시 --------------------------------------------------------
//      자료형을 구별하여 처리하기
#include <iostream>

template <auto Value>
void printType() {
    if constexpr (std::is_same_v<decltype(Value), int>) {
        std::cout << "Integer value: " << Value << "\n";
    }
    else if constexpr (std::is_same_v<decltype(Value), char>) {
        std::cout << "Character value: " << Value << "\n";
    }
    else {
        std::cout << "Other type value: " << Value << "\n";
    }
}

int main() {
    printType<42>();
    printType<'C'>();
    printType<3.14>();
}


/*
//타입의 사이즈 추출
//  Extracting the value of SIZE without knowing its type

    template<std::size_t SIZE>
    class Foo {};

    template <template<auto> class T, auto K>
    auto extractSize(const T<K>&) {
        return K;
    }

    int main() {
        Foo<6> f1;
        Foo<13> f2;
        std::cout << extractSize(f1) << std::endl;
        std::cout << extractSize(f2) << std::endl;
    }

*/

/*
//가변인자 템플릿 
//      good examples where using template <auto> with variadic template parameters 

    template <auto ... vs> struct HeterogenousValueList {};
    using MyList1 = HeterogenousValueList<42, 'X', 13u>;

    template <auto v0, decltype(v0) ... vs> struct HomogenousValueList {};
    using MyList2 = HomogenousValueList<1, 2, 3>;

    //In pre - C++1z, while HomogenousValueList could be simply written as

    template <typename T, T ... vs> struct Cxx14HomogenousValueList {};
    using MyList3 = Cxx14HomogenousValueList<int, 1, 2, 3>;

    //writing an equivalent of HeterogenousValueList would not be possible without wrapping the values in some other templates, for example:

    template <typename ... ValueTypes> struct Cxx14HeterogenousValueList {};
    using MyList4 = Cxx14HeterogenousValueList<constant<int, 42>, constant<char, 'X'> >;

*/

/*
//std::integral_constant -------------------------------------

template<class T, T val>
struct integral_constant
{
   static constexpr T value = val;

   using value_type = T;
   using type = integral_constant;

   constexpr operator value_type() const noexcept { return value; }

   [[nodiscard]] constexpr value_type operator()() const noexcept { return value; }
};

template<bool val>
using bool_constant = integral_constant<bool, val>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;


//With template <auto> -------------------------------

template<auto val>              //
struct integral_constant
{
   static constexpr auto value = val;

   using value_type = decltype(val);
   using type = integral_constant;

   constexpr operator value_type() const noexcept { return value; }

   [[nodiscard]] constexpr value_type operator()() const noexcept { return value; }
};

using true_type = integral_constant<true>;
using false_type = integral_constant<false>;

*/