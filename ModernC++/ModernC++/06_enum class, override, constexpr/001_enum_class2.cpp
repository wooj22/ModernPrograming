//기존 C++98 에서 enum 의 문제점이라고 한다면 
//  enum은 별도의 이름공간(namespace)를 가지고 있지 않는 것
//  enum 들을 정확하게 구분하기 위해서 enum class가 도입

//enum class 요약 ***
//
//  enum class를 쓰면 "열거형이름::열거자" 이런식으로 접근이 가능하다.
//  enum class를 쓰면 중복되는 열거자 이름이 있어도 괜찮다.
//  enum class를 쓰면 암시적 형변환이 막히기 때문에 명시적 형변환을 해야한다.
//  enum class를 쓰면 전방 선언이 가능하다.

#include<iostream>
using namespace std;

enum class Subject : int; //전방선언

int main(void)
{
    //선언한 것 사용
    if (static_cast<int>(Subject::KOREAN) == 1) {
        cout << "KOREAN is 1" << endl;
    }
    else {
        cout << "KOREAN is not 1" << endl;
    }

    return 0;
}

//enum class정의
enum class Subject : int
{
    MATH,
    KOREAN,
    ENGLISH,
};
