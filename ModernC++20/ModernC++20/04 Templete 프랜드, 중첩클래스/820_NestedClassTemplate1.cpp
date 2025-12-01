//중첩 클래스 템플릿
// nested_class_template1.cpp //MSDN

#include <iostream>
using namespace std;

class X                                 //class
{
    template <class T>                  //template
    struct Y {
        T m_t;
        Y(T t) : m_t(t) { }
    };

    Y<int> yInt;    //int
    Y<char> yChar;  //char

public:
    X(int i, char c) : yInt(i), yChar(c) { }
    void print() {
        cout << yInt.m_t << " " << yChar.m_t << endl;
    }
};

int main()
{
    X x(1, 'a');
    x.print();
}


// nested_class_template2.cpp// compile with: /EHsc

#include <iostream>
using namespace std;

template <class T>                      //template
class X
{
    template <class U> class Y          //template
    {
        U* u;
    public:
        Y();
        ~Y();
        U& Value();
        void print();
    };

    Y<int> y;       //int - > T
public:
    X(T t) { y.Value() = t; }
    void print() { y.print(); }
};

template <class T>
template <class U>
X<T>::Y<U>::Y() {
    cout << "X<T>::Y<U>::Y()" << endl;
    u = new U();
}

template <class T>
template <class U>
X<T>::Y<U>::~Y() {
    cout << "X<T>::Y<U>::~Y()" << endl;
    delete u;
}

template <class T>
template <class U>
U& X<T>::Y<U>::Value() {
    return *u;
}

template <class T>
template <class U>
void X<T>::Y<U>::print() {
    cout << this->Value() << endl;
}

int main()
{
    X<int> x = X<int>(10);          x.print();
    X<char> c = X<char>('a');       c.print();
    //X<double> d = X<double>(10.5);  d.print();    //warning

    //X<int>* xi = new X<int>(10);    xi->print();    delete xi;
    //X<char>* xc = new X<char>('a'); xc->print();    delete xc;
    //X<double>* xd = new X<double>(10.5);   xd->print();    delete xd;
}



// 아래 코드의 출력값은? ------------------------------------------------

//아래 1,2 두 함수를 클래스 외부에 정의하세요.

#include <iostream>
using namespace std;

template <class T> class X
{
    template <class U> class Y
    {
        U u = {};
    public:
        Y(U t) : u(t) { }
        void print() { std::cout << u << std::endl; }   //2
    };
    Y<int> y = Y<int>(2);
public:
    X(T t) { }
    void print() { y.print(); }     //1
};

int main() {
    X<int> x(1); x.print();
}

/*
#include <iostream>
using namespace std;

template <class T> class X
{
    template <class U> class Y
    {
        U u = {};
    public:
        Y(U t) : u(t) { }
        void print();       //2
    };

    Y<int> y = Y<int>(2);

public:
    X(T t)  { }
    void print();       //1
};

int main() {
    X<int> x(1); x.print();
}

template <class T> template <class U>
void X<T>::Y<U>::print() { std::cout << u << std::endl; }   //2

template <class T>
void X<T>::print() { y.print(); } //1

*/
