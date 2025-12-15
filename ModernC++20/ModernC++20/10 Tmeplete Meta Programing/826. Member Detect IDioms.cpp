//C++ 템플릿 디자인 //Member Detect IDioms
// 
//      클래스의 멤버 타입 존재 여부 확인
//      클래스의 멤버 함수 존재 여부 확인
  

//컴파일 타임의 함수 시그니처에 대한 특성만 활용하는 특성을 이용하는 기법

// 함수 시그니처만 사용하므로 구현부가 없어도 괜찮음
char foo(int a);
short foo(double d);

int main()
{
    int n = 10;

    cout << sizeof(n) << endl;          // 4
    //cout << sizeof(foo) << endl;      // Error
    cout << sizeof(foo(3)) << endl;     // 1 char
    cout << sizeof(foo(3.3)) << endl;   // 2 short
}

//----------------------------------------------------------------------

#include <iostream>
#include <vector>
using namespace std;

// 멤버 타입을 가진 데이터용 템플릿(반환값이 char로 1바이트)
template<typename T>
char check(typename T::value_type* a);

// 멤버 타입이 없는 데이터용 템플릿(반환값이 short로 2바이트)
template<typename T>
short check(...);

// 멤버 타입 존재 여부를 확인하는 함수
template<typename T>
struct has_value_type
{
    // 반환값(value)이 char(1바이트)일때는 true, short(2바이트)일때는 false
    static constexpr bool value = (sizeof(check<T>(0)) == 1);
};


// 멤버 타입이 없는 데이터
struct NoValueType { };

// 멤버 타입이 있는 데이터
struct HasValueType { typedef int value_type; };

int main()
{
    cout << has_value_type<HasValueType>::value << endl;
    cout << has_value_type<NoValueType>::value << endl;

    HasValueType t1;
    cout << sizeof(check<HasValueType>(0)) << endl;
    NoValueType t2;
    cout << sizeof(check<NoValueType>(0)) << endl;
}

//----------------------------------------------------------------------
//예시) resize 함수가 존재하는지 알아보기

#include <iostream>
#include <vector>
using namespace std;

// 멤버함수가 존재할 경우 
template<typename T>
char check(decltype(T().resize(0))* a);

// 멤버함수가 존재하지 않을 경우
template<typename T>
short check(...);

// 멤버함수 존재 체크
template<typename T>
struct has_resize
{
    static constexpr bool value = (sizeof(check<T>(0)) == 1);
};

int main()
{
    // vector는 resize가 있으므로 true 리턴
    cout << has_resize<vector<int>>::value << endl;

    // array는 resize가 없으므로 false 리턴
    cout << has_resize<array<int, 10>>::value << endl;
}