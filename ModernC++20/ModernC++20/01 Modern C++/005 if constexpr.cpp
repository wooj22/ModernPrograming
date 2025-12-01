//if constexpr
//		일반적인 if문은 실행시간에 조건식을 조사하지만 
//		if constexpr은 컴파일 시간에 조건식을 조사.
// 
//		조건식은 반드시 컴파일 시간에 값을 결정할 수 있어야 한다. (static if 라고도 불린다.)
//		탬플릿을 만들 때 주로 사용함. (일반적인 코딩에서는 잘 사용하지 않음...)

#include <iostream>
using namespace std;

int main()
{
    int n = 0;

    if (n == 0)
    {
    }

    if constexpr (n == 0)  // error //컴파일시간에 확정 안됨.
    {
    }

    if constexpr (sizeof(n) == 0)  // ok..
    {
    }

}

//if constexpr 가 템플릿에서 사용되는 예제

template<typename T>
void foo(T a)
{
    if (0)            // 실행 중에 해당 조건이 체크됨. 컴파일 단계에서 if 안의 코드 수행 체크됨.
        *a = 0;

    //if constexpr (0)    // 컴파일 중에 해당 조건을 체크하기 때문에 *a = 0; 코드를 수행 X
    //    *a = 0;
}

int main()
{
    int n = 0;

    foo(&n); // T : int*    //주소  //*a = 0; 코드 컴파일 통과.

    foo(n);  // T : int     //주소가 아니므로 *a = 0; 에서 error  // if constexpr 로 변경하면 통과.
}
