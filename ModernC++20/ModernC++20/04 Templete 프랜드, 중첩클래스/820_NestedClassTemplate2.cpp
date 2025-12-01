#include <iostream>
using namespace std;

//중첩 클래스 ---------------------------------------------------

class Person        //class
{
private:
    int age;
public:
    class Card      //class
    {
    public:
        char* number;
        int money = 100;
        void Show();
    };
};

void Person::Card::Show() { 
    cout << money << endl; 
}

int main(void) 
{
    Person::Card card;
    card.Show();
}

//중첩 클래스 템플릿 ---------------------------------------------------------------

template <typename T>
class Outer             //template
{
public:
    class Nested        //class
    {
    public:
        void nested() { cout << "nested()" << endl; }
    };

    Nested outer() const
    {
        cout << "outer()" << endl;
        return Nested();
    }
};

int main(void)
{
    Outer<int> out;

    // Nested 클래스에 있는 nested() 함수를 호출하세요. ***

    Outer<int>::Nested n = out.outer();
    n.nested();
}


// outer() 함수를 외부에 선언해 보자. *** -------------------------------------------

template <typename T>
class Outer
{
public:
    class Nested
    {
    public:
        void nested() { cout << "nested()" << endl; }
    };

    Nested outer() const;
};

template <typename T>
Outer<T>::Nested Outer<T>::outer() const        
{
    cout << "outer()" << endl;
    return Nested();
}

// 사용하기 ---------

int main(void)
{
    Outer<int> out;
    Outer<int>::Nested n = out.outer();
    n.nested();
}

//의존 타입 ***
//   인라인 구현을 사용하면 그런 의존성은 없다. 함수의 반환 유형이 그냥 Nested이기 때문이다.
//   유형 자체가 템플릿 유형 매개변수에 따라 달라지면, (중첩 의존 타입)
//   그 부유형(subtype)을 참조할 때마다 typename 키워드를 붙여야 한다. ***



//중첩 클래스 템플릿 ---------------------------------------------------------------

#include <iostream>
using namespace std;

template <typename T1>          //template
class Outer
{
public:
    template <typename T2>      //요기가 추가되면? 
    class Nested
    {
    public:
        void nested() { cout << "nested()" << endl; }
    };

    Nested<T1> outer() const;
};

template <typename T1>
Outer<T1>::Nested<T1> Outer<T1>::outer() const    //
{
    cout << "outer()" << endl;
    return Nested<T1>();
}

int main(void)
{
    Outer<int> out;
    Outer<int>::Nested<int> n = out.outer();
    n.nested();
}


/*
템플릿을 위한 새로운 이름
    C++11부터는 typedef 키워드를 이용하여 템플릿 특수화를 위한 새로운 이름을 선언할 수 있습니다.

예제
    typedef X<double, 3.14> DoubleX;
    DoubleX double_x;               // DoubleX 는 X<double, 3.14> 타입임.

예제
    using DoubleX = X<double, 3.14>;
    DoubleX double_x;
*/