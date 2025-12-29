//가변템플릿을 사용하여
// 
//아래와 같이 다양한 인수를 처리하는 함수를 작성하세요.

#include <iostream>

inline void print()
{
    std::cout << '\n';
}

template <typename T, typename... Ts>
void print(const T& first, const Ts&... rest)
{
    std::cout << first;
    ((std::cout << ' ' << rest), ...);
    std::cout << '\n';
}

int main()
{
    print();
    print(1);
    print(1, 3.1, "abc");
    print(1, 2, 3, 4, 5, 6, 7);
}

