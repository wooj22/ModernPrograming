//형식이 아닌 매개 변수 (값 매개 변수) 사용  //타입이 아닌 템플릿 인자

//템플릿으로 배열 출력하기 ----------------------------------- 

#include <iostream>
#include <array>
using namespace std;

template<class T, std::size_t N>
void func(T(&arr)[N]) {
    static_assert(N > 1, "배열의 크기는 1보다 커야 합니다.");
    for (auto&& a : arr)
        std::cout << a << std::endl;
}

int main()
{
    int a[] = { 1, 2, 3, 4, 5 };
    func(a);                    //배열의 형태 그대로 참조로 전달하기

    return 0;
}

//템플릿에서 배열 초기화 하기 --------------------------------

template<class T, std::size_t N>
void func(T (&arr)[N]) {
    for (auto& a : arr)
        a = T{};            // 기본값을 가진 임시객체 대입
}


/*
//C++20 //concepts 사용

#include <iostream>
#include <concepts>         //C++20

template <std::integral T, std::size_t N>       // CONCEPT integral
void func(const T(&arr)[N])
{
    for (auto& a : arr)
        if (a % 2 == 1)
            std::cout << a << std::endl;
}

int main()
{
    int arr[20](1, 3, 2, 5, 55, 2, 1, 4, 6, 8, 2, 5, 3);
    func(arr);
}
*/