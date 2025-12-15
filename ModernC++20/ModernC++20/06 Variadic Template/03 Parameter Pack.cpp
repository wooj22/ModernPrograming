//https://en.cppreference.com/w/cpp/language/parameter_pack

//함수 매개 변수 팩은 
//	    0 개 이상의 함수 인수를 허용하는 함수 매개 변수입니다.
//템플릿 매개 변수 팩은 
//	    0 개 이상의 템플릿 인수(유형, 비 유형 또는 템플릿)를 허용하는 템플릿 매개 변수입니다.

#include <iostream>

template<class... Types> void f(Types... args);     //variadic 함수 템플릿

template<class... Types> struct Tuple {};		    //variadic 클래스 템플릿

int main() {

	f();				    // OK : args에는 인수가 없습니다.
	f(1);				    // OK : args에는 하나의 인수가 포함됩니다. int
	f(2, 1.0);			    // OK : args에는 int와 double의 두 가지 인수가 있습니다.

    Tuple<> t0;             // 유형에는 인수가 없습니다.
	Tuple<int> t1;          // 유형에는 하나의 인수가 포함됩니다. int
	Tuple<int, float> t2;   // 유형에는 두 개의 인수가 포함됩니다 : int 및 float
	Tuple<0> error;         // 오류 : 0은 유형이 아닙니다.
}


//기본 '클래스 템플릿'에서 템플릿 매개 변수 팩은 
//      템플릿 매개 변수 목록의 마지막 매개 변수여야 합니다. ***
//
//      '함수 템플릿'에서 템플릿 매개 변수 팩은 함수 인수에서 추론되거나, 
//      기본 인수가 있는 경우 목록의 앞부분에 나타날 수 있습니다.

#include <iostream>

template<typename... Ts, typename U> struct Invalid;    // 오류 : Ts 마지막 매개 변수 아님

template<typename... Ts, typename U, typename = void>
void valid(U, Ts...);		    // OK : U를 추론 할 수 있습니다.
//void valid (Ts ..., U);	    // 사용할 수 없음 : Ts ...이 위치에서 추론되지 않은 컨텍스트입니다.

int main() {

	valid(1.0, 1, 2, 3);	    // OK : U를 double로, Ts를 {int, int, int}로 추론합니다.
	return 0;
}


//팩 확장 ( Pack Expansion ) -------------------------------------------------------------------
//
//  하나 이상의 매개 변수 팩 이름이 한 번 이상 나타나는 패턴 뒤에 줄임표 ( 패턴... )
//  패턴은 패턴의 0개 이상의 쉼표로 구분된 인스턴스화로 확장된다.       ( a1, a2, a3 ... ) 


template<class... Us> void f(Us... pargs) { }

template<class... Ts> void g(Ts... args) {
    f(&args...);            // "&args..."는 팩 확장입니다. // "&args"는 패턴입니다.
}

int main() {
    g(1, 0.2, "a");

    // Ts ... args는     int E1, double E2, const char * E3로 확장됩니다.     
    // &args...는        &E1, &E2, &E3으로 확장됩니다.             
    // Us... pargs는     int* E1, double* E2, const char** E3로 확장됩니다.
}


//두 매개 변수 팩의 '이름이 동일한 패턴'으로 표시되면, 
//      동시에 확장되며 길이가 같아야 합니다.

template<typename...> struct Tuple {};
template<typename T1, typename T2> struct Pair {};

template<class ...Args1> struct zip {
    template<class ...Args2> struct with {
        typedef Tuple<Pair<Args1, Args2>...> type;
        // Pair <Args1, Args2> ...는 팩 확장입니다.
        // Pair <Args1, Args2>는 패턴입니다.
    };
};

typedef zip<short, int>::with<unsigned short, unsigned>::type T1;
// Pair <Args1, Args2> ...는 다음으로 확장됩니다.
// Pair<short, unsigned short>, Pair<int, unsigned int>
// T1은 Tuple <Pair <short, unsigned short>, Pair <int, unsigned >>입니다.

typedef zip<short>::with<unsigned short, unsigned>::type T2;
// 오류 : 팩 확장에 길이가 다른 매개 변수 팩이 포함됨


//팩 확장이 다른 팩 확장 내에 중첩 된 경우 
//      가장 안쪽에 있는 팩 확장 안에 나타나는 매개변수 팩이 확장되며, 
//      포함하는 팩 확장에는 언급된 다른 팩이 있어야 하지만 가장 안쪽에 있는 팩에는 언급되지 않습니다.

template<class ...Args>
void g(Args... args) 
{

    f( const_cast<const Args*>(&args)... );

    // const_cast <const Args *> (& args)는 패턴이며 두 팩을 확장합니다.
    // (Args 및 args) 동시에 확장

    f( h(args...) + args... );      // 중첩 팩 확장 :

    // 내부 팩 확장은 "args ..." 이며 먼저 확장됩니다.
    // 외부 팩 확장은 h (E1, E2, E3) + args ..., 확장됩니다.
    // (h (E1, E2, E3) + E1, h (E1, E2, E3) + E2, h (E1, E2, E3) + E3)
}


//확장 위치 ------------------------------------------------------------------------------------
//      확장이 발생하는 위치에 따라 쉼표로 구분 된 결과 목록은 
//      함수 매개 변수 목록, 멤버 이니셜 라이저 목록, 속성 목록 등 다른 유형의 목록입니다.
// 
//      다음은 허용되는 모든 컨텍스트 목록입니다.

//함수 인수 목록
//      팩 확장은 함수 호출 연산자의 괄호 안에 나타날 수 있으며, 
//      이 경우 줄임표 왼쪽의 가장 큰 표현식 또는 braced-init-list(중괄호 초기화)가 확장된 패턴입니다.

f(&args...);                // f (&E1, &E2, &E3)로 확장
f(n, ++args...);            // f (n, ++E1, ++E2, ++E3);
f(++args..., n);            // f (++E1, ++E2, ++E3, n);
f(const_cast<const Args*>(&args)...);// f(const_cast<const E1*>(&X1), const_cast<const E2*>(&X2), const_cast<const E3*>(&X3))
f(h(args...) + args...);    // f(h(E1,E2,E3) + E1, h(E1,E2,E3) + E2, h(E1,E2,E3) + E3)

//공식적으로 함수 호출 표현식의 표현식 목록 은 initializer-list 로 분류되고 
//패턴은 initializer-clause 이며 이는 할당 표현식 또는 중괄호 초기화 목록 입니다.


//괄호로 묶인 초기화
//      팩 확장은 직접 초기화 프로그램, 함수 스타일 캐스트 및 
//      기타 컨텍스트(멤버 초기화 프로그램, new-expression 등) 의 괄호 안에 표시 될 수 있으며, 
//      이 경우 규칙은 위의 함수 호출 표현식에 대한 규칙과 동일합니다.

Class c1(&args...);                             // Class::Class (&E1, &E2, &E3) 호출
Class c2 = Class(n, ++args...);                 // 호출 Class::Class (n, ++E1, ++E2, ++E3);
::new((void*)p) U(std::forward<Args>(args)...)  // std::allocator::allocate


//중괄호로 묶인 초기화 
//      braced-init-list (괄호로 묶은 이니셜 라이저 및 기타 braced-init-lists목록) 안에 
//      팩 확장이 나타날 수 있습니다.

template<typename... Ts> void func(Ts... args) {
    const int size = sizeof...(args) + 2;
    int res[size] = { 1,args...,2 };
    // 이니셜 라이저 목록은 시퀀싱을 보장하므로 다음과 같은 용도로 사용할 수 있습니다.
    // 팩의 각 요소에 대해 순서대로 함수를 호출합니다.
    int dummy[sizeof...(Ts)] = { (std::cout << args, 0)... };
}


//템플릿 인수 목록
//      템플릿에 확장과 일치하는 매개 변수가 있는 경우 
//      팩 확장은 템플릿 인수 목록의 어느 곳에서나 사용할 수 있습니다.

template<class A, class B, class...C> void func(A arg1, B arg2, C...arg3)
{
    container<A, B, C...> t1;  // expands to container<A,B,E1,E2,E3> 
    container<C..., A, B> t2;  // expands to container<E1,E2,E3,A,B> 
    container<A, C..., B> t3;  // expands to container<A,E1,E2,E3,B> 
}


//함수 파라미터 목록
//      함수 매개 변수 목록에서 생략 부호가 매개 변수 선언에 나타나는 경우
//      매개 변수 선언은 패턴입니다.

template<typename ...Ts> void f(Ts...) {}

f('a', 1);          // Ts ... void f (char, int) 로 확장
f(0.1);             // Ts ... void f (double)로 확장

template<typename ...Ts, int... N> void g(Ts(&...arr)[N]) {}   //배열 참조

int n[1];
g<const char, int>("a", n); // Ts (& ... arr) [N] 확장  // const char (&)[2], int(&)[1]
                             
    //참고: 패턴 Ts(&...arr)[N] 에서 줄임표는 다른 모든 팩 확장에서와 같이 마지막 요소가 아닌 가장 안쪽 요소입니다.
    //참고 : C++ 11 문법에서는 괄호로 묶은 줄임표에 이름  Ts(&...)[N] 은 사용할 수 없습니다 .


//템플릿 파라미터 목록
//      팩 확장은 템플릿 매개 변수 목록에 나타날 수 있습니다.

template<typename... T> struct value_holder
{
    template<T... Values>   // 유형이 아닌 템플릿 매개 변수로 확장
    struct apply { };       // <int, char, int(&)[5]>와 같은 목록
};


//기본 지정자와 멤버 이니셜 라이저 목록
//      팩 확장은 클래스 선언 에서 기본 클래스 목록을 지정할 수 있습니다.
//      일반적으로 이는 생성자가 멤버 초기화 목록 에서 팩 확장을 사용하여 
//      이러한 기본의 생성자를 호출 해야 함을 의미합니다 .

template<class... Mixins>
class X : public Mixins...      //기본 클래스 목록
{
public:
    X(const Mixins&... mixins) : Mixins(mixins)... { }  //생성자 호출
};


//람다 캡처
//      람다 식 의 캡처 절에 매개 변수 팩이 나타날 수 있습니다 .

template<class ...Args>
void f(Args... args) {
    auto lm = [&, args...]{ return g(args...); };
    lm();
}


//sizeof... 연산자
//      sizeof... 연산자뿐만 아니라 팩 확장으로 분류됩니다.

template<class... Types>
struct count {
    static const std::size_t value = sizeof...(Types);
};


//동적 예외 사양(C++ 17)
//      동적 예외 사양 의 예외 목록은 팩 확장 일 수도 있습니다.

template<class...X> void func(int arg) throw(X...)
{
    // ... 다른 상황에서 다른 X를 던진다.
}

//정렬 지정자
//      팩 확장은 alignas 키워드에 사용되는 유형 목록과 표현식 목록 모두에서 허용됩니다 .

//속성 목록
//      팩 확장은 [[attributes...]] 에서와 같이 속성 목록에서 허용됩니다.예를 들면 다음과 같습니다. 
void [[attributes...]] function()

//Fold-expressions(C++ 17)
//      fold-expressions 에서 패턴은 확장되지 않은 매개변수 팩을 포함하지 않는 전체 하위 표현식입니다.

//Using-declarations
//      에서 선언자 목록에 줄임표가 나타날 수 있습니다 . 이는 매개변수 팩에서 파생할 때 유용합니다.

template <typename... bases>
struct X : bases... {
    using bases::g...;
};
X<B, D> x;      // OK : B::g 및 D::g 도입




//Example -------------------------------------------------------------------

#include <iostream>

void tprintf(const char* format) // 기본 함수
{
    std::cout << format;
}

template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... Fargs) // 재귀 가변 함수
{
    for (; *format != '\0'; format++) {
        if (*format == '%') {
            std::cout << value;
            tprintf(format + 1, Fargs...);  // 재귀 호출
            return;
        }
        std::cout << *format;
    }
}

int main()
{
    tprintf("% world% %\n", "Hello", '!', 123);  // 예상 출력은 ?      

    return 0;
}

//Output:
//Hello world!123    // % 위치에 각 인수가 들어감


//위의 예제는 std::printf 와 유사한 함수를 정의 하여 형식 문자열에서 각 문자 % 를 값으로 바꿉니다.
//형식 문자열 만 전달되고 매개 변수 확장이 없는 경우 첫 번째 과부하가 호출됩니다.
//두 번째 오버로드에는 인수 헤드와 매개 변수 팩에 대한 별도의 템플릿 매개 변수가 포함되어 있으므로 
//재귀 호출이 비워 질 때까지 매개 변수의 꼬리만 전달할 수 있습니다.
//Targs 는 템플릿 매개 변수 팩이고 Fargs 는 함수 매개 변수 팩입니다.