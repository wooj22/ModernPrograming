//어트리뷰트(Attributes) 예제

//--------------------------------------------------------------------------
// likely, unlikely   //C++20

//두 어트리뷰트 모두 문에 적용되는 어트리뷰트들인데, 이름에서 추측할 수 있듯이 
//likely는 실행 가능성이 높은 문에, 
//unlikely는 실행 가능성이 낮은 문에 붙여 컴파일러가 최적화하도록 하는 어트리뷰트입니다.

//기존의 C++에서는 switch 문 같은 경우에서 
//switch문을 2중으로 겹쳐서 자주 쓰이지 않는 case들은 
//안쪽 switch문에 넣는 식으로 최적화하는 경우가 많았는데, 
//이런 경우에 likey, unlikey 어트리뷰트를 사용하면 더 깔끔하게 최적화.

    int f(int i)
    {
        switch (i)
        {
        case 1: [[fallthrough]];
        [[likely]] case 2: return 1;
        }
        return 2;
    }


#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>

namespace with_attributes {
    constexpr double pow(double x, long long n) noexcept {
        if (n > 0) [[likely]]
            return x * pow(x, n - 1);
        else [[unlikely]]
            return 1;
    }
    constexpr long long fact(long long n) noexcept {
        if (n > 1) [[likely]]
            return n * fact(n - 1);
        else [[unlikely]]
            return 1;
    }
    constexpr double cos(double x) noexcept {
        constexpr long long precision{ 16LL };
        double y{};
        for (auto n{ 0LL }; n < precision; n += 2LL) [[likely]]
            y += pow(x, n) / (n & 2LL ? -fact(n) : fact(n));
            return y;
    }
}  // 네임스페이스 with_attributes

namespace no_attributes {
    constexpr double pow(double x, long long n) noexcept {
        if (n > 0)
            return x * pow(x, n - 1);
        else
            return 1;
    }
    constexpr long long fact(long long n) noexcept {
        if (n > 1)
            return n * fact(n - 1);
        else
            return 1;
    }
    constexpr double cos(double x) noexcept {
        constexpr long long precision{ 16LL };
        double y{};
        for (auto n{ 0LL }; n < precision; n += 2LL)
            y += pow(x, n) / (n & 2LL ? -fact(n) : fact(n));
        return y;
    }
}  // 네임스페이스 no_attributes


double gen_random() noexcept {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(-1.0, 1.0);
    return dis(gen);
}

volatile double sink{}; // 부작용 보장

int main() {
    for (const auto x : { 0.125, 0.25, 0.5, 1. / (1 << 26) }) {
        std::cout
            << std::setprecision(53)
            << "x = " << x << '\n'
            << std::cos(x) << '\n'
            << with_attributes::cos(x) << '\n'
            << (std::cos(x) == with_attributes::cos(x) ? "equal" : "differ") << '\n';
    }

    auto benchmark = [](auto fun, auto rem) {
        const auto start = std::chrono::high_resolution_clock::now();
        for (auto size{ 1ULL }; size != 10'000'000ULL; ++size) {
            sink = fun(gen_random());
        }
        const std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
        std::cout << "Time: " << std::fixed << std::setprecision(6) << diff.count() << " sec " << rem << std::endl;
        };

    benchmark(with_attributes::cos, "(with attributes:)");
    benchmark(no_attributes::cos, "(without attributes)");
    benchmark([](double t) { return std::cos(t); }, "(std::cos)");
}


​
//--------------------------------------------------------------------------
//no_unique_address
//
//  빈 구조체(클래스)는 크기가 1바이트로 정의되는데, 
//  빈 구조체(클래스)를 다른 구조체(클래스)에서 멤버 변수로 선언할 때 
//  이 어트리뷰트를 해당 멤버 변수에 적용시켜주면 
//  컴파일러가 그 빈 구조체(클래스)를 실제로는 포함시키지 않도록 최적화할 수 있습니다.


#include <iostream>

struct Empty {}; // 빈 클래스

struct X {
    int i;
    Empty e;
};

struct Y {
    int i;
    [[no_unique_address]] Empty e;
};

struct Z {
    char c;
    [[no_unique_address]] Empty e1, e2;
};

struct W {
    char c[2];
    [[no_unique_address]] Empty e1, e2;
};

int main()
{
    // 빈 클래스 유형의 모든 객체 크기는 1 이상입니다.
    static_assert(sizeof(Empty) >= 1);

    // ea 고유 주소를 제공하려면 적어도 하나 이상의 바이트가 필요합니다.
    static_assert(sizeof(X) >= sizeof(int) + 1);

    // 최적화 된 빈 멤버
    std::cout << "sizeof(Y) == sizeof(int) is " << std::boolalpha
        << (sizeof(Y) == sizeof(int)) << '\n';

    // e1과 e2는 같은 주소를 가질 수 없습니다.
    // [[no_unique_address]]로 표시되어 있어도 동일한 유형입니다.
    // 그러나 둘 중 하나는 c와 주소를 공유 할 수 있습니다.
    static_assert(sizeof(Z) >= 2);

    // e1과 e2는 같은 주소를 가질 수 없지만 둘 중 하나는 공유 할 수 있습니다.
    // c [0] 및 다른 하나는 c [1]
    std::cout << "sizeof(W) == 2 is " << (sizeof(W) == 2) << '\n';
}
​

//--------------------------------------------------------------------------
//nodiscard
//
//  이 어트리뷰트는 C++17에 추가된 어트리뷰트로, 
//  반환 값이 있는 함수에서 사용됐을 때 반환 값이 무시되면 경고를 발생시키는 어트리뷰트입니다.
//  구조체나 클래스에서도 사용할 수 있는데, 
//  이 경우 해당 구조체(클래스)를 반환하는 함수의 반환 값이 무시됐을 경우 경고를 발생시킵니다.
// 
//  C++17에서 추가됐는데  
//  C++20부터는 발생하는 경고 메시지를 설정할 수 있게 되었다.

//[[nodiscard("메시지")]]
//...
//위와 같은 형태로 사용하면 반환 값이 버려졌을 때의 경고 메시지를 정할 수 있어요.


struct [[nodiscard]] error_info { };

error_info enable_missile_mode() { return error_info{}; }

void test_missiles() {
    enable_missile_mode();      // 컴파일러는 nodiscard 값을 버릴 때 경고 할 수 있습니다.
}

error_info& enable_missile_mode2() { error_info e; return e; }   //&

void test_missiles2() {
    enable_missile_mode2();     // nodiscard 유형은 값으로 반환되지 않으며 경고도 없습니다.
}

int main() {

}