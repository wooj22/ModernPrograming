//assert
// 
//	런타임시 들어온 인자가 false 이면 Assertion failed 를 출력하며 프로그램을 종료시킨다.
//  디버그 모드에서 작동

//-----------------------------------------------------
#include <iostream>
#include <cassert> 
using namespace std;

int main()
{
    int number = 5;
    assert(number == 4);            //

    return 0;
}

//-----------------------------------------------------
#include <iostream>
#include <cassert> 
#include <array> 
using namespace std;

void printValue(const array<int, 5>& my_array, const int& ix)
{
    assert(ix >= 0);
    assert(ix <= my_array.size() - 1);

    std::cout << my_array[ix] << std::endl;
}

int main()
{
    array<int, 5> my_array{ 1, 2, 3, 4, 5 };

    printValue(my_array, 4);
    printValue(my_array, 5);    //

    return 0;
}

//static_assert 
// 
//	C++11부터는 런타임에서만 사용 가능한 assert() 이외,
//	컴파일 시점에도 사용이 가능한 static_assert() 를 제공한다.

//-----------------------------------------------------
#include <cassert>
using namespace std;

static_assert(1 > 2, "error");      //컴파일 error

static_assert(sizeof(double) > 8, "error!!");

int main()
{

}

//-----------------------------------------------------
//type_traits와 같이 사용하기 
// 
//  템플릿 내부에서  
//  에러를 좀 더 이쁘게 보여주고 
//  사용 가능한 타입을 필터링하기 위해 static_assert를 사용할 수 있다.

#include <cassert>
using namespace std;

template<typename T>
T square(T a)
{
    return a * a;
}

int main()
{
    int n = 7;
    square(n);              // ok

    square(&n);             // 포인터로 넘겨버렸다!! 빌드 error
}

//square 함수에서 정수형과 실수형만 허용하고자 한다면 다음과 같이 작성이 가능하다.

#include <iostream>
#include <cassert>
using namespace std;

template<typename T>
T square(T a)
{
    static_assert(is_integral<T>::value, "T should be integer");        //에러 출력
    //static_assert(is_integral<T>::value || is_floating_point<T>::value, 
    //"T should be integer or floating point value");
    return a * a;
}

int main()
{
    int n = 7;
    square(n);

    square(&n);             // 포인터! error
}

//type_traits 
//  컴파일 시점에 타입 정보를 분석하거나 변환하기 위한 메타프로그래밍 도구 모음 
// 
//  형식 인수의 속성에 대한 정보를 제공하거나 
//  변환된 형식을 생성하는 컴파일 시간 상수에 대한 템플릿을 정의
//  https://learn.microsoft.com/ko-kr/cpp/standard-library/type-traits?view=msvc-170
//
//왜 중요한가?
//  표준 라이브러리의 절반이 type_traits 기반
//  템플릿 기반 엔진/게임 엔진 구조에서 필수