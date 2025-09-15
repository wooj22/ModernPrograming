//Circular references - 순환 참조 문제

//순환 참조
//      클래스가 서로 참조하는 경우
//      
//      헤더를 서로 참고하면 컴파일 에러 우려, 전방선언을 통해 해결
//      커플링이 증가, 인터페이스를 활용하여 느슨한 연결을 하자.

//스마트 포인터의 경우, 참조카운트가 제데로 작동되지 못하는 문제가 발생.

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
    //cout << party.use_count() << endl;

    for (int i = 0; i < 5; i++)
    {
        UserPtr user(new User);

        party->AddMember(user);     // 순환 참조가 발생한다.
        user->SetParty(party);      // 순환 참조가 발생한다.

        //user는 이 스코프 안에서 소멸되지만, 이 스코프가 종료되어도 user의 refCount = 1
        //cout << party.use_count() << endl;
        //cout << user.use_count() << endl;
    }

    // 여기에서 party.reset을 수행해 보지만,
    // 5명의 파티원이 party 객체를 물고 있어 아직 refCount = 5 의 상태
    // 따라서, party가 소멸되지 못하고, party의 vector에 저장된 user 객체들 역시 소멸되지 못한다.
    party.reset();

    //해결책
    //  User 객체가 Party 객체를 shared_ptr가 아닌 weak_ptr을 사용하여 들고 있다면,
    //  검색 비용 회피와 dangling pointer의 위험에서 모두 벗어날 수 있다.

    return 0;
}