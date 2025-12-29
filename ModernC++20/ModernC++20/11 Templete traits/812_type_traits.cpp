//템플릿 메타 함수 (template meta function)
// 
//      함수는 아니지만 마치 함수 처럼 동작하는 탬플릿 클래스.
//      컴파일 시간에 '타입에 대한 정보'를 얻거나 '변형된 타입'을 얻을 때 사용.


//템플릿 메타 함수를 만들자. 
//type_traits 만들기       - 템플릿에서 사용하기 위한 여러 특질
// 
//예시) is_void<>  //void 타입인지 아닌지 구별하는 탬플릿 클래스

#include <iostream>

template <typename T>
struct is_void {            //상수값을 같는 구조체 //메타함수 역활
    static constexpr bool value = false;
};

template <>                 //특수화 이용해서 분기 구현
struct is_void<void> {
    static constexpr bool value = true;
};


template <typename T>
void tell_type() {
    if (is_void<T>::value) {
        std::cout << "T 는 void ! \n";
    }
    else {
        std::cout << "T 는 void 가 아니다. \n";
    }
}

int main() 
{
    tell_type<int>();       // void 아님!
    tell_type<void>();      // void!
}

// 템플릿 메타 함수 들을 제공해주는 type_traits 라이브러리 ***

//type traits
//    1. 컴파일 시간에 타입에 대한 정보를 얻거나 변형된 타입을 얻을 때 사용하는 도구(메타함수)
//    2. <type_traits> 헤더로 제공 (C++11부터)

#include <iostream>
#include <type_traits>      //

template <typename T>
void tell_type() {
    if (std::is_void<T>::value) {            
        std::cout << "T 는 void ! \n";
    }
    else {
        std::cout << "T 는 void 가 아니다. \n";
    }
}

int main() 
{
    tell_type<int>();       // void 아님!
    tell_type<void>();      // void!
}


//type_traits 라이브러리 ---------------------------------------------------------------

//type traits의 개념은 다음과 같다.
//	1. 컴파일 시간에 타입에 대한 정보를 얻거나 변형된 타입을 얻을 때 사용하는 도구(메타함수)
//	2. <type_traits> 헤더로 제공 (C++11부터)

//type traits는 크게 두 가지 기능을 제공한다.
//	1. 타입에 대한 조회
//	2. 타입에 대한 변형 타입 구하기 - 포인터 제거, 포인터 추가 등

https://en.cppreference.com/w/cpp/header/type_traits


//type_traits
//  형식 인수의 속성에 대한 정보를 제공하거나 
//  변환된 형식을 생성하는 컴파일 시간 상수에 대한 템플릿을 정의하고 있다.
//https://learn.microsoft.com/ko-kr/cpp/standard-library/type-traits?view=msvc-170

