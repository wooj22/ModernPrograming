// std::ref()
//    & 와 다르게, 타입만 같다면 참조대상을 바꿀 수 있다.

#include <iostream>
#include <functional>
using namespace std;

int main()
{
    int n1 = 10;
    int n2 = 20;

    int& r1 = n1;
    int& r2 = n2;

    r1 = r2;
    // r1이 r2를 가리키게 될까?
    // 아니면 값이 20으로 변경되나?

    cout << n1 << endl;
    cout << n2 << endl;
    cout << r1 << endl;
    cout << r2 << endl;
    // 정답은 값만 20으로 변경! -> 참조형은 한 번 초기화 되면 변하지 않음.

    reference_wrapper<int> r1(n1);
    reference_wrapper<int> r2(n2);

    r1 = r2;   //이 경우는 ?

    // 얕은 복사가 일어난다. -> r1이 가리키는 값이 n2로 변경이 된다는 말!

}

/*
    vector<int&> v(10);              // vector에는 참조를 못넣음

    vector<reference_wrapper<int>>;  // 단, reference_wrapper는 들어간다
*/