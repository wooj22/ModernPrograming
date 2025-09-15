//RAII
//      Resource Acquisition Is Initialization. 리소스 획득은 초기화입니다.
//      C++에서 자주 쓰이는 idiom
//      자원의 안전한 사용을 위해 객체가 쓰이는 스코프를 벗어나면 자원을 해제해주는 기법
//      stack에 할당된 자원은 자신의 scope가 끝나면 메모리가 해제되며 destructor가 불린다는 원리를 이용

#include <iostream>
#include <memory>

class MyString
{
public:
    char* c = nullptr;

    MyString(size_t len) { c = new char[len]; }     //new
    ~MyString() { delete[] c; }                     //delete
};

int main()
{
    char* c = new char[100];
    strcpy_s(c, strlen(c), "Hello, world!");
    //throw 0;  //예외 발생하면 memory leak
    delete[] c;

    //RAII 패턴으로 바꾸면, delete 없이 객체 생성하여 사용

    MyString s(100);
    //throw 0;
    strcpy_s(s.c, strlen(s.c), "Hello, world!");

}

//스마트 포인터를 사용한 안전한 클래스

#include <memory>
#include <iostream>
#include <cstring>

class SafeString {
private:
    std::unique_ptr<char[]> data;

public:
    SafeString(const char* str) {
        size_t len = strlen(str) + 1;
        data = std::make_unique<char[]>(len);
        strcpy(data.get(), str);
    }

    void print() const {
        std::cout << data.get() << '\n';
    }

    // 복사/이동/소멸자 필요 없음 → Rule of Zero
};

//복사 생성자 / 이동 생성자 / 소멸자 등을 직접 구현하지 않아도 안전
//메모리 누수나 double - free 없이 객체를 사용할 수 있음
//RAII 원칙에 완벽히 부합

