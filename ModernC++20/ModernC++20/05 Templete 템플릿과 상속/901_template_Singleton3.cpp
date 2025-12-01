//----------------------------------------------------------------------------
// template Singleton

#include <memory>
#include <iostream>

template<typename T>
class Singleton {

public:
    static T& instance();

protected:
    Singleton() { std::cout << "Singleton()" << '\n'; }
    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;
    ~Singleton() { std::cout << "~Singleton()" << '\n';  }
};

template<typename T>
T& Singleton<T>::instance()
{
    static const std::unique_ptr<T> instance{ std::make_unique<T>()};
    return *instance;
}


//#include <iostream>

class Test final : public Singleton<Test>
{
    friend Singleton<Test>;
    friend std::unique_ptr<Test> std::make_unique<Test>();
    friend std::unique_ptr<Test>::deleter_type;
    Test() { std::cout << "constructed" << std::endl; }     //private 인 경우 
    ~Test() { std::cout << "destructed" << std::endl; }
public:
    void use() const { std::cout << "in use" << std::endl; };
};

int main()
{
    Test::instance().use();

    auto const& testRef = Test::instance();
    testRef.use();
}