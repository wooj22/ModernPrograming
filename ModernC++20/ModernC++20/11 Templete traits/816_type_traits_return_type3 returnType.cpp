// ReturnType 예제
//http://ajwmain.iptime.org/programming/cpp/202012270/%EC%BB%B4%ED%8C%8C%EC%9D%BC%ED%83%80%EC%9E%84%EC%97%90_%ED%95%A8%EC%88%98%EC%9D%98_%EB%B0%98%ED%99%98_%ED%83%80%EC%9E%85%EC%9D%84_%EC%95%8C%EC%95%84%EB%82%B4%EB%8A%94_%EB%B0%A9%EB%B2%95.html

#define _MEMBER_CV(FUNC, REF_OPT, NOEXCEPT_OPT)\
FUNC(, REF_OPT, NOEXCEPT_OPT)\
FUNC(const, REF_OPT, NOEXCEPT_OPT)\
FUNC(volatile, REF_OPT, NOEXCEPT_OPT)\
FUNC(const volatile, REF_OPT, NOEXCEPT_OPT)

#define _MEMBER_CV_REF(FUNC, NOEXCEPT_OPT)\
_MEMBER_CV(FUNC, , NOEXCEPT_OPT)\
_MEMBER_CV(FUNC, &, NOEXCEPT_OPT)\
_MEMBER_CV(FUNC, &&, NOEXCEPT_OPT)

#define _MEMBER_CV_REF_NOEXCEPT(FUNC)\
_MEMBER_CV_REF(FUNC, )\
_MEMBER_CV_REF(FUNC, noexcept)

template <typename FuncType, typename... Args>
class ReturnType
{
    template <typename T>
    static T MakeT();

public:
    using Type = decltype(MakeT<FuncType>()(MakeT<Args>()...));
};

template <typename R, typename... Args>
class ReturnType<R(Args...), Args...>
{
public:
    using Type = R;
};

template <typename R, typename... Args>
class ReturnType<R(Args...) noexcept, Args...>
{
public:
    using Type = R;
};

#define _MEMFUNPTR(CV_OPT, REF_OPT, NOEXCEPT_OPT)\
template <typename R, typename C, typename... Args>\
class ReturnType<R(C::*)(Args...) CV_OPT REF_OPT NOEXCEPT_OPT, C, Args...>\
{\
public:\
    using Type = R;\
};

_MEMBER_CV_REF_NOEXCEPT(_MEMFUNPTR)
#undef _MEMFUNPTR

template <typename... T>
using ReturnType_t = typename ReturnType<T...>::Type;


//-----------------------------------------------------------------------------------

#include <iostream>
#include <functional>

// 함수 타입
using FuncType = char(int);

// 함수 포인터 타입
using FuncPtrType = char(*)(int);

// 함수 참조자 타입
using FuncRefType = char(&)(int);

// operator () 연산자를 오버로딩한 클래스
struct Less
{
    bool operator ()(int lhs, int rhs) const {
        return lhs < rhs;
    }
};

// 표준 함수자 클래스
using StdFunc = std::function<double(const int&, const char*)>;

// 람다
auto lambda = [](char&&, int&)->int { return 0; };

// 멤버 함수 포인터, 어떤 한정사가 와도 된다.
class SomeClass {};
using MemFuncPtrType = float(SomeClass::*)(void*) const&;


// 타입 출력 함수
template <typename T>
void PrintType() { std::cout << "Other type" << std::endl; }

template <>
void PrintType<bool>() { std::cout << "bool type" << std::endl; }

template <>
void PrintType<char>() { std::cout << "char type" << std::endl; }

template <>
void PrintType<int>() { std::cout << "int type" << std::endl; }

template <>
void PrintType<float>() { std::cout << "float type" << std::endl; }

template <>
void PrintType<double>() { std::cout << "double type" << std::endl; }


int main()
{
    // 함수 타입
    PrintType<ReturnType_t<FuncType, int>>();

    // 함수 포인터 타입
    PrintType<ReturnType_t<FuncPtrType, int>>();

    // 함수 참조 타입
    PrintType<ReturnType_t<FuncRefType, int>>();

    // operator () 연산자를 오버로딩한 클래스
    PrintType<ReturnType_t<Less, int, int>>();

    // 표준 함수자 클래스
    PrintType<ReturnType_t<StdFunc, const int&, const char*>>();

    // lambda
    PrintType<ReturnType_t<decltype(lambda), char&&, int&>>();

    // 멤버 함수 포인터
    PrintType<ReturnType_t<MemFuncPtrType, SomeClass, void*>>();

    return 0;
}
