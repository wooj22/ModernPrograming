//C++11 표준 type_traits 예제 -------------------------------------------------------------
//
//      is_pointer, remove_pointer

// 변형된 타입을 얻는 traits
//      typename remove_pointer<T>::type;
//      remove_pointer_t<T> n;  // C++14
// 
// 타입의 정보를 조사하는 traits
//      bool b = is_pointer<T>::value;
//      bool b = is_pointer_v<T>;  // C++17
//      함수 오버로딩 사용(true_type, false_type) 활용


//간소화된 버전
//      C++14 기본 제공      remove_pointer_t<T> n;
//      C++17 기본 제공      bool b = is_pointer_v<T>;


#include <iostream>
#include <type_traits>
using namespace std;

//using을 사용해서 간소화 가능
template<typename T>
using remove_pointer_type = typename remove_pointer<T>::type;

// C++17에서는 variable template을 사용해서 간소화 가능
//template<typename T>
//inline constexpr bool is_pointer_v = is_pointer<T>::value;

template<typename T> void foo(T a)
{
    // 포인터를 제거한 타입 반환
    typename remove_pointer<T>::type rawType;
    remove_pointer_type<T> rawType2;

    // 포인터 타입 여부 확인
    bool isPointer = is_pointer<T>::value;
}

int main()
{
    int n = 0;
    foo(&n);
}


//C++11 표준 type_traits 예제 -------------------------------------------------------------
// 
//  is_array<T>::value : 배열 확인
//  extent<T, 0>::value : 배열 각 차원의 요소 수 
//  is_same<T, U>::value : 타입 같음 비교
//  remove_cv<T, U>::type : const, volatile 속성 제거(타입 비교시 이용)
//  decay<T, U>::type : 배열을 포인터화 사용 필요 시


#include <iostream>
#include <type_traits>
using namespace std;

// 배열 정보 조사하기
// array => pointer : decay
template<typename T> void foo(T& a)
{
    if (is_array<T>::value)
    {
        cout << "array" << endl;

        cout << extent<T, 0>::value << endl;
        cout << extent<T, 1>::value << endl;
    }
}

template<typename T, typename U> void hoo(T a, U b)
{
    // 두 타입 비교
    bool ret1 = is_same<T, U>::value;

    // 배열일 경우 포인터화 비교
    bool ret2 = is_same<typename decay<T>::type, typename decay<U>::type>::value;

    // const, volatile 제거 후 비교
    bool ret3 = is_same<typename remove_cv<T>::type, typename remove_cv<U>::type>::value;

    cout << ret1 << endl;
    cout << ret2 << endl;
    cout << ret3 << endl;
}

int main()
{
    int x = 1;
    const int cx = 1;
    int* xp = &x;
    int a[3][2] = { 1,2,3,4,5,6 };
    foo(a);
    hoo(x, cx);
}
