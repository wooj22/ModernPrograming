//템플릿 분기문 

//SFINAE - Substitution failure is not an error
//      새로운 분기가 추가되면 기존 함수들의 템플릿 명세를 수정해야 합니다.

//꼬리표 분배 방법 (tag dispatching) 은 
//		템플릿 명세로 구분하는 것을, '함수의 인자'로 구분하여 사용하는 방법이다.
//
//		표면에 드러난 함수와 처리하는 함수를 나눈다.
//		드러난 함수는 타입에 따라 알맞은 꼬리표를 실제 처리하는 함수에 전달해 주고, 
//		처리하는 함수는 꼬리표에 따라 오버로딩해서 실제 사용한다.

//전달하는 방식
//		tag dispatching by type
//				템플릿 특수화(template specialization)
//		tag dispatching by instance
//				객체 넘겨 주기 (특수화 해야 할 타입이 많고, 기능이 겹친다면)


#include <iostream>
#include <functional>
#include <type_traits>
using namespace std;

template<typename T1, typename T2>
auto mul(T1 v1, T2 v2) {
    return v1 * v2;
}

//첫번째 인자가 정수인지, 실수인지 출력하기   // 일단, 스피네 방식으로 구현 

template<typename T1, typename T2,
    std::enable_if_t<std::is_floating_point<T1>::value, int> = 0>
auto mul(T1 v1, T2 v2) {
    std::cout << v1 << "is floating point!" << std::endl;
    return v1 * v2;
}

template<typename T1, typename T2,
    std::enable_if_t<std::is_integral<T1>::value, int> = 0>
auto mul(T1 v1, T2 v2) {
    std::cout << v1 << "is integral!" << std::endl;
    return v1 * v2;
}

//첫번째 인자가 long 타입이면, 저 둘과 따로 분리해서 처리하려고 한다. ( long int, long double )
 
//스피네는 하나만 선택하게 해야하므로 (for this, ad hoc)
//경우가 추가되면 
//기능이 바뀌지 않는 기존의 함수를 수정해야 하고, 코드가 점점 더 복잡해진다.

//꼬리표 분배(tag dispatching) 기법으로

struct integral_type {};
struct float_type {};
struct long_type {};

template<typename T>   //what_type를 통해서 미리 정의된 꼬리표를 받음 
using what_type =       
std::conditional_t<     //std::conditional ---> bool ? A : B
    std::is_same<T, long>::value || std::is_same<T, long double>::value,
        long_type,      //
    std::conditional_t<
        std::is_integral<T>::value,
        integral_type,  //
        float_type>     //
>;

template<typename T1, typename T2>  auto mul_impl(T1 v1, T2 v2, long_type) {
    std::cout << v1 << "is long type!" << std::endl;
    return v1 * v2;
}
template<typename T1, typename T2>  auto mul_impl(T1 v1, T2 v2, integral_type) {
    std::cout << v1 << "is integral type!" << std::endl;
    return v1 * v2;
}
template<typename T1, typename T2>  auto mul_impl(T1 v1, T2 v2, float_type) {
    std::cout << v1 << "is floating point type!" << std::endl;
    return v1 * v2;
}

template<typename T1, typename T2> 
auto mul(T1 v1, T2 v2) {
    return mul_impl(v1, v2, what_type<T1>());   //실제 구현
}

//새로운 경우가 추가되면, 
// what_type 의 명세만 수정하고 새로운 mul_impl을 오버로드하면 됨 


//using 및 std::conditional 을 사용했지만, 
//구조체나 상속된 꼬리표를 사용해도 무방하다.
// 
//경우가 2가지 밖에 없다면, 
//표준 STL 타입인 std::true_type 및 std::false_type 를 사용하면 됨

template<typename T1, typename T2>
auto mul_impl(T1 v1, T2 v2, std::true_type) {
    std::cout << v1 << "is floating point type!" << std::endl;
    return v1 * v2;
}
template<typename T1, typename T2>
auto mul_impl(T1 v1, T2 v2, std::false_type) {
    std::cout << v1 << "is integral type!" << std::endl;
    return v1 * v2;
}

template<typename T1, typename T2>
auto mul(T1 v1, T2 v2) {
    return mul_impl(v1, v2, std::is_floating_point<T1>());
}