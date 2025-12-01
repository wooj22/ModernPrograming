// common_type<>
// 
//      다양한 타입의 데이타 여러개를 인자로 받아 '공통타입'으로 변환
//      공통타입 : 두 개 이상의 타입을 처리할 때, 주어진 타입들을 모두 포함할 수 있는 타입
//      common_type<T1, T2, ...> 
//
//      common_type<T1, T2>::type
//      type 멤버는 매개 변수 목록의 '모든 형식을 변환'할 수 있는 공용 형식이다. 
//      매개 변수는 완전한 형식이거나 void 인 형식 목록입니다.

//std::common_type<short, int>::type    -> int  // 모두 int로 변환 가능
 
//std::is_same<int, int>::value         -> true (1)  //타입비교

#include <iostream>
#include <type_traits>

int main()
{
    std::common_type<short, int>::type number;
    std::cout << typeid(number).name() << std::endl;    // short, int  -> int

    typedef std::common_type<unsigned char, short, int>::type Numeric;

    std::cout << std::boolalpha;
    std::cout << std::is_same<int, Numeric>::value << std::endl;
    std::cout << std::is_same<short, Numeric>::value << std::endl;

    //아래 코드의 출력은?

    std::common_type_t<int, double> num;                // common_type_t
    std::cout << typeid(num).name() << std::endl;       // ???      double

    // 공용형식?

    typedef std::common_type<int, int*>::type type;     //공용형식 없음
}

// 상속관계의 경우 ---------------------------------------------------------------

#include <iostream>
#include <type_traits>

struct Base {};
struct Derived : Base {};

int main()
{
    typedef std::common_type<unsigned char, short, int>::type NumericType;
    typedef std::common_type<float, double>::type FloatType;
    typedef std::common_type<const int, volatile int>::type ModifiedIntType;
    typedef std::common_type<Base, Derived>::type ClassType;

    std::cout << std::boolalpha;
    std::cout << "Test for typedefs of common_type int" << std::endl;
    std::cout << "NumericType: "    << std::is_same<int, NumericType>::value << std::endl;
    std::cout << "FloatType: "      << std::is_same<int, FloatType>::value << std::endl;
    std::cout << "ModifiedIntType: "<< std::is_same<int, ModifiedIntType>::value << std::endl;
    std::cout << "ClassType: "      << std::is_same<int, ClassType>::value << std::endl;

    std::cout << "---------------------------" << std::endl;
    std::cout << "Test for typedefs of common_type Base" << std::endl;
    std::cout << "NumericType: "    << std::is_same<Base, NumericType>::value << std::endl;
    std::cout << "FloatType: "      << std::is_same<Base, FloatType>::value << std::endl;
    std::cout << "ModifiedIntType: "<< std::is_same<Base, ModifiedIntType>::value << std::endl;
    std::cout << "ClassType: "      << std::is_same<Base, ClassType>::value << std::endl;

    return 0;
}

//-----------------------------------------------------------------------------
//템플릿에서 활용

#include <iostream>
#include <type_traits>

template<class T>
struct Number { T n; };

template<class T, class U>
Number<typename std::common_type<T, U>::type> operator+(const Number<T>& lhs,
    const Number<U>& rhs)
{
    return { lhs.n + rhs.n };
}

int main()
{
    Number<int> i1 = { 1 }, i2 = { 2 };
    Number<double> d1 = { 2.3 }, d2 = { 3.5 };
    std::cout
        << "i1i2: " << (i1 + i2).n << '\n'
        << "i1d2: " << (i1 + d2).n << '\n'
        << "d1i2: " << (d1 + i2).n << '\n'
        << "d1d2: " << (d1 + d2).n << '\n';
}

//다양한 auto 변수(예: int, double 등)가 혼합되어 있을 때
#include <type_traits>
#include <iostream>

template <typename T1, typename T2>
auto sum(T1 a, T2 b) -> std::common_type_t<T1, T2> {
    return a + b;
}

//타입이 2개보다 많은 경우도 쉽게 지원
template <typename... Args>
auto sum_all(Args... args) -> std::common_type_t<Args...> {
    return (args + ...);
}

//C++20에서 concept와 함께 사용하여 타입 제약을 명확하게 하고, 여러 auto 타입 인자의 공통 타입을 구하는 예

#include <concepts>
#include <type_traits>
#include <iostream>

template <typename T, typename U>
concept CommonTypeConvertible =
    requires(T t, U u) {
    typename std::common_type_t<T, U>;
    { static_cast<std::common_type_t<T, U>>(t) };
    { static_cast<std::common_type_t<T, U>>(u) };
};

template <CommonTypeConvertible T, CommonTypeConvertible U>
auto add(T a, U b) -> std::common_type_t<T, U> {
    return a + b;
}

int main() {
    auto r = add(1, 3.14);   // double
    std::cout << r << std::endl;
}

//C++20부터 std::common_type은 
// 타입 변환의 명확성, concept와의 결합 사용성, 그리고 새로운 표준 타입 지원을 통해 
// 실전 코드에서 예상하지 못한 타입 오류를 더욱 효과적으로 방지

// 예) char8_t, enum class 등 새로운 타입군 지원
#include <type_traits>
static_assert(std::is_same_v<std::common_type_t<char8_t, char8_t>, char8_t>);


//std::common_type은 불완전한 타입에 대해 동작하지 않습니다.

//% 불완전한 형식
// 
//      불완전한 형식이란 선언만 되어 구현 정보(크기 등)를 알 수 없는 타입.
//      '식별자 크기'를 확인하는 데 필요한 정보는 포함하지 않는 형식입니다.
//      크기와 멤버 정보를 알 수 없기 때문에, 해당 타입 자체로 객체를 생성하거나 값을 직접 쓸 수 없다.
// 
//  아직 멤버를 지정하지 않은 구조체 형식
//  아직 멤버를 지정하지 않은 공용 구조체 형식
//  아직 차원을 지정하지 않은 배열 형식

struct student* ps;
struct student {int num; } /* student structure now completed */

char a[];  /* a has incomplete type */
char a[25]; /* a now has complete type */

//불완전한 타입 사용처와 한계
// 
//  불완전한 타입은 선언(식별자)만으로 코드를 연결하는 용도로 쓰이며, 
//  구체적 연산이나 메모리 할당에는 반드시 타입 완성이 필요하므로 타입 선언 및 정의 순서에 주의해야 합니다.
//  PImpl 패턴, API 노출 제한, 순환 참조 등에서 효과적으로 사용

