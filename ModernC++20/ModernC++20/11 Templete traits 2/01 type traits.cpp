//type_traits 는 타입에 대한 상수 정보를 가진 구조체다.  //C++
// 
//      Type의 다양한 속성들에 대해 조사할 수도, 프로퍼티를 변경할 수도 있다.


//사용 예시 //type traits 중에 하나인 std::is_floating_point
//
//      template<typename T> 
//      struct is_floating_point;

#include <iostream>
#include <type_traits>
using namespace std;

class Class {};

int main()
{
    cout << std::is_floating_point<Class>::value << '\n';
    cout << std::is_floating_point<float>::value << '\n';
    cout << std::is_floating_point<int>::value << '\n';
}

/*
//개념적으로 이런식의 클래스가 생성된다.
    struct is_floating_point<Class> { ​​​static const bool value = false; };
    struct is_floating_point<float> { ​​​​static const bool value = true; };
    struct is_floating_point<int> { ​​​static const bool value = false; };
*/


//사용 예시 //조건부 컴파일 ---------------------------------------------------------
// 
//  int가 인자로 전달 될 때 컴파일러가 signed에 관련된 알고리즘 함수를 선택하고, 
//  unsigned int가 전달 될때는 unsigned에 최적화된 함수를 선택하여 컴파일 하도록 해보자.

#include <iostream>
#include <type_traits>
using namespace std;

void algorithm_signed(int i) { cout << "algorithm_signed" << endl; }
void algorithm_unsigned(unsigned u) { cout << "algorithm_unsigned" << endl; }

template <typename T>
void algorithm(T t)
{
    if constexpr (std::is_signed<T>::value) {
        algorithm_signed(t);
    }
    else if constexpr (std::is_unsigned<T>::value) {
        algorithm_unsigned(t);
    }
    else {
        static_assert(std::is_signed<T>::value || std::is_unsigned<T>::value,
            "Must be signed or unsigned!");
    }
};

int main()
{
    algorithm(3);       // T 가 int, algorithm_signed()이 컴파일에 포함된다.

    unsigned x = 3;
    algorithm(x);       // T 가 unsigned int, algorithm_unsigned()가 컴파일에 포함된다.

    algorithm("hello"); // T 가 string, 빌드 에러!!
}


//사용 예시 //타입 변경하기 ------------------------------------------------------------
//
//  std::move (타입 T를 rvalue 레퍼런스 타입인 T&&로 변경해주는 유틸리티 함수) 의 경우

template <typename T>
typename remove_reference<T>::type&& move(T&& arg)
{
    ​​return static_cast<typename remove_reference<T>::type&&>(arg);    //std::remove_reference 타입 트레이츠를 사용
}



//깔끔하게 type traits 사용하기

std::is_signed<T>::value;
std::is_signed_v<T>;        //C++14

std::remove_const<T>::type;
std::remove_const_t<T>;     //C++14
