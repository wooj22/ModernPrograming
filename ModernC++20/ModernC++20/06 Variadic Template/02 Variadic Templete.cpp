//C++
//가변 길이 템플릿 - 형식매개변수가 여러개

//가변인자 템플릿(Variadic template) --------------------------------------------------------

#include <iostream>

void print(int a1) { std::cout << a1 << std::endl; }
void print(int a1, double a2) { std::cout << a1 << " " << a2 << std::endl; }

template <typename... Types>        //템플릿 파리미터 팩 (parameter pack)  ***
void print(Types... args) {         //함수 파라미터 팩 (parameter pack)    //T 대신 Types로 복수형 단어로 사용

    print(args...);                 //팩 확장 (Pack Expansion)  ***
    
    //args... 에는 print 에 전달된 인자들 a1, a2, ... 로 추가가능한 표현식
}

int main()
{
    print(1);
    print(1, 2.5);
}

//재귀 활용 ***
/*
    #include <iostream>

    template <typename T>
    void print(T arg) {                         //재귀 호출 종료용
        std::cout << arg << std::endl;
    }

    template <typename T, typename... Types>    //템플릿 파리미터 팩 (parameter pack)  
    void print(T arg, Types... args) {          //함수 파라미터 팩 (parameter pack) //T 대신 Types로 복수형 단어로 주로 사용
        std::cout << arg << ", ";
        print(args...);                         //팩 확장 (Pack Expansion)  
    }

    int main() {
        print(1, 3.1, "abc");
        print(1, 2, 3, 4, 5, 6, 7);
    }
*/

//가변인자 템플릿(Variadic template) --------------------------------------------------------
//
//  가변인자 템플릿의 인자 "Types"는 여러개의 타입을 나타냄
//  가변인자 함수 템플릿의 인자인 "args"안에는 여러개의 값이 들어있고 "Parameter Pack"이라고 함

    #include <iostream>
    using namespace std;

    // 가변인자 클래스 템플릿
    template<typename... Types> 
    class tuplex
    {
    };

    // 가변인자 함수 템플릿
    template<typename... Types>            //템플릿 파라미터 팩  // 타입네임이 여러개
    void foo(Types... args)                //함수 파라미터 팩    // 타입이 여러개
    {
    }

    int main()
    {
        // 가변인자 클래스 템플릿 (타입 생략, 복수의 타입까지...)
        tuplex<> t0;
        tuplex<int> t1;
        tuplex<int, char> t2;

        // 가변인자 함수 템플릿 (인자 생략, 복수의 인자까지...)
        foo();
        foo(1);
        foo(1, 3.4, "A");
    }

//Parameter Pack -----------------------------------------------------------------------------
//   가변인자 템플릿으로 전달받은 파라미터 집합을 파라미터 팩(Parameter Pack)이라 함

//  Pack Expansion (팩 확장)
//      받은 Parameter Pack을 다시 전달할때 요소 전체를 풀어쓰는 방법을 Pack Expansion이라 함 ***
//      0개 이상의 쉼표로 구분된 인스턴스화로 확장 ***
//      goo(args...);           // args...  -->  1,2,3

//  Parameter Pack 요소의 갯수를 얻어 오기 
//      sizeof...(args), sizeof...(Types) 함수를 이용 

    #include <iostream>
    using namespace std;

    // Pack expansion을 통해 Parameter Pack을 전달 받을 함수
    void goo(int n, double d, const char* s)
    {
        cout << "goo : " << n << ", " << d << ", " << s << endl;    // 1, 3.4, "AAA"
    }

    // 가변인자 함수 템플릿
    template<typename... Types>
    void foo(Types... args)
    {
        // args : Parameter Pack
        cout << sizeof...(args) << endl;        // 3 //Parameter Pack 요소의 갯수
        cout << sizeof...(Types) << endl;       // 3

        //goo(args);                            // Error //그대로 다른 함수의 인자로는 사용할 수 가 없다
        goo(args...);                           // Pack expansion  // goo( 1, 3.4, "AAA")
    }

    int main()
    {
        //foo();        
        //foo(1);  
        foo(1, 3.4, "AAA");
        //   Types : int, double, const char*
        //   args  : 1, 3.4, "AAA"
    }


//Pack Expansion 은 '함수 호출 인자' 또는 'list 초기화'를 사용한 표현식에서 사용할 수 있음   
// 
//  함수 호출 인자                    // ... 해석이 가능한 곳 --->  , 로 구분되어 확장
//      foo(args...);
//  배열 이용
//      컴파일러에 따라 빈값이 허용 안 될 수 있으므로 첫번째 요소를 더미로 0으로 지정
//      함수가 반환 타입이 void 경우 대비해서 '대체 반환값(x, 0) 패턴' 사용
//      int x[] = { 0, (print(args), 0)... };
//  초기화 리스트 이용
//      빈값이 허용 됨으로 배열에 비해서 첫번째 요소 더미 0을 생략 할 수 있음
//      initializer_list<int> e = { (print(args), 0)... };

    #include <iostream>
    using namespace std;

    int print(int a) { cout << a << ", ";  return 0; }

    void goo(int n, double d, const char* s) {  cout << "goo : " << n << " " << d << " " << s << endl; }
    int hoo(int a) { return -a; }

    template<typename ... Types>
    void foo(Types ... args)
    {
        // Pack expansion   // 함수인자
        print(args...);             // Error(함수 호출 인자 갯수가 다름)
        //print(args);              // Error(함수 호출 인자 or list 초기화가 아님)
        //print(args)...;           // Error(함수 호출 인자 or list 초기화가 아님)

        // Pack expansion   // 배열 이용 하기 
        int nums[] = { args... };
        //int nums[] = { args... };        // { 1, 2, 3 }
        //int nums[] = { (--args)... };    // { 0, 1, 2 }                      //Expansion 예제 
        //int nums[] = { print(args)... }; // { print(1), print(2), print(3) } //Expansion 예제         
        for (auto n : nums)
            cout << n << endl;

        // Pack expansion   // 배열 이용
        int ea[] = { 0, (print(args), 0)... };      //인자가 하나도 없는 경우를 대비 맨앞에 0

        // Pack expansion   // 초기화 리스트 이용
        initializer_list<int> ei = { (print(args), 0)... }; //, 첫번째 표현식의 값이 무엇이든 간에 콤마 오른쪽 값을 반환하는 표현
    }

    int main()
    {
        foo(1, 2, 3);
        // Types : int, int, int
        // args : 1, 2, 3
    }


//Expansion 예제 ---------------------------------------------------------------------

    #include <iostream>
    using namespace std;

    template<typename ... Types> void foo(Types ... args)
    {
        // Types : int, double

        int x[] = { args... };
        pair<Types...> p1;                  // pair<int, double> // OK
        tuple<Types...> t1;                 // tuple<int, double> // OK

        tuple<pair<Types...>> t2;           // tuple<pair<int, double>> // OK
        tuple<pair<Types>...> t3;           // tuple<pair<int>, pair<double>> // Error

        tuple<pair<int, Types>...> t4;      // tuple<pair<int, int>, pair<int, double>> // OK

        pair<tuple<Types...>> p2;           // pair<tuple<int, double>> // Error
        pair<tuple<Types>...> p3;           // pair<tuple<int>, tuple<double>> // OK

    }

    int main()
    {
        foo(1, 3.4);                        // 컴파일이 가능한지 볼 것
        // args : 1, 3.4
        // Types : int, double
    }

//연습) 가변 템플릿으로 구현하세요 --------------------------------------------------------

#include <iostream>

/*
template <typename T>
void print(T arg) {                         //재귀 호출 종료용
    std::cout << arg << std::endl;
}

template <typename T, typename... Types>    //템플릿 파리미터 팩 (parameter pack)  
void print(T arg, Types... args) {          //함수 파라미터 팩 (parameter pack) //T 대신 Types로 복수형 단어로 주로 사용
    std::cout << arg << ", ";
    print(args...);                         //팩 확장 (Pack Expansion)  //args... 에는 print 에 전달된 인자들 , 로 추가
}
*/

int main() {
    print(1, 3.1, "abc");
    print(1, 2, 3, 4, 5, 6, 7);
}
