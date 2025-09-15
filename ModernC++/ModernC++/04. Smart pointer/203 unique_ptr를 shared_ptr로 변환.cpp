//unique_ptr를 shared_ptr로 변환

#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() { std::cout << "MyClass 생성됨" << std::endl; }
    ~MyClass() { std::cout << "MyClass 파괴됨" << std::endl; }
    void show() { std::cout << "Hello from MyClass!" << std::endl; }
};

int main() {
    // unique_ptr 생성
    std::unique_ptr<MyClass> uniquePtr = std::make_unique<MyClass>();

    // unique_ptr를 shared_ptr로 변환 ***
    std::shared_ptr<MyClass> sharedPtr = std::move(uniquePtr);

    // shared_ptr 사용
    sharedPtr->show();  // 출력: Hello from MyClass!

    // unique_ptr는 이제 nullptr로 변환됨
    if (!uniquePtr) {
        std::cout << "uniquePtr는 이제 nullptr입니다." << std::endl;
    }

    return 0;
}


//unique_ptr 로 shared_ptr 생성 ---------------------------------------

#include <iostream>
#include <memory>                               //#include
using namespace std;

class Person
{
private:
    string _name;
    int _age;
public:
    Person(const string& name, int age);        // 기초 클래스 생성자의 선언
    ~Person() { cout << "소멸자" << endl; }
    void ShowPersonInfo();
};
Person::Person(const string& name, int age)     // 기초 클래스 생성자의 정의
{
    _name = name;
    _age = age;
    cout << "생성자" << endl;
}
void Person::ShowPersonInfo() {
    cout << _name << " " << _age << endl;
}

int main(void)
{
    unique_ptr<Person> p = make_unique<Person>("지훈", 19);
    p->ShowPersonInfo();

    //shared_ptr<Person> p = make_shared<Person>("지훈", 19);
    //cout << "현재 소유자 수 : " << p.use_count() << endl; // 1
    //auto han = p;
    //cout << "현재 소유자 수 : " << p.use_count() << endl; // 2
    //han.reset(); // shared_ptr인 han을 해제함.
    //cout << "현재 소유자 수 : " << p.use_count() << endl; // 1

    return 0;
}


// shared_ptr 로 unique_ptr 생성 ---------------------------------------
// shared_ptr → unique_ptr 역변환은 불가능합니다.
{
    std::shared_ptr<Foo> sp = std::make_shared<Foo>();
    std::unique_ptr<Foo> up = std::unique_ptr<Foo>(sp.get());  // X 위험한 코드, 동일한 객체를 이중 삭제

    // get()으로 raw pointer 획득 (소유권 없음)
    // 
    // shared_ptr는 내부적으로 컨트롤 블록에 객체 파괴자를 등록하고 있어서
    // 소유권을 외부로 넘기는 release() 같은 기능이 존재하지 않습니다.
}



