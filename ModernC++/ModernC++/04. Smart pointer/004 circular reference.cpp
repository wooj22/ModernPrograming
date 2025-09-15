//순환 참조(circular reference) 문제
// 
//      std::shared_ptr을 사용할 때 발생할 수 있는 '메모리 누수(memory leak)'의 주요 원인 중 하나

#include <iostream>
#include <memory>

class A;

class B {
public:
    std::shared_ptr<A> a;   //
    ~B() { std::cout << "B destroyed\n"; }
};

class A {
public:
    std::shared_ptr<B> b;   //
    ~A() { std::cout << "A destroyed\n"; }
};

int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();

    a->b = b;
    b->a = a;  // 순환 참조 발생

    // a와 b가 모두 사용 후 종료되지만, A와 B는 여전히 메모리에 남아 있음

    return 0;
}

//순환 참조(circular reference) 문제

#include <iostream>
#include <memory>
#include <vector>

class Person;  // 전방 선언

class Group {
public:
    std::vector<std::shared_ptr<Person>> members;   //
    ~Group() { std::cout << "Group destroyed\n"; }
};

class Person {
public:
    std::vector<std::shared_ptr<Group>> groups;     //
    ~Person() { std::cout << "Person destroyed\n"; }
};

int main() {
    // Person과 Group 객체 생성
    std::shared_ptr<Person> p1 = std::make_shared<Person>();
    std::shared_ptr<Person> p2 = std::make_shared<Person>();
    std::shared_ptr<Group> g1 = std::make_shared<Group>();
    std::shared_ptr<Group> g2 = std::make_shared<Group>();

    // 서로를 참조하여 순환 참조 발생
    p1->groups.push_back(g1);
    p2->groups.push_back(g2);
    g1->members.push_back(p1);
    g2->members.push_back(p2);

    // p1, p2, g1, g2가 소멸되어야 하지만, 순환 참조로 인해 메모리 누수 발생

    return 0;
}

//순환 참조(circular reference) 문제

#include <iostream>
#include <memory>
#include <vector>

class Light;  // 전방 선언

class Camera {
public:
    std::vector<std::shared_ptr<Light>> lights;     // 여러 Light 객체를 참조
    ~Camera() { std::cout << "Camera destroyed\n"; }
};

class Light {
public:
    std::shared_ptr<Camera> camera;             // 현재 활성화된 Camera를 참조
    ~Light() { std::cout << "Light destroyed\n"; }
};

int main() {
    // Camera와 Light 객체 생성
    std::shared_ptr<Camera> cam = std::make_shared<Camera>();
    std::shared_ptr<Light> light1 = std::make_shared<Light>();
    std::shared_ptr<Light> light2 = std::make_shared<Light>();

    // 순환 참조 발생
    cam->lights.push_back(light1);
    cam->lights.push_back(light2);
    light1->camera = cam;
    light2->camera = cam;

    // cam, light1, light2는 순환 참조로 인해 소멸되지 않음

    return 0;
}