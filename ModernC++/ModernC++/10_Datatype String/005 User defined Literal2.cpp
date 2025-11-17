//예시 

#include <iostream>

// used as conversion with constexpr 
constexpr long double operator"" _deg(long double deg)
{
    return deg * 3.141592 / 180;
}

// used with custom type
struct mytype
{
    unsigned long long m;
    mytype(unsigned long long m) : m(m)
    {
    }
};

mytype operator "" _mytype(unsigned long long n)
{
    return mytype(n);
}

int main()
{
    double x = 90.0_deg;
    std::cout << std::fixed << x << '\n';

    mytype y = 123_mytype;
    std::cout << y.m << '\n';
}


/*
    cout << fixed; 의 뜻은 소수점을 고정시켜 표현을 하겠다는 뜻.
    cout.precision(6); 의 뜻은 6자리까지 표현을 하겠다는 뜻.
    이 두 표현을 합치면, 소수점 6자리 표현하겠다는 뜻.

    cout.setf(ios::fixed); 로도 표현이 가능
    해제는 cout.unsetf(ios::fixed);
*/


//연습) 길이 단위 변환 (예: cm를 m로 변환) 코드 작성하세요.

#include <iostream>

// 사용자 정의 리터럴: cm를 m로 변환
constexpr double operator"" _m(long double cm) {
    return cm / 100.0; // 1 m = 100 cm
}

int main() {
    double length = 150.0_m; // 150 cm를 m로 변환
    std::cout << "길이: " << length << " m" << std::endl; // 출력: 1.5 m
    return 0;
}