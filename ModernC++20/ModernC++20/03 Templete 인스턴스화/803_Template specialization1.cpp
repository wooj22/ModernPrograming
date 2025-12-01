//템플릿 특수화 / 부분 특수화(Template specialization)
//      템플릿의 특정 패턴에 대해서 별도의 처리가 하고 싶을 경우, 
//      부분 특수화 또는 특수화를 이용할 수 있음

#include <iostream>
using namespace std;

// 메인 템플릿(Primary template)         // 기본적으로 모든 패턴은 메인 템플릿이 처리함
template<typename T> class stack
{
public:
    void push(T a) { cout << "T" << endl; }
};

// 부분 특수화(Partial specialization)   // 모든 포인터 타입에 대해서 별도로 처리하고 싶을 경우 부분 특수화를 적용할 수 있음
template<typename T> class stack<T*>
{
public:
    void push(T* a) { cout << "T*" << endl; }
};

// 특수화(Speicalization)              // char포인터에 대해서만 별도로 처리하고 싶을 경우 특수화를 적용할 수 있음
template<> class stack<char*>
{
public:
    void push(char* a) { cout << "char*" << endl; }
};


int main()
{
    stack<int> s1; s1.push(0); // 메인 템플릿 사용
    stack<int*> s2; s2.push(0); // 부분 특수화 템플릿 사용
    stack<char*> s3; s3.push(0); // 특수화 템플릿 사용
}


//------------------------------------------------------------------------------
#include <iostream>
using namespace std;

// 1. <T, U> 메인 템플릿
template<typename T, typename U> class test
{
public:
    static void foo() { cout << "T, U" << endl; }
};

// 2. <T*, U> 부분 특수화
template<typename T, typename U> class test<T*, U>
{
public:
    static void foo() { cout << "T*, U" << endl; }
};

// 3. <T*, U*> 부분 특수화
template<typename T, typename U> class test<T*, U*>
{
public:
    static void foo() { cout << "T*, U*" << endl; }
};

// 4. <T, T> 부분 특수화
template<typename T> class test<T, T>
{
public:
    static void foo() { cout << "T, T" << endl; }
};

// 5. <int, T> 부분 특수화
template<typename T> class test<int, T>
{
public:
    static void foo() { cout << "int, T" << endl; }
};

// 5-1. <int, int> 특수화
template<> class test<int, int>
{
public:
    static void foo() { cout << "int, int" << endl; }
};

// 6. <int, short> 특수화
template<> class test<int, short>
{
public:
    static void foo() { cout << "int, short" << endl; }
};

// 7. T, test<U, V> 부분 특수화
template<typename T, typename U, typename V>
class test<T, test<U, V>>
{
public:
    static void foo() { cout << "T, test<U, V>" << endl; }
};

int main()
{
    test<double, int>::foo();               // 1. <T, U> 메인 템플릿
    test<int*, double>::foo();              // 2. <T*, U> 부분 특수화
    test<int*, double*>::foo();             // 3. <T*, U*> 부분 특수화
    test<int, int>::foo();                  // 4. <int, int> // 인자가 <int, int>일 경우 4.<T, T> 5.<int, T> 패턴이 2개이상 일치하므로 5-1 특수화 추가 구현 필요
    test<int, char>::foo();                 // 5. <int, T> 부분 특수화 
    test<int, short>::foo();                // 6. <int, short> 특수화
    test<double, test<char, short>>::foo(); // 7. T, test<U, V> 부분 특수화
}


//템플릿 특수화(specialization) / 부분 특수화(Partial specialization) 주의사항
//
//  부분 특수화에서 T의 타입이 결정되는 방식을 주의해야 함
//  부분 특수화에서 기본 파라미터는 표시하지 않음 (메인 템플릿에 정의 값을 그대로 승계함)
//  클래스의 특정 '멤버 함수'만 특수화 할 수 있으나 부분 특수화는 불가능


// 부분 특수화 시 T 타입의 주의 ------------------------------------------------

    // 메인 템플릿에 포인터값이 넘어 왔을 경우 T는 포인터 타입임
    template<typename T> class Test
    {
    public:
        static void foo() { cout << typeid(T).name() << endl; }
    };

    // 아래와 같이 포인터 타입으로 부분 특수화를 했을 경우 T는 포인터 타입이 아님 ***
    template<typename T> class Test<T*>
    {
    public:
        static void foo() { cout << typeid(T).name() << endl; }
    };


// 메인 템플릿에 정의된 파라미터 기본 파라미터 ------------------------------------

    template<typename T, int N = 10> class Test
    {
    public:
        static void foo() { cout << typeid(T).name() << endl; }
    };

    // 부분 특수화에서는 기본 파라미터를 표시하지 않음(메인 템플릿의 기본 파라미터 값 승계) ***
    template<typename T, int N> class Test<T*, N>
    {
    public:
        static void foo() { cout << typeid(T).name() << endl; }
    };



// 클래스 템플릿 // 특정 멤버 함수의 특수화 ------------------------------------

    template<typename T>
    class Stack
    {
    public:
        T pop() {}
        void push(T a);
    };

    // 특정 멤버 함수의 특수화가 필요할 경우 구현부를 분리
    template<typename T>
    void Stack<T>::push(T a)
    {
        cout << "T" << endl;
    }

    // 특정 멤버 함수의 특수화 구현 (부분 특수화는 불가능함) ***
    template<>
    void Stack<char*>::push(char* a)
    {
        cout << "char*" << endl;
    }

    int main()
    {
        Stack<int> s1; s1.push(0);
        Stack<char*> s2; s2.push(0);
    }
