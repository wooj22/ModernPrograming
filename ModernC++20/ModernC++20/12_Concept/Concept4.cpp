//C++20 표준에서 상당히 많은 컨셉들 이미 제공하고 있다 ***
//https://en.cppreference.com/w/cpp/concepts
// 
// std::integral<T>                  //정수 형식(char, short, int, long, unsigned 형식)
// std::floating_point<T>	         //부동 소수점 형식(float, double, long double)
// std::same_as<T, U>                //두 형식이 같은지 체크
// std::derived_from<T, U>           //첫번째 인자가 두번째 인자의 파생 형식인지 체크
// std::convertible_to<T, U>         //첫번째 인자가 두번째 인자로 변환이 가능하지 체크
// std::moveable<T>                  //이동 가능 여부
// std::copyable<T>                  //복사 가능 여부
// std::invocable<F, ...Args>	     //std::invoke를 호출 할 수 있는지 여부
// std::equality_comparable<T>	     //객체 상등 비교 가능 여부
// std::three_way_comparable<T, U>   //<=>연산자
// std::random_access_iterator<It>	 //임의 접근 반복자
// std::sortable<It>	             //요소들의 순서를 변경해서 정렬된 순차열을 만들 수 있음

 
//integral<T> -----------------------------------------------------------------

#include <concepts>
#include <iostream>

void print(std::integral auto i) {                      //약식 함수 템플릿 사용 // auto //C++20
    std::cout << "Integral: " << i << '\n';
}

void print(auto x) {
    std::cout << "Non-integral: " << x << '\n';
}

int main()
{
    std::cout << std::boolalpha;

    print(true); static_assert(std::integral<bool>);
    print('o'); static_assert(std::integral<char>);
    print(007); static_assert(std::integral<int>);

    print(2e2); static_assert(!std::integral<float>);
    print("∫∫∫"); static_assert(!std::integral<decltype("")>);
}

//std::same_as<T,T> -------------------------------------------------

#include <concepts>
#include <iostream>

template<typename T, typename ... U>
concept IsAnyOf = (std::same_as<T, U> || ...);      //같은 타입인지 구별

template<typename T>
concept IsPrintable = 
    std::integral<T> || 
    std::floating_point<T> ||
    IsAnyOf<std::remove_cvref_t<std::remove_pointer_t<std::decay_t<T>>>, char, wchar_t>;

void println(IsPrintable auto const ... arguments)
{
    (std::wcout << ... << arguments) << '\n';
}

int main() {
    println("Example: ", 3.14, " : ", 42, " : [", 'a', L'-', L"Z]");
}


//std::derived_from<T,T> -------------------------------------------------

#include <concepts>

class A {};

class B : public A {};

class C : private A {};

int main()
{
    // std::derived_from == true only for public inheritance or exact same class
    static_assert(std::derived_from<B, B> == true);      // same class: true
    static_assert(std::derived_from<int, int> == false); // same primitive type: false
    static_assert(std::derived_from<B, A> == true);      // public inheritance: true
    static_assert(std::derived_from<C, A> == false);     // private inheritance: false  ***

    // std::is_base_of == true also for private inheritance
    static_assert(std::is_base_of_v<B, B> == true);      // same class: true
    static_assert(std::is_base_of_v<int, int> == false); // same primitive type: false
    static_assert(std::is_base_of_v<A, B> == true);      // public inheritance: true
    static_assert(std::is_base_of_v<A, C> == true);      // private inheritance: true  
}

