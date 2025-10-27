// 람다 캡처 변수의 범위  -------------------------------------
// 
//		람다에서 캡처는 오직 람다가 만들어지는 범위에서 볼 수 있는 
//      non-static 지역변수에 대해서만 가능하다.

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int evenCount1 = 0;                         //1.범위를 벗어난 전역에 위치, 바깥쪽 범위의 변수가 아님

int main()
{
    int evenCount2 = 0;                     //2.람다 선언된 바깥쪽 범위의 변수

    static int evenCount3 = 0;              //3.람다 선언된 바깥쪽 범위의 변수

    vector<int> v;
    for (int i = 0; i < 10; ++i) { v.push_back(i); }

    for_each(v.begin(), v.end(), [](int n) {
        if (n % 2 == 0) { evenCount2++; }		            //바깥쪽 변수는 캡처해야 사용 가능.
        });

    for_each(v.begin(), v.end(), [&](int n) {
        if (n % 2 == 0) { evenCount2++; }		            //& 는 바깥쪽 모든 변수 캡처
        });

    for_each(v.begin(), v.end(), [&](int n) {
        if (n % 2 == 0) { evenCount1++; }		            //[&]나[=]는  바깥쪽 모든 변수 캡처
        });

    for_each(v.begin(), v.end(), [evenCount1](int n) {      //전역 변수는 캡처 대상이 아님.
        if (n % 2 == 0) { evenCount1++; }                   //전역 변수는 캡처와 상관없이 사용됩니다.
        });

    for_each(v.begin(), v.end(), [evenCount3](int n) {
        if (n % 2 == 0) { evenCount3++; }		            //static 변수는 캡처 대상이 아님. 
        });

    cout << evenCount1 << " " << evenCount2 << endl;
}


//default 캡쳐 
//
//    람다 캡처 변수는 바깥쪽 함수(main) 범위에 속해야 한다. ( 람다가 정의된 곳 ) ***
//    [&] 나 [=] 는 Scope내의 모든 변수 캡쳐
//    값으로 캡쳐되는 값은 const로 캡쳐된다. 수정하려면 mutable을 사용
 
//전역 변수, static은  캡쳐 대상이 아님
//    static 이나 전역변수는 따로 정의하지 않아도 접근 가능.

/*
    int global{ 42 };
    int main()
    {
        auto lambda{ [=] { global = 2; } };
        lambda();
        // global now has the value 2
    }​
*/

//전역 변수는 비록 값으로 캡처하더라도 항상 레퍼런스 캡처처럼 작동합니다.

#include <iostream>
#include <array>
#include <algorithm>

int sum = 0;

int main() {
    std::array<int, 5> numbers = { 1, 2, 3, 4, 5 };

    // 전역 변수 sum을 참조로 캡처 //error 수정하세요.
    std::for_each(numbers.begin(), numbers.end(), [&sum](int& number) {
        sum += number;
        });

    return 0;
}

/*
    //선언된 번위에 없음. // 람다 캡처 변수는 바깥쪽 함수 범위에 속해야 합니다. 
    //전역이므로 그냥 캡처

    std::for_each(numbers.begin(), numbers.end(), [&](int& number) {        
        sum += number;
        });
}
*/



//람다에서 참조로 캡쳐된 변수를 수정하면 원본도 같이 수정됩니다.
//      기본 캡쳐를 사용해서 전체를 값이나 참조로 캡쳐하는 것 보다는 
//      명시적으로 캡쳐하는 것을 권장합니다. ***

//람다에서 참조로 변수를 캡쳐한 람다가 실행되는 시점까지 유효해야 합니다.
//      람다는 수행시점과 선언 시점이 다르기 때문에, 주의해서 사용 해야 합니다.

//값으로 캡쳐한다고 하더라도 
//      포인터를 대상으로 하거나 대상 객체 멤버 중에 포인터가 포함된 변수를
//      람다식에서 사용한다면 수행 시점까지 유효함을 지킬 수 있도록 설계 해야 합니다.


#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

class SomeClass
{
public:
    // 함수객체를 리턴합니다.
    std::function<int(const int)> GetAddFunc()
    {
        // [value=value](const int iadd) c++ 14부터는
        // Generalized capture를 지원하기 때문에 해당 문제를 해결할 수 있습니다.
        return [=](const int iadd)
            {
                return value + iadd; // value는 실제로는 this->value 입니다.
            };
    }
private:
    int value = 1;
};

// SomeClass를 통한 함수 사용
int main()
{
    // SomeClass 할당
    SomeClass* s = new SomeClass;

    // f에 Closure의 복사본을 저장합니다.
    auto f = nullptr != s ? s->GetAddFunc() : nullptr;

    // SomeClass 할당 해제
    delete s;

    // 비정상적인 값 출력
    if (f)
        std::cout << f(10) << std::endl;
}
