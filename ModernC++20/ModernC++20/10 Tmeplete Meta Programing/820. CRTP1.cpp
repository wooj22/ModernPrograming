//CRTP(Cruiously Recurring Template Pattern) 활용
//
//  기반클래스에서 파생클래스의 이름을 사용할 수 있게 하는 기법

/*
    #include <iostream>
    using namespace std;

    class Window
    {
    public:
        void msgLoop() 
        {
            OnClick();
        }
        void OnClick() { cout << "Window OnClick" << endl; }
    };

    class FrameWindow : public Window
    {
    public:
        void OnClick() { cout << "FrameWindow OnClick" << endl; }
    };

    int main()
    {
        FrameWindow fw;
        fw.msgLoop();       // OUTPUT : Window OnClick

        //파생클래스의 OnClick 함수를 호출하기 위해서 어떻게 ?    

        ---> virtual
    }
*/

//가상함수로 만들면 가상함수 테이블이 관리됨. (동적 다형성)
//비 가상 함수(Non virtual function)를 가상 함수 처럼 동작하게 하자. 
// 
//파생클래스를 만들때 기반클래스의 템플릿 인자로 파생클래스 이름을 전달
//this 포인터를 파생클래스 타입으로 캐스팅 후 함수 호출 (정적 다형성) ***

#include <iostream>
using namespace std;

template<typename T>
class Window
{
public:
    void msgLoop()
    {        
        static_cast<T*>(this)->OnClick();       // this 포인터를 파생클래스인 T 타입으로 캐스팅 후 호출
    }

    void OnClick() { cout << "Window OnClick" << endl; }    //가상함수로 만들면 가상함수 테이블이 관리됨
};

class FrameWindow : public Window<FrameWindow>      //기반클래스의 템플릿 인자로 파생클래스 이름을 전달
{
public:
    void OnClick() { cout << "FrameWindow OnClick" << endl; }
};

int main()
{
    FrameWindow fw;         
    fw.msgLoop();           // OUTPUT : FrameWindow OnClick   // T* == FrameWindow*

    //Window<FrameWindow> w = fw;
    //w.msgLoop();
}
