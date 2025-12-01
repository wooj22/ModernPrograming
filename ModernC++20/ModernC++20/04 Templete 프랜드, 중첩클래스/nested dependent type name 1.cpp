//typename

//중복의존 타입과 템플릿 구현시 오류 해석하기

#include <iostream>
using namespace std;

template <typename T>
void func() 
{
     T::t * p;                // t 는 T에 의존한다.  컴파일러는 value로 해석함. 잘못된 코드로 컴파일 실패

     //typename T::t* p;      //1. func<A>();   // t 가 타입이라고 알려주어야 한다.  

     //int p = 0;
     //p = T::t * p;          //2. func<B>();   // T::t 를 value로 사용 
}

struct A {
    using t = int;
};

struct B {
    const static int t = 0;
};

int main(void)
{
    func<A>();
    func<B>();
}