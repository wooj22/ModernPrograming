//constexpr 람다 식
// 
//  Visual Studio 2017 버전 15.3 이상(에서 사용 / std:c++17 constexpr 가능) : 
//  상수 식 내에서 캡처하거나 도입하는 각 데이터 멤버의 초기화가 허용되는 경우 
//  람다 식을 상수 식으로 constexpr 선언하거나 상수 식에서 사용할 수 있습니다.

    int y = 32;
    auto answer = [y]() constexpr
    {
        int x = 10;
        return y + x;
    };

    constexpr int Increment(int n)
    {
        return [n] { return n + 1; }();
    }

//람다의 결과가 constexpr 함수의 요구 사항을 충족하면, 람다는 암시적 constexpr 함수다.

    auto answer = [](int n)
    {
        return 32 + n;
    };

    constexpr int response = answer(10);

//람다가 암시적 또는 명시적으로 constexpr 이면, 함수 포인터로 변환하면 constexpr 함수가 생성됩니다.

    auto Increment = [](int n)
    {
        return n + 1;
    };

    constexpr int(*inc)(int) = Increment;