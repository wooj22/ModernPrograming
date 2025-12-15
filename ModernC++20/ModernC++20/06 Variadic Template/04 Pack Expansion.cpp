//Pack Expansion 예시

//배열 혹은 initializer_list를 이용한 가변 인자의 Pack Expansion의 경우에는 편하지만 
//      동일 타입에 대해서만 가능한 단점
//      서로 다른 타입들이 넘어오는 경우에는?  --> 재귀, 튜플 활용

//Tuple Pack Expansion -------------------------------------------------------------------
//      array or tuple에 담기

#include <iostream>
#include <tuple>
using namespace std;

template<typename ... Types>
void foo(Types ... args)
{
    // 각각의 타입별 값을 tuple 개별 요소로 추가
    tuple<Types...> tp(args...);

    cout << get<0>(tp) << endl;
    cout << get<1>(tp) << endl;
    cout << get<2>(tp) << endl;
}

int main()
{
    foo(1, 2.3, "456");
}

//재귀호출 스러운 Pack Expansion ----------------------------------------------------------
//      재귀 호출과 유사한 호출식을 사용하기
//      1번째 인자는 이름 있는 변수, 2번째 인자는 가변 인자로 구현

#include <tuple>

void foo() {}  // 재귀 호출 종료용

template<typename T, typename ... Types>
void foo(T arg1, Types ... args)
{
    std::cout << arg1 << std::endl;
    foo(args...);
}

int main()
{
    foo(1, 2.3, "456");
}

// 아래처럼 반복 호출 됨
// foo(1, 2.3, "456")
// foo(2.3, "456")
// foo("456")
// foo()  - 일반 함수
// 
// 템플릿 함수는 컴파일 시간에 컴파일러에 의해 각각 타입에 대한 함수를 생성하게 되므로 오버로딩 된 함수를 호출하게 된다.


//재귀 함수 호출을 종료하기 위해 베이스 케이스를 꼭 만들어줘야 한다는 점이 불편.
// 
//하지만 C++ 17 에 새로 도입된 Fold 형식을 사용한다면 이를 훨씬 간단하게 표현


