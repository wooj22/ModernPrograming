//싱글톤을 만드는 더 좋은 방법은 C++11 Magic Statics 에 의존하는 것입니다. 간단히 다음과 같이 하십시오.
//https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2660.htm

#include <iostream>

class Test {
private:
    Test() { std::cout << "constructed" << std::endl; }; // Disallow instantiation outside of the class.
public:
    ~Test() { std::cout << "destructed" << std::endl; }
    Test(const Test&) = delete;
    Test& operator=(const Test&) = delete;
    Test(Test&&) = delete;
    Test& operator=(Test&&) = delete;

    static auto& instance() {
        static Test test;
        return test;
    }

    void use() const { std::cout << "in use" << std::endl; };
};

int main()
{
    //Test cannot_create; /* ERROR */

    std::cout << "Entering main()" << std::endl;
    {
        Test::instance().use();
    }
    {
        Test::instance().use();
    }
    std::cout << "Leaving main()" << std::endl;
}

// 위 코드에서 싱글톤 부분에 템플릿 상속을 적용하자.

//----------------------------------------------------------------------------
// template Singleton

#include <memory>

template<typename T>
class Singleton {
public:
    static T& instance();

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


int main()
{
    // Test cannot_create; /* ERROR */

    std::cout << "Entering main()" << std::endl;
    {
        auto const& t = Test::instance();
        t.use();
    }
    {
        Test::instance().use();
    }
    std::cout << "Leaving main()" << std::endl;
}