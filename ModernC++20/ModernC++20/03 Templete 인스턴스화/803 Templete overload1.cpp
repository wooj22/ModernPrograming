//함수 오버로드
//      일반함수 처럼 함수 템플릿도 오버로딩 할 수 있다.

#include <iostream>
#include <typeinfo>
using namespace std;

//일반함수
inline int const& func(int const& a, int const& b)
{
    cout << "int const& func (int const& a, int const& b)" << endl;
    return a;
}
//함수 템플릿
template <typename T>
inline T const& func(T const& a, T const& b)
{
    cout << "template <typename T> T const& func (T const& a, T const& b)" << endl;
    cout << "T is " << typeid(T).name() << endl;
    return a;
}

//3개 인자 받는 함수 템플릿
template <typename T>
inline T const& func(T const& a, T const& b, T const& c)
{
    cout << "template <typename T> T const& func (T const& a, T const& b, T const& c)" << endl;
    cout << "T is " << typeid(T).name() << endl;
    return ::func(::func(a, b), c);
}

int main()
{
    func(7, 42, 68); cout << endl;        // 3개 인자 받는 템플릿 호출

    func(7.0, 42.0); cout << endl;        // func<double> 호출 인자추론(argument deduction)

    func('a', 'b'); cout << endl;         // func<char> 호출 인자추론

    func(7, 42); cout << endl;            // 일반함수 호출

    func<>(7, 42); cout << endl;          // func<int> 인자추론

    func<double>(7, 42); cout << endl;    // func<double> 명시 호출

    func('a', 42.7); cout << endl;        // 일반함수 호출  //암시적 형변환
}

//템플릿이 더 잘 맞는 함수를 생성할 경우에는 템플릿을 선택합니다. ***
// 
//동일할 경우는 
//템플릿이 아닌, 일반함수가 템플릿으로 만들어진 함수보다 더 우선순위가 높습니다 ***

//템플릿에서는 일반함수와 달리 자동으로 데이터형 변환하지 않는다. ***
