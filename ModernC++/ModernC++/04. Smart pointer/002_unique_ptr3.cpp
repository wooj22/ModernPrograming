//custom deleter
// 
//      unique_ptr 은 메모리의 할당에는 관여하지 않으면서, 메모리의 해제를 수행.
//      new 가 아니라 malloc 과 같이 다른 형태로 할당했다면 문제가 발생할 것입니다. 
//      이때는 custom deleter를 구현해주어야 합니다.

//      std::unique_ptr 의 자원 해제 동작은 delete 를 통해 이루어지지만
//      custom deleters 를 명시해줄 경우 해당 custom deleter 를 이용해 자원을 해제한다

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct MyDeleter
{
    MyDeleter() { cout << "MyDeleter()" << endl; }
    ~MyDeleter() { cout << "~MyDeleter()" << endl; }
    void operator()(void* x) { free(x); }
};

int main()
{
    unique_ptr<int, MyDeleter> a( (int*)malloc(sizeof(int)) );    //MyDeleter 함수객체 전달

    return 0;
}


//함수 포인터을 통한 custom deleter 정의 -----------------------------------
/*

    void my_deleter(void* x) { free(x); cout << "my_deleter()" << endl; }

    int main()
    {
        unique_ptr<int, void (*)(void* x)> a((int*)malloc(sizeof(int)), my_deleter);    
    }

*/


//lambda expression을 통한 custom deleter 정의 -----------------------------------
/*
    class Player {
    public:
        Player() : name("") {}
        Player(string n) : name(n) {}
        string name;
    };

    auto myDeleter = [](Player* pPlayer) {
        cout << "myDeleter" << '\n';
        delete pPlayer;
    };

    int main(void)
    {
        unique_ptr<Player, decltype(myDeleter)> uptr(new Player(), myDeleter);
    }
*/


/*
// 상속관계에서 사용하는 예제 --------------------------------------------------

    #include <iostream>
    #include <memory>
    #include <vector>
    using namespace std;

    class Player {
    public:
        Player() : name("") {}
        Player(string n) : name(n) {}
        virtual ~Player() { cout << "~Player()" << '\n'; }  //가상함수
        string name;
    };

    class Hero : public Player {
    public:
        Hero(string n) : Player(n) {}
    };

    class Enemy : public Player {
    public:
        Enemy(string n) : Player(n) {}
    };

    template<typename Ts>
    auto makePlayer(Ts&& params)             //팩토리 함수
    {
        auto myDeleter = [](Player* pPlayer) { delete pPlayer; };

        std::unique_ptr<Player, decltype(myDeleter)> pPlayer(nullptr, myDeleter);

        if (params == "hero") {
            pPlayer.reset(new Hero(std::forward<Ts>(params)));
        }
        else {
            pPlayer.reset(new Enemy(std::forward<Ts>(params)));
        }
        return pPlayer;
    }

    int main() {

        //std::unique_ptr<Player> pPlayer(nullptr);
        //pPlayer.reset(new Hero("hero") );

        auto hero = makePlayer<string>("hero");
        cout << hero->name << '\n';

        auto enemy = makePlayer<string>("enemy");
        cout << enemy->name << '\n';

    }

*/


//default deleter를 쓰는 경우에는
//      std::unique_ptr의 크기가 정확히 raw pointer와 같다
//
//custom deleter를 쓰는 경우에는
//      함수 포인터인 경우에는 워드(word) 하나 크기에서 2개 크기로 늘린다.
//      함수 객체인 경우에는 해당 함수 객체가 내부에 저장하고 있는 상태의 개수에 따라 std::unique_ptr의 크기가 달라진다.
//      아무것도 capture 하지 않은 lambda expression 같이 Stateless한 함수 객체는 크기에 있어서 어떤 패널티도 없다.
//      즉, captureless lambda expression으로 짜는 게 더 좋다.


