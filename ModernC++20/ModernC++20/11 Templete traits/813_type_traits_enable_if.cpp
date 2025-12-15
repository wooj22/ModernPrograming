//enable_if 
//      enable_if 는 2개의 템플릿 인자 <bool _Test, typename _Type>를 받아,
//      _Test가 참인 경우 _Type에 대한 type aliasing을 제공하는 구조체이다.
// 
//      따라서, bool 형 조건이 false인 경우 아무런 타입을 제공하지 않음으로써, 컴파일 타임 에러를 유발할 수 있다.
/*
	template <bool _Test, typename _Ty = void>
	struct enable_if
	{
		// 기본적으로 _Ty에 대한 type aliasing을 제공하지 않는다.
	};
	// _Test가 true인 템플릿 부분 특수화 버전. 
	template <typename _Ty>
	struct enable_if<true, _Ty>
	{	
		using type = _Ty ;  // _Type에 대한 type aliasing을 제공한다.
	};
*/

#include <type_traits>
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
/// enable_if가 반환값으로 사용된 경우    
//      T가 float, doule, long double 인 경우 T 타입을 반환한다.
template <typename T>
typename enable_if_t<is_floating_point_v<T>, T>
foo1(T t)
{
    cout << "foo1: 실수형\n";
    return t;
}

// enable_if_t 는 C++11에서 지원하는 Aliasing template을 이용한 헬퍼!
//      typename enable_if<is_integral<T>::value, T>::type과 동일하다.
//      T가 정수형인 경우 T 타입을 반환한다
template <typename T>
enable_if_t<is_integral_v<T>, T>
foo1(T t)
{
    cout << "foo1: 정수형\n";
    return t;
}

//---------------------------------------------------------------------------
/// enable_if가 함수 인자로 사용된 경우
//      T가 정수형이 아닌 경우 컴파일 에러가 발생하며,
//      T가 만약 int 타입인 경우 아래 함수는 다음과 같다.
/*
        int foo2(int num, void* p = 0)
        {
            return num;
        }
*/
template <typename T>
T foo2(T t, typename enable_if_t<is_integral_v<T> >* = 0)   // 템플릿 2번째 인자를 생략함으로써, defalut인 void 타입이 된다.
{
    return t;
}

//---------------------------------------------------------------------------
// enable_if가 함수 템플릿 인자로 사용된 경우
//      enable_if의 템플릿 2번째 인자를 생략함으로써, defalut template parameter인 void 타입이 된다
template <typename T, typename = typename enable_if_t<is_integral_v<T> > >
T foo3(T t)
{
    return t;
}

//---------------------------------------------------------------------------
/// enable_if가 클래스 템플릿 인자로 사용된 경우

template <typename T, typename Enable = void>
class A; // undefined

// 템플릿 부분 특수화에 사용됨
// enable_if의 템플릿 2번째 인자를 생략함으로써, defalut template parameter인 void 타입이 된다
// 역시 실수형이 아니면 컴파일 에러
template <typename T>
class A<T, typename enable_if_t<is_floating_point_v<T> > >
{
};

int main()
{
    // OK, 정수형 foo1 호출
    foo1(10);

    // OK, 실수형 foo1 호출 // 만약, 실수형 foo1 함수가 정의되어 있지 않다면, 컴파일 에러
    foo1(1.2);

    // foo2는 정수형만 지원한다. // foo2(0.1)은 컴파일 에러
    foo2(7);

    // foo3도 정수형만 지원한다 // foo3(1.2);은 컴파일 에러
    foo3(34); // OK

    // A<int> a1; 컴파일 에러
    A<double> a1; // OK
}


//static_assert

//enable_if 를 이용하여, 해당 함수나 클래스의 메인 타입 T의 타입을 컴파일 타임에 한정 지을 수 있다.
//C++의 유사한 기능으로 static_assert를 이용하는 방법도 있다.
// 
//static_assert의 경우 컴파일 타임에 발생시킬 에러 메시지를 우리가 '지정'할 수 있지만,
//enable_if의 경우 "error C2079 'XXX'는 정의되지 않은 YYY을(를) 사용합니다"로 출력되는 차이점은 있다.

// 함수 signature에서 제한하려는 타입에 대해 바로 알 수 있음
template <typename T>
typename enable_if_t<is_floating_point_v<T>, T>
foo1(T t)
{
    cout << "foo1: 실수형\n";
    return t;
}

// 제한하려는 특징이 signature에 드러나지 않고, body를 살펴 보아야만 알 수 있다.
template <typename T>
T foo1(T t)
{
    static_assert(is_floating_point_v<T>);

    cout << "foo1: 실수형2\n";
    return t;
}
