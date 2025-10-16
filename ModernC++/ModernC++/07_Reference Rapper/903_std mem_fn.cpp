// 함수를 객체로
// 
//      Callable 들을 객체의 형태로 보관할 수 있는 std::function 이라는 클래스를 제공
//      mem_fn 예제,  bind 예제 

//mem_fn ----------------------------------------------------------------------------------
//      
//		'클래스의 멤버 함수'를 호출할 수 있는 객체를 생성하는 유틸리티
//      멤버 함수들을 함수 객체로 (맴버 pointers 를 위한  wrapper objects 생성한다.)
//      주로 알고리즘과 함께 사용하거나 멤버 함수를 인수로 전달할 때 유용


#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class MyClass {
public:
    void display() const {
        std::cout << "MyClass에서 인사드립니다!" << std::endl;
    }
};

int main() {
    std::vector<MyClass> objects(3);

    // mem_fn을 사용하여 각 객체의 display 메서드를 호출
    std::for_each(objects.begin(), objects.end(), std::mem_fn(&MyClass::display));

    return 0;
}

//--------------------------------------------------------------------------------
int main() {

    vector<int> a(1);
    vector<int> b(2);
    vector<int> c(3);
    vector<int> d(4);

    vector<vector<int>> container;      //각 벡터의 크기를 출력해보자.
    container.push_back(a);
    container.push_back(b);
    container.push_back(c);
    container.push_back(d);

    vector<int> size_vec(4);
    transform(container.begin(), container.end(), size_vec.begin(),
        std::mem_fn(&vector<int>::size));                                   //mem_fn

    for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr) {
        std::cout << "벡터 크기 :: " << *itr << std::endl;
    }

    //멤버 함수 size를 function 으로 리턴
    //std::function<size_t(const vector<int>&)> sz_func = &vector<int>::size; // 이런 표현을  
    //std::mem_fn(&vector<int>::size)                                         // 이렇게 사용하면 편리
    //[](const auto& v) { return v.size()}                                    // 람다를 사용하면 더 간단.  
}

//--------------------------------------------------------------------------------
//Use std::mem_fn to store and execute a member function and a member object:

#include <functional>
#include <iostream>
#include <memory>

struct Foo
{
    void display_greeting() { std::cout << "Hello, world.\n"; }

    void display_number(int i) { std::cout << "number: " << i << '\n'; }

    int add_xy(int x, int y) { return data + x + y; }

    template<typename... Args>
    int add_many(Args... args) { return data + (args + ...); }

    auto add_them(auto... args) {               // C++20 required
        return data + (args + ...);
    }

    int data = 7;
};

int main()
{
    auto f = Foo{};

    auto greet = std::mem_fn(&Foo::display_greeting);
    greet(f);

    auto print_num = std::mem_fn(&Foo::display_number);
    print_num(f, 42);

    auto access_data = std::mem_fn(&Foo::data);
    std::cout << "data: " << access_data(f) << '\n';

    auto add_xy = std::mem_fn(&Foo::add_xy);
    std::cout << "add_xy: " << add_xy(f, 1, 2) << '\n';

    auto u = std::make_unique<Foo>();
    std::cout << "access_data(u): " << access_data(u) << '\n';
    std::cout << "add_xy(u, 1, 2): " << add_xy(u, 1, 2) << '\n';

    auto add_many = std::mem_fn(&Foo::add_many<short, int, long>);
    std::cout << "add_many(u, ...): " << add_many(u, 1, 2, 3) << '\n';

    auto add_them = std::mem_fn(&Foo::add_them<short, int, float, double>);
    std::cout << "add_them(u, ...): " << add_them(u, 5, 7, 10.0f, 13.0) << '\n';
}
