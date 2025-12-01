//structured binding (구조적 바인딩)
//  C++17
//  auto 뒤에 대괄호[]로 변수를 묶은 다음 
//  구조체, 클래스, 배열, pair, tuple 등 다양한 타입에 여러개의 값이 들어있는 자료형을 
//  한번에 여러 변수로 가져올 수 있다.

#include <functional>
#include <iostream>
#include <tuple>
using namespace std;

struct Point
{
    int x;
    int y;
};

int main()
{
    //구조체    
    Point pt = { 1,2 };             
    //int a = pt.x;
    //int b = pt.y;

    auto [a, b]     = pt;
    auto& [rx, ry]  = pt;

    //배열
    int x[2] = { 1,2 };             
    auto [x1, x2]   = x;

    //pair
    pair<int, double> p(1, 3.4);                
    auto [n, d]     = p;

    //tuple
    tuple<int, short, double> t3(1, 2, 3.4);    
    auto [a1, a2, a3] = t3;
}

//----------------------------------------------------------------
//초기화문을 구조화된 바인딩과 함께 사용

#include <iostream>
#include <set>
using namespace std;

int main()
{
    set<int> s;

    s.insert(5);
    s.insert(10);           //추가성공 여부를 pair<itr, bool>로 반환한다.

    //pair로 반환되는 것을 it, success로 나누어 받아 처리하라.

    if (auto [it, success] = s.insert(10); success == false)
    {
        cout << "실패" << endl;
    }
}

//연습) --------------------------------------------------------------

#include <iostream>
#include <set>
#include <utility>
using namespace std;

int main()
{

    pair<string, int> itemsToAdd[3]{ {"hello", 1}, { "world", 2 }, { "world", 2 } };

    set<pair<string, int>> mySet;

    // itemsToAdd 배열의 값들을 mySet에 추가(insert)하고, 
    // 성공적으로 추가되었는지 확인 출력하는 코드를 작성하라.

    for (auto& p : itemsToAdd)
    {
        if (const auto [iter, inserted] = mySet.insert(p); inserted)   //pair<iterator, bool>
            cout << "Value(" << iter->first << ", " << iter->second << ") was inserted" << "\n";
        else
            cout << "Value(" << iter->first << ", _) not inserted!" << "\n";
    }
}