//템플릿 매개변수 (Template parameters)
//      템플릿 선언 구문의 '매개변수'
//      type, non-type, or template
// 
//템플릿 인수 (Template arguments)
//      템플릿이 인스턴스화 될 때 템플릿 파라미터를 치환할 "값"
//      type, non-type, or template


//인자 추론 : 
//      '명시적'으로 제시되지 않은 함수 템플릿 인자는 
//      호출시, 함수 호출 '인수의 데이터형'을 통해 추론된다. ***

//Template 인수
//      Template type arguments         데이터형 인수 (타입)
//      Template non-type arguments     데이터형이 아닌 인수 (비타입)
//      Template template arguments     템플릿 인수

//-------------------------------------------------------------------------------------------------
1. 함수 템플릿 인수 추론

    #include <iostream>
    using namespace std;

    template <typename T>
    inline T const& max2(T const& a, T const& b)
    {
        return  a < b ? b : a;
    }

    int main()
    {
        max2(1.0, -3.0);          // 템플릿 인자는 묵시적으로 double로 추론

        max2<double>(1.0, -3.0);  // 명시적인 템플릿 인수

        max2<int>(1.0, 3.0);      // 명시인 <int> 표기로 추론하지 않음 // 결국 int형이 됨 
    }

    //출력은?

    #include <iostream>
    using namespace std;

    template <typename T = int>
    void func(T const& a)
    {
        std::cout << typeid(T).name() << std::endl;
    }

    int main()
    {
        func(1.0);                          // double
        func<int>(1.0);                     // int
        func<>(1.0);                        //                
    }

//어떤 템플릿 인자는 결코 추론 될 수 없다

    template <typename DstT, typename SrcT>
    inline DstT implicit_cast(SrcT const& x)   // SrcT 추론될수 있지만, DstT 추론 되지 않음 //warning
    {
        std::cout << typeid(x).name() << std::endl;
        return x;
    }

    int main()
    {
        double value1 = implicit_cast(-1);              //error

        double value1 = implicit_cast<double>(-1);      //-1
        double value2 = implicit_cast<int>(-1.0);       //-1.0
    }

//함수 템플릿은 오버로딩될 수 있기 때문에 
//함수 템플릿을 위해 모든 인자를 제공하는 것만으로는 필요한 함수를 식별하기 충분하지 않을 수 있다.

    #include <iostream>

    template <typename T> void multi(T) {};
    template <typename T> void multi(T&) {};

    int main()
    {
        int n = 0;
        multi(n);                   //추론 오류
        return 0;
    }

    //---------------------------------------------

    #include <iostream>

    template <typename Func, typename T>
    void apply(Func func_ptr, T x)
    {
        func_ptr(x);
    }

    template <typename T> void single(T) {}

    template <typename T> void multi(T) {}
    template <typename T> void multi(T*) {}

    int main()
    {
        apply(&single<int>, 3);

        apply(&multi<int>, 7);      //에러 //multi<int>가 하나가 아님, Func 추론 오류 

        return 0;
    }

//함수 템플릿을 위해 템플릿 인수를 명시한다면 옳지 않는 C++형을 생성하려 시도할 수도 있습니다.
//템플릿으로 치환이 실패하는 경우.

    template <typename T> int test(typename T::X a) { return 0; }   //치환 실패
    template <typename T> int test(T a) { return 0; }               //치환 성공

    int main(void)
    {
        std::cout << test(2);       // 컴파일 가능 ?
    }

    //SFINAE ***
    // 
    //  int를 첫번째 템플릿으로 치환하려는 시도가 '실패'했다고 해서 
    //  (int에는 X라는 데이터형을 갖는 멤버가 없으므로)
    //  표현식이 유효하지 않는 것이 아니라는 것 기억해야 합니다. 실패한 것만 무시합니다. ***
    // 
    //  치환 실패는 오류 아님(SFINAE : Substitution Failure Is Not An Error)법칙은 
    //  실제로 함수 템플릿을 오버로딩 할 경우 중요한 역할을 합니다.


//-------------------------------------------------------------------------------------------------
2. 데이터형 인수 (Template type arguments)

//A template argument for a type template parameter must be a type-id, (형식 이름)
//which may name an incomplete type ( 불완전한 형식도 가능하다. )

    template<typename T>
    class X {};             // class template

    struct A;               // incomplete type (불완전한 형식) - size 없음

    typedef struct {} B;    // type alias to an unnamed type

    int main()
    {
        X<A> x1;            // OK: 'A' names a type
        X<A*> x2;           // OK: 'A*' names a type
        X<B> x3;            // OK: 'B' names a type
    }

//템플릿 데이터형 인수로 할 수 없는 두가지가 있습니다
// 
//    이름 붙여지지 않은 클래스형(unnamed class type)이나 
//    이름 붙여지지 않은 열거형(unnamed enumeration type)에 속하는 데이터형은 
//    데이터형 인수가 될 수 없습니다
//
//    이름이 붙여지지 않은 클래스형이나 이름 붙여지지 않은 열거형이라도 
//    typedef로 이름을 부여한다면 데이터형 인수가 될수 있다.            ***   

    #include <iostream>

    template<typename T> class List { };

    enum { red, green, blue } *ColorPtr;

    struct { double x, y, z; } Point;

    typedef struct { double x, y, z; } Pos;

    int main()
    {
        List<ColorPtr> error2;      //에러 //이름 없는 열거형

        List<Point> ok;             //에러 //이름 없는 클래스형

        List<Pos> ok;               //이름 없는 클래스형을 typedef 로 이름 붙임
    }


//기타 데이터형은 템플릿 인수로 사용될 수 있지만 
//      이들 템플릿 파라미터 치환에 따른 템플릿 생성이 '유효'해야만 합니다. ***

    template<typename T>
    void clear(T P) {
        *p = 0;
    }

    int main()
    {
        int a;
        clear(a);       //error //int는 단항 연산자* 지원하지 않는다
    }

//-------------------------------------------------------------------------------------------------
3. 데이터형이 아닌 인수 (Template non-type arguments)

//컴파일 시 결정되는 '정수형(혹은 열거형)' 상수값.  ( C++20 이전 )
// 
//대응되는 파라미터가 그 값과 일치하는 데이터형을 가지거나  
//'묵시적으로 변환'될 수 있을 경우에만 가능합니다 (예를 들어 int 파라미터에 char가 제공된 경우) 
// 
//외부변수나 함수의 이름 앞에 &(의 주소) 연산자가 붙은 경우 
//함수나 배열변수일 경우 & 는 생략할 수 있습니다 (데이터형이 아닌 '포인터형' 파라미터)

    #include <iostream>

    int a = 0;

    template <typename T, T nontype_param>  // 타입, 그 타입의 값
    class C;                                
    //class C {};   // 미정의해도 포인터는 가능    

    class X {
    public:
        int n;
        static bool b;
    };
    bool X::b = false;

    template<typename T> void templ_func();

    int main()
    {
        C<int,  33>* c1;            // 정수형, 정수값

        C<int*, &a>* c2;            // 외부 변수의 주소

        void f();
        void f(int);
        C<void (*)(int), f>* c3;    // 함수의 이름 : 오버로딩 해석은 f(int)를 선택 //&가 생략된 것으로 간주


        C<bool&, X::b>* c4;         // 정적 클래스 멤버는 수용할 수 있는 변수와 함수 이름임    
        C<bool*, &X::b>* c44;       // 정적 클래스 멤버 //포인터 상수 

        C<int&, X::n>* c5;          // 일반 멤버 //인스턴스 생성 없이 호출 X //error
        C<int X::*, &X::n>* c55;    // 일반 멤버 //포인터 상수의 예

        C<void(), &templ_func<double> >* c6;   // 함수 템플릿 인스턴스도 함수임  // templ_func<double>() 의 주소
    }



//-------------------------------------------------------------------------------------------------
4. 템플릿 템플릿 인수 (Template template arguments)

//템플릿 템플릿 인수는 
//      자신이 치환할 템플릿 템플릿 파라미터의 파라미터와 
//      정확히 일치하는 파라미터를 가진 클래스 템플릿 이어야 합니다

    #include <list>

    template <typename T1, typename T2,
        template<typename> class Container > //A 부분 // Container : 1개의 템플릿 파라미터를 갖는 템플릿 템플릿 파라미터
    class Relation
    {
    public:
        //...
    private:
        Container<T1> dom1;
        Container<T2> dom2;
    };

    int main()
    {
        Relation< int, double, std::list > rel; 
        //에러 std::list는 하나 이상의 템플릿 파라미터 가짐 //C++17 이상은 추론가능 
    }

    // list는 다음과 같이 선언되어 있습니다
    // namespace std {
    //     template <typename T,  typename Allocator = allocator<T> >
    //     class list; 
    // }
    // 즉 템플릿 파라미터가 2개 입니다


//템플릿 템플릿 매개변수에 대한 템플릿 인수는 
//      클래스 템플릿 또는 템플릿 별칭의 이름을 지정 하는 id-expression 이어야 합니다.
//
//      인수가 클래스 템플릿인 경우 매개변수를 일치시킬 때, '기본 템플릿'만 고려됩니다.
//      부분 전문화(있는 경우)는 
//      이 템플릿 템플릿 매개변수를 기반으로 하는 전문화가 '인스턴스화 되는 경우'에만 고려됩니다.

    #include <iostream>

    template<typename T>        // primary template
    class A { int x; };

    template<typename T>        // partial specialization //부분특수화
    class A<T*> { long x; };

    // class template with a template template parameter V
    template< template<typename> class V >
    class C
    {
        V<int> y;   // uses the primary template
        V<int*> z;  // uses the partial specialization
    };

    int main(){
        C<A> c;     // c.y.x has type int,  c.z.x has type long
    }

//C++17 예시 -----------------------------------------------

    #include <iostream>
    #include <memory>
    #include <string>
    #include <vector>

    template<class T> class A {  };
    template<class T, class U = T> class B {  };
    template<class... Types> class C {  };

    template<template<class> class P> class X {  };

    template<template<class...> class Q> class Y {  };

    template<auto n> class D {  };      // note: C++17
    template<template<int> class R> class Z {  };

    template<int> struct SI { };
    template<template<auto> class> void FA();   // note: C++17

    int main()
    {
        X<A> xa; // OK
        X<B> xb; // OK after P0522R0 // Error earlier: not an exact match //호환되는 인수에 템플릿 템플릿 매개 변수 일치
        X<C> xc; // OK after P0522R0 // Error earlier: not an exact match //가변 템플릿

        Y<A> ya; // OK
        Y<B> yb; // OK
        Y<C> yc; // OK

        Z<D> zd; // OK after P0522R0: the template parameter
             // is more specialized than the template argument //템플릿인수보다 전문화된 선언

        FA<SI>(); // Error //인스턴스화 할때 문제됨
    }

//-------------------------------------------------------------------------------------------------
// 동일성 (Template argument equivalence)
//      템플릿 인자의 두 집합은 인자의 값들이 1:1로 같을 때 동일하다고 봅니다. *** 
//
//  테이터형 인자의 경우, 
//      typedef 이름은 중요하지 않습니다. 그보다는 가리키는 '진짜 데이터형'이 중요합니다.
// 
//  데이터형이 아닌 인자의 경우, 
//      값을 어떻게 표현했는지 중요하지 않습니다. 두 인자의 '값'을 비교합니다. 

    template <typename T, int I>
    class Mix;

    typedef int Int;

    Mix<int, 3 * 3>* p1;
    Mix<Int, 4 + 5>* p2;    // p2는 p1과 동일한 데이터형을 가짐 <int, 9>


//함수 템플릿에서 생성된 함수는 이들이 동일한 데이터형과 동일한 이름을 가진다 하더라도 
//      일반함수와 동일할 수 없습니다 *** 
//
//  이를 통해 클래스 멤버에 대한 중요한 두가지 결과를 이끌어낼수 있습니다
// 
//    멤버 함수 템플릿에서 생성된 함수는 가상 함수를 오버라이딩(overriding)하지 않습니다.
// 
//    생성자 템플릿에서 만들어진 생성자는 기본 복사 생성자가 될 수 없습니다.
//    (이와 유사한 이유로 할당 템플릿에서 생성된 할당은 복사 할당 연산자가 될 수 없습니다) 

//https://en.cppreference.com/w/cpp/language/template_parameters
//https://wikidocs.net/455