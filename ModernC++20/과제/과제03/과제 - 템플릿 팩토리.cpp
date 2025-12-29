// 템플릿, 스마트 포인터 사용하기
// 
// 다양한 타입의 객체를 자동으로 생성하고 이를 관리하는 
// 팩토리 클래스를 구현하세요.                          

#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <functional>

enum class PType { Player, Monster, Npc};

// Base class for objects
class Base {
public:
    virtual void info() const = 0; // Pure virtual function
    virtual ~Base() = default;
};

class Player : public Base {
public:
    void info() const override { std::cout << "I am Player" << std::endl; }
};

class Monster : public Base {
public:
    void info() const override { std::cout << "I am Monster" << std::endl; }
};

class Npc : public Base {
public:
    void info() const override { std::cout << "I am Npc" << std::endl; }
};


// Factory 클래스를 구현하세요.


int main() {
    // Factory instance
    Factory factory;

    // Register types //객체 등록
    factory.registerType<Player>(PType::Player);
    factory.registerType<Monster>(PType::Monster);
    factory.registerType<Npc>(PType::Npc);

    // Create objects //객체를 반환
    auto objA = factory.createObject(PType::Player);
    auto objB = factory.createObject(PType::Monster);
    auto objC = factory.createObject(PType::Npc);

    // Call info() on each object
    if (objA) objA->info();  // Output: I am Player
    if (objB) objB->info();  // Output: I am Monster
    if (objC) objC->info();  // Output: I am Npc

    return 0;
}