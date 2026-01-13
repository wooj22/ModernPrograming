// 템플릿 템플릿 파라미터 

#include <iostream>
#include <list>

// std::list 와 값을 받아 해당 리스트에 값을 추가하는 코드를 작성하세요.     
template <template<typename, typename> class Container, typename T>
void addToContainer(Container<T, std::allocator<T>>& c, const T& value)
{
    c.push_back(value);
}

int main() {

    // int 타입의 std::list
    std::list<int> intList;

    // list에 값 추가
    addToContainer(intList, 5);
    addToContainer(intList, 10);
    addToContainer(intList, 15);

    for (auto& e : intList) std::cout << e << std::endl;
}

