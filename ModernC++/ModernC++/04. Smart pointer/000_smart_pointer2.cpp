//메모리 관리 오류
//  첫 번째로 메모리를 사용한 후에 해제하지 않은 경우, 해제없이 재할당하는 경우.
//  두 번째로 발생 가능한 문제는, 이미 해제된 메모리를 다시 참조하는 경우

/*
// double free 버그
        Data* data = new Data();
        Date* data2 = data;
        delete data;          // data 의 입장 : 사용 다 했으니 소멸시켜야지.
        delete data2;         // data2 의 입장 : 나도 사용 다 했으니 소멸시켜야지
*/

//C++ 에서 자원을 관리하는 방법
//  RAII 패턴 ***
//      - Resource Acquisition Is Initialization  
//      - 자원의 획득은 초기화다 
//      스택에 할당된 메모리는 자동으로 해제되는 것을 이용한 디자인 패턴 - 자원 관리를 안전하게

#include <iostream>
#include <memory>

class MyString
{
public:
    char* c = nullptr;

    MyString(size_t len) { c = new char[len]; }
    ~MyString() { delete[] c; }                     //RAII 패턴
};

int main()
{
    // 반드시 delete 필요
    {
        char* c = new char[100];
        strcpy_s(c, 14, "Hello, world!");
        //throw 0;  //예외 발생하면 memory leak
        delete[] c;
    }

    //RAII 패턴으로 바꾸면, delete 없이 객체 생성하여 사용
    {
        MyString s(100);
        //throw 0;  //예외 발생하면 객체 소멸시 소멸자 호출
        strcpy_s(s.c, 14, "Hello, world!");
    }

}

