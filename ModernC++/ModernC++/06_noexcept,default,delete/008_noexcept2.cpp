// strong exception guarantee

//  C++11 이후 std::vector뿐만 아니라, STL 컨테이너들은 move semantics가 모두 적용되어 있다.
//  원소에 대한 이동 처리를 할 때, 
//  해당 원소가 move시 noexcept를 지원하지 않으면,
//  move semantics가 아닌 copy semantics로 element를 처리한다.
// 
//  move semantics의 혜택을 제대로 누리려면, 
//  noexcept 한정자를 통해 strong exception guarantee를 보장해 줘야 한다. ***

#include <iostream>
#include <vector>

struct foo
{
    int value;

    explicit foo(int value) : value(value)
    {
        std::cout << "foo(" << value << ")\n";
    }

    foo(foo const& other) : value(other.value)
    {
        std::cout << "foo(foo(" << value << "))\n";
    }

    foo(foo&& other) noexcept : value(std::move(other.value))  //noexcept
    {
        other.value = -1;
        std::cout << "foo(move(foo(" << value << "))\n";
    }

    ~foo()
    {
        if (value != -1)
            std::cout << "~foo(" << value << ")\n";
    }
};

int main()
{
    std::vector<foo> foos;
    foos.emplace_back(1);

    // 이때, 벡터의 확장을 위해 reserve가 발생.
    // 만약 foo의 이동 생성자가 noexcept를 보장하지 않으면, copy construction이 발생한다
    // 즉, reallocating 과정에서 이동이 아닌 복사가 발생하여 성능 이득을 얻지 못하게 되는 것이다
    foos.emplace_back(2);
}