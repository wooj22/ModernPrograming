//is_array 예제 
//      간단히 템플릿 파라미터 T가 배열 타입 여부 확인 도구
// 
//  메인 템플릿(Main template)에서 false 반환(value = false)
//  배열 타입 부분 특수화(Partial specialization)에서 true 반환(value = true)
//  타입을 정확히 알아야 함
//      int x[3]; 에서 x는 변수 이름, 변수 이름을 제외한 나머지 요소(int[3])이 타입임
//  unknown size array type(T[])에 대해서도 부분 특수화가 필요함


//std::is_array  ------------------------------------------------------

#include <array>
#include <iostream>
#include <type_traits>

class A {};

int main()
{
    std::cout << std::boolalpha;
    std::cout << std::is_array<A>::value << '\n';
    std::cout << std::is_array<A[]>::value << '\n';
    std::cout << std::is_array<A[3]>::value << '\n';
    std::cout << std::is_array<float>::value << '\n';
    std::cout << std::is_array<int>::value << '\n';
    std::cout << std::is_array<int[]>::value << '\n';
    std::cout << std::is_array<int[3]>::value << '\n';
    std::cout << std::is_array<std::array<int, 3>>::value << '\n';
}


//-------------------------------------------------------------------------------
//  is_array 구현

#include <iostream>
#include <type_traits>
using namespace std;

template<typename T> 
struct is_array_custom
{
    static constexpr bool value = false;
};

// 크기를 알 수 있는 배열의 부분 특수화
template<typename T, size_t N>
struct is_array_custom<T[N]>
{
    static constexpr bool value = true;
};

// 크기를 알 수 없는 배열의 부분 특수화
template<typename T>
struct is_array_custom<T[]>
{
    static constexpr bool value = true;
};

template<typename T> void foo(T& a)
{
    // 크기를 알 수 있는 배열 확인
    if (is_array_custom<T>::value)
        cout << "array" << endl;
    else
        cout << "not array" << endl;
}

int main()
{
    int x[3] = { 1, 2, 3 };
    foo(x);

    // 크기를 알 수 없는 배열을 사용하는 패턴도 존재함
    if (is_array_custom<int[]>::value)
        cout << "array" << endl;
}


//is_array 배열 크기 구하기 ----------------------------------------------
//      부분 특수화로 배열의 크기도 구할 수 있음
//      c++11 extent<T, 0>::value 존재

#include <iostream>
#include <type_traits>
using namespace std;

template<typename T> struct is_array_custom
{
    static constexpr bool value = false;
    static constexpr size_t size = -1;
};

//사이즈를 알 수 있는 배열에 대한 부분 특수화에서 N이 배열의 크기
template<typename T, size_t N>
struct is_array_custom<T[N]>
{
    static constexpr bool value = true;
    static constexpr size_t size = N;
};

template<typename T> void foo(T& a)
{
    if (is_array_custom<T>::value)
        cout << "size of array : " << is_array_custom<T>::size << endl;
}

int main()
{
    int x[3] = { 1, 2, 3 };
    foo(x);
}
