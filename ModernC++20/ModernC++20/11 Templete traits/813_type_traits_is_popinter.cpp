//type traits 개념
//    컴파일 타임에 타입에 대한 정보를 얻거나 변형된 타입을 얻을때 사용하는 도구(메타 함수)
//    <type_traits> 헤더로 제공됨 (c++11)
 
//type query를 위한 type traits 만드는 방법
//    메인 템플릿(Primary template)에서 false 반환(value = false)
//    부분 특수화(Partial specialization)에서 true 반환(value = true)

//is_pointer 예제
//    간단히 템플릿 파라미터 T가 포인터 타입 여부 확인 도구
//    메인 템플릿(Primary template)에서 false 반환(value = false)
//    포인터 타입용 부분 특수화(Partial specialization)에서 true 반환(value = true)

#include <type_traits>

int main()
{
    class A {};

    static_assert(
        not std::is_pointer<A>::value
        && not std::is_pointer_v<A>   // same thing as above, but in C++17!
        && not std::is_pointer<A>()   // same as above, using inherited operator bool
        && not std::is_pointer<A>{}   // ditto
        && not std::is_pointer<A>()() // same as above, using inherited operator()
        && not std::is_pointer<A>{}() // ditto
        && std::is_pointer<A*>::value
        && std::is_pointer<A const* volatile>()
        && not std::is_pointer<A&>::value
        && not std::is_pointer<int>::value
        && std::is_pointer<int*>::value
        && std::is_pointer<int**>::value
        && not std::is_pointer<int[10]>::value
        && not std::is_pointer<std::nullptr_t>::value
        );
}
//---------------------------------------------------------------------------

#include <iostream>
#include <type_traits>
using namespace std;

template<typename T> struct is_pointer_custom
{
    enum { value = false };
};

// 포인터 타입에 대해서 부분 특수화 필요
template<typename T> struct is_pointer_custom<T*>
{
    enum { value = true };
};

template<typename T> void foo(T v)
{
    if (is_pointer_custom<T>::value)
        cout << "pointer" << endl;
    else
        cout << "not pointer" << endl;
}

int main()
{
    int n = 3;
    foo(n);
    foo(&n);
}

//is_pointer 개선 예제 ---------------------------------------------------

//c++11 기준 코드 개선
//좀더 다양한 포인터 타입 지원(const, volatile, const volatile)

#include <iostream>
#include <type_traits>
using namespace std;

template<typename T> struct is_pointer_custom
{
    //enum { value = false }; 
    static constexpr bool value = false; // c++11
};

// 포인터 타입에 대해서 부분 특수화 필요
template<typename T> struct is_pointer_custom<T*>
{
    //enum { value = true };
    static constexpr bool value = true; // c++
};

// 포인터 타입에 대해서 부분 특수화 필요
template<typename T> struct is_pointer_custom<T* const>
{
    //enum { value = true };
    static constexpr bool value = true; // c++
};

// 포인터 타입에 대해서 부분 특수화 필요
template<typename T> struct is_pointer_custom<T* volatile>
{
    //enum { value = true };
    static constexpr bool value = true; // c++
};

// 포인터 타입에 대해서 부분 특수화 필요
template<typename T> struct is_pointer_custom<T* const volatile>
{
    //enum { value = true };
    static constexpr bool value = true; // c++
};

int main()
{
    cout << is_pointer_custom<int>::value << endl;
    cout << is_pointer_custom<int*>::value << endl;
    cout << is_pointer_custom<int* const>::value << endl;
    cout << is_pointer_custom<int* volatile>::value << endl;
    cout << is_pointer_custom<int* const volatile>::value << endl;
    cout << is_pointer_custom<int* volatile const>::value << endl;
}
