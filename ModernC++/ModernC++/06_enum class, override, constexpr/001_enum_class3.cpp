//범위 없는 enum 이 유용한 상황도 있다.

#include <iostream>
#include <vector>
using namespace std;

//  튜플 지정할 때

/*
    // 튜플 사용법
    tuple<int, double> my_tp = make_tuple(1, 1.2);
    auto v1 = std::get<0>(my_tp);
    auto v2 = std::get<1>(my_tp);

    auto[a,b] = make_tuple(2, 0.5); //C++17
    cout << a << " " <<  b << endl;
*/

using UserInfo = std::tuple<std::string, std::string, std::size_t>;

enum UserInfoFields { uiName, uiEmail, uiReputation };


int main()
{
    UserInfo uInfo;

    auto val = std::get<1>(uInfo);
    auto va2 = std::get<uiEmail>(uInfo);        // 위치 지정

    // 범위 있는 enum 버전은 훨씬 장황하다.

    enum class UserInfoFields { uiName, uiEmail, uiReputation };
    auto va3 = std::get<static_cast<std::size_t>(UserInfoFields::uiEmail)>(uInfo); //

    return 0;
}

/*
    // 템플릿을 활용하면 조금 편리하게 사용 가능.
    template <typename E>                                           // C++14
    constexpr auto toUType(E enumerator) noexcept                   // toUType 정의
    {
        return static_cast<std::underlying_type_t<E>>(enumerator);
    }

    auto va4 = std::get<toUType(UserInfoFields::uiEmail)>(uInfo);   // toUType 사용

*/

//std::underlying_type_t 을 사용하면 열거자의 타입에 맞는 값을 반환한다.
// 
//  Enum 이라는 enum class : char 객체 E = 'C' 가 있을 때,
//  std::underlying_type_t<Enum>(E) ; 의 값은 'C' 이다. 

enum class Enum : char
{
    D = 'A',
    E = 'C'
};

int main()
{
    Enum E = Enum::E;

    std::cout << std::underlying_type_t<Enum>(E);
}
