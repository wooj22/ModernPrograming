//type traits 기능
 
//integral_constant ***
// 
//  컴파일 타임에 결정된 '상수 값을 별도 타입화' 하여 함수 오버로딩을 할 수 있도록 만드는 int2type 기술
//  int2type 기술을 C++11에서 표준화한 integral_constant

#include <type_traits>
#include <iostream>

int main()
{
    std::cout << "integral_constant<int, 5> == "
        << std::integral_constant<int, 5>::value << std::endl;
    std::cout << "integral_constant<bool, false> == " << std::boolalpha
        << std::integral_constant<bool, false>::value << std::endl;

    std::cout << std::bool_constant<false>::value << std::endl;     //using 
    std::cout << std::bool_constant<false>() << std::endl;          //operator()() 
    std::cout << std::false_type::value << std::endl;
    std::cout << std::false_type() << std::endl;

    return (0);
}

//-----------------------------------------------------------------------------------------------

//기본 함수 오버로딩(Function overloading)
//  인자의 개수가 다르거나 인자 타입이 다르면, 아래와 같이 인수에 따라 서로 다른 함수가 호출 되게 할 수 있음
//  인자가 개수가 같고 인자의 타입도 같을때 다른 함수가 되게 하려면 ?

#include <iostream>
using namespace std;

void foo(int n) {}
void foo(double d) {}

int main()
{
    foo(1); // foo(int)
    foo(1.2); // foo(double)
}


//int2type
//    컴파일 타임 정수형 상수를 각각의 독립된 타입으로 만드는 기술
//    int2type을 사용하면 컴파일 타임에 결정된 정수형 상수를 모두 다른 타입으로 만들 수 있음
//        1, 2는 같은 타입이지만, int2type<1>, int2type<2>는 다른 타입
//    int2type을 함수 오버로딩에 사용하거나 템플릿 인자, 상속등에 사용할 수 있음

#include <iostream>
using namespace std;

// 같은 정수형 타입이지만 값에 따라 별도의 타입으로 생성
template<int N> struct int2type
{
    static constexpr int value = N;
};

int main()
{
    int2type<1> t0; // int2type<1> 타입
    int2type<2> t1; // int2type<2> 타입
}


//int2type 예제
//  printv 함수에서 받은 값의 포인터 타입 여부에 따라 분기처리 코드가 작성되어 값과 포인터 참조값을 출력하도록 되어 있음
//  포인터 여부는 컴파일 타임에 체크되지만 if 구문이 런타임 조건문으로 하위 코드들은 모두 컴파일 대상
//  포인터가 아닌 값에 대해서는 사용할 수 없는 구분이 포함되어 간접 참조 에러가 발생함.
// 
//  간접 참조 에러가 발생하는 구문을 별도의 함수 템플릿으로 분리함
//  각 함수 템플릿은 int2type을 활용하여 인자 타입으로 구분하여 사용
//  동일 이름을 가지는 함수가 여러개 있을때, 어느 함수를 호출할지는 컴파일 타임에 결정됨
//  호출이 결정되지 않은 템플릿은 instantiation 되지 않음

#include <iostream>
using namespace std;


// 포인터 타입 체크용 메인 템플릿
template<typename T> struct is_pointer_custom
{
    //enum { value = false }; 
    static constexpr bool value = false; // c++11
};

// 포인터 타입에 대해서 부분 특수화 필요
template<typename T> struct is_pointer_custom<T*>
{
    //enum { value = true };
    static constexpr bool value = true; // 포인터 이면 true
};

//...


// 같은 정수형 타입이지만 값에 따라 별도의 타입으로 생성되는 타입 도구
template<int N> struct int2type
{
    static constexpr int value = N;
};

// 컴파일 타임 상수 값 구분용 함수 템플릿
template<typename T>
void printv_imp(T v, int2type<1>)
{
    cout << v << " : " << *v << endl;
}

// 컴파일 타임 상수 값 구분용 함수 템플릿
template<typename T>
void printv_imp(T v, int2type<0>)
{
    cout << v << endl;
}

// 값을 받아서 출력하고, 포인터일 경우 포인터의 값까지 출력
template<typename T> void printv(T v)
{
    // 아래의 조건으로 분기 코드 작성시 
    // if 구문이 런타임 조건문으로, 포인터가 아닌 값에 대해서 컴파일 에러 발생, 어떻게 해결 ?

    //if(is_pointer_custom<T>::value)
    //    cout << v << " : " << *v << endl;
    //else
    //    cout << v << endl;

    // 출력 구현부를 별도로 분리하여 함수 템플릿으로 타입을 구분하여 문제 해결 가능

    printv_imp(v, int2type<is_pointer_custom<T>::value>());
    // is_pointer_custom 반환 값에 의해(포인터: int2type<1>, 포인터 아님: int2type<0> 타입)
}

int main()
{
    int n = 3;
    printv(n);
    printv(&n);
}


//integral_constant 예제 ---------------------------------------------------------------------------------
//
//int뿐 아니라 모든 정수 계열 상수 값을 타입으로 만들 수 있게 하는 템플릿 (실수는 템플릿 인자 사용X)
//    bool, char, short, int, long, long long
// 
//true_type, false_type
//    true / false: 참 거짓을 나타내는 값, 서로 같은 타입
//    true_type / false_type : 참 거짓을 나타내는 값, 서로 다른 타입
// 
//is_pointer등의 type_traits를 만들때 intergral_constant를 기반 클래스로 사용하여 간소화 및 가독성을 높일 수 있음
//    T가 포인터가 아니라면, value = false, 기반 클래스는 false_type
//    T가 포인터라면, value = true, 기반 클래스는 true_type

#include <iostream>
using namespace std;

template<typename T, T N>
struct integral_constant
{
    static constexpr T value = N;
};

{
    // int 타입 0, 1 서로 다른 타입
    integral_constant<int, 0> t0;
    integral_constant<int, 1> t1;

    // short 타입, 0, 1 서로 다른 타입
    integral_constant<short, 0> s0;
    integral_constant<short, 1> s1;

    // bool 타입, true, false 서로 다른 타입
    integral_constant<bool, true> tb1;
    integral_constant<bool, false> tb0;
}

// bool 타입은 활용 빈도가 높으므로 true_type, false_type 별칭 만들어서 사용
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template<typename T>
struct is_pointer : false_type
{
    // false_type 상속으로 아래 코드 생략 ***
    //static constexpr bool value = false;
};

template<typename T>
struct is_pointer<T*> : true_type
{
    // true_type 상속으로 아래 코드 생략
    //static constexpr bool value = true;
};


//C++11 type_traits 활용하여 int2type 예제 간소화 ---------------------------------------------
//
//      C++11 <type_traits> 헤더 포함
//      int2type<0>, int2type<1>                        ->  integral_constant<0>, integral_constant<1>
//      integral_constant<0>, integral_constant<1>      ->  false_type, true_type

#include <iostream>
#include <type_traits>
using namespace std;

// 컴파일 타임 상수 값 구분용 함수 템플릿
template<typename T>
void printv_imp(T v, true_type) {                   //true_type 형식
    cout << v << " : " << *v << endl;
}

// 컴파일 타임 상수 값 구분용 함수 템플릿
template<typename T>
void printv_imp(T v, false_type) {
    cout << v << endl;
}

// 값을 받아서 출력하고, 포인터일 경우 포인터의 값까지 출력
template<typename T> void printv(T v)
{
    printv_imp(v, is_pointer<T>());
}

int main()
{
    int n = 3;
    printv(n);
    printv(&n);
}


//C++17 // if constexpr 를 사용하여 컴파일 타임에 분기처리 가능 ----------------------------

#include <iostream>
#include <type_traits>
using namespace std;

// 값을 받아서 출력하고, 포인터일 경우 포인터의 값까지 출력
template<typename T> void printv(T v)
{
    if constexpr (is_pointer<T>::value)
        cout << v << " : " << *v << endl;
    else
        cout << v << endl;
}

int main()
{
    int n = 3;
    //double n2 = 3.1;
    printv(n);
    printv(&n);
}
