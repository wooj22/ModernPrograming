//--------------------------------------------------------------------------------------
//typename 키워드
//      템플릿 의존적으로 타입의 이름에 접근할때는 typename 키워드를 붙여야한다. ***
 
//--------------------------------------------------------------------------------------
//template 키워드
//      종속적인 템플릿 이름은 template 키워드를 함께 사용해야 합니다. ***
//      데이터형 이름 T 와 함께 <>를 쓰는 경우 
//      컴파일러는 프로그래머가 template라는 키워드를 프로그램에 직접 사용하지 않으면 
//      종속 이름이 템플릿을 참조한다고 간주하지 않는다. 

#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Test
{
public:
    template<typename T> static void f() {}
    template<typename T> class Complex {};
};

template<typename T> void foo(T a) // T: Test
{
    // OK
    Test::f<int>();

    // Error(임의 타입 T에서 < 연산자의 정의를 알 수 없음)
    T::f<int>(); 

    // OK(임의 타입 T로 사용할 경우 ::template 키워드를 사용해야한다.)
    T::template f<int>();


    // OK
    Test::Complex<int> c1;

    // Error(::Complex가 값인지 타입인지 알수 없음)
    T::Complex<int> c2; 

    // Error(임의 타입 T에서 < 연산자 정의를 알 수 없음)
    typename T::Complex<int> c3; 

    // OK(임의 타입 T로 사용할 경우 ::template 키워드를 사용해야한다.)
    typename T::template Complex<int> c4;
}

int main()
{
    Test t;
    foo<Test>(t);
}

// 충첩된 경우, 키워드 template 이 필요한 경우 -----------------------------
/*

    #include <iostream>
    #include <vector>
    #include <list>
    using namespace std;

    template<class T> class Shell {
    public:
        template<int N> class In {
        public:
            template<int M> class Deep {
            public:
                virtual void f()  {}
            };
        };
    };

    template<typename T, int N>
    class Weird {
    public:
        void case1(typename Shell<T>::template In<N>::template Deep<N>* p) {
            p->template Deep<N>::f();       //
        }
        void case2(typename Shell<T>::template In<N>::template Deep<N>& p) {
            p.template Deep<N>::f();        //
        }
    };


    //Weird 클래스의 case1 함수를 호출해 보세요. ***

    int main()
    {
        Weird<int, 2> obj;

        //Shell<int> o;
        //Shell<int>::In<2>::Deep<2> d;
        //obj.case1(&d);
    }

*/


//template 키워드 --------------------------------------------------

#include <iostream>    
using namespace std;

int const VAL = 5;

struct something
{
    template<int n>  void A(int value) {}

    int B;
};

template <class T>
void f(T& x)
{
    x.A<3>(VAL);    //1번          
    x.B<3>(VAL);    //2번          
}

int main()
{
    something thing;
    f(thing);
}

//1번은 x의 멤버 함수 템플릿 A를 호출하는 코드
//2번은 x의 멤버 변수 B와 3을 < 비교한 논리값(0 or 1) 을 다시 VAL과 >비교하는 코드
/*
    void f(T& x)
    {
        x.template A<3>(VAL);   //1번
        x.B<3>(VAL);            //2번
    }
*/

//--------------------------------------------------------------------------------------
//멤버 템플릿 특수화의 이름이 
//  후위 표현식(postfix-experssion) 안의 . 나 -> 뒤 또는 
//  한정된 식별자(qualified-id) 안의 내포된 이름 지정자(nested-name-specifier) 뒤에 나오며 
//
//  템플릿 매개변수(template-parameter)에 명시적으로 의존하는 경우는 
//  template 키워드 사용

// . -> :: 한정을 통해서 멤버 템플릿에 접근하는 의존적 이름 앞에는 template 키워드 사용 ***

    template <class T> void f(T& x, T* y)
    {
        int n = x.template convert<int>();              // .
        int m = y->template convert<int>();             // ->
    }

//typename과 달리 template 키워드는 기반 클래스를 나타내는 클래스 템플릿 이름에서도 필수 입니다 

    template <class T>
    struct other
    {
        template <class U> struct base;
    };

    template <class T> struct other;

    template <class T>
    struct derived : other<T>::template base<int>       //기반 클래스의 템플릿
    {};

    //템플릿 안 어디서든 실질적으로 멤버 템플릿 식별자 앞에 들어가는 경우라면 
    // template을 붙여도 되고 안해도 됩니다

    template <class T>
    struct derived1 : other<int>::base<T>               //안 해도 되고
    {};

    template <class T>
    struct derived2 : other<int>::template base<T>      //붙여도 된다.
    {};


//템플릿 바깥에서는 template 키워드는 안됩니다. 명시적(완전) 템플릿 특수화도 템플릿 바깥에 해당합니다

    template <> struct derived<int>: other<int>::template base<int>  //오류
    {};

//using 선언(using-declaration) 안에서도 template 사용하면 안됩니다

    template <class T>
    struct derived : base<T>
    {
        using base<T>::template apply;  //오류
    };
