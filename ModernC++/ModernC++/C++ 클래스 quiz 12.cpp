//클래스 CNumber에 적절한 함수를 추가하여 
//아래와 같이 출력하도록 코드를 수정하세요(4점)
//
// 출력값: 3

#include<iostream> 
using namespace std;

class CNumber {
public:
    int num = 0;
    CNumber(int a) :num(a) { }
};

int main() 
{
    CNumber a(0);
    CNumber b(2);

    a.Add(1).Add(b);
    cout << a.num << endl;  //출력 값은 3
}