
//concept 절(clause)
//		template < template-parameter-list > 
//		concept concept-name = constant-expression;

//constraint - expression은 다음 중 하나입니다.
//		기존 concept나 컴파일 시점 술어의 논리 조합
// 
//		논리 조합에는 논리 연산자(&&, || , !) 을 사용할 수 있습니다.
//		컴파일 시점의 술어는 컴파일 시점에 bool 값을 돌려주는 호출 가능 객체 입니다.

//concept 절의 다양한 사용법들 -----------------------------------------------------------

#include <iostream>
#include <concepts>
using namespace std;

// Integral은 is_integral_v 컴파일 술어를 사용해서 정의합니다.
template <class _Ty>
concept Integral = is_integral_v<_Ty>;

// Signed_Integral는 콘셉트인 Integral을 사용해서 정의합니다. 
// static_cast<_Ty>(-1) < static_cast<_Ty>(0) 컴파일 술어를 사용
template <class _Ty>
concept Signed_Integral = Integral<_Ty> && static_cast<_Ty>(-1) < static_cast<_Ty>(0);

// Unsigned_Integral은 콘셉트인 Integral, Signed_Integral을 사용해서 정의합니다.
template <class _Ty>
concept Unsigned_Integral = Integral<_Ty> && !Signed_Integral<_Ty>;



//requires 절(clause)
//		템플릿 함수에서 제약 조건을 참조 할 때 사용 ***
//		템플릿 인자가 가져야 하는 제약 조건(concept, traits 등)을 기술하는 문법
//		컴파일 타임에 결정되는 bool 타입의 상수 값만을 사용 할 수 있다.

//requires 절의 다양한 사용법들 -----------------------------------------------------------

#include <iostream>
#include <concepts>
using namespace std;

template <class T> requires true  // 의미는 없지만 이렇게 적어도 된다!!
void foo(T a) {
}

template <class T> requires false // 무조건 fasle를 리턴하기 때문에 이 함수는 사용 할 수 없다
void foo(T t) {
}

template <class T> requires std::is_pointer_v<T> // type trait를 바로 사용 할 수 있다
void foo(T t) {
}

template <class T> requires 1	// ERROR!!. int를 사용 할 수는 없다
void foo(T t) {
}

bool check_error() { return true; }

template <class T> requires (check_error()) // ERROR!!. 상수식이 아니라 Error
void foo(T t)
{
}

constexpr bool check_ok() { return true; }

template <class T> requires (check_ok()) // constexpr로 컴파일 타임에 평가 되기 때문에 OK
void foo(T t)
{
}

template <class T> requires (sizeof(T) > 4) // 상수표현식을 바로 사용하는 것도 OK
void foo(T t)
{
}

template <class T> concept GreaterThan4 = sizeof(T) >= 4;
template <class T> requires GreaterThan4<T> // concept를 사용하는 것도 OK
void foo(T t)
{
}


//requires expression (requires 표현식)  ----------------------------------------------------
// 
//		컨셉에서 제약조건(요구사항) 을 정의 할 때 사용 ***
// 
//		requires { requirement-seq; };						// 인자 없이 제약조건 만을 적을 수 있다.
//		requires ( prameter-list ) { requirement-seq; }; 	// 인자를 이용한 제약조건도 가능하다.// 
//		여러개의 제약 조건을 묶어 하나의 이름으로 사용가능, 복잡한 제약 조건 사용 가능


template <class T>
concept HasValueType = requires				//아무런 인자 없이 T 라는 타입에 value_type이 있는지만 검사
{
	typename T::value_type;					//{ requirement-seq }
};

template <class T>
concept Comparable1 = requires(T a, T b)	//표현식에서 인자를 사용할 때  ( prameter-list )
{
	​​​​a < b;									//{ requirement-seq }
};

//여러개의 제약 조건 예시						//{ requirement-seq } -> return-type-requirement(optional);

#include <concepts>

template <class T>
concept Comparable2 = requires(T a, T b)
{
	{ a < b } -> std::convertible_to<bool>;
};
//템플릿 파라메터의 타입이 '<' 연산이 가능하고, 그 결과 값의 타입이 bool 타입으로 변환이 가능해야 한다
//bool 타입 캐스팅 같은 것은 사용 할 수 없다.

template <class T>
concept Equality = requires(T a, T b)
{
	{ a == b } -> std::convertible_to<bool>;
	{ a != b } -> std::convertible_to<bool>;
};
//템플릿 타입 a, b는 '==' 오퍼레이션과 '!=' 오퍼레이션을 지원 해야하고, 둘다 bool 타입을 리턴해야만 참이 된다.

template <class T>
concept Container = requires(T t)
{
	t.begin();
	t.end();
};
//타입 T 객체의 begin()과 end()함수를 호출 할 수 있어야 한다는 뜻


//---------------------------------------------------------------------------------------
//requires 절 없이도 컨셉을 사용 할 수 있다.
//		concept은 bool 값을 리턴하는 메타 타입으로 사용가능하다. ***

#include <iostream>
#include <type_traits>
#include <concepts>
using namespace std;

template <class T>
concept Integeral =  std::is_integral_v<T>;

int main()
{
	bool result = Integeral<int>; // 컴파일 타임에 결정 된다!!
}


/*
요구 조건 표현식 종류 -  
        단순 요구 조건, 형식 요구 조건, 복합 요구 조건, 중첩 요구 조건

//단순 요구 조건
//아래 예제와 같이 괄호에 묶여서 선언되어 사용됩니다.

    // Addable는 T타입에 대해서 a + b 표현식이 유효해야 합니다.
    template<typename T>
    concept Addable = requires(T a, T b) {
        a + b;
    };

    // Subtractable는 T타입에 대해서  a - b 표현식이 유효해야 합니다.
    template<typename T>
    concept Subtractable = requires(T a, T b) {
        a - b;
    };

    // Swappable은 T, U가 swap 표현식을 만족 해야 합니다.
    template<typename T, typename U = T>
    concept Swappable = requires(T&& t, U&& u)
    {
        swap(std::forward<T>(t), std::forward<U>(u));
        swap(std::forward<U>(u), std::forward<T>(t));
    };


//형식 요구 조건
//형식 요구 조건을 표현 할 때는 typename과 형식 이름을 사용합니다.

    template<typename T>
    using Ref = T&;

    template<typename T>
    concept RequirementType = requires {
        // T가 key_type을 가져야 합니다.
        typename T::key_type;
        typename T::allocator_type;
        // Ref를 T로 인스턴스화 할 수 있어야 합니다.
        typename Ref<T>;
    };

    auto printValueType(RequirementType auto a) {
        cout << typeid(a).name() << endl;
    }

    int main()
    {
        // printValueType(std::vector<int>{1, 2, 3});  // 관련 제약 조건이 충족되지 않습니다
        printValueType(std::map<int, int>{ {1, 2}, { 2, 3 }, { 3, 4 } });
    }


//복합 요구 조건
//복합 요구 조건이 단순 요구 조건가 다른 점은
//      퓨현식에 {}(중괄호)를 감싸야 합니다.
//      noexcept 지정자와 반환 형식 요구조건을 추가로 붙일 수 있습니다.

// 복합 요구 조건은 다음의 형식을 만족해야 합니다.
//      { expression } noexcept(optional) return-type-requirement(optional) ;


    template<typename T>
    concept C2 = requires(T x)
    {
        // *x라는 표현식이 유효해야 합니다
        // T::inner라는 타입도 유효 해야 합니다.
        // *x의 결과는 T::inner로 변환 가능해야합니다.
        {*x} -> std::convertible_to<typename T::inner>;

        // x + 1라는 표현식이 유효 해야 하며 그 결과가 int형식이어야 합니다.
        {x + 1} -> std::same_as<int>;
    };

//중첩 요구 조건
//중첩 요구 조건은 requires안에 requires로 시작하는 표현식이 있는 것을 말합니다.

    template<class T>
    concept Semiregular = DefaultConstructible<T> &&
        CopyConstructible<T> && Destructible<T> && CopyAssignable<T> &&
    requires(T a, size_t n)
    {
        requires Same<T*, decltype(&a)>; // 중첩 요구 조건
        requires Same<T*, decltype(new T)>; // 중첩 요구 조건
        requires Same<T*, decltype(new T[n])>; // 중첩 요구 조건
        { a.~T() } noexcept; // 복합 요구 조건
        { delete new T }; // 복합 요구 조건
        { delete new T[n] }; // 복합 요구 조건
    };

*/
