// unique_ptr 소유권,  소유권 이전하기

#include <iostream>
using namespace std;

// 복사 불가능한 객체 만들기
class A {
    int a = 0;
public:
    A() {}
    A(int a):a(a) {};
    A(const A& a) = delete;             // 복사생성자 삭제하기

    void print() { std::cout << a << std::endl; }
};

int main()
{
    A a(3);             // 가능
    A b(a);             // 불가능 (복사 생성자는 삭제됨)

    //unique_ptr 도 마찬가지로 unique_ptr 의 복사 생성자가 명시적으로 삭제되었습니다.
    //      그 이유는 unique_ptr 는 어떠한 객체를 유일하게 소유해야 하기 때문
}


//unique_ptr 소유권 이전하기 ---------------------------------------------------

#include <iostream>
using namespace std;

int main()
{
    std::unique_ptr<A> pa(new A(0));
    pa->print();

    // pb 에 소유권을 이전하라.
    std::unique_ptr<A> pb = std::move(pa);      //이동 ***
    pb->print();
    //pa->print();                              //empty 


    // reset()  //재설정, 해제 ------------------------------------------
    unique_ptr<A> test;
    test.reset(new A);          // Test 객체에 대한 소유권 획득    
    test.reset(new A);          // 위에서 생성한 Test 객체는 소멸되고, 지금 생성한 녀석을 소유    
    test.reset();               // 해제


    // release()  //메모리 해제 없이 소유권만 반환 -----------------------
    auto up_org = std::make_unique<std::string>("hello");
    std::unique_ptr<std::string> up_new{ up_org.release() };
    if (up_new)                                                 // nullptr가 아니면 true
        std::cout << "The up_new is " << *up_new << std::endl;
    if (!up_org)                                                // nullptr이면 true
        std::cout << "The up_org is nullptr" << std::endl;

    //release() 된 것은  delete 해주어야 한다. ***
}

/*
// make_unique<>()  //unique_ptr 을 쉽게 생성하기 ----------------------------------

    #include <iostream>
    #include <memory>

    class Foo 
    {
        int a, b;
    public:
        Foo() { a = 0; b = 0; }
        Foo(int a, int b) : a(a), b(b) { std::cout << "생성자" << std::endl; }
        ~Foo() { std::cout << "소멸자" << std::endl; }
        void print() { std::cout << "a : " << a << ", b : " << b << std::endl; }
    };

    int main() 
    {
        //unique_ptr<Foo> foo = make_unique<Foo>(3, 5);
        //foo->print();

        auto foo = std::make_unique<Foo>(3, 5);         //auto
        ptr->print();

        //배열
        //std::unique_ptr<Foo[]> test = std::make_unique<Foo[]>(3);
        //test[0].print();

        //재할당
        foo.reset(new Foo(1, 5));
        foo->print();

        //Copy // Compiler error       
        // unique_ptr<Foo> foo2 = foo;      
        // unique_ptr<Foo> foo2(foo);

    }       


//주의) //생성은 사용자가 잘 해야 한다. 동일 포인터로 두개의 unique_ptr 선언하면 ???
    {
        
        int * a0 = new int(0);
        unique_ptr<int> a1(a0);
        unique_ptr<int> a2(a0);

        //make_unique 사용하는 것이 코드 중복이나 예외 안정성 측면에서 유리
    }

//주의) //소유권 이전 후 사용하면 ??
    {
        unique_ptr<int> num1 = make_unique<int>(10);
        cout << *num1 << endl;

        unique_ptr<char> char1 = make_unique<char>('d');
        cout << *char1 << endl;

        unique_ptr<char> char2( move(char1) );      // move
                
        cout << "Char1: " << *char1 << endl;        // Run-time error
        cout << "Char2: " << *char2 << endl;

    }

//unique_ptr 를 함수 인자로 전달하기 ---------------------------------- get() ***

    #include <iostream>
    #include <memory>

    class A {
        int* data;
    public:
        A() {
            std::cout << "자원 획득!" << std::endl;
            data = new int[100];
        }
        ~A() {
            std::cout << "자원 해제!" << std::endl;
            delete[] data;
        }

        void some() { std::cout << "일반 포인터와 동일하게 사용가능!" << std::endl; }
    };

    void do_something(A* ptr) { ptr->some(); }  // 전달할 함수

    int main() {
        std::unique_ptr<A> pa(new A());

        //do_something에 전달해서 some() 함수 실행하기

        do_something( pa.get() );               //***
    }

    //unique_ptr 은 어떤 객체의 유일한 소유권을 나타내는 포인터 이며, 
    //unique_ptr 가 소멸될 때, 가리키던 객체 역시 소멸된다.

    //만약에 다른 함수에서 unique_ptr 가 소유한 객체에 일시적으로 접근하고 싶다면,
    //      get 을 통해 해당 객체의 포인터를 전달하면 된다. (raw 포인터를 얻어 함부로 쓰면 안되겠죠.)
    //만약에 소유권을 이동하고자 한다면,
    //      unique_ptr 를 move 하면 된다. (이동하고 안 사용하겠다는 경우)

*/
