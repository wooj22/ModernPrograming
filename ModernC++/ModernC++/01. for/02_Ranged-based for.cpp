//범위 기반 for 루프(ranged-based for loop)는 
//      고정 배열뿐만 아니라
//      std::vector, std::list, std::set, std::map과 같은 구조에서도 작동한다.

#include <iostream>
#include <vector>
using namespace std;

int main() {

    //std::vector, 고정 배열  모두 사용가능

    std::vector<int> fibo = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };
    for (const auto& n : fibo)
        std::cout << n << ' ';
    std::cout << '\n';


    //for 와는 달리 한계 존재
    // 1. 범위기반 for문에서는 index 정보가 존재하지 않습니다.
    // 2. 범위기반 for 배열의 요소를 변경할 수 없다. 별도 선언 필요.

    vector<int> v = { 1,2,3,4,5,6,7,8,9 };

    //cout << "ex1) 기존의 반복문" << endl;
    for (vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;

    //cout << "ex2) 범위기반 반복문" << endl;   //범위기반 for문
    for (int elem : v)
    {
        cout << elem << " ";
    }
    cout << endl;

    //원래 데이터 변경 되는 경우는?
     
    //cout << "ex3) 기존 반복문에서 원래 데이터 변경 확인" << endl;
    for (vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter)
    {
        *iter += 10;  cout << *iter << " ";
    }
    cout << endl;
    for (int elem : v) { cout << elem << " "; } //


    //cout << "ex4) 범위기반 반복문에서 원래 데이터 변경 확인" << endl;
    for (int elem : v)
    {
        elem += 100; cout << elem << " ";
    }
    cout << endl;
    for (int elem : v) { cout << elem << " "; }

    //원래 데이터 변경을 하려면???     ->  & 참조 사용해야함

    return 0;
}

