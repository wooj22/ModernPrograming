//멤버 함수 참조 한정사

//-----------------------------------------------------------------------------
//멤버 함수 참조 한정사를 사용하면 
// 
//  멤버 함수가 호출되는 객체(*this)의 좌측값 버전과 우측값 버전을 다른 방식으로 처리할 수 있다.
//  멤버 함수를 좌측값에만 또는 우측값에만 사용할 수 있게 제한할 수 있다.
//  가상 함수가 아닌 멤버 함수에도 멤버 함수 참조 한정사를 적용할 수 있다.

#include <iostream>
#include <vector>
using namespace std;

class Widget {
public:
    void doWork(void)&          // doWork의 이 버전은 *this가 좌측값일 때에만 적용된다.
    {
        cout << "&" << endl;
    }
    void doWork(void)&&         // doWork의 이 버전은 *this가 우측값일 때에만 적용된다.
    {
        cout << "&&" << endl;
    }
};

int main()
{
    Widget w;                       // 보통 객체(좌측값을 돌려줌)
    w.doWork();                     // 좌측값용 Widget::doWork(즉, Widget::doWork &)를 호출한다.

    Widget makeWidget(void);        // 팩토리 함수(우측값을 돌려줌)
    makeWidget().doWork();          // 우측값용 Widget::doWork(즉, Widget::doWork &&)를 호출한다.

    //doSomething(w);               // 함수를 통한 전달, 작성해 보세요.
    //doSomething(makeWidget());
}

Widget makeWidget(void)
{
    return Widget();
}

//-----------------------------------------------------------------------------
// 좌측값 인수만 받는 함수를 작성하고 싶다면, 비 const 좌측값 참조 매개변수를 선언하면 된다.
void doSomething(Widget& w)    // 좌측값 Widget만 받는 함수
{
    w.doWork();
}

// 우측값 인수만 받는 함수를 작성하고 싶다면, 우측값 참조 매개변수를 선언하면 된다.
void doSomething(Widget&& w)   // 우측값 Widget만 받는 함수
{
    std::forward<Widget&&>(w).doWork();
}


// 멤버 함수 참조 한정사는 
//   멤버 함수가 호출되는 객체, 즉 *this에 대해 이러한 구분이 가능하게 만드는 것일 뿐이다.
//   주어진 멤버 함수가 호출되는 대상(*this)이 const임을 명시하기 위해 멤버 함수 선언 끝에 붙이는 const와 딱 비슷하다.


//-----------------------------------------------------------------------------
// 이런 문법이 필요한 예를 보자.

// 예를 들어 Widget 클래스에 std::vector 데이터 멤버가 있으며, 
// 그것에 직접 접근할 수 있는 접근용 멤버 함수를 클라이언트에게 제공한다고 하자.

#include <iostream>
#include <vector>
using namespace std;

class Widget {
public:
    using DataType = std::vector<double>;

    DataType& Get(void) { return values; }  // 접근용 멤버 함수
private:
    DataType values;
};

Widget makeWidget() { Widget w;  return w; }

int main()
{
    //다음과 같은 클라이언트 코드에서 어떤 일이 일어나는지 생각해 보자.
    Widget w;

    auto vals1 = w.Get();                   // w.values를 vals1에 복사    
    // Widget::data의 반환 타입은 좌측값 참조이므로, 이 코드는 하나의 좌측값으로 vals1을 초기화한다, 따라서, vals1은 w.values 로부터 복사 생성된다.

    // 다음으로, Widget을 생성하는 팩터리 함수가 있고, 이 함수가 돌려준 객체를 이용해서 변수를 초기화한다고 하자.    
    auto vals2 = makeWidget().Get();       // Widget 안에 있는 values를 vals2에 복사

    // 마찬가지로 vals2는 Widget안의 values로부터 복사 생성된다.
    // 그러나 이번에는 Widget이 makeWidget이 돌려준 임시 객체(즉, 우측값)이다.
    // 따라서 그 임시 객체 안의 std::vector를 복사하는 것은 '시간 낭비'이다.
}


// 이를 해소하기 위해 정말로 필요한 것은 ? ------------------------------------------------------------
// 
//   Get 가 우측값 Widget에 대해 호출된 경우에는 반드시 우측값을 돌려주게 하는 것이다.
//   Get 를 좌측값 Widget과 우측값 Widget에 대해 개별적으로 오버로딩하면 그런 일이 가능하다.

#include <iostream>
#include <vector>
using namespace std;

class Widget {
public:
    using DataType = std::vector<double>;

    DataType& Get(void)&            // 좌측값 Widget에 대해서는 좌측값을 반환
    {
        cout << "&" << endl;
        return values;
    }

    DataType&& Get(void)&&         // 우측값 Widget에 대해서는 우측값을 반환
    {
        cout << "&&" << endl;
        return std::move(values);
    }

private:
    DataType values;
};

Widget makeWidget(void) {
    Widget w;
    return w;
}

int main()
{
    // 이제 클라이언트 코드는 우리가 원했던 방식으로 작동한다.

    Widget w;

    auto vals1 = w.Get();                  // Widget::data의 좌측값 오버로딩된 함수를 호출; vals1은 복사 생성됨
    auto vals2 = makeWidget().Get();       // Widget::data의 우측값 오버로딩된 함수를 호출; vals2는 이동 생성됨

    return 0;
}