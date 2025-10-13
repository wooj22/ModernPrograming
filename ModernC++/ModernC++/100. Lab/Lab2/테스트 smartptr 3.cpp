// Circular references - 순환 참조 문제 해결하세요.

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Player;

class Party
{
private:
    vector<shared_ptr<Player> > m_MemberList;

public:
    Party() {}
    ~Party() { m_MemberList.clear(); std::cout << "~Party()" << "\n"; }

    void AddMember(const shared_ptr<Player>& member)
    {
        m_MemberList.push_back(member);
    }
};

class Player
{
private:
    //shared_ptr<Party> m_Party;
    weak_ptr<Party> m_Party;    // weak_ptr 로 변경

public:
    Player() {}
    ~Player() { std::cout << "~Player()" << "\n"; }

    void SetParty(const weak_ptr<Party>& party)
    {
        m_Party = party;
    }
};

int main() {
    shared_ptr<Party> party = std::make_shared<Party>();
    cout << party.use_count() << endl;

    for (int i = 0; i < 3; i++)
    {
        shared_ptr<Player> player = std::make_shared<Player>();

        party->AddMember(player);     // 둘다 shared_ptr일 경우 순환 참조 발생
        player->SetParty(party);      // 둘다 shared_ptr일 경우 순환 참조 발생
    }

    party.reset();
    cout << party.use_count() << endl;
}