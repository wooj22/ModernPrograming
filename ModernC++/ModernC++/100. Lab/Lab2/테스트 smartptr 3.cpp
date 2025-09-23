//Circular references - 순환 참조 문제 해결하세요.

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
    shared_ptr<Party> m_Party;

public:
    Player() {}
    ~Player() { std::cout << "~Player()" << "\n"; }

    void SetParty(const shared_ptr<Party>& party)
    {
        m_Party = party;
    }
};

int main() {
    shared_ptr<Party> party(new Party);
    cout << party.use_count() << endl;

    for (int i = 0; i < 3; i++)
    {
        shared_ptr<Player> player(new Player);

        party->AddMember(player);     // 순환 참조가 발생한다.
        player->SetParty(party);      // 순환 참조가 발생한다.
    }

    party.reset();
}
