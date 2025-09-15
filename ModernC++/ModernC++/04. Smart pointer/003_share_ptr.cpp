//shared_ptr
//  하나의 특정 객체를 참조하는 스마트 포인터가 총 몇 개인지를 참조하는 스마트 포인터
//	여러 개의 스마트 포인터가 하나의 객체를 '같이 소유' 해야 하는 경우
//	특정 자원을 몇 개의 객체에서 가리키는지를 추적한 다음에, 
//  그 참조 수가 0 이 되면 비로소 해제를 시켜주는 방식의 포인터.

//참조 횟수(reference count)
//  이렇게 참조하고 있는 스마트 포인터의 개수를 '참조 횟수(reference count)'라고 합니다.
//  참조 횟수는 특정 객체에 새로운 shared_ptr이 추가될 때마다 1씩 증가하며, 수명이 다할 때마다 1씩 감소합니다.
//  따라서 마지막 shared_ptr의 수명이 다하여 참조 횟수가 0이 되면, delete 키워드를 사용하여 메모리를 자동으로 해제합니다.

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class A {
    int* data;
public:
    A() {
        data = new int[100];
        std::cout << "생성" << std::endl;
    }
    ~A() {
        std::cout << "소멸" << std::endl;
        delete[] data;
    }

    void func() {}
};


int main()
{
    shared_ptr<int> ptr1(new int(5));       // int형 shared_ptr인 ptr1을 선언하고 초기화함.

    cout << ptr1.use_count() << endl;       // 1  //참조 횟수

    auto ptr2(ptr1);                        // 복사 생성자를 이용한 초기화
    cout << ptr1.use_count() << endl;       // 2

    auto ptr3 = ptr1;                       // 대입을 통한 초기화
    cout << ptr1.use_count() << endl;       // 3


    // use_count(), reset() -------------------------------------------------------

    shared_ptr<A> p = make_shared<A>();
    cout << "현재 소유자 수 : " << p.use_count() << endl; // 1
    auto han = p;
    cout << "현재 소유자 수 : " << p.use_count() << endl; // 2
    han.reset();                                                // shared_ptr인 han을 해제함.
    cout << "현재 소유자 수 : " << p.use_count() << endl; // 1


    // get() // 참조하는 객체의 주소를 반환 -----------------------------------------

    shared_ptr<A> spA(new A());
    A* pA = spA.get();          // spA가 참조하는 객체의 주소를 반환

    spA.get()->func();          // spA가 참조하는 객체의 메서드에 접근 #1    
    (*spA).func();              // spA가 참조하는 객체의 메서드에 접근 #2    
    spA->func();                // spA가 참조하는 객체의 메서드에 접근 #3


    // use_count() //참조 중인 소유자의 수를 반환 -----------------------------------

    shared_ptr<A> p1(new A());
    shared_ptr<A> p2(p1);               // p2 역시 생성된 객체 A 를 가리킨다.
    cout << p1.use_count() << endl;     //??? 2
    cout << p2.use_count() << endl;     //??? 2


    //vector 소멸자 호출이 언제 이루어지는지 살펴보자 -------------------------------

    vector<shared_ptr<A>> vec;

    vec.push_back(shared_ptr<A>(new A()));
    vec.push_back(shared_ptr<A>(vec[0]));
    vec.push_back(shared_ptr<A>(vec[1]));

    cout << "첫 번째 소멸!" << endl;
    vec.erase(vec.begin());

    cout << "다음 원소 소멸!" << endl;
    vec.erase(vec.begin());

    cout << "마지막 원소 소멸!" << endl;
    vec.erase(vec.begin());

    cout << "프로그램 종료!" << endl;
}

/*
// make_shared ---------------------------------------------------------------------------------------

    auto p1 = std::make_shared<A>();

    //new 의 직접 사용에 비해, make 함수를 사용하면
    //소스 코드의 중복이 없어지고 예외 안전성이 확보되며, std::make_shared의 경우 더 작고 빠른 코드가 산출된다.

    //std::shared_ptr에 대해서는 make 함수가 부적합한 경우가 있는데,
    //  첫째로, 커스텀 메모리 관리를 가진 클래스를 다루는 경우와
    //  둘째, 메모리가 넉넉하지 않은 시스템에서 큰 객체를 다루고, 
    //      std::weak_ptr들이 해당 std::shared_ptr보다 오래 살아남는 경우이다.

    //make 함수의 사용이 불가능 또는 부적합한 경우로는
    //  커스텀 삭제자를 지정 해야 하는 경우와 중괄호 초기치를 전달해야 하는 경우가 있다.


//garbage collection 과 비교 

    shared_ptr은 garbage collection 처럼 
    여럿이 공유하는 자원을 더 이상 필요없을 때 자동으로 해제해줄 뿐만 아니라, 
    어느 시점에 해제되는지도 알 수 있다. ***


//shared_ptr 특징
    std::shared_ptr은 일반 포인터의 2배 크기를 갖게 된다.
        - 내부적으로 자원에 대한 포인터와 해당 포인터의 레퍼런스 카운트 두 개를 관리
    레퍼런스 카운트를 관리하기 위한 메모리는 동적으로 할당된다.
        - 해당 오브젝트와 별도록 관리된다. (control block)
    레퍼런스를 증가시키고 감소시키는 동작은 반드시 원자적(atomic)이어야 한다.
        - 여러 개의 스레드에서 동시에 읽고 쓰는 동작이 발생할 수 있기 때문이다.


//control block ***

    실제로는 레퍼런스 카운트 외의 여러 가지 std::shared_ptr을 관리하기 위한 정보를 
    control block 이라고 해서 따로 할당한 다음, 
    그 곳을 가리키는 포인터를 들고 있는 식으로 구성된다.

//컨트롤 블록을 생성할지 말지의 여부를 결정하는 것은 아래의 규칙을 따른다.

    std::make_shared 는 항상 컨트롤 블록을 생성한다.
    std::shared_ptr이 std::unique_ptr 로부터 생성될 경우.
    std::shared_ptr의 생성자가 raw pointer를 인자로 호출되었을 경우.

    마지막 규칙 주의 ***
        같은 raw pointer로 두 개의 std::shared_ptr을 만들 경우, 중복 해제하는 문제 발생
        다른 변수에 저장해서 넘기지 말고, new로 바로 넘기는 식으로 초기화면 
        같은 객체에 대해 두 개 이상의 컨트롤 블록이 생기는 문제를 피할 수 있다.

        //따로 대입하지 않고 바로 new를 이용해 넘김
        std::shared_ptr<Widget> spw1(new Widget, loggingDel);
        //spw2는 spw1과 같은 컨트롤 블록을 씀.
        std::shared_ptr<Widget> spw2(spw1);


//this 포인터 ---------------------------------------------------------------------------------------
    자신을 가리키는 추가적인 shared_ptr 인스턴스를 생성할 수 있도록 하려면
        std::enable_shared_from_this 를 상속받고,
        shared_from_this()를 사용하여 현재 객체를 가리키는 shared_ptr를 얻습니다.

    this를 추가하기 전에, 이미 외부에서 이 객체를 가리키는 std::shared_ptr이 있었다면 
    하나의 객체에 대해 두 개의 컨트롤 블록 생성하게 되고, 중복 해제하는 문제 발생.
    this 포인터로부터 안전하게 std::shared_ptr을 생성할 수 있는 방법이 필요하게 됨

// enable_shared_from_this -------------------------------------------

    //shared_from_this() 함수는 현재 오브젝트에 대한 컨트롤 블록이 있는지 검사한 후, 
    //해당 컨트롤 블록을 가리키는 std::shared_ptr 포인터를 생성한다.

    #include <iostream>
    #include <memory>

    class A : public std::enable_shared_from_this<A>        //
    {
        int* data;
    public:
        A() {
            data = new int[100];
            std::cout << "자원을 획득함!" << std::endl;
        }
        ~A() {
            std::cout << "소멸자 호출!" << std::endl;
            delete[] data;
        }
        
        //std::shared_ptr<type> getPtr() { return std::shared_ptr<type>(this); } //새로운  콘트롤 블럭

        std::shared_ptr<A> get_shared_ptr() { return shared_from_this(); }  //동일한 콘트롤 블럭 사용

        
    };

    int main()
    {
        std::shared_ptr<A> pa1 = std::make_shared<A>();     //이미 shared_ptr가 관리하고 있을 때
        std::shared_ptr<A> pa2 = pa1->get_shared_ptr();     

        std::cout << pa1.use_count() << std::endl;
        std::cout << pa2.use_count() << std::endl;
    }

    //shared_from_this()를 호출하기 전에 반드시 해당 객체에 대한 shared_ptr이 먼저 생성되어 있어야 한다.


//custom deleter ---------------------------------------------------------------------------------------

    std::unique_ptr과 마찬가지로 기본적으로 자원 파괴시 delete를 이용, 역시 custom deleter도 지원한다.
    다른 점은 std::shared_ptr의 경우
    custom deleter의 타입이 포인터 자체의 타입에 영향을 끼치지 않는다.

    //custom deleter.
    auto loggingDel = [](Widget* pw) {
        delete pw;
    };

    //unique_ptr은 deleter의 타입이 포인터의 타입에 영향을 미친다
    std::unique_ptr<Widget, decltype(loggingDel)> upw(new Widget, loggingDel);

    //shared_ptr은 그렇지 않다
    std::shared_ptr<Widget> spw(new Widget, loggingDel);

//따라서, 서로 custom deleter가 다른 std::shared_ptr들을 하나의 컨테이너에 다같이 담아 보관할 수 있다.

    //custom deleters.
    auto customDeleter1 = [](Widget* pw) { ... };
    auto customDeleter2 = [](Widget* pw) { ... };

    std::shared_ptr<Widget> pw1(new Widget, customDeleter1);
    std::shared_ptr<Widget> pw2(new Widget, customDeleter2);

    //다 같이 담을 수 있음.
    std::vector< std::shared_ptr<Widget> > vpw{ pw1, pw2 };


*/


//대부분의 경우, std::shared_ptr은 공유 자원의 lifetime을 관리하기에 아주 좋은 수단이다.
// 
//하지만, 만약 배타적 소유권이 더 어울린다는 생각이 조금이라도 든다면 
//std::unique_ptr이 나은 선택일 수 있다.
//std::unique_ptr의 성능은 raw pointer와 거의 동일하며, std::shared_ptr로 변경하기도 아주 쉽다.

//또 한 가지 std::shared_ptr은 배열에 대해서는 동작하지 않는다. (C++17 이전)
//배열의 경우 대부분 std::vector, std::array, std::string 같은 것을 쓰는 것이 훨씬 좋다.



