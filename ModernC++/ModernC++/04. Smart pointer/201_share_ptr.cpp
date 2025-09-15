#include <iostream>
#include <memory> 
using namespace std;

class A{
public:
    int n = 0
};

int main()
{
    //make_shared
    shared_ptr<A> sp = make_shared<A>();
    cout << sp->n << endl;;

    //use_count
    shared_ptr<A> p1(new A());
    shared_ptr<A> p2(p1);      // p2 역시 생성된 객체 A 를 가리킨다.
    cout << p1.use_count();    // 2
    cout << p2.use_count();    // 2
}

//-------------------------------------------------------------------------------------
//reset()
//shared_ptr 객체가 가리키는 포인터를 연결하거나 연결해제하기 위해서 reset() 메소드를 사용합니다.
//파라미터 없이 reset 함수를 사용하면 상황에 따라 참조 카운터가 1 감소하거나 0이 됩니다.
//만약 참조 카운터가 0이되면 포인터가 삭제됩니다.

#include <iostream>
#include <memory> 

int main()
{
    shared_ptr<int> s1 = make_shared<int>(10);

    cout << s1.use_count() << endl;


    shared_ptr<int> s2 = s1;

    cout << s1.use_count() << " " << s2.use_count() << endl;

    s1.reset();

    cout << s1.use_count() << " " << s2.use_count() << endl; // (1)

    return 0;
}

//shared_ptr에 nullptr을 대입하면 파라미터없이 reset 함수를 사용한 것과 똑같이 동작


//-------------------------------------------------------------------------------------
//참조 호출 사용하지 않는 경우

#include <iostream>
#include <memory> 

void f(shared_ptr<int> s)
{
    cout << s.use_count() << endl;  // (1)
}

int main()
{
    shared_ptr<int> s1 = make_shared<int>(10);
    cout << s1.use_count() << endl;

    f(s1);

    cout << s1.use_count() << endl;

    return 0;
}

//참조 호출 사용하는 경우

#include <iostream>
#include <memory> 

void f(shared_ptr<int>& s)
{
    cout << s.use_count() << endl;  // (1) 참조 카운터가 증가하지 않습니다
}

int main()
{
    shared_ptr<int> s1 = make_shared<int>(10);
    cout << s1.use_count() << endl;

    f(s1);

    cout << s1.use_count() << endl;

    return 0;
}

//-------------------------------------------------------------------------------------
//move()
//move를 사용하여 shared_ptr 변수가 가리키는 포인터를 다른 shared_ptr로 이동할 수 있습니다.
//기존 shared_ptr은 참조 카운터가 0이 됩니다.

#include <iostream>
#include <memory> 

int main()
{
    shared_ptr<int> s = make_shared<int>(10);  // (1)

    cout << s.use_count() << " " << *s << endl;

    shared_ptr<int> s2;

    cout << s.use_count() << " " << s2.use_count() << endl;

    s2 = move(s);  // (2)

    cout << s.use_count() << " " << s2.use_count() << endl;   // (3)

    return 0;
}

//-------------------------------------------------------------------------------------
//shared_ptr 객체를 생성한 후, 가리키는 포인터가 없으면 nullptr을 가리키게 됩니다.
{
    if (!ptr3)
        std::cout << "Yes, ptr3 is empty" << std::endl;

    if (ptr3 == NULL)
        std::cout << "ptr3 is empty" << std::endl;

    if (ptr3 == nullptr)
        std::cout << "ptr3 is empty" << std::endl;

    //shared_ptr이 가리키고 있는 내부 포인터를 다음처럼 접근 (주의)

    std::shared_ptr<Sample> ptr = std::make_shared<Sample>();
    Sample* rawptr = ptr.get();
}

//-------------------------------------------------------------------------------------
//shared_ptr 사용시 주의할 점

//1. 둘 이상의 shared_ptr이 같은 포인터를 가리키도록 하면 하면 안됩니다.
//하나의 shared_ptr 객체가 소멸하면서 포인터의 메모리를 해제하더라도 다른 shared_ptr 객체는 여전히 포인터를 가리키고 있기 때문입니다.

#include <iostream>
#include <memory> 

int main()
{
    int* num = new int(10);

    std::shared_ptr<int> s1;
    std::shared_ptr<int> s2;
    s1.reset(num);
    s2.reset(num);
    std::cout << s1.use_count() << " " << *s1 << std::endl;
    std::cout << s2.use_count() << " " << *s2 << std::endl;

    s2.reset();   // (1)
    std::cout << s1.use_count() << " " << *s1 << std::endl;  // (2)
    std::cout << s2.use_count() << " " << *s2 << std::endl; // (3)

    //(1) s2 shared_ptr이 소멸되면서 s2가 가리키는 포인터의 메모리도 해제되었지만 s1은 여전히 해당 포인터를 가리키는 상태입니다.
    //(2) s1의 가리키는 포인터가 가리키는 메모리는 이미 해제 되었기 때문에 엉뚱한 값이 출력됩니다.
    //(3) 이미 메모리 해제된 포인터를 접근하려고 하면 에러가 납니다.

    return 0;
}

//2. 힙(heap) 대신에 스택(stack)을 가리키는 포인터를 사용하여 shared_ptr 객체를 생성하면 안됩니다.
//힙 메모리를 사용하면 스코프를 벗어나도(예를들어 지역 함수를 벗어나도) 포인터가 가리키는 메모리가 유지되지만
//스택 메모리를 사용하면 스코프를 벗어나는 순간 사라지기 때문에 문제가 발생합니다.

#include <iostream>
#include <memory> 

void f1(std::shared_ptr<int> &s1)
{
    int* num1 = new int(10);
    s1.reset(num1);

    std::cout << "in function : " << s1.use_count() << " " << *s1 << std::endl;
}

void f2(std::shared_ptr<int>& s2)
{
    int num2 = 20;
    s2.reset(&num2);  // (1)

    std::cout << "in function : " << s2.use_count() << " " << *s2 << std::endl;
}

int main()
{
    std::shared_ptr<int> s1;
    f1(s1);
    std::cout << "out of function : " << s1.use_count() << " " << *s1 << std::endl;

    std::shared_ptr<int> s2;
    f2(s2);
    std::cout << "out of function : " << s2.use_count() << " " << *s2 << std::endl; // (2)

    return 0;
}

//(1) 지역변수를 가리키는 포인터를 shared_ptr에서 가리키도록 합니다.
//(2) shared_ptr 변수인 s2는 여전히 지역변수 num2를 가리키고 있지만 num2는 함수를 벗어나는 순간 소멸되었기 때문에
//shared_ptr 변수 s2가 가리키는 값을* s2로 출력해보면 원하는 값이 출력되지 않습니다.
//프로그램 오류까지 발생합니다.


//-------------------------------------------------------------------------------------
//함수 객체 또는 람다(lambda) 함수로 custom deleter를 지정할 수 있습니다.

#include <iostream>
#include <memory>

void Deleter(int* x) {
    delete[] x; printf("delete\n");
}

int main()
{
    int* buffer1 = new int[1024];
    std::shared_ptr<int> foo1;
    foo1.reset(buffer1, [](int* p) { delete[] p; printf("delete\n"); });

    int* buffer2 = new int[1024];
    std::shared_ptr<int> foo2;
    foo2.reset(buffer2, Deleter);

    return 0;
}

//shared_ptr 올바른 배열 생성 // C++17이상에서 동작. -------------------------

#include <iostream>
#include <memory>
using namespace std;

int main() 
{
    struct A {
        A() { cout << "A()" << endl; }
        ~A() { cout << "~A()" << endl; }
    };

    shared_ptr<A[]> array(new A[10]);       //<A[]>
}


//use template

template<class T> shared_ptr(T*)->shared_ptr<T>;
template<class T> shared_ptr(T* [])->shared_ptr<T[]>;

shared_ptr array(new A[10]);