//unique_ptr  //C++14 

//배타적 소유권
//    하나의 스마트 포인터만이 특정 객체를 소유할 수 있도록, 
//    객체에 소유권 개념을 도입한 스마트 포인터
//    일반 포인터와는 달리, 사용 후에 delete 키워드를 사용하여 메모리를 해제할 필요가 없다. ***
// 
//소유권 이전
//    unique_ptr 인스턴스는 복사할 수는 없습니다.  ***
//    move() 멤버 함수를 통해 소유권을 이전할 수는 있다. 
//    소유권이 이전되면, 이전 unique_ptr 인스턴스는 더는 해당 객체를 소유하지 않게 재설정됩니다.

#include <iostream>
#include <memory>                       // #include <memory> 
#include <vector>
using namespace std;

/*
int main(void)
{
    int* ptr(new int(5));       // new
    cout << *ptr << endl;
    delete ptr;                 // delete
}
*/

int main(void)
{
    unique_ptr<int> ptr1(new int(5));   // int형 unique_ptr인 ptr1을 선언하고 초기화함.

    cout << *ptr1 << endl;              // -> 포인터 처럼 사용 ***

    //->연산자와* 연산자를 오버로딩해서 저장된 포인터에 직접 접근하는 방법을 제공해서
    //포인터처럼 동작하도록 지원합니다.

    
    //대입 연산자를 이용한 복사는 오류를 발생시킴. ***

    unique_ptr<int> ptr2 = ptr1;         // error 

    //소유권 이전은 가능하다 ***

    auto ptr2 = move(ptr1);             // move //ptr1에서 ptr2로 소유권을 이전함.   
    ptr1.reset();                       // ptr1가 가리키고 있는 메모리 영역을 삭제함. ptr1 = nullptr;

    // 재설정 하기, reset ---------------------------------------------------
    // 소유권은 하나만 가진다. 재설정을 통해 재할당 가능    

    ptr1.reset(new int(3));
    cout << *ptr1 << endl;

    // 원시 포인터 얻기, get ------------------------------------------------
    // get 함수는 unique_ptr에 저장된 포인터를 포인터 형태로 리턴합니다. 

    int* ptr = ptr1.get();              // 원시 포인터 얻기 ( .로 접근 ) 

    // 함수에 매게변수로 전달하려면 ???  --> get() 함수를 통해 빌려 쓰면 됨 *** 

    // 원시 포인터 반환, release ---------------------------------------------

    auto ptr3 = ptr1.release();         // move //원시 포인터에 대한 소유권을 박탈하고 원시 포인터를 반환
    delete ptr3;                        // 메모리를 해제하지 않기 때문에 전달받는 주체가 메모리 할당 해제를 수행해야 합니다.
}

//make_unique() 함수
// 
//   전달받은 인수를 사용해 지정된 타입의 객체를 생성하고, 생성된 객체를 가리키는 unique_ptr을 반환.
//   이 함수를 사용하면, 예외 발생에 대해 안전하게 대처할 수 있다. (외부에서 new 안함 ) 

int main(void)
{
    unique_ptr<int> uptr = make_unique<int>(5);    // new int(5)   //영역 나가면 자동 소멸 //delete 필요 없음
    //auto uptr = make_unique<int>(5);
}

// make_unique 사용하기 ---------------------------------------------------------

class Player {
public:
    Player() : name("") {}
    Player(string n) : name(n) {}
    string name;
};

int main(void)
{
    // 원시 포인터 공유되는 경우 여전히 오류 가능성이 있다. 
    Player* p = new Player("A");
    std::unique_ptr<Player> player1(p);
    std::unique_ptr<Player> player2(p); // 같은 포인터를 가진 두개 객체가 존재
    
    // make_unique<> 사용으로 안전하게 사용
    unique_ptr<Player> uptr = make_unique<Player>("name");

    
    //배열 동적할당을 선언하는 방법 ---------------------------------------

    // C++11 (C++14를 쓸 수 없는 경우)
    std::unique_ptr<Player> player3(new Player("A"));
    std::unique_ptr<Player[]> players3(new Player[20]);         

    // C++14
    std::unique_ptr<Player> player2 = std::make_unique<Player>("A");
    std::unique_ptr<Player[]> players2 = std::make_unique<Player[]>(20);

    // unique_ptr<> 로 배열 사용가능. 하지만
    // std::vector나 std::array, std::string 을 사용하는 것이 배열에 대해선 더 안정적이고 유용하다.

}

//언제 unique_ptr을 사용하는게 좋을까요 ? 
//  - 동시에 참조하지 않을 때
// 
//  클래스 멤버 변수로 활용할 때. 소멸자가 호출되면 알아서 해제되기 때문에 편리하다.
//  두번째, 지역 변수로 활용할 때. 개발자의 실수를 줄여줄 수 있습니다.
//  세번째, STL 벡터에 포인터를 저장할 때. 벡터를 clear 하면, unique_ptr은 자동적으로 포인터를 지워줍니다.


/*

// unique_ptr 로 클래스 동적할당 하기 -----------------------------------------

    #include <iostream>
    #include <memory>
    using namespace std;

    class Person
    {
    private:
        string _name;
        int _age;
    public:
        Person(const string& name, int age) : _name(name),_age(age) { cout << "생성자" << endl; }
        ~Person() { cout << "소멸자" << endl; }
        void Show() { cout << _name << " " << _age << endl; }
    };

    //클래스 객체를 유니크포인터로 동적할당 후, 맴버를 호출해서 출력하세요.

    int main(void)
    {
        unique_ptr<Person> p1(new Person("지훈", 19));

        //unique_ptr<Person> p1 = make_unique<Person>("지훈", 19);    //make_unique

        //auto p1 = make_unique<Person>("지훈", 19);                  //auto

        p1->Show();     //맴버 접근, 포인터 처럼 사용

        return 0;
    }

// make_unique  배열 사용하기 ---------------------------------------------------------

    #include <iostream>
    #include <memory>
    using namespace std;

    class Player {
    public:
        Player() : name("") {}
        Player(string n) : name(n) {}
        string name;
    };

    int main(void)
    {
        // C++11 (C++14를 쓸 수 없는 경우)
        //std::unique_ptr<Player> player3(new Player("A"));
        //std::unique_ptr<Player[]> players3(new Player[20]);

        // C++14 
        std::unique_ptr<Player> player2 = std::make_unique<Player>("A");
        std::unique_ptr<Player[]> players2 = std::make_unique<Player[]>(20);

        // unique_ptr<> 로 배열 사용가능. 하지만
        // std::vector나 std::array, std::string 을 사용하는 것이
        // 배열에 대해선 더 안정적이고 유용하다. ***
    }


// vector 에 할당하기 ---------------------------------------------------------

    #include <iostream>
    #include <vector>
    #include <memory>
    using namespace std;

    class Player {
    public:
        Player() : name("") {}
        Player(string n) : name(n) {}
        string name;
    };

    int main(void)
    {
        vector<unique_ptr<Player>> players;         // 포인터 배열 ***

        players.push_back(make_unique<Player>("AAA"));
        players.push_back(make_unique<Player>("BBB"));
        players.push_back(make_unique<Player>("CCC"));

        // Pass by const reference when possible to avoid copying.
        for (const auto& p : players)
        {
            cout << p->name << endl;
        }
    }

// emplace_back 함수를 이용하면, vector 안에 unique_ptr 을 직접 생성하면서 집어넣을 수 있다. ***

    #include <iostream>
    #include <memory>
    #include <vector>

    class A {
        int* data;
    public:
        A(int i) {           
            data = new int[100];
            data[0] = i;
        }
        ~A() {         
            delete[] data;
        }

        void some() { std::cout << "값 : " << data[0] << std::endl; }
    };

    int main()
    {
        std::vector<std::unique_ptr<A>> vec;

        vec.emplace_back( new A(1) );           // ***

        // vec.push_back(std::unique_ptr<A>(new A(1))); 과 동일

        vec.back()->some();
    }

//STL 벡터에, 이미 만들어진 unique_ptr 객체 추가하기 ------------------------------------------------------

    class Player {
    public:
        Player() : name("") {}
        Player(string n) : name(n) {}
        string name;
    };

    int main(void)
    {
        std::vector<std::unique_ptr<Player>> players;                   //unique_ptr vector

        std::unique_ptr<Player> p1 = std::make_unique<Player>("p1");    //만들어진 unique_ptr

        players.push_back(p1);            // error 이유는 ???         
    
        //p1 과 vector 의 소유권 충돌
        
        //벡터안에 유니크 포인터를 추가하기 위해서는, move 함수를 활용해서,
        //소유권 전체를 넘겨주어야 컴파일이 정상적으로 동작합니다. ***

        players.push_back(std::move(p1));


    //const 유니크 포인터는 어떨까 ? ------------------------------------------------

        const std::unique_ptr<Player> p1 = std::make_unique<Player>();
        //const 유니크 포인터의 경우에는 소유권 이전이 되지 않고 컴파일 에러 ***


    //std::unique_ptr의 또다른 장점은 이게 std::shared_ptr과 호환이 된다는 점이다. ***

        //std::unique_ptr이 std::shared_ptr로 변환된다.
        std::shared_ptr<Player> sp = makePlayer(arguments);
    }

*/