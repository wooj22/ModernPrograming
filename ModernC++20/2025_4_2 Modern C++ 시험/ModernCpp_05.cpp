// CRTP
//
// 아래 Mouse, Keyboard 각각 구현된 싱글톤 코드가 있습니다. 
// CRTP 를 활용하여 하나의 템플릿으로 구현되도록 수정하세요.

#include <iostream>
using namespace std;

template<class T>
class Device
{
protected:
    Device() {};

public:
    static T& GetInstance()
    {
        static const std::unique_ptr<T> instance{ new T() };
        return *instance;
    }

    Device(const Device&) = delete;
    Device& operator=(const Device&) = delete;
};



class Mouse : public Device<Mouse>
{
public:
    Mouse() { std::cout << "create mouse" << endl; }
};

class Keyboard
{
public:
    Keyboard() { std::cout << "create keyboard" << endl; }
};

int main()
{
    Mouse& mouse = Device<Mouse>::GetInstance();
    Keyboard& keyboard = Device<Keyboard>::GetInstance();

    return 0;
};
