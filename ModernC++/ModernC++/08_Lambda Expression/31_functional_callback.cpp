// callback 활용하기

#include <iostream>
#include <functional>
using namespace std;

enum class EventType {
    ok,
    yes,
    no,
    cancel
};

class PopUp {

    function<void(EventType)> callback;

public:
    void Show(function<void(EventType)> call)
    {
        callback = call;
    }
    void OnClick(EventType event)       //이벤트 발생시 호출
    {
        callback(event);
    }

    void Update()
    {
        OnClick(EventType::ok);             //ok 버튼 클릭
        OnClick(EventType::yes);            //yes 버튼 클릭
        OnClick(EventType::no);             //no 버튼 클릭
        OnClick(EventType::cancel);         //cancel 버튼 클릭
    }
};


void main()
{
    PopUp popup;
    popup.Show([](EventType rt) {
        if (rt == EventType::ok) { cout << "ok" << endl; }
        if (rt == EventType::yes) { cout << "yes" << endl; }
        if (rt == EventType::no) { cout << "no" << endl; }
        if (rt == EventType::cancel) { cout << "cancel" << endl; }
        });

    //popup.Update();   //test
}