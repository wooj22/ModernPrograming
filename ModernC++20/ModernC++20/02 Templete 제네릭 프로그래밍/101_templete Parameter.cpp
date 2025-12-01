#include <iostream>
using namespace std;

//템플릿 파라미터의 지원 종류
//      타입 파라미터, 값(비타입) 파라미터, 템플릿 템플릿 파라미터

//		type     template Parameter     데이터형 (type) 파라미터				- typename T
//		nontype  template Parameter     데이터형이 아닌 (nontype) 파라미터	- int N
//		template template Parameter     템플릿 템플릿 파라미터				- template<typename> class A

//타입(Type) ----------------------------------------------------------------
//      타입 파라미터

    template<typename T>    //<class T>
    class List
    {
    };

    int main()
    {
        List<int> l1;       //int  //OK
    }

//값(Non-type) ------------------------------------------------------------
//      정수형 상수
//      열거형 상수(Enum)
//      포인터형(일반 객체 포인터형, 함수 포인터형과 멤버 접근 포인터형)
//      참조자형(객체에 대한 참조자와 함수에 대한 참조자 모두 가능)
//
//      auto 사용 가능 (C++17)
//      a floating-point type, a literal class type (C++20)

    #include <iostream>
    using namespace std;

    // 1. 정수형 상수 (실수 안됨, C++20 이후는 가능)
    template<int N>                             //int
    class Test1 {};

    // 2. enum 상수
    enum Color { red = 1, green = 2 };
    template<Color> class Test2 {};             //enum

    // 3. 포인터 : 지역변수 주소 안됨. 전역변수 주소는 가능. // no linakge를 가지는 변수 주소는 안됨.
    template<int*> class Test3 {};              //*

    template <typename T,                       //데이터형 파라미터
        typename T::Allocator* allocator>       //데이터형이 아닌 파라미터
    class List;

    // 4. 함수 포인터 : 가능
    template<int(*)(void)> class Test4 {};      //

    // C++17 에서는 auto 타입 사용가능 ***
    template<auto N> struct Test                //auto
    {
        Test() { cout << typeid(N).name() << endl; }
    };

    int x = 0;

    int main()
    {
        int n = 10;

        // Non-type 파라미터    
        Test1<10> t1;       // OK
        Test1<n> t2;        // Error(변수 안됨);

        Test2<red> t3;      // OK(enum)

        Test3<&n> t4;       // Error(지역변수 주소 안됨)
        Test3<&x> t5;       // OK(전역 변수, Static 변수 주소 가능)

        Test4<&main> t6;    // OK(함수 포인터 가능)

        // C++17 auto 지원
        Test<10> a1;
        Test<&x> a2;
        Test<&main> a3;
    }

    template<auto...>               //가변 템플릿 auto ***
    struct C {};
    
    int main()
    {
        C<'C', 0, 2L, nullptr> x;   // OK
    }


//템플릿(Template)------------------------------------------------------------
//      템플릿에 템플릿을 파라미터로 사용 가능

    #include <iostream>
    using namespace std;

    template<typename T> class List {};

    // 템플릿 파라미터(template parameter)
    template<typename T, template<typename> class C> class Stack    //
    {
        //C c;      // Error    // C는 템플릿
        C<T> c;     // OK       // C<T> == List<int>
    };

    int main()
    {
        //List s1;              // Error(list는 타입이 아니고 템플릿)
        List<int> s2;           // OK(list<int>는 타입)

        Stack<int, List> s3;        // <type, template>   //OK
    }

    //템플릿 템플릿 파라미터의 템플릿 파라미터의 이름은, 
    //      그 템플릿 템플릿 파라미터의 '다른 파라미터'의 선언에만 사용됩니다

    template< template<typename T> class List> //T는 템플릿 템플릿 파라미터의 파라미터 T
    class Node
    {
        static T* storage;  //에러 //T는 템플릿 템플릿 파라미터의 파라미터. 여기서 사용 될 수 없음.
    };

    template< template<typename T, T*> class Buf> //T는 다른 템플릿 템플릿 파라미터의 다른 파라미터 T*를 선언할 수 있음    
    class Lexer
    {
        static char storage[5];
        Buf<char, &Lexer<Buf>::storage[0]> buf;     
    };


//템플릿 파라미터 기본값 사용 --------------------------------------------------------
//      함수 파라미터와 동일하게 기본값 지원

    #include <iostream>
    using namespace std;

    // 기본값 파라미터(default parameter)
    template<typename T = int, int N = 10> class Stack
    {
    };

    int main()
    {
        Stack<int, 10> s1;
        Stack<int> s2;
        Stack<> s3;    // 템플릿이므로 꼭 stack<>을 사용해야 함 //지금은 class template  추정가능
    }


//템플릿 선언의 도입부에 있는 파라미터화 절에서 선언됩니다. 

    template <typename, int>        //이런 선언에서는 이름을 쓰지 않아도 됩니다.
    class X;

//템플릿 파라미터 이름은 그 이후의 파라미터 선언에서도 사용 될 수 있음.

    template <typename T,           //첫번째 파라미터가
        T* Root,                    //두번째 세번째 파라미터 선언에서 사용 되었음
        template<T*> class Buf>
    class Structure;

//기본인수는 자신의 파라미터에 종속되지 않는다. 하지만 이전 파라미터에 종속될 수 있습니다.

    template <typename T, typename Allocator = allocator<T> >
    class List;


//---------------------------------------------------------------------------------------------------
//    C++20 이후부터는 
//    
//    '실수형 타입' 및 '클래스 타입'도 템플릿 파라미터로 사용할 수 있게 되었다. ***


//템플릿의 비타입 인수에서의 클래스 사용 가능 ***
/*
    기존의 C++에서는 비타입 인수에서 클래스를 사용할 수 없었는데, C++20 부터는 드디어 가능해졌다. 

    대신, 사용할 수 있는 클래스 타입에 제약이 있다. ( literal class type )
        - 리터럴 클래스 타입
        - 모든 부모 클래스(base class)와 비정적(non-static) 멤버 변수들이 
          public 및 non-mutable. (protected/private 멤버 함수는 가능하다.)
        - 모든 부모 클래스와 비정적 멤버 변수들이 
          structural 타입이거나 (아마도 다차원의) 그것들의 배열. (structural 타입은 위에 제시된 타입들을 의미한다.)
*/

    //TMP를 할 때 유용 --------------------------------------- 

    #include <iostream>
    #include <array>
    using namespace std;

    template <std::array ARR>
    void PrintLiteralArray()
    {
        for (const auto& value : ARR) {
            cout << value << endl;
        }
    }

    int main()
    {
        PrintLiteralArray < array<int, 3>{1, 2, 3} > ();
        return 0;
    }

    //------------------------------------------------------------
    #include <iostream>
    using namespace std;

    template<class T, int N>
    class MyClass {
    };
    template <MyClass a>                // class 인자 가능
    void MyClassTest() {
    }

    int main()
    {
        MyClass<int, 3> cc;  MyClassTest < cc > (); 

        MyClassTest < MyClass<int, 3>{} > ();
        //MyClassTest < MyClass<int, 3>() >();            //error

        return 0;
    }

https://en.cppreference.com/w/cpp/language/template_parameters