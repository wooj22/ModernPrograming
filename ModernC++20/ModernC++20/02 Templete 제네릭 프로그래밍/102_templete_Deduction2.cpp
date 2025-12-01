//C++17 이전까지는 클래스 템플릿은 함수 인자를 통해 타입을 추론 할 수 없기 때문에, 
//      클래스 템플릿 사용이 복잡하고 불편함

//      대안으로 "클래스 템플릿의 객체를 생성하는 함수 템플릿"을 사용하는 방법으로 구현.
//      함수 인자를 통해서 컴파일러가 추론(Argument Type Deduction)할 수 있는 특징을 활용하는 기법.

#include <iostream>

template<typename T> void foo(T a) {}

template<typename T, typename U> struct pair
{
    T first;
    U second;
    pair(const T& a, const U& b) : first(a), second(b) {}
};

template<typename T, typename U>
pair<T, U> make_pair(const T& a, const U& b)
{
    return pair<T, U>(a, b);
}

int main()
{
    pair<int, double> p(1, 3.4);
    foo(p);

    foo(pair<int, double>(1, 3.4)); //C++17 이전 // 클래스 템플릿은 꼭 타입 전달 필요 
    foo(make_pair(1, 3.4));         //간편하게 사용하기 위해  // 함수 템플릿으로 타입 추론하여 클래스 객체 생성


    pair p1(1, 3.4);                //C++17
    foo(p1);                        
    foo(pair(1, 3.4));              //바로 사용 가능
}
