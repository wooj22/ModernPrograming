// 템플릿을 활용한 싱글톤을 구현하고, 사용 예시를 작성하세요. // CRTP

#include <iostream>

//Singleton<T>

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