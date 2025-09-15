//C++에서 모든 표현식은 Lvalue 또는 Rvalue 이다.

//C++11 표준에서는 
//      Lvalue 참조자 외에 
//      Rvalue를 참조할 수 있는 Rvalue 참조자를 추가했다.
//
//      Rvalue reference를 파라미터로 갖는 새로운 타입의 생성자가 추가되었으며,
//      이를 이동 생성자(move constructor)라고 한다.
//https://docs.microsoft.com/ko-kr/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170&viewFallbackFrom=vs-2019

/*
//이동 생성자 작성하기
    T( T&& a);
    이동 생성자는 호출되면 얕은 복사(shallow copy)를 하고 원본의 소유권을 대상으로 이전(move)하는 방식으로 객체를 생성한다.
    원본 객체를 nullptr로 초기화하여 접근할 수 없게 만든다.

//이동생성자의 호출 조건

    1. 임시객체를 전달할 때 - rvalue
    2. std::move()를 사용하여 인자를 rValue 참조자로 변환하여 전달할 때 - lvalue

//클래스 작성할때 필요하다면 5가지의 생성자를 구현해야 한다. ( Rule Of Five )
    Foo();
    ~Foo() noexcept;
    Foo(const Foo& p);                // 복사 생성자 선언
    Foo& operator=(const Foo& p);     // 복사 대입 연산자 선언
    Foo(Foo&& p) noexcept;            // 이동 생성자 선언
    Foo& operator=(Foo&& p) noexcept; // 이동 대입 연산자 선언
*/

//이동 생성자 및 이동 할당 연산자를 작성하면,
//      적은 복사, 메모리 할당 및 메모리 할당 취소 작업을 수행하기 때문에 효율적이다.
// 
//이동 생성자와 복사 생성자를 모두 구현해 놓으면, 
//      코드 상황에 따라 복사가 되거나, 이동이 된다.


#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class Person {
    char* name;
    int age;
public:
    Person();                                   // 생성자
    Person(const char _name[], int _age);       // 생성자
    ~Person();                                  // 소멸자

    Person(const Person& p);                    // 복사 생성자 선언
    Person& operator=(const Person& p);         // 복사 대입 연산자 선언
    Person(Person&& p) noexcept;                // 이동 생성자 선언
    Person& operator=(Person&& p) noexcept;     // 이동 대입 연산자 선언

    //Setter method
    void setName(const char _name[]) {
        name = new char[strlen(_name) + 1];     // NULL문자를 고려하여 +1만큼 할당
        strcpy_s(name, strlen(_name) + 1, _name);
    }
    void setAge(int age) { this->age = age; }

    // Getter method
    string getName() { return name; }
    int getAge() { return age; }

    void ShowData();
};

Person::Person() {
    //cout << " 매개변수 없는 생성자 호출 - 메모리 주소 : " << this << endl;
    name = nullptr;
    age = 0;
}

Person::Person(const char _name[], int _age) {
    //cout << " 생성자 호출 - 메모리 주소 : " << this << endl;
    name = new char[strlen(_name) + 1]; // NULL문자를 고려하여 +1만큼 할당
    strcpy_s(name, strlen(_name) + 1, _name);

    age = _age;
}

Person::~Person() { // DeAllocate the heap
    //cout << " 소멸자 호출 - 메모리 주소 : " << this << endl;
    delete[] name;
}

Person::Person(const Person& p) : age(p.age) {
    cout << " Copy constructor 호출 - 메모리 주소 : " << this << endl;
    name = new char[strlen(p.name) + 1];        // NULL문자를 고려하여 +1만큼 할당
    strcpy_s(name, strlen(p.name) + 1, p.name); // 깊은 복사
    // The statement name = new char; will create the new heap location
    // and then copies the value of obj content to new heap location.
}

Person& Person::operator=(const Person& p) {
    cout << " Copy assignment operator 호출- 메모리 주소 : " << this << endl;
    if (this != &p) {
        delete[] name;
        name = new char[strlen(p.name) + 1];        // NULL문자를 고려하여 +1만큼 할당
        strcpy_s(name, strlen(p.name) + 1, p.name); // 깊은 복사

        age = p.age;
    }
    return *this;
}

Person::Person(Person&& other) noexcept {
    cout << " Move constructor 호출 - 메모리 주소 : " << this << endl;
    name = other.name; // 얕은 복사
    age = other.age;

    // 임시객체 소멸 시에 메모리를 해제하지 못하게 한다.
    other.name = nullptr; // nullptr 는 C++ 11 에 추가된 키워드로, 기존의 NULL 대체
    other.age = 0;
}

Person& Person::operator=(Person&& other) noexcept {
    cout << " Move assignment operator 호출 - 메모리 주소 : " << this << endl;
    if (this != &other) {
        delete[] name;
        name = other.name; // 얕은 복사
        age = other.age;

        other.name = nullptr; // 이전 객체에서 pointer는 null 선언 //delete에서 지워지지 않음 
        other.age = 0;
    }
    return *this;
}

void Person::ShowData() {   // 클래스 외부에서 클래스 멤버 함수 정의
    cout << " name : " << name << ", age : " << age << endl;
}

Person setData() {
    Person tmp;
    tmp.setName("이순신");
    tmp.setAge(54);
    return tmp;
}


int main()
{
    Person p1("홍길동", 30);
    //p1.ShowData(); cout << endl;

    Person p2(p1);                  // 복사 생성자 호출
    //Person p2 = std::move(p1);    //move 함수를 이용해서 p1를 생성할 때 이동생성자를 호출하게 함    
    p2.setAge(40);
    p1.ShowData();
    p2.ShowData(); cout << endl;

    Person p3;
    p3 = p1; // p3.operator=(p1);   // 복사 대입 연산자 호출
    //p3 = std::move(p1);           // 이동 대입 연산자 호출
    p3.setAge(50);
    p1.ShowData();
    p3.ShowData(); cout << endl;

    // 객체가 소멸되는 순서는 객체가 생성된 순서의 반대다.
}
