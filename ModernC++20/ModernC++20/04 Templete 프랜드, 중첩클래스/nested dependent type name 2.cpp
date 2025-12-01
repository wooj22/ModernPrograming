//비 의존 타입 이름 : 템플릿 매개변수와 관계없는 타입 (ex : int )

//의존 타입 이름 : 템플릿 매개변수에 종속된 이름

//중첩 의존 타입 이름 : 클래스 안에 중첩된 의존 이름.
//  템플릿 매개변수에 종속된 이름을 의미하는데, 이 중첩 의존 이름이 혼란을 불러올 때가 있다.

#include <iostream>
using namespace std;

template<typename C>
void print(const C& container)
{
    if (container.size() >= 2)
    {
        typename C::const_iterator iter(container.begin());   //템플릿 매개변수 C를 사용함 ***

        //C, const_iterator 모두 type  

        //컴파일러는 기본적으로 중첩 의존 이름을 만났을 때 
        //그 이름이 타입이 아니라고 가정하게끔 설계되어 있다.
        //따라서 위와 같이 typename 키워드를 붙여 준다.
    }
}

int main(void)
{
}

//여기서 예외가 있는데, 
//  이 중첩 의존 타입 이름이 
//  기본 클래스의 리스트에 있거나 멤버 초기화 리스트 내의 기본 클래스 식별자로서 있을 경우에는 
//  typename 키워드를 붙여줘서는 안된다.

template<typename T>
class Base
{
public:
    class Nested {

    };
};

template<typename T>
class Derived : public Base<T>::Nested {          // 상속되는 기본 클래스 리스트라 typename X
public:
    explicit Derived(int x) : Base<T>::Nested()   // 멤버 초기화 리스트에 있어서 typename X
    {
        typename Base<T>::Nested temp;            // 중첩 의존 타입 이름이며 두 경우 모두 아니므로 typename O
    }
};

int main() {
    //Derived<int> b(1);
}