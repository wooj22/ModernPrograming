//type traits 기능(C++11)

//type에 대한 query : is_pointer<>, is_array<>, extent<>
//type에 대한 변형 타입 : remove_pointer<>, add_pointer<>

#include <iostream>
#include <type_traits>
using namespace std;

template<typename T> void foo(T a)
{
    bool b = is_pointer<T>::value;
    typename remove_pointer<T>::type t;

    cout << b << " " << typeid(t).name() << endl;
}

int main()
{
    int n = 10;
    foo(n);
    foo(&n);
}

//remove_pointer 구현 예제 -------------------------------------------------------
// 
//  remove_pointer_custom 메인 템플릿 생성
//      int -> int 반환
//  remove_pointer_custom 부분 특수화(Partial specialization) 생성
//      int* -> int 반환

#include <iostream>
using namespace std;

// Main template
template<typename T>
struct remove_pointer_custom
{
    typedef T type;
};

// Partial specialization
template<typename T>
struct remove_pointer_custom<T*>
{
    typedef T type;
};

template<typename T> void foo(T a)
{
    // 값이 아닌 타입을 꺼낼때는 typename을 꼭 사용 필요
    typename remove_pointer_custom<T>::type t;

    cout << typeid(t).name() << endl;
}

int main()
{
    int n = 10;
    foo(&n);
}


//remove_all_pointer 구현 예제 -------------------------------------------------------
// 
//    중첩 포인터까지 모두 제거 되는 remove_pointer 구하는 방법

#include <iostream>
using namespace std;

template<typename T>
struct remove_all_pointer_custom
{
    typedef T type;
};

template<typename T>
struct remove_all_pointer_custom<T*>
{
    // 포인터 타입일때까지 포인터를 제거하며 자기 자신을 호출하고 최종 메인 템플릿이 호출됨
    typedef typename remove_all_pointer_custom<T>::type type;
};

int main()
{
    typename remove_all_pointer_custom<int**>::type n;
    cout << typeid(n).name() << endl;
}
