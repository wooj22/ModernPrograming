//CRTP // virtual 없이 다형성 구현하기

/*
#include <iostream>  // virtual 다형성 

class Animal {
public:
    virtual void print() const {}
};

class Cat : public Animal {
public:
    void print() const { std::cout << "Cat\n"; }
};

class Dog : public Animal {
public:
    void print() const { std::cout << "Dog\n"; }
};

int main()
{
    Animal* cat = new Cat;  cat->print();
    Animal* dog = new Dog;  dog->print();
}
*/

#include <iostream>

template<typename T>
class Animal {
public:
    void print() const {
        (static_cast<const T&>(*this)).print();
    }
};

class Cat : public Animal<Cat> {
public:
    void print() const { std::cout << "Cat\n"; }
};

class Dog : public Animal<Dog> {
public:
    void print() const { std::cout << "Dog\n"; }
};

template<typename T>
void print_animal(const Animal<T>& animal) {
    animal.print();
}
int main()
{
    Cat cat;    print_animal(cat);
    Dog dog;    print_animal(dog);
}