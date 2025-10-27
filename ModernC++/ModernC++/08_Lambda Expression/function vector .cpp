//다양한 함수를 배열로 저장하는 코드

#include <iostream>
#include <functional>
#include <vector>

// 가변 인수 처리 함수 (종료 조건)
void processArgs() { std::cout << std::endl; }

// 가변 인수 처리 함수 (적어도 하나의 인수가 있을 때)
template<typename T, typename... Args>
void processArgs(T first, Args... rest) {
    std::cout << first << " "; //"Processing argument: "
    processArgs(rest...);
}

// 템플릿을 사용한 덧셈 함수
template<typename T>
T add(T a, T b) {
    return a + b;
}

// 템플릿을 사용한 함수 반환 함수
template<typename... Args>
auto makeFunc(Args... rest) {
    // add 함수를 반환하는 람다 표현식
    return [=]() { return processArgs(rest...); };
}

int main()
{
    //makeFunc(1, 2)();
    //makeFunc('a','b','c')();

    // std::function 객체 생성
    std::vector< std::function<void()> > fn_list;

    fn_list.push_back(makeFunc(1, 2, 3));
    fn_list.push_back(makeFunc(1.5, 3.2f, 'A'));
    fn_list.push_back(makeFunc('a', "abc"));

    fn_list[1] = nullptr;

    for (size_t i = 0; i < fn_list.size(); i++)
    {
        if (fn_list[i]) fn_list[i]();
    }

    return 0;
}

