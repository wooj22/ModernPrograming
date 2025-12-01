
//C++ 17에서는 
// 
//  클래스 템플릿 타입 추론(Class Template Type Deduction) 가능. <> 생략가능
//  Container 를 인자로 넣을 경우는, Container 내부 값의 타입 추론이 필요하다.
    
// CTAD - Class Template Argument Deduction

    #include <iostream>
    #include <vector>
    #include <list>
    using namespace std;

    template<typename T>
    class Vector
    {
        T* buff;
        int size;
    public:
        Vector() {}                             //생성자 #1
        Vector(int sz, T value) {}              //생성자
        template<typename C> Vector(C c) {}     //생성자 템플릿
    };
    Vector()->Vector<int>;                      //#1 Vector 기본 생성자 호출 시 int로 타입 추론 가이드
    template<typename C> Vector(C c) -> Vector<typename C::value_type>;

    //사용자 정의 템플릿 인자 추론 가이드 (defined deduction guides)
    //C++ 17의 클래스 사용자 정의 타입 추론을 정의할 때, 값의 타입이 필요한 경우는 auto 사용이 불가

    int main()
    {
        Vector v(10, 3);

        Vector v1;                              //#1

        // Vector에 list Container 를 인자로 넣을 경우, Container 내부 값의 타입 추론이 필요하다.
        list s = { 1,2,3 };
        Vector v2(s);
    }

// Deduction Guide (C++17) ---------------------------------------------------------

    #include <iostream>
    #include <type_traits>      // std::is_same_v (C++17 이상)
    using namespace std;

    template<typename T>
    class container {
    public:
        container(T t) : elem{ t } {}
        T elem;
    };

    container(const char*)->container<string>;  //주목! //const char* 형식의 매개변수는 T에 string을 넘긴다

    int main() {
        container cnt{ "CONTAINER" };

        // 이 부분을 결과를 확인하세요.
        int rt = static_cast<int>(!is_same_v<decltype(cnt.elem), string>);

        // decltype(cnt.elem)은 cnt.elem의 타입을 가져옴, 그것을 string과 비교
        // 같으면 true, 그걸 반전시키니 false, int로 캐스팅 = 0.

        cout << rt << endl;                     //주목! 부분을 주석처리하면 1

        return 0;
    }


//CTAD; User-defined deduction guides (사용자 정의 템플릿 인자 추론 가이드)
//      사용자가 정의하는 템플릿 인자 추론 가이드(지침)

// 추론 가이드를 추가해서 해결해 봅시다.

    #include <iostream>
    #include <type_traits>

    using namespace std;

    template <typename T>
    class Foo
    {
    public:
        explicit Foo(const T& a) : data(a) { }
        Foo(const T& a, const T& b) : data(a + b) { }
        T data;
    };
    //template <typename T, typename U> Foo(T, U) -> Foo<double>;
    //
    //or
    // 
    //template <typename T, typename U>
    //Foo(T, U) -> Foo<std::common_type_t<T, U>>;       //std::common_type // 여러 형식의 공용 형식을 결정

    int main()
    {
        Foo f1{ 42 };
        Foo f2{ 42, 77.7 };     //int, double 
        cout << f2.data << endl;

        return 0;
    }
/*
// Deduction Guide //가변템플릿 //C++20 이상 ----------------------------------------
//      
// User-defined deduction guides (사용자 정의 템플릿 인자 추론 가이드)

    #include <iostream>

    using namespace std;

    template<class... Ts> struct overload : Ts... { using Ts::operator()...; };   //상속
    template<class... Ts> overload(Ts...) -> overload<Ts...>;

    int main()
    {
        auto a = overload{
            []() { cout << "()" << endl; },
            [](int) { cout << "(int)" << endl; },
            [](float) { cout << "(float)" << endl; },
        };

        a();
        a(42);
        a(42.0f);

        return 0;
    }

    //만약 이 문법이 없었다면 위 코드를 아래처럼 구현해야 했겠죠.
    template<class... Ts> struct overload : Ts...
    {
        overload(Ts&&...) { }
        using Ts::operator()...;
    };
    //전혀 쓸모 없는, 오직 꼼수만을 위한 생성자를 추가해줘야 합니다.
*/