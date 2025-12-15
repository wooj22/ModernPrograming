#include <iostream>
#include <vector>
using namespace std;

// const - 실수를 줄이자.

int get_int() { return 1; }

int main()
{
    int a = 0;
    a = 1;                      //변수로 사용하는 것보다, 변경되지 않는 것이면 상수로 사용

    const int a = 0;                //상수로 사용      // 컴파일러가 최적화
    const int b = a;                //변수할당 가능.   // 값이 컴파일타임에 정해진다는 보장 안됨
    const int c = get_int();        //const로 받는다.   //실시간으로 받아온 값을 유지할 것이라는 것을 알 수 있다.

    constexpr int a = 0;        //컴파일타임에서 사용할때 더 확실히 오류 검출
    constexpr int b = a;            //error
    constexpr int c = get_int();    //error
}

/*

// 문제) 코드를 개선해서 실수를 막아봅시다.

class A {
public:
    void setVector(std::vector<int>& v) {}      //v 값의 변화가 없음
    void printVec() {}                          //name 값의 변화가 없음
    string& getNameRef() { return name; }       //반환값의 변화가 없음
private:
    string name;
};

//답

class A {
public:
    void setVector(const std::vector<int>& v) {}
    void printVec() const {}
    const string& getNameRef() { return name; }
private:
    string name;
};

*/