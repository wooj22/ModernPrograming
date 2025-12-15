// func(1,2,3,4);  //Fold Expression  4가지 방식으로 빼기를 구현하세요.
// 
// (pack op ...)           (1) Unary right fold
// (... op pack)           (2) Unary left fold
// (pack op ... op init)   (3) Binary right fold
// (init op ... op pack)   (4) Binary left fold

#include <iostream>
using namespace std;

template <typename... TArgs>
int UnaryRightFold(TArgs&&... args) { return (args - ...); }

template <typename... TArgs>
int UnaryLeftFold(TArgs&&... args) { return (... - args); }

template <typename... TArgs>
int binaryRightFold(TArgs&&... args) { return (args - ... - 10); }

template <typename... TArgs>
int binaryLeftFold(TArgs&&... args) { return (10 - ... - args); }

int main()
{
    cout << UnaryRightFold(1, 2, 3, 4) << endl;     // 1 - (2 - (3 - 4))
    cout << UnaryLeftFold(1, 2, 3, 4) << endl;      // (( 1 - 2) - 3) - 4
    cout << binaryRightFold(1, 2, 3, 4) << endl;    // 1 - (2 - (3 - (4 -10)))
    cout << binaryLeftFold(1, 2, 3, 4) << endl;     // (((10 - 1) - 2) - 3) - 4

    return 0;
}


//예시 ---------------------------------------------------------------------

#include <iostream>

template <typename Int, typename... Ints>
Int diff_from(Int start, Ints... nums) {
    return (start - ... - nums);		//이항 좌측 Fold
}

// 100 에서, 임의의 가변 데이타를 빼는 함수 구현하기 ***

int main()
{
    std::cout << diff_from(100, 1, 4, 2, 3, 10) << std::endl;
    // 100 - 1 - 4 - 2 - 3 - 10
}