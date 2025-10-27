// C++ 11의  유니폼 초기화 (균일한 초기화) (중괄호 초기화)

// 중괄호 초기화를 사용하면 좋은 점 
// 
//      C++의 가장 성가신 구문 해석에서 자유롭다.  //함수연산자 ()
//      축소 변환(narrowing conversion)을 방지한다.

#include <iostream>

int main() 
{
    int value1 = 5;
    int value2(5);      // 변수,객체의 초기화
    int value3{5};      // C++ 11의 유니폼 초기화(균일한 초기화)(중괄호 초기화)
    int value4{};       // default initialization to 0      

    cout << value1 << endl;
    cout << value2 << endl;
    cout << value3 << endl;
    cout << value4 << endl;


    // 성가신 구문 해석에서 벗어날 수 있다.

    class Coo { };
    Coo coo;        // 객체의 기본 생성
    Coo coo();      // 함수선언
    Coo coo{};      // 객체의 기본 생성


    // 중괄호 초기화는 축소변환(narrowing conversion)을 지원하지 않는다.
    // 즉 자동으로 변환되는 것을 막을 수 있다.
    
    int v1(5.1); std::cout << v1;
    int v2{ 5.1 };                  // error //유니폼 초기화는 형 변환을 허용하지 않는다

    double d{ 0.5f };
    int i{ d };						// error // 데이터가 잘리는 변환을 지원하지 않는다.
    int i2{ static_cast<int>(d) };	// 명시적인 형변환이 필요하다. ***

    double x, y, z;
    int sum1{ x + y + z };			// error 
    int sum2(x + y + z);			// OK (표현식의 값이 int에 맞게 잘려나감)
    int sum3 = x + y + z;			// 마찬가지

    return 0;
}



//성가신 구문 해석(most vexing parse)
//
// “선언으로 해석할 수 있는 것은 선언으로 해석해야 한다” 는 규칙이다.

// 성가신 구문 해석의 예 1 ----------------------------------------------------------

    #include <iostream>
    class A {
     public:
      A() { std::cout << "A 의 생성자 호출!" << std::endl; }
    };
    int main() {
      A a();            // ??? --> 인자를 받지 않는 함수 a를 선언한 것   // A a;
    }

// 성가신 구문 해석의 예 2 ----------------------------------------------------------

    #include <iostream>
    class A {
     public:
      A() { std::cout << "A 의 생성자!" << std::endl; }
    };
    class B {
     public:
      B(A a) { std::cout << "B 의 생성자!" << std::endl; }
    };

    int main() 
    {
      B b(A());         // 뭐가 출력될까요? //인자로 A 를 리턴하고 인자가 없는 함수를 받으며, 리턴 타입이 B 인 함수 b
    }


// 문제는
//    ()가  함수의 인자들을 정의하는데도 사용되고, 
//          그냥 일반적인 객체의 생성자를 호출하는데 
//    에도 사용되기 때문
// 
//    C++ 11 에서는 이러한 문제를 해결하기 위해 
//    균일한 초기화(Uniform Initialization) 라는 것을 도입

    A a{};      로 수정하면 확실한 초기화.
    B b(A{});   로 수정하면 확실한 초기화.



// ------------------------------------------------------------------------------
//  {} 를 이용한 생성의 경우 한 가지 큰 차이가 있는데, 일부 암시적 타입 변환들 불허한다.

class A
{
public:
    A(int x) { std::cout << "A 의 생성자 호출!" << std::endl; }
};

int main() {
    A a(3.5);       // Narrow-conversion 가능
    A b{ 3.5 };     // Narrow-conversion 불가 ***
}

// {} 를 이용한 생성 -----------------------------------------------------------
//      함수 리턴 시에 굳이 생성하는 객체의 타입을 다시 명시하지 않아도 됩니다. ***

#include <iostream>

class A {
public:
    A(int x, double y) { std::cout << "A 생성자 호출" << std::endl; }
};

A func() {
    return { 1, 2.3 };      // return A(1, 2.3); 과 동일,   A{ 1, 2.3 }
}

int main()
{
    func();
}


// 초기화자 리스트 (Initializer list) -----------------------------------------------

// 객체 = { , , };   이런식으로 클래스를 초기화가 가능한 클래스 만들기

#include <iostream>
#include <vector>
int main()
{
    int arr[] = { 1, 2, 3, 4 };                 //배열

    std::vector<int> v = { 1, 2, 3, 4, 5 };     //vector

    std::map<std::string, int> m = 
        { {"abc", 1}, {"hi", 3}, {"hello", 5}, {"c++", 2}, {"java", 6} };

    auto ls = { 1, 2, 3 };  

}

//사용자 정의 클래스에서 std::vector 처럼 { , , } 초기화를 하려면 ??? 
// 
//      1. initializer_list<>를 매개변수로 받는 생성자를 만든다.
//      2. {} 유니폼 초기화(Uniform Initialization)로 생성자를 호출한다.

//      {} 를 이용해서 생성자를 호출한다면,
//              클래스에 initializer_list 생성자가 있으면 이것을 우선 호출
//      () 를 사용해서 생성자를 호출한다면,
//              initializer_list 생성자는 호출되지 않고 일반 생성자를 찾음

class A 
{
public:
    A(std::initializer_list<int> l) {
        for (auto itr = l.begin(); itr != l.end(); ++itr) {
            std::cout << *itr << std::endl;
        }
    }
};

int main() { 
    A a = {1, 2, 3, 4, 5};  // initializer_list 초기화
}

// 만약 T가 std::initializer_list에 특수화 돼 있는 경우, T는 std::initializer_list에 의해 직접초기화 됩니다.
//
// 그렇지 않다면, 두 단계로 나뉘어 집니다.
// 
// 1) std::initializer_list 를 인수로 갖는 모든 생성자, 또는 기본값을 갖는 생성자는 
//      오버로드에 의해 std::initializer_list로 초기화 됩니다.
// 
// 2) 이전 단계에서 오버로드가 되지 않는다면, 
//      복사 목록 초기화 방법 중 가장 맞는 방법을 호출하고, 만약 아니면 컴파일이 실패합니다.

//---------------------------------------------
#include <iostream>
#include <initializer_list>

class NumberContainer {
public:
    NumberContainer(std::initializer_list<int> nums) {
        for (int n : nums)
            std::cout << n << " ";
        std::cout << std::endl;
    }
    NumberContainer(int n) {
        std::cout << "단일 int: " << n << std::endl;
    }
};

int main() {
    NumberContainer c1{ 1, 2, 3 };  // std::initializer_list<int> 생성자 호출
    NumberContainer c2(10);         // int 생성자 호출
}

//---------------------------------------------
#include <initializer_list>

template<typename T>
class Container {
public:
    Container(std::initializer_list<T> elems) {
        for (const auto& elem : elems) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Container<int> c1{ 1, 2, 3 };               // int 타입 리스트 초기화
    Container<double> c2{ 1.1, 2.2, 3.3 };      // double 타입 리스트 초기화
    Container<const char*> c3{ "a", "b", "c" }; // 문자열 리스트 초기화

    return 0;
}

//initializer_list 와 auto --------------------------------------------------------------------------

//{} 를 이용해서 생성할 때 타입으로 auto 를 지정한다면 initializer_list 객체가 생성
auto list = { 1, 2, 3 };

//C++ 11 에서는
auto a = { 1 };         // std::initializer_list<int>
auto b{ 1 };            // std::initializer_list<int>
auto c = { 1, 2 };      // std::initializer_list<int>
auto d{ 1, 2 };         // std::initializer_list<int>

//C++ 17 부터는 ***
auto a = { 1 };         // 첫 번째 형태이므로 std::initializer_list<int>
auto b{ 1 };            // 두 번째 형태 이므로 그냥 int
auto c = { 1, 2 };      // 첫 번째 형태이므로 std::initializer_list<int>
auto d{ 1, 2 };         // 두 번째 형태 인데 인자가 2 개 이상이므로 컴파일 오류

//auto 를 같이 사용 할 때 주의 C++ 17 ----------------------------------------------------------------

auto d{1, 2};                       // 두 번째 형태 인데 인자가 2 개 이상이므로 컴파일 오류
auto e = { 1, 2, 3.0 };             // 오류! std::initializer_list<T>의 T를 추론할 수 없음


// 문자열을 다룰 때 주의 ----------------------------------------------------------------------------

auto list = {"a", "b", "c"};        // initializer_list<const char*>    

//using namespace std::literals;    // 문자열 리터럴 연산자를 사용하기 위해 추가해줘야 함.
auto list = {"a"s, "b"s, "c"s};     // initializer_list<std::string> 


/*

//auto 의 경우는 중괄호 초기치를 initializer_list 로 추론 ***

    auto x = { 11, 23, 9 };     // x의 타입은 std::initializer_list<int>


//템플릿 함수에 동일한 중괄호 초기치를 전달하면 타입 추론이 실패해서 컴파일이 거부된다.

    template <typename T>
    void foo(T param);

    foo({ 11, 23, 9 });         // 오류! T에 대한 타입을 추론할 수 없음


    //하지만 param의 타입이 T에 대한 std::initializer_list<T>인 템플릿에, 그 중괄호 초기치를 전달하면 
    //템플릿 타입 추론 규칙들에 의해 T의 타입이 제대로 추론된다.

    template <typename T>
    void foo(std::initializer_list<T> initList);

    foo({ 11, 23, 9 });     // T는 int로 추론되며, 타입은// std::initializer_list<int>로 추론된다.


//중괄호 초기치를 돌려주는 함수의 반환 타입을 auto로 지정하면, 컴파일에 실패하게 된다.
//C++14 람다의 매개변수 타입 명세에 auto를 사용하는 경우에도, 마찬가지 이유로 컴파일에 실패 한다.

    //반환 타입이 auto 인 경우

    auto createInitList(void)
    {
        return { 1, 2, 3 };         // 오류! { 1, 2, 3 }의 타입을 추론할 수 없음
    }

    //람다의 매개 변수 타입 명세에 auto를 사용하는 경우

    #include <iostream>
    #include <vector>

    int main() {

        std::vector<int> v;
        auto resetV = [&v](const auto& newValue) { v = newValue; };

        //std::vector<int> v2 = { 1,2,3 };
        //resetV(v2);

        resetV({ 1, 2, 3 });          // 오류! { 1, 2, 3 }의 타입을 추론할 수 없음
    }

*/