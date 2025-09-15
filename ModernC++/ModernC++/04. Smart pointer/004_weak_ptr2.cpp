// weak_ptr 활용 예제
// 
//      순환 참조 해결
//      팩토리 함수에서의 활용
//      Observer Pattern의 구현


//Circular references - 순환 참조 문제 해결하세요.

/*

    #include <memory>    // for shared_ptr
    #include <vector>
    #include <iostream>
    using namespace std;

    class User;
    typedef shared_ptr<User> UserPtr;      //

    class Party
    {
    public:
        Party() {}
        ~Party() { m_MemberList.clear(); }
    public:
        void AddMember(const UserPtr& member) { m_MemberList.push_back(member); }
        //private:
        vector<UserPtr> m_MemberList;
    };

    typedef shared_ptr<Party> PartyPtr;     //

    class User
    {
    public:
        void SetParty(const PartyPtr& party) { m_Party = party; }
    private:
        PartyPtr m_Party;
    };

    int main()
    {
        PartyPtr party(new Party);

        for (int i = 0; i < 5; i++)
        {
            UserPtr user(new User);
            party->AddMember(user);     // 순환 참조가 발생한다.
            user->SetParty(party);      // 순환 참조가 발생한다.
        }
        party.reset();
        return 0;
    }

*/

#include <memory>    // for shared_ptr
#include <vector>
#include <iostream>
using namespace std;

class User;
typedef shared_ptr<User> UserPtr;      //

class Party
{
public:
    Party() {}
    ~Party() { m_MemberList.clear(); }
public:
    void AddMember(const UserPtr& member) {        m_MemberList.push_back(member);    }
    //private:
    vector<UserPtr> m_MemberList;
};

//typedef shared_ptr<Party> PartyPtr;     //
typedef weak_ptr<Party> PartyWeakPtr;   // weak_ptr

class User
{
public:
    void SetParty(const PartyPtr& party) {
        m_Party = party;
    }
private:
    // PartyPtr m_Party;
    PartyWeakPtr m_Party;    // weak_ptr을 사용함으로써, 상호 참조 회피
};

int main() {
}
