//weak_ptr 
//
//  순환 참조 문제를 해결하기 위해 나타난 것이 바로 weak_ptr (서로가 상대방을 가리키는 shared_ptr를 가지는 경우)
//  weak_ptr은 하나 이상의 shared_ptr 인스턴스가 소유하는 객체에 대한 접근을 제공하지만,
//  소유자의 수에는 포함되지 않는 스마트 포인터다.
//
//  weak_ptr 는 생성자로 shared_ptr 나 다른 weak_ptr 를 받습니다. 
//  또한 shared_ptr 과는 다르게, 이미 제어 블록이 만들어진 객체만이 의미를 가지기 때문에, 
//  평범한 포인터 주소값으로 weak_ptr 를 생성할 수는 없습니다.

#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Player {
public:
    Player() : name("") {}
    Player(std::string n) : name(n) {}
    std::string name;
};

int main()
{
    std::weak_ptr<Player> player(new Player("A"));                //error


    std::shared_ptr<Player> owner = std::make_shared<Player>("p");     //강한 참조
    std::weak_ptr<Player> weakOwner = owner;                           //약한 참조 (shared_ptr로 생성)

    std::cout << owner.use_count() << '\n';     //???
    //shared_ptr의 객체만 참조할 뿐, shared_ptr의 reference count를 올리지 않는다. 

    std::shared_ptr<Player> owner2(owner);
    std::cout << weakOwner.use_count() << '\n';  //shared_ptr 의 reference count


    //공유 포인터 확인하기. -----------------------------------------------  
    auto ptr = weakOwner.lock();            // shared_ptr 반환받아 사용 ***
    if (ptr != nullptr)                     // nullptr 확인이 가능하다.
    {
        std::cout << "!nullptr" << '\n';
    }

    owner = nullptr;
    //ptr = nullptr;
    //weakOwner.reset();
    if (weakOwner.expired())                // 해지 확인 // bool 반환
    {
        std::cout << "expired" << '\n';
    }


    // weak_ptr 사용하기 -----------------------------------------------
    
    //약한 포인터로 공유 포인터 만들기 
    std::shared_ptr<Player> lockedOwner = weakOwner.lock();

    //get() 없음 //직접적으로 사용할 수 없다. *** 
    //      포인터에 엑세스를 원하면 lock() 통해 shared_ptr로 convert 한 뒤, 
    //      shared_ptr의 get() 를 사용해야 한다.


    //같은 weak_ptr 또는 shared_ptr로부터만 복사 생성 / 대입 연산이 가능하며,
    //shared_ptr 로만 convert가 가능하다.
    // 
    //사실 weak_ptr이 shared_ptr을 참조할 때 shared_ptr의 weak reference count는 증가시킨다.
    //객체의 생명 주기에 관여하는 strong reference count를 올리지 않는 것 뿐이다.


}

//---------------------------------------------------------------------------------------
// 참고한 sharedptr 가 댕글링된 경우

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Player {
public:
    Player() : name("") {}
    Player(std::string n) : name(n) {}
    std::string name;
};

int main()
{
    auto spw = std::make_shared<Player>();
    std::weak_ptr<Player> wpw(spw);

    //여기서 reference count는 0이 되고 Player은 파괴된다.  //wpw는 댕글링(dangling)됨.
    spw = nullptr;


    //만약 wpw가 이미 댕글링되었다면, spw1은 null이 된다.
    std::shared_ptr<Player> spw1 = wpw.lock();    
    auto spw2 = wpw.lock(); //마찬가지. auto를 썼을 뿐


    //이렇게 생성자의 인자로 넘길 경우, wpw가 댕글링됐다면 std::bad_weak_ptr 예외를 던진다. ***
    std::shared_ptr<Player> spw3(wpw);
}

//---------------------------------------------------------------------------------------
//weak_ptr은 다음과 같은 경우에 사용하면 유용하다. 
//    어떠한 객체를 참조하되, 객체의 수명에 영향을 주고 싶지 않은 경우
//    그리고 매번 특정 객체의 ID로 컬렉션에서 검색하고 싶지 않을 경우
//    그러면서 dangling pointer의 잠재 위험성을 없애고 싶을 때


// vector 에서 사용 -------------------------------------------

#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Player {
public:
    Player() : name("") {}
    Player(const std::string& s) : name(s) {}
    std::string name;
    std::weak_ptr<Player> other;        //


    void set_other(std::weak_ptr<Player> o) {
        other = o;
    }
    void access_other() {
        std::shared_ptr<Player> o = other.lock();   //lock
        if (o) { std::cout << "접근 : " << this->name << " -> " << o->name << std::endl; }
        else { std::cout << "이미 소멸됨" << std::endl; }
    }
};

int main()
{
    std::vector<std::shared_ptr<Player>> vec;
    vec.push_back(std::make_shared<Player>("Player1"));
    vec.push_back(std::make_shared<Player>("Player2"));

    vec[0]->set_other(vec[1]);          //상호 참조
    vec[1]->set_other(vec[0]);          //상호 참조

    // pa 와 pb 의 ref count 는 그대로다.
    std::cout << "vec[0] ref count : " << vec[0].use_count() << std::endl;
    std::cout << "vec[1] ref count : " << vec[1].use_count() << std::endl;

    // weak_ptr 로 해당 객체 접근하기    //lock()
    vec[0]->access_other();


    // 벡터 마지막 원소 제거 (vec[1] 소멸)
    vec.pop_back();
    vec[0]->access_other();  // 접근 실패!
}
