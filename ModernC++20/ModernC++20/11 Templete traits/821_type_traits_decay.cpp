//C++11 표준 type_traits 예제 -------------------------------------------------------------
//      std::decay
// 
//      std::decay<T>는 T 타입 본연의 형식으로 strip-down 시키는 역할
//      형식을 비참조, 비상수, 비휘발성으로 만들거나, 함수 또는 배열 형식에서 형식에 대한 포인터를 만듭니다.

//cppreference.com의 예제

#include <iostream>
#include <type_traits>

template <typename T, typename U>
struct decay_equiv : std::is_same<typename std::decay<T>::type, U>::type
{
};

int main()
{
    std::cout << std::boolalpha
        << decay_equiv<int, int>::value << '\n'
        << decay_equiv<int&, int>::value << '\n'
        << decay_equiv<int&&, int>::value << '\n'
        << decay_equiv<const int&, int>::value << '\n'
        << decay_equiv<int[2], int*>::value << '\n'
        << decay_equiv<int(int), int(*)(int)>::value << '\n';
}

/*
    template <typename T>
    struct decay
    {
        using U = remove_reference_t<T>;

        using type =
            conditional_t<
                is_array_v<U>,
                add_pointer_t<remove_extent_t<U>>,
                conditional_t<is_function_v<U>, add_pointer_t<U>, remove_cv_t<U>>
            >;
    };

    template <typename T>
    using decay_t = typename decay<T>::type;

-------------------------------------------------------------------------------
a. remove_reference 수행

    // Line 4
    using U = remove_reference_t<T>;

    decay는 가장 먼저 T에 참조성을 제거하는 것으로부터 시작한다.

b. 배열일 경우

    // Line 7 ~ 9
    conditional_t<is_array_v<U>, add_pointer_t<remove_extent_t<U>>, ...(FalseType)>;

    U 형식이 배열 타입 U[N]이라면, extent를 제거하고 포인터로 변경시킨다.
    즉, std::decay::type은 U[N] 타입에서 U* 타입으로 결정된다.

c-1. 배열은 아닌데 함수인 경우

    // Line 10
    conditional_t<is_function_v<U>, add_pointer_t<U>, ...(FalseType)>;

    U 형식이 함수일 경우, 즉 R(Args...)일 경우 std::decay::type은 R(*)(Args...) 타입으로 결정된다.

c-2. 배열도 아니고 함수도 아닌 경우

    // Line 10
    conditional_t<is_function_v<U>, ...(TrueType), remove_cv_t<U>>;

    이 경우 remove_cv_t(U)로 인해 std::decay_type은 U에서 const/volatile이 모두 제거된 타입으로 결정된다.
    이 과정에서 (함수도, 배열도 아니기에) 동일 타입의 LValue에서 RValue로 암시적 변환이 일어남을 유념하자.
*/