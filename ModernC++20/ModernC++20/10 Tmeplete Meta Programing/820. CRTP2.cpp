//CRTP 활용하기
 
//CRTP 활용한 Unique한 기반 클래스 만들기
//      기반 클래스의 static memeber data는 모든 파생 클래스에 의해 공유됨
//      파생 클래스 별로 다른 static member data가 필요한 경우, 서로 다른 기반 클래스를 사용해야 함
//      CRTP를 사용하면 
//      모든 파생클래스 별로 다른 타입의 기반클래스를 만들 수 있음 ***


//static 멤버 데이터를 관리하는 단일 클래스
/*
    #include <iostream>
    using namespace std;

    class Object
    {
    public:
        static int cnt;

        Object() { ++cnt; }
        ~Object() { --cnt; }

        static int getCount() { return cnt; }
    };
    int Object::cnt = 0;

    int main()
    {
        Object c1, c2;
        cout << c1.getCount() << endl;
    }
*/

//static 멤버 데이터를 관리하는 유일한 기반 클래스

#include <iostream>
using namespace std;

template<typename T>
class Object
{
public:
    static int cnt;
    Object() { ++cnt; }
    ~Object() { --cnt; }
    static int getCount() { return cnt; }
};
template<typename T> int Object<T>::cnt = 0;

class Mouse : public Object<Mouse>
{
};

class Keyboard : public Object<Keyboard>
{
};

int main()
{
    Mouse m1, m2;
    Keyboard k1, k2, k3;
    cout << m1.getCount() << endl;      //???
    cout << k1.getCount() << endl;      //???
}


//CRTP 활용한 싱글톤(Singleton) 만들기 ***

#include <memory>

template<typename T>
class Singleton {
public:
    static T& instance();           // 
    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;
protected:
    struct token {};
    Singleton() {}
};

template<typename T>
T& Singleton<T>::instance()
{
    static const std::unique_ptr<T> instance{ new T{token{}} };
    return *instance;
}

#include <iostream>

class Test final : public Singleton<Test>
{
public:
    Test(token) { std::cout << "constructed" << std::endl; }
    ~Test() { std::cout << "destructed" << std::endl; }

    void use() const { std::cout << "in use" << std::endl; };
};

int main() {

    Test::instance().use();

}