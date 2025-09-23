//weak_ptr 참조카운트 살펴보기
// 
//      순환 참조 문제를 해결하기 위해 나타난 것이 바로 weak_ptr
//      weak_ptr 는 생성자로 shared_ptr 나 다른 weak_ptr 를 받습니다. 
// 
//      또한 shared_ptr 과는 다르게, 이미 제어 블록이 만들어진 객체만이 의미를 가지기 때문에, 
//      평범한 포인터 주소값으로 weak_ptr 를 생성할 수는 없습니다.
//      같은 weak_ptr 또는 shared_ptr로부터만 복사 생성 / 대입 연산이 가능하며,
//      shared_ptr로만 convert가 가능하다.

#include <memory>       //for shared_ptr/weak_ptr
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    shared_ptr<int> sp1(new int(5));    // strong refCount = 1

    weak_ptr<int> wp1 = sp1;            // shared_ptr sp1으로부터 복사 생성 // weak_ptr이 참조하여, strong refCount = 1, weak refCount = 1

    {
        shared_ptr<int> sp2 = wp1.lock();   // wp1이 참조하고 있던 sp1을 weak_ptr::lock 이용해 sp2가 참조 // string refCount = 2, weak refCount = 1
        if (sp2) {
            // weak_ptr<_Ty>의 _Ty 포인터에 엑세스 하려면 // 이렇게 shared_ptr로 convert하는 방법 밖에 없다.
        }
    }   // sp2가 여기에서 소멸, strong RefCount = 1, weak refCount = 1

    sp1.reset(); // sp1.reset으로 인해 strong refCount = 0, 즉 sp1 소멸  // wp1이 참조하고 있던 sp1이 소멸되었으므로, wp1은 expired

    shared_ptr<int> sp3 = wp1.lock();   // expired된 wp1은 참조하고 있는 shared_ptr이 없다. // 따라서, sp3도 empty
    if (sp3)
    {
        // 여기 문장은 실행되지 않는다
    }

    return 0;
}

//weak_ptr의 할당 받은 자원 사용 하기
//      weak_ptr은 할당 받은 자원을 직접적으로 사용하지 못합니다.
//      직접적인 사용을 막기 위해서 operator-> 및 operator*와 get() 함수가 구현되어 있지 않습니다.
//      lock함수를 통해서 우회적으로 사용 ***
//      lock을 통해서 리턴하는 shared_ptr을 위해서 참조 카운트를 증가, 참조카운트가 0이 되는 것을 방지.

//weak_ptr은 다음과 같은 경우에 사용하면 유용하다.
//      어떠한 객체를 참조하되, 객체의 수명에 영향을 주고 싶지 않은 경우
//      그리고 매번 특정 객체의 ID로 컬렉션에서 검색하고 싶지 않을 경우
//      그러면서 dangling pointer의 잠재 위험성을 없애고 싶을 때


//------------------------------------------------------------------------------

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class A {
    std::string s;
    std::weak_ptr<A> other;

public:
    A(const std::string& s) : s(s) { std::cout << "자원을 획득함!" << std::endl; }

    ~A() { std::cout << "소멸자 호출!" << std::endl; }

    void set_other(std::weak_ptr<A> o) { other = o; }

    void access_other() {
        std::shared_ptr<A> o = other.lock();
        if (o) {
            std::cout << "접근 : " << o->name() << std::endl;
        }
        else {
            std::cout << "이미 소멸됨 ㅠ" << std::endl;
        }
    }

    std::string name() { return s; }
};

int main()
{
    std::vector<std::shared_ptr<A>> vec;
    vec.push_back(std::make_shared<A>("자원 1"));
    vec.push_back(std::make_shared<A>("자원 2"));

    vec[0]->set_other(vec[1]);          //상호참조 //weak_ptr 을 shared_ptr로 생성
    vec[1]->set_other(vec[0]);          //상호참조 //weak_ptr 을 shared_ptr로 생성

    // pa 와 pb 의 ref count 는 그대로다.
    std::cout << "vec[0] ref count : " << vec[0].use_count() << std::endl;
    std::cout << "vec[1] ref count : " << vec[1].use_count() << std::endl;

    // weak_ptr 로 해당 객체 접근하기
    vec[0]->access_other();

    // 벡터 마지막 원소 제거 (vec[1] 소멸)
    vec.pop_back();
    vec[0]->access_other();  // 접근 실패!
}


//------------------------------------------------------------------------------
//Circular reference 회피 예제

#include <memory>    // for shared_ptr
#include <vector>

using namespace std;

class User;
typedef shared_ptr<User> UserPtr;

class Party
{
public:
    Party() {}
    ~Party() { m_MemberList.clear(); }

public:
    void AddMember(const UserPtr& member) {
        m_MemberList.push_back(member);
    }

    void RemoveMember() {
        // 제거 코드
    }

private:
    typedef vector<UserPtr> MemberList;
    MemberList m_MemberList;
};
typedef shared_ptr<Party> PartyPtr;
typedef weak_ptr<Party> PartyWeakPtr;

class User
{
public:
    void SetParty(const PartyPtr& party)
    {
        m_Party = party;
    }

    void LeaveParty()
    {
        if (!m_Party.expired())
        {
            // shared_ptr로 convert 한 뒤, 파티에서 제거
            // 만약, Party 클래스의 RemoveMember가 이 User에 대해 먼저 수행되었으면, m_Party는 expired 상태
            PartyPtr partyPtr = m_Party.lock();
            if (partyPtr)
            {
                partyPtr->RemoveMember();
            }
        }
    }

private:
    // PartyPtr m_Party;
    PartyWeakPtr m_Party;    // weak_ptr을 사용함으로써, 상호 참조 회피
};

int main()
{
    // strong refCount = 1;
    PartyPtr party(new Party);

    for (int i = 0; i < 5; i++)
    {
        // 이 UserPtr user는 이 스코프 안에서 소멸되지만,
        // 아래 party->AddMember로 인해 이 스코프가 종료되어도 user의 refCount = 1
        UserPtr user(new User);

        party->AddMember(user);

        // weak_ptr로 참조하기에 party의 strong refCount = 1
        user->SetParty(party);
    }
    // for 루프 이후 strong refCount = 1, weak refCount = 5

    // 여기에서 party.reset을 수행하면, strong refCount = 0
    // 즉, 파티가 소멸되고 그 과정에서 m_MemberList가 clear -> user들의 strong RefCount = 0 -> user 소멸
    // party와 5개의 user 모두 정상적으로 소멸
    party.reset();

    return 0;
}