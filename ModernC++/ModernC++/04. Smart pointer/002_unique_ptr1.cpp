//연습) 포인터(Pointer)를 컨테이너(Container)에 저장하기
 
// 다음 코드를 스마트 포인터로 변경하세요.

#include <vector>
#include <iostream>

class Player {
private:
    std::string name;
    unsigned char level;
public:
    Player() : name(), level() { };
    Player(std::string name, unsigned char level) : name(name), level(level) {}
    ~Player() { std::cout << "call by Destructor \n"; }

    void Display() const {
        std::cout << "name: " << name << " Level: " << static_cast<int>(level) << std::endl;
    }
};

int main() {
    std::vector<Player*> playerList;    //포인터를 백터로 관리
    playerList.emplace_back(new Player{ "Park", 5 });
    playerList.emplace_back(new Player{ "Kim", 15 });
    playerList.emplace_back(new Player{ "Kang",27 });
    playerList.emplace_back(new Player{ "Song",69 });

    for (auto& i : playerList)
        i->Display();

    for (auto& i : playerList) {
        delete i;                       //delete
    }

    playerList.clear();
}

/*
 
using spPlayer = std::unique_ptr<Player>;

int main() 
{
    std::vector<spPlayer> playerList;
    playerList.emplace_back(new Player{ "Park", 5 });
    playerList.emplace_back(new Player{ "Kim", 15 });
    playerList.emplace_back(new Player{ "Kang",27 });
    playerList.emplace_back(new Player{ "Song",69 });

    for (auto& i : playerList)
        i->Display();   
    
    //delete

    playerList.clear();
}
*/

//컨테이너 활용
// 
//  보통은 컨테이너에 객체보단 포인터를 저장하는 것이 더 좋고, 
//  원시 포인터(Raw Pointer)보단 스마트 포인터(Smart Pointer)가 대부분 더 좋다.

//컨테이너(Container)에 포인터(Pointer)를 저장하면 좋은 점
// 
//  포인터 복사가 객체 복사보다 보통은 훨씬 더 빠르다
//  컨테이너에 포인터를 저장하면 다형성(Polymorphic behaviour)을 얻을 수 있다.
//  객체를 정렬하는 것보다 빠르다. 객체가 아니라 포인터만 이동하면 되기 때문.