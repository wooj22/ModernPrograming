// 스마트포인터 다형성, 실형식을 확인하기 ***

#include <iostream>
#include <memory>

class Animal {
public:
    virtual ~Animal() = default;
    virtual void speak() const {  }
};

class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Woof!" << std::endl;
    }
};
class Cat : public Animal {
public:
    void speak() const override {
        std::cout << "Meow!" << std::endl;
    }
};

void Print_if_dog(const std::unique_ptr<Animal>& a) {

    if (Dog* dog = dynamic_cast<Dog*>(a.get()))
    {
        dog->speak();
    }
}

int main() {
    std::unique_ptr<Animal> dog = std::make_unique<Dog>();  // Dog 객체를 유일하게 소유   
    std::unique_ptr<Animal> cat = std::make_unique<Cat>();  // Dog 객체를 유일하게 소유

    // Dog 인 경우에만 출력하세요 
    Print_if_dog(dog);
    Print_if_dog(cat);

    return 0;
}

// 실형식을 확인 - dynamic_pointer_cast
// 
//      shared_ptr -> dynamic_pointer_cast
//      unique_ptr -> dynamic_cast
//
//      if (std::shared_ptr<Dog> dog = std::dynamic_pointer_cast<Dog>(a))  a->speak();
//      if (Dog* dog = dynamic_cast<Dog*>(a.get())) a->speak();

// 실형식을 확인 - typeid
// 
//      std::cout << "Real type: " << typeid(*animal).name() << std::endl;

// std::unique_ptr에서는 dynamic_cast를 사용하여 객체의 실형식을 확인하고, 필요에 따라 소유권을 이전하는 방식을 사용해야 합니다.
//      release()와 reset() 을 활용하여 unique_ptr 간의 소유권 이전을 안전하게 처리할 수 있습니다.
//
//      std::unique_ptr<Dog> dogPtr(dynamic_cast<Dog*>(a.release()));  