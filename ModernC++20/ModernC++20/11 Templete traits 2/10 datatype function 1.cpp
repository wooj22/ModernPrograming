//데이터형 함수
//      데이터형 함수는 데이터형 인자를 받아 결과로 데이터형이나 상수를 생성한다

//클래스형 결정 -------------------------------------------------------------------------------

//SFINAE(Substitution Failure Is Not An Error 치환 실패는 오류가 아님) 법칙을 사용한다.
//SFINAE는 활용할 때 중요한 것은 클래스형에서는 유효하지 않지만 다른 데이터형에서는 유효하거나 그 반대인 데이터형 생성을 찾는 것이다.

#include <iostream> 

template<typename T>
class IsClassT {
private:
    typedef char One;                   // 1 byte
    typedef struct { char a[2]; } Two;  // 2 byte
    template<typename C> static One test(int C::*); // C 의 int 멤버를 가리키는 포인터 - 이 문법은 클래스에만 사용할 수 있다
    template<typename C> static Two test(...);      // Will be chosen if T is anything except a class.
public:
    enum { Yes = sizeof(IsClassT<T>::test<T>(0)) == 1 };
    enum { No = !Yes };
};

// 템플릿 인자로 전달해 확인
template <typename T>
void check()
{
    if (IsClassT<T>::Yes)   std::cout << " IsClassT " << std::endl;
    else                    std::cout << " !IsClassT " << std::endl;
}

// 함수 호출 인자로 전달해 확인
template <typename T>
void checkT(T)
{
    check<T>();
}

class MyClass {};

struct MyStruct {};

union MyUnion {};

void myfunc() {}

enum E { e1 }e;

int main()
{
    std::cout << "int     : ";    check<int>();

    std::cout << "MyClass : ";    check<MyClass>();

    std::cout << "MyStruct: ";    MyStruct s;  checkT(s);

    std::cout << "MyUnion : ";    check<MyUnion>();

    std::cout << "enum    : ";    checkT(e);

    std::cout << "myfunc(): ";    checkT(myfunc);
}


//---------------------------------------------------------------

#include <type_traits>
#include <iostream>

struct Trivial
{
    int val;
};

int main()
{
    std::cout << "is_class<Trivial> == " << std::boolalpha
        << std::is_class<Trivial>::value << std::endl;
    std::cout << "is_class<int> == " << std::boolalpha
        << std::is_class<int>::value << std::endl;

    return (0);
}