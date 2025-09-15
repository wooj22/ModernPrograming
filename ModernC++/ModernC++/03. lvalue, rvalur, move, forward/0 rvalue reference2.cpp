// const && 
//      rvalue를 const로 제한한 타입 
//      수정 불가능한 임시 객체에 대한 참조
//      
//      특정 상황에서만 드물게 사용, 보통 이동을 막기 위한 제약 수단 
//      - 주로 라이브러리 내부의 방어적 코드, 오버로딩 구분, API 오용 방지 목적으로 사용

#include <iostream>
#include <string>
#include <utility>
using namespace std;

class A {};

void foo(A& a) { cout << "&" << endl; }
void foo(A&& a) { cout << "&&" << endl; }
void foo(const A& a) { cout << "const &" << endl; }
//void foo(const A&& a) { cout << "const &&" << endl; }

int main()
{
    A o;
    foo(o);
    foo(A());

    const A co;
    foo(co);
    foo(move(co));  //
}

------------------------------------------------------------------------------
//참조 한정자

#include <iostream>
#include <string>
#include <utility>
using namespace std;

struct A {
    std::string abc = "abc";
    std::string& get()& { std::cout << "&" << std::endl; return abc; }
    std::string get()&& { std::cout << "&&" << std::endl; return std::move(abc); }
    std::string const& get() const& { std::cout << "const &" << std::endl; return abc; }
    std::string get() const&& { std::cout << "const &&" << std::endl; return abc; }
};

int main()
{
    A a1; a1.get();
    const A a2{}; a2.get();
    A().get();
    const A a3{}; std::move(a3).get();
}

//쓰이는 예시 ------------------------------------------------------------

//표준 라이브러리는 const T&& 를
//몇 가지 경우에 rvalue 참조 오버로드를 삭제된 것으로 선언하는 데 사용합니다.

template <class T> void as_const(const T&&) = delete;
template <class T> void ref(const T&&) = delete;
template <class T> void cref(const T&&) = delete;
//const 를 사용해서, 보편적인 참조가 되는 것을 방지합니다.

//또한 래핑된 값에 액세스할 때 래퍼(예: std::optional)의 반환 유형으로 사용되므로 
//값 범주가 *this유지됩니다. const T를 이동시키는 경우.
constexpr const T&& operator*() const&&;
constexpr const T&& value() const&&;

//std::tuple, std::variant 등에서 std::get 을 통해 액세스됩니다 
template <class T, class... Types>
constexpr const T&& get(const std::variant<Types...>&& v);
template< class T, class... Types >
constexpr const T&& get(const tuple<Types...>&& t) noException;
