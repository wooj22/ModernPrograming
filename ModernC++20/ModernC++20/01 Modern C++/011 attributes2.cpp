//attribute 정리
//      attribute(속성) 라는 것은 컴파일러에 추가 정보를 전달하는 구문으로 [[attributes]] 이라고 쓴다.
//      최적화나 경고 추가나 제어 등을 할 수 있다.
//C++ 표준 특성
//https://docs.microsoft.com/ko-kr/cpp/cpp/attributes?view=msvc-170

//C++ 20에서 추가된 Attributes ***
//  [[nodiscard(“reason”)]]
//  [[likely]]
//  [[unlikely]]
//  [[no_unique_address]]


// nodiscard 속성  //C++20
// 
//  함수
//  함수의 반환 값을 파기해서는 안 되는 것을 나타내는 특성.
//  파기된 경우 경고문이 나온다.

    #include <iostream>

    [[nodiscard]] int* create()
    {
        return new int(0);
    }

    int main()
    {
        create(); // warning C4834: 'nodiscard' 특성이 포함된 함수의 반환 값을 버리는 중

        //int* p = create();

        return 0;
    }

// likely, unlikely 속성  //C++20
// 
//  if switch-case  //조건 분기에서 빈도를 나타내는 속성.
//  분기가 선택 되기 쉬운 경우는 likey, 
//  선택 되기 어려운 경우는 unlikey를 지정하는 것으로 '최적화 힌트'를 준다.

    #include <iostream>

    bool normal();
    bool rare();

    int main()
    {
        if (normal()) [[likely]]
        {
        }
        if (rare()) [[unlikely]]
        {
        }
        //대부분 0으로 예측이 된다면 unlikely(x) 의 형태로 쓰고, 
        //1로 예상되는 값을 likely(x) 로 쓴다.
        //예측을 도와 줌으로써 성능의 향상을 볼 수 있도록 하는 것이다.

        return 0;
    }

// no_unique_address 속성  //C++20
// 
//  비 정적 멤버 함수
//  데이터 멤버가 이 클래스의 다른 모든 비 정적 데이터 멤버와 
//  서로 다른 주소를 가질 필요가 없다는 것을 나타내는 특성

//  Empty Class 타입의 멤버를 가질 때 독립적인 주소를 가질 필요 없다."는 의미를 가진다. 
//  Empty Class를 멤버변수를 가지고 있어도 크기에 포함되지 않는다.

    #include <iostream>

    struct Empty {};

    struct Test1 {
        int x;
        Empty _noused;
    };

    struct Test2 {
        int x;
        [[no_unique_address]] Empty _noused;
    };

    int main()
    {
        static_assert(sizeof(Empty) >= 1);
        static_assert(sizeof(Test1) >= sizeof(int) + 1);
        static_assert(sizeof(Test2) == sizeof(int));

        return 0;
    }