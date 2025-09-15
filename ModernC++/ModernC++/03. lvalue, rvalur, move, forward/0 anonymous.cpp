//임시 객체 //익명 객체 

#include <iostream>

class A
{
public:
    void print() { std::cout << "Hello" << std::endl; }
};

int main()
{
    int n(1);       //n 이라는 이름의 변수(객체)에 1이라는 값 할당

    int(1);         //???  //임시 객체 // 1이라는 값 할당된 이름없는 객체

    A a;            //a 라는 이름의 객체
    a.print();

    A();            //익명 객체 // A형식으로 생성된 이름없는 객체

    A().print();    //이름 없는 A 타입의 익명 객체가 생성 후, 이 익명 객체로 멤버함수 print()를 호출


    //익명 객체는 R-Value 로서 작동한다. ***
    //      따라서 익명 객체는 생성되고 멤버를 호출한 후 실행이 끝나자마자 바로 사라진다.
        
    decltype(A()) obj;              //obj 의 자료형은?       // A

    auto obj1 = A();                //obj1 의 자료형은?      // A
    
    auto&& obj2 = A();              //obj2 의 자료형은?      // A&&

    decltype(move(obj)) obj3;       //obj3 의 자료형은?      // A&&

    return 0;
}

//-------------------------------------------------------------------------
#include <iostream>
using namespace std;

class Cents
{
private:
    int m_cents;
public:
    Cents(int cents) { m_cents = cents; }           // Cents 클래스의 생성자
    int getCents() const { return m_cents; }        // Cents 클래스의 멤버 함수
};

Cents add(const Cents& c1, const Cents& c2)         // 일반 함수
{
    return Cents(c1.getCents() + c2.getCents());    // 익명 객체 리턴
}

int main()
{
    cout << add(Cents(6), Cents(8)).getCents() << endl;     // 익명객체로 사용
    return 0;
}
