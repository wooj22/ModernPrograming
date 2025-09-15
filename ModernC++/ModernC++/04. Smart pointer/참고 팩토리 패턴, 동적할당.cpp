#include <iostream>
#include <string>
#include <memory>
#include <map>

// Product 클래스 (Base)
class Product {
public:
    virtual void Use() const = 0;
    virtual ~Product() = default;
};

// ConcreteProductA 클래스
class ConcreteProductA : public Product {
public:
    void Use() const override {
        std::cout << "Using ConcreteProductA" << std::endl;
    }
};

// ConcreteProductB 클래스
class ConcreteProductB : public Product {
public:
    void Use() const override {
        std::cout << "Using ConcreteProductB" << std::endl;
    }
};

// 팩토리 클래스
class Factory {
public:
    // 팩토리에서 객체 생성
    std::unique_ptr<Product> CreateProduct(const std::string& type) {
        if (type == "A") {
            return std::make_unique<ConcreteProductA>();
        }
        else if (type == "B") {
            return std::make_unique<ConcreteProductB>();
        }
        else {
            return nullptr;
        }
    }
};

int main() {
    Factory factory;

    // Product A 생성 및 사용
    std::unique_ptr<Product> productA = factory.CreateProduct("A");
    if (productA) {
        productA->Use();  // 출력: Using ConcreteProductA
    }

    // Product B 생성 및 사용
    std::unique_ptr<Product> productB = factory.CreateProduct("B");
    if (productB) {
        productB->Use();  // 출력: Using ConcreteProductB
    }

    return 0;
}