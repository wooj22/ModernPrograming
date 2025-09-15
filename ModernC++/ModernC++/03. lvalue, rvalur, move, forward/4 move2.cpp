//복사 생성자, 이동 생성자 예시

//vector 에서 사용하기

#include <iostream>
#include <cstring>
#include <vector>

class MyString
{
    char* content;                  // 문자열 데이터를 가리키는 포인터
    int len;                        // 문자열 길이
    int memory_capacity;            // 현재 할당된 용량

public:
    MyString();
    MyString(const char* str);      // 문자열로 부터 생성    
    MyString(const MyString& str);  // 복사 생성자    
    MyString(MyString&& str);       // 이동 생성자
    ~MyString();

    MyString operator+(const MyString& s);
    void reserve(int size);
    int length() const;
    void print();
    void println();
};

MyString::MyString() {
    std::cout << "생성자 호출 ! " << std::endl;
    len = 0;
    memory_capacity = 0;
    content = nullptr;
}

MyString::MyString(const char* str) {
    std::cout << "생성자 호출" << std::endl;
    len = strlen(str);
    memory_capacity = len;

    content = new char[len];
    for (int i = 0; i != len; i++) content[i] = str[i];
}
MyString::MyString(const MyString& str) {               //복사 생성자의 정의 
    std::cout << "복사 생성자 호출" << std::endl;
    len = str.len;
    memory_capacity = str.len;

    content = new char[len];
    for (int i = 0; i != len; i++) content[i] = str.content[i];
}
MyString::MyString(MyString&& str) {                    //이동 생성자의 정의
    std::cout << "이동 생성자 호출" << std::endl;
    len = str.len;
    memory_capacity = str.memory_capacity;
    content = str.content;
    str.content = nullptr;   // 임시 객체 소멸 시에 메모리를 해제하지 못하게 한다.
}
MyString::~MyString() {
    if (content) delete[] content;        //nullptr 가 아닐 때에만 delete
}

MyString MyString::operator+(const MyString& s) {
    MyString str;
    str.reserve(len + s.len);
    for (int i = 0; i < len; i++)   str.content[i] = content[i];
    for (int i = 0; i < s.len; i++) str.content[len + i] = s.content[i];
    str.len = len + s.len;
    return str;
}

void MyString::reserve(int size) {
    if (size > memory_capacity) {
        char* prev_content = content;

        content = new char[size];
        memory_capacity = size;

        for (int i = 0; i != len; i++)
            content[i] = prev_content[i];

        if (prev_content != nullptr) delete[] prev_content;
    }
}

int MyString::length() const {
    return len;
}
void MyString::print() {
    for (int i = 0; i != len; i++) std::cout << content[i];
}
void MyString::println() {
    print(); std::cout << std::endl;
}

int main()
{
    MyString str1("abc");
    MyString str2("def");

    //객체 연산 지원하기 ---------------------------------

    MyString str3 = str1 + str2;
    //MyString&& str3 = str1 + str2;    //우측값 레퍼런스는 레퍼런스 하는 임시 객체가 소멸되지 않도록 붙들고 있다

    str3.println();
    std::cout << std::endl;

    //vector 에 추가하기 ---------------------------------

    MyString s("abc");
    std::vector<MyString> vec;
    vec.resize(0);

    std::cout << "첫 번째 추가 ---" << std::endl;
    vec.push_back(s);
    std::cout << "두 번째 추가 ---" << std::endl;
    vec.push_back(s);
    std::cout << "세 번째 추가 ---" << std::endl;
    vec.push_back(s);

    //vector 는 이동 생성자가 noexcept 가 아니면 이동 생성자를 사용하지 않습니다 ***

    //이동생성자가 호출되도록 해보자.

}