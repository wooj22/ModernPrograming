//pImpl(pointer to Implementation) idiom
//  
//  프로그램 빌드에 걸리는 시간을 줄여주기 위한 기법중 하나다.
//  클래스의 데이터 멤버를 구현 객체(implementation class or struct)에 옮긴 후 
//  그걸 가리키는 포인터를 멤버로 들고 있게 만드는 것이다.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
//Widget.h에 아래와 같이 선언되어 있다면 

class Gadget {};

class Widget
{
public:
    Widget();

private:
    std::string name;
    std::vector<double> data;
    Gadget g1, g2, g3;
};

//구현이 바뀔 때마다 Widget.h를 include한 모든 파일들이 다 다시 컴파일되어야하기 때문에 
//컴파일에 드는 시간이 늘어나게 된다.
*/

class Gadget {};

class Widget
{
public:
    Widget();
    ~Widget();

private:
    struct Impl;    //선언은 했으나 구현하지 않은 타입을 불완전한 타입(incomplete type)이라고 한다
    Impl* pImpl;
};

//Widget.h에는 std::string, std::vector, Gadget이 없어지므로 컴파일 속도에 향상


//Widget의 실제 데이터 멤버들을 여기다가 정의

struct Widget::Impl
{
    std::string name;
    std::vector<double> data;
    Gadget g1, g2, g3;
};

//pImpl 동적으로 할당
Widget::Widget() : pImpl(new Impl)
{
}

Widget::~Widget()
{    
    delete pImpl; //동적으로 할당한 pImpl 소멸될 때 해제
}

//실제 해당 클래스들을 참조해서 사용하는 .cpp파일만 구현이 바뀔 때 다시 컴파일되므로 컴파일 속도가 훨씬 빨라질 것이다.

int main()
{

    return 0;
}


//Pros(장점)
//공유 라이브러리의 바이너리 호환성 유지에 도움(Header에 변경 사항이 없으므로) / 인터페이스의 세부 사항 숨기기 / 컴파일 시간의 향상
//Cons(단점)
//더 많은 할당으로 인해 메모리 사용량이 증가 / 유지 보수 노력 증가(세부 구현 사항을 확인하거나 수정하는데 더 노력이 필요합니다) / 성능 손실(내용을 인라인 하지 못할 수 있다고 합니다)