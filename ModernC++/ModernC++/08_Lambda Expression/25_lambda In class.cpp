//클래스의 멤버 함수 내에 
//      lambda 함수를 정의하고, 이 lambda 함수에서 해당 클래스의 멤버를 호출하는 것이 가능하다.

//클래스의 멤버를 호출할 때는 반드시 ‘this’ 를 캡쳐해야 한다. ***
//*this 를 사용하면 value 캡쳐가 가능     // C++17

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class PrimeNumber
{
private:
    typedef vector<int> PrimeNumberList;
    PrimeNumberList m_primeList;                //멤버

    void _Print(int primeNumber) const
    {
        cout << "The prime number : " << primeNumber << endl;
    }
public:
    PrimeNumber()
    {
        m_primeList.push_back(1);
        m_primeList.push_back(2);
        m_primeList.push_back(5);
        m_primeList.push_back(7);
    }

    void PrintPrimeNumbers() const
    {
        for_each(m_primeList.begin(), m_primeList.end(),
            [this](int primeNumber)                     // this를 캡쳐 !!!
            {
                _Print(primeNumber);                    //private 멤버 함수 호출
            });
    }
};

int main()
{
    PrimeNumber pn;
    pn.PrintPrimeNumbers();     

    return 0;
}

//클래스 멤버 함수 내 lambda 함수는 해당 클래스에서 'friend 함수'로 인식하므로,
//  lambda 함수에서 클래스의 private 멤버에도 접근이 가능하다.
// 
//클래스 멤버 함수안에서 정의되는 것뿐만 아니라 lambda 자체가 멤버로 선언될 수도 있습니다. 
//이럴 경우 기존 멤버 다루듯 하면 됩니다. [this]로 현재 객체를 참조로 캡처할 수 있는 것도 마찬가지입니다.


//C++17 이상에서 inline static을 사용하면 클래스 내부에서 람다를 정적 멤버로 가질 수 있습니다.

#include <iostream>

struct Example {
    static inline auto func = []() { std::cout << "Static Lambda\n"; };
};

int main() {
    Example::func();  //use
}
//이 경우에는 auto가 허용됩니다.
//static 멤버이므로 인스턴스에 종속되지 않으며,
//람다를 클래스 수준 상수처럼 재사용할 수 있습니다.

