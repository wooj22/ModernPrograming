//weak_ptr 활용 예제
// 
//      순환 참조 해결
//      팩토리 함수에서의 활용
//      Observer Pattern의 구현


//팩토리 함수에서의 활용 -----------------------------------------------------------------

    #include <memory>
    #include <unordered_map>

    class Player {
        // Player 클래스 정의
    };

    //어떤 unique ID에 따라 읽기만 가능한 객체에 대한 스마트 포인터를 제공하는 팩토리 함수
    std::unique_ptr<const Player> LoadPlayer(int id) {
        // Player 객체를 unique_ptr로 생성 후 반환 (예시)
        return std::make_unique<const Player>();
    }

    //최적화는 캐싱을 이용하는 것
    //이 경우에 적합하게 이용될 수 있는 것이 std::weak_ptr이다. 
    //std::weak_ptr은 캐시된 오브젝트가 파괴되었을 때 그걸 감지해줄 수 있다.

    std::shared_ptr<const Player> fastLoadPlayer(int id)
    {
        static std::unordered_map<int, std::weak_ptr<const Player>> cache;

        // 캐시에서 weak_ptr을 lock 해서 shared_ptr 획득 시도
        auto objPtr = cache[id].lock();

        if (!objPtr) { // 캐시 없거나 소멸된 경우
            // unique_ptr -> shared_ptr 변환
            std::shared_ptr<const Player> newPlayer = std::move(LoadPlayer(id));
            cache[id] = newPlayer; // 캐시에 저장
            objPtr = newPlayer;
        }
        return objPtr;
    }

//Observer Pattern의 구현 -----------------------------------------------------------------

//옵저버(Observer) 디자인 패턴에서 가장 중요한 객체는 
//      Subject(상태가 바뀔 수 있는 객체)와 Observer(상태가 바뀌었을 때 이를 통지 받는 객체)이다.
// 
//대부분의 구현에서 각각의 Subject들은 그 멤버로 자신의 Observer에 대한 포인터를 갖고 있게 된다.
//이렇게 하면 상태가 바뀌었을 때 Observer에 통지를 하기 쉬워지기 때문이다.
//각각의 Suject들은 Observer를 언제 파괴해야할지 같은 거에는 별 관심이 없으나, 해당 Observer가 파괴되었는지 아닌지에는 민감하다.
//Observer가 파괴되었으면 더 이상 상태 변화 통지를 하지 않아야하기 때문이다.
//따라서 각각의 Subject는 자신의 상태변화를 통지할 Observer들의 포인터를 std::weak_ptr로 들고 있는 것이 가장 좋을 것이다.

    #include <iostream>
    #include <vector>
    #include <memory>

    class Observer;

    // Subject 클래스
    class Subject {
        std::vector<std::weak_ptr<Observer>> observers;
    public:
        void addObserver(std::shared_ptr<Observer> obs) { observers.push_back(obs); }
        void notify();
    };

    // Observer 클래스
    class Observer : public std::enable_shared_from_this<Observer> {
    public:
        virtual void update() = 0; // 순수 가상 함수
        std::shared_ptr<Observer> getPtr() { return shared_from_this(); }
    };

    // ConcreteObserver 예시
    class ConcreteObserver : public Observer {
        int id;
    public:
        ConcreteObserver(int id) : id(id) {}
        void update() override { std::cout << "Observer " << id << " updated.\n"; }
    };

    void Subject::notify() {
        for (auto it = observers.begin(); it != observers.end(); ) {
            if (auto obs = it->lock()) { // weak_ptr를 shared_ptr로 변환 시도
                obs->update();
                ++it;
            }
            else {
                // 이미 소멸된 Observer는 리스트에서 제거
                it = observers.erase(it);
            }
        }
    }

    int main() {
        auto subject = std::make_shared<Subject>();
        auto obs1 = std::make_shared<ConcreteObserver>(1);
        auto obs2 = std::make_shared<ConcreteObserver>(2);

        subject->addObserver(obs1);
        subject->addObserver(obs2);

        subject->notify();

        obs1.reset(); // obs1 소멸

        subject->notify(); // obs2만 업데이트 호출됨

        return 0;
    }

