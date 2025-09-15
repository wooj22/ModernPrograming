//pImpl(pointer to Implementation) idiom
//  
//  프로그램 빌드에 걸리는 시간을 줄여주기 위한 기법중 하나다.
//  클래스의 데이터 멤버를 구현 객체(implementation class or struct)에 옮긴 후 
//  그걸 가리키는 포인터를 멤버로 들고 있게 만드는 것이다.

//Widget이 Impl에 대해 배타적 소유권을 갖고 있는 것이므로(자신의 데이터 멤버니까) std::unique_ptr을 사용


#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Widget.h --------------------------------------------------------

class Widget
{
public:
    Widget();
    ~Widget(); //소멸자 만들어줌

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

//Widget.cpp -----------------------------------------------------

class Gadget {};

struct Widget::Impl //Impl 정의
{
    std::string name;
    std::vector<double> data;
    Gadget g1, g2, g3;
};

//make_unique를 이용해 std::unique_ptr 생성
Widget::Widget() : pImpl(std::make_unique<Impl>())
{
}
//소멸자 추가! 여기 구현함으로써 소멸자가 Impl 구조체의 정의를 알 수 있게 함.
Widget::~Widget()
{
    //Impl 처리
}

int main()
{
    Widget w; //소멸자 구현 없으면 error 발생! //소멸자는 Impl 어떤 것인지 알 수 없다 -> 소멸자 선언.

    //자동생성되는 special member function들은 더 남아있다.
    //바로 이동 및 복사와 관련된 생성자, 대입 연산자들이다.
    //이 역시 자동으로 생성되며 소멸자와 거의 비슷한 이유로 컴파일 에러를 일으키게 된다

    return 0;
}

/*
//Widget.h
class Widget
{
public:
    Widget();

    //선언만 해둔다.
    ~Widget();
    Widget(Widget&& rhs);
    Widget& operator=(Widget&& rhs);
    Widget(Widget& rhs);
    Widget& operator=(const Widget& rhs);

private:
   struct Impl;
   std::unique_ptr<Impl> pImpl;
};

//Widget.cpp

...

Widget::~Widget() = default;

//이동 구현
Widget::Widget(Widget&& rhs) = default;
Widget& Widget::operator=(Widget&& rhs) = default;

//복사 생성자 깊은 복사 하도록 구현
Widget::Widget(const Widget& rhs)
: pImpl(std::make_unique<Impl>(*rhs.pImpl))
{
}

//복사 대입 연산자도 마찬가지
Widget& Widget::operator=(const Widget& rhs)
{
    *pImpl = *rhs.pImpl;
    return *this;
}

*/

/*
std::shared_ptr은 어떨까?

    std::shared_ptr을 이용할 경우 std::unique_ptr을 이용할 때와는 다르게 
    기본 생성하는 함수들을 그대로 내버려둬도(구현부를 Impl 구조체보다 아래 두는 등의 처리를 하지 않아도) 
    제대로 컴파일되고 결과도 이상하지 않게 잘 동작한다. 

std::unique_ptr과 std::shared_ptr의 이런 차이가 발생하는 가장 큰 이유는, 

    std::unique_ptr의 타입에는 custom deleter의 타입이 포함되지만, 
    std::shared_ptr의 타입에는 포함되지 않는다는 것이다. 

    std::unique_ptr은 타입에 deleter의 타입이 포함되기 때문에 
    컴파일러가 자동으로 함수들을 생성할 때 불완전한 타입이 포함되어 있으면 안 된다. 
    반면 std::shared_ptr은 deleter의 타입이 자신의 타입에 포함되지 않기 때문에 
    컴파일러가 자동으로 함수를 생성할 때 deleter의 타입이 불완전해도 괜찮다.

*/