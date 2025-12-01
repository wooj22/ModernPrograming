//변수 템플릿

#include <iostream>
using namespace std;

const double pi = double(3.141592);     //변수

template<typename T>                    //변수 템플릿 ***
constexpr T pi = T(3.1415926535897932385);

int main(void)
{
    cout << pi<int> << endl;			//템플릿 변수 
}


//변수를 다양한 타입으로 사용하기. (변수 템플릿, Variable template ))

#include <iostream>
using namespace std;

template<typename T = long double>      //기본값
constexpr T pi = T(3.1415926535897932385);

template<>                              //특수화
constexpr char const* pi<char const*> = "PI";

int main(void)
{
    cout << pi<int> << endl;			

    cout << pi<> << endl;;              //

    cout << pi<char const*> << endl;    //

    return 0;
}


//namespace 범위에서 사용 가능
//A variable template may be introduced by a template declaration at namespace scope

template<class T>
constexpr T pi = T(3.1415926535897932385L); // variable template

template<class T>
T circular_area(T r)                        // function template
{
    return pi<T> * r * r;                   // pi<T>  변수 템플릿 인스턴스화 ***
}


//클래스에서는 static 으로 사용한다. ***
//When used at class scope, variable template declares a static data member template.

#include <array> 
using namespace std;
using namespace std::literals;

struct vector_constants
{
    template<class T>
    using vec = array<T, 3>;   // alias template

    template<class T>          // static data member template  //클래스에서 static 으로 사용 
    static constexpr vec<T> zero = { 0,0,0 };

    template<class T>
    static constexpr vec<T> one = { 1,1,1 };
};

int main() {
    vector_constants::vec<int> ar = { 1,2,3 };
    //array<int, 3> ar = { 1,2,3 };

    cout << vector_constants::one<int>[0];
}

//변수 템플릿 특수화 ----------------------------------------

template <typename T>
class MyClass {
public:
    template <typename U>
    static constexpr U value = U(42);
    // 특수화
    template <>
    static constexpr int value<int> = 99;
};

int main() {
    std::cout << MyClass<int>::value<double> << '\n'; // 42.0 출력
    std::cout << MyClass<int>::value<int> << '\n';    // 99 출력
    return 0;
}