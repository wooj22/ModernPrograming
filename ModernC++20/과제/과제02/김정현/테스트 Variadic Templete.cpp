//가변템플릿을 사용하여
// 
//아래와 같이 다양한 인수를 처리하는 함수를 작성하세요.

#include <iostream>

template<typename ...Ts>
void print(Ts ...args)
{
    //auto it = [](auto value) { std::cout << value << " "; };
    //(it(args), ...);
    ((std::cout << args << " "), ...);
    std::cout << std::endl;
}

//void print() { std::cout << std::endl; }
//
//template<typename T , typename ...Ts>
//void print(T value, Ts ...args)
//{
//    std::cout << value << " ";
//    print(args...);
//}

int main()
{
    print();
    print(1);
    print(1, 3.1, "abc");
    print(1, 2, 3, 4, 5, 6, 7);
}

