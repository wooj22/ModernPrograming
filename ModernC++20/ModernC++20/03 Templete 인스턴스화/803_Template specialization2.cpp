//조건에 따른 처리하기 - 템플릿 특수화 활용

//IfThenElse 예제 ------------------------------------------------------------

//컴파일 시간, bool 값에 따라 type 을 선택하는 도구
//      일반적으로 IfThenElse, IF, Select 등 이름으로 구현함
//      C++ 표준에는 conditional 이름으로 제공  //<type_traits> 헤더

#include <iostream>
using namespace std;

// IfThenElse 메인 템플릿
template<bool b, typename T, typename F> struct IfThenElse          
{
    typedef T type;
};
// 부분 특수화
template<typename T, typename F> struct IfThenElse<false, T, F>
{
    typedef F type;
};

int main()
{
    // 첫번째 파라미터를 true로 할 경우 T 반환
    IfThenElse<true, int, double>::type t0;     // int

    // 첫번째 파라미터를 false로 셋팅할 경우 F 반환
    IfThenElse<false, int, double>::type t1;    // double

    cout << typeid(t0).name() << endl;
    cout << typeid(t1).name() << endl;
}


//conditional<> 활용 ------------------------------------------------------------
//      조건에 따라 서로 다른 타입을 선택하는 데 사용됩니다.

#include <iostream>
#include <type_traits>

int main() {
    // 조건에 따라 타입을 선택
    using SelectedType = std::conditional<true, int, double>::type;
    //using SelectedType = std::conditional<false, int, double>::type;

    // 선택된 타입 확인
    if constexpr (std::is_same_v<SelectedType, int>) {
        std::cout << "int" << std::endl;
    }
    else
        std::cout << "double" << std::endl;
    }

    return 0;
}

//해석 연습 ---------------------------------------------------------
#include <iostream>
#include <type_traits>
using namespace std;

template<size_t N> struct Bit
{
    // bit 단위로 데이터 관리가 필요할 경우 조건별 타입을 사용할 수 있음
    // 8이하 : char,   16이하 : short,   32이하 : int...
    using type = 
        typename conditional< 
            (N <= 8), char, typename conditional< (N <= 16), short, int >::type         
        >::type;

    type bitmap;
};

int main()
{
    Bit<32> b1;
    Bit<8> b2;
    Bit<16> b3;

    cout << sizeof(b1) << endl;
    cout << sizeof(b2) << endl;
    cout << sizeof(b3) << endl;
}


/*

    template <bool B, class T, class F>
    struct conditional {
        using type = T;     // 조건 B가 true일 때 T를 선택
    };

    template <class T, class F>
    struct conditional<false, T, F> {
        using type = F;     // 조건 B가 false일 때 F를 선택
    };

    template <bool B, class T, class F>
    using conditional_t = typename conditional<B, T, F>::type;

*/