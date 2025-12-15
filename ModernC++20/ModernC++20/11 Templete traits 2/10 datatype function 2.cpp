//데이터형 함수
//      데이터형 함수는 데이터형 인자를 받아 결과로 데이터형이나 상수를 생성한다

//참조자와 한정자 -------------------------------------------------------------------------------

#include <type_traits>
#include <iostream>

template <typename T>
void apply(T& arg, void (*func)(T))
{
    func(arg);
}

void print(int a)           //int
{
    std::cout << a << std::endl;
}
void incr(int& a)           //int&
{
    ++a;
}

int main()
{
    int x = 7;
    apply(x, incr);         //int& & 가 되어 오류 
    apply(x, print);        //인자의 데이터형은 int&와 void(*)(int)  //ok

}

//데이터형이 참조자가 아닐 경우에만 "참조 연산자" 적용하는 데이터형 함수를 생성할 수 있다. 
//반대 연산인 참조 없애기(데이터형이 참조자일 경우에만)를 제공할 수 있다. 

#include <type_traits>
#include <iostream>

template <typename T>
class TypeOp {              // 기본 템플릿 
public:
    typedef T           ArgT;
    typedef T           BareT;
    typedef T const     ConstT;
    typedef T&          RefT;
    typedef T&          RefBareT;
    typedef T const&    RefConstT;
};

template <typename T>
class TypeOp <T const> {    // const형을 위한 부분 특수화
public:
    typedef T const     ArgT;
    typedef T           BareT;
    typedef T const     ConstT;
    typedef T const&    RefT;
    typedef T&          RefBareT;
    typedef T const&    RefConstT;
};

template <typename T>
class TypeOp <T&> {         // 참조를 위한 부분 특수화
public:
    typedef T& ArgT;
    typedef typename TypeOp<T>::BareT   BareT;
    typedef T const                     ConstT;
    typedef T&                          RefT;
    typedef typename TypeOp<T>::BareT&  RefBareT;
    typedef T const&                    RefConstT;
};

template<>
class TypeOp <void> {   // void를 위한 전체 특수화
public:
    typedef void         ArgT;
    typedef void         BareT;
    typedef void const   ConstT;
    typedef void         RefT;
    typedef void         RefBareT;
    typedef void         RefConstT;
};

template <typename T>
void apply(typename TypeOp<T>::RefT arg, void (*func)(T))
{
    func(arg);
}


void print(int a)           //int
{
    std::cout << a << std::endl;
}
void incr(int& a)           //int&
{
    ++a;
}

int main()
{
    int x = 7;
    apply(x, incr);         // 인자의 데이터형은 int&와 void(*)(int&)
    apply(x, print);        // 인자의 데이터형은 int&와 void(*)(int)
}
