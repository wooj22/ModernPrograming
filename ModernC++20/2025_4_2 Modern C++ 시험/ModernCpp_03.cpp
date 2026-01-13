// 가변 탬플릿
//
// 예시와 같이 임의의 형식 데이타가 출력되도록
// print_all 함수를 가변 탬플릿으로 구현하세요.

#include <iostream>

// 가변 탬플릿 print_all 함수 구현
template<class... Args>
void print_all(Args... data)
{
    for (auto& d : data)
    {
        std::cout << data << " ";
    }
    std::cout << std::endl;
}

int main()
{
    print_all("abc");			//출력 : abc

    print_all(1, 1.5);			//출력 : 1 1.5

    print_all(1, 1.5, "abc");	//출력 : 1 1.5 abc
}

