//C++11 표준 type_traits 예제 -------------------------------------------------------------

// std::conditional< Bool조건, TrueType, FalseType >::type
// 
//      조건이 참(true)일 경우, type은 TrueType
//      조건이 거짓(false)일 경우, type은 FalseType

/*
    template <bool BoolType, typename TrueType, typename FalseType>
    struct conditional
    {
        // BoolType이 false라면, type은 FalseType
        using type = FalseType;
    };

    template <typename TrueType, typename FalseType>
    struct conditional<true, TrueType, FalseType>
    {
        // 조건이 참(true)일 경우, type은 TrueType
        using type = TrueType;
    };

    // C++14에 추가된 Helper
    template <bool BoolType, typename TrueType, typename FalseType>
    using conditional_t = typename conditional<BoolType, TrueType, FalseType>::type;


//(컴파일 타임에...)
//      BoolType의 평가가 true이면, std::condition::type은 TrueType 형식이 되는 것이고
//      BoolType의 평가가 false이면, std::condition::type은 FalseType 형식이 되는 것이다.

*/


#include <iostream>
#include <type_traits>
#include <typeinfo>

int main()
{
    typedef std::conditional<true, int, double>::type Type1;
    typedef std::conditional<false, int, double>::type Type2;
    typedef std::conditional<sizeof(int) >= sizeof(double), int, double>::type Type3;

    std::cout << typeid(Type1).name() << '\n';
    std::cout << typeid(Type2).name() << '\n';
    std::cout << typeid(Type3).name() << '\n';
}

/*
#include <iostream>
#include <type_traits>

int main()
{
    std::conditional<false, int, double>::type a;       //a 의 자료형은?

    using type = std::conditional_t<sizeof(int) >= sizeof(short), int, short>;
    type b;             //b 의 자료형은?
}

*/