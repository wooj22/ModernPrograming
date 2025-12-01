//typename 키워드 1
//      템플릿 매개변수를 선언하는 경우 
//      템플릿 매개변수를 선언하는 경우의 class 및 typename은 완전히 같은 의미 

    template <typename T> class Widget;
    template <class T> class Widget;

//typename 키워드 2
//      템플릿에서 타입이라고 알려주기 위해 typename을 사용하는 경우

//      템플릿에서 클래스이름::xx 접근 가능한 요소들
//      값 : enum 상수, static 멤버 변수
//      타입 : typedef, using



//템플릿 매개변수를 선언 ----------------------------------------------------------------

#include <iostream>
    template <typename T>
    class MyTypeClass
    {
    public:
        typedef T A;
        static int B;
        class C {};
        static void D(void) {}
    };

    void foo()
    {
        MyTypeClass<int>::A* E;     //1번 A의 포인트 변수 E를 선언
        MyTypeClass<int>::B* F;     //2번 정적 변수 B와 변수 F를 곱셈
        MyTypeClass<int>::C* G;     //3번 하위 클래스인 C의 포인트 변수 G를 선언
        MyTypeClass<int>::D* H;     //4번 정적 함수 D와 변수 H를 곱셈하는 코드
    }


//의존이름(dependent name) ------------------------------------------------------------
//      템플릿 매개변수 T 에 의존하는 이름 ***

    template<typename T>
    void f()
    {
        T::A* pa;       //T::A  // 템플릿 매개변수 T에 의존 
    }

//전용 가능한 이름 검색에서 타입 이름이 나오거나, typename으로 정의 되지 않는 한 
//템플릿 선언이나 정의에서 사용되고 템플릿 매개변수에 의존적인 이름은 타입의 이름으로 쓰일 수 없다 ***
//
//즉, '템플릿 안'에서 '의존 타입'이면 typename 을 붙여야 한다. ***

    template <class C>
    struct something
    {
        typedef typename C::value_type value_type;      //그 멤버 이름과 똑같이 짓는 것이 관례
        typedef typename value_type::is_const is_const;
    };

//규칙은 의존적 이름 하나마다 typename 하나씩 붙인다.

    template <class Sequence>
    struct key_iterator_generator
    {
        typedef typename projection_iterator_gen<
            select1st<typename Sequence::value_type>,
            typename Sequence::const_iterator
        >::type type;
    };

//비의존적(non-dependent) 이름이면 typename 붙여도 되고 안 붙여도 됩니다.

//템플릿 없으면 붙이면 안됩니다.


//------------------------------------------------------------------------------------
//using 선언에서 종속 이름

//using 선언(using declaration)은 네임스페이스와 클래스라는 두 공간의 이름을 불러들이는 것을 말한다

    class BX
    {
    public:
        void f(int);
        void f(char const*);
        void g();
    };

    class DX : private BX
    {
    public:
        using BX::f;
    };

   
//종속이름에 대해 using 선언으로 해당 데이터형(type)까지 불러들이고 싶다면 
//    키워드 typename을 삽입해 명시적으로 알려야 한다 ****

    // 이름에 대해서는 이미 알고 있지만 
    // 이것이 데이터형 이름인지, 템플릿 이름인지 혹은 그 외 것의 이름인지에 대해서는 모른다.

    template<typename T>
    class BXT
    {
    public:
        typedef T Mystery;                  //여기에 접근 

        template<typename U>
        struct Magic;
    };

    template<typename T>
    class DXTT : private BXT<T>
    {
    public:
        using typename BXT<T>::Mystery;     //typename
        Mystery* p;
    };