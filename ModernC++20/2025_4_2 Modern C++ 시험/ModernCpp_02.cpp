// invoke 사용하기
// 
// MyStruct 객체의 맴버 함수를 호출하는 코드입니다.
// 아래 표시된 문장을 
// invoke 함수를 이용해 호출하는 코드로 '변경'하세요.

#include <iostream>
#include <functional> 

struct MyStruct
{
    const int data = 0;
    int func(const int i) { return data; }
};

int main()
{
    MyStruct s;

    std::cout << std::invoke(&MyStruct::func, s, 10) << std::endl;;
}
