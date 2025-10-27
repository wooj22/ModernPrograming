// 람다 사용시 주의할 부분

// default capture mode를 피하라 ***

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// by-reference와 by-value라는 두 가지의 기본 캡쳐 모드
//      그런데 이 두 가지의 기본 캡쳐 모두 잠재적인 문제점을 갖고 있다.

// by-reference 기본 캡쳐 모드는 댕글링의 위험이 있다.
//      만약 람다에 의해 생성된 클로져의 생명주기가 지역변수나 매개변수보다 더 길다면, 
//      이 변수들에 대한 레퍼런스가 댕글링을 일으키게 된다.

    // filters 
    using FilterContainer = vector<function<bool(int)> >;
    FilterContainer filters;

    //filters의 생명주기가 divisor보다 길다. 사용할 때 참조 대상이 먼저 사라지면 문제됨.  //1

    void addDivisorFilter()
    {
        auto calc1 = computeSomeValue1();
        auto calc2 = computeSomeValue2();
        auto divisor = computeDivisor(calc1, calc2);                                //divisor 선언

        filters.emplace_back( [&](int value) { return value % divisor == 0; } );    //divisor 사용

        //filters.emplace_back( [&divisor](int value) { return value % divisor == 0; } );
    }


//by-value
//      이런 댕글링 문제를 해결할 수 있는 방법 중 하나는 by-value 기본 캡쳐 모드를 사용하는 것이다.   //2

        filters.emplace_back([=](int value) { return value % divisor == 0; });

//by-value 기본 캡쳐 모드를 사용한다 하더라도
//      포인터 변수를 by-value로 캡쳐하는 경우는 여전히 문제
//      smart pointer를 쓰면 문제 없다고 할 수 있지만, 그러나 이 역시 틀린 말이다.
//      어쩔 수 없이 쓸 수 밖에 없는 raw pointer가 존재하기 때문이다. 예를 통해 알아보자.

    class Widget
    {
    public:
        void addFilter() const;
    private:
        int divisor = 2;
    };    

    void Widget::addFilter() const  //이 클래스는 자신의 멤버 divisor를 통해 filter 함수를 추가한다.
    {
        filters.emplace_back( [=](int value) { return value % divisor == 0; } );
    }

//람다가 캡쳐하는 것은 해당 람다가 생성된 범위에서 볼 수 있는 static이 아닌 지역 변수이다 (매개 변수 포함).
//  그러나, Widget::addFilter에서 divisor는 지역 변수가 아니라 
//  Widget 클래스의 데이터 멤버이다. 즉, 이건 캡쳐되지 않는다는 것이다. ***

    //심지어, divisor를 명시적으로 캡쳐한다 해도(값이든 레퍼런스든) 컴파일되지 않는다.
    //divisor는 지역 변수도 매개변수도 아니기 때문이다.
    void Widget::addFilter() const
    {
        filters.emplace_back( [divisor](int value) { return value % divisor == 0; } );  //error
    }

    //기본 캡쳐모드가 divisor를 캡쳐하지 않는데 어떻게 람다 내부에서 divisor를 쓸 수 있는 걸까 ? 
    //그것은 바로 this 덕분이다.
    //클래스의 멤버 변수는 호출될 때 자동으로 this를 함수의 첫번째 인자로 받는데(this call) 
    //이 this가 캡쳐되어 this의 멤버 변수인 divisor를 쓸 수 있게 되는 것이다.

    //by-value 기본 캡쳐 모드를 사용했을 때 컴파일러는 내부적으로 코드를 아래와 같이 취급한다.
    void Widget::addFilter() const
    {
        auto currentObjectPtr = this;  //
        filters.emplace_back(
            [currentObjectPtr](int value) { return value % currentObjectPtr->divisor == 0;
            });
    }

    //즉, 저 필터 함수가 사용될 때 캡쳐한 this 의 생명주기가 더 짧다면 
    //이 역시 댕글링 문제를 일으킬 수 있는 것이다.
    //this 라는 raw pointer를 쓰기 때문에 스마트 포인터를 쓴다고 해도 댕글링 문제가 발생하게 된다.

    using FilterContainer = vector<function<bool(int)>>;
    FilterContainer filters;

    void doSomeWork()
    {
        auto pw = make_unique<Widget>();
        pw->addFilter();    // this 사용 
    }


//해결 방법은 ?

//이런 문제는 캡쳐하고 싶은 멤버 변수를 지역 변수에 복사한 후 이를 캡쳐함으로써 해결할 수 있다.

    void Widget::addFilter() const
    {
        auto divisorCopy = divisor;     // 새로운 변수  
        filters.emplace_back( [divisorCopy](int value) { return value % divisorCopy == 0; } );
    }

//C++14에서는 더 좋은 방법인 일반화된 람다 캡쳐(generalized lambda capture)를 지원한다.

    void Widget::addFilter() const
    {
        filters.emplace_back(
            [divisor = divisor](int  value) { return value % divisor == 0; }
        );
    }

//by-value 기본 캡쳐 모드의 또다른 문제점은 
    //  해당 클로져가 독립적이고 외부 데이터의 변화로부터 어떤 영향도 받지 않을 것처럼 보이게 만든다는 것이다.
    //  하지만, 이건 사실이 아니다.
    //  람다는 지역 변수와 매개변수 뿐만 아니라 정적 객체(static object)들로부터도 영향을 받는다. ***

    void addDivisorFilter()
    {
        static auto calc1 = computeSomeValue1();
        static auto calc2 = computeSomeValue2();
        static auto divisor = computeDivisor(calc1, calc2);     //static

        filters.emplace_back(
            [=](int value) { return value % divisor == 0; }
        );

        ++divisor;
    }

    //위 코드에서 람다 내부에 쓰인 divisor는 캡쳐된게 아니다. 
    //divisor는 정적 변수기 때문에 캡쳐되지 않고, 해당 외부의 값을 그냥 가리킬 뿐이다.
    //즉, divisor 값이 변하면 람다 내부의 결과도 변한다. 외부 데이터의 변화에 완전히 독립적이라고 할 수 없는 것이다.
    // 
    //하지만[=]을 보면 왠지 모르게 해당 람다가 외부 데이터로부터 독립적이며 내부에서 쓰는 값들은 전부 복사본인 것처럼 느껴진다.
    //코드를 오해하기 쉽게 만드는 것이다.

    
//결론 : 기본 캡쳐 모드 쓰지 마라! ------------------------------------------------------------
//      C++14에서는 더 좋은 방법인 일반화된 람다 캡쳐(generalized lambda capture)를 지원한다.

    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <functional>
    using namespace std;

    // filters 
    using FilterContainer = vector<function<bool(int)>>;
    FilterContainer filters;

    class Widget
    {
    public:
        void addFilter() const;
    private:
        int divisor = 2;        //객체 맴버
    };

    void Widget::addFilter() const
    {
        //filters.emplace_back( [divisor](int  value) { return value % divisor == 0; } );             //error //캡쳐 불가
     
        filters.emplace_back( [=](int value) { return value % divisor == 0; } );                    // this->divisor

        //filters.emplace_back( [divisor = divisor](int  value) { return value % divisor == 0; } );   // 일반화된 람다 캡쳐 
    }

    void doSomeWork()
    {
        auto pw = make_unique<Widget>();       
        pw->addFilter();                            // pw 가 사라지면, filters 내부 람다는 댕글링. 
    }

    int main()
    {
        Widget widget;
        widget.addFilter();
        //cout << filters[0](2);
        doSomeWork();
        //cout << filters[1](2);
        return 0;
    }