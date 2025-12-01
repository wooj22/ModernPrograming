//Attributes
//    C++에서 Attributes는 코드의 특정 요소(함수, 클래스, 변수 등)에 대해 추가적인 메타데이터를 제공하여, 
//    컴파일러나 런타임에게 특정 동작이나 최적화 힌트를 전달하는 역할을 합니다.
//
//    [[attribute-name]] 형태로 선언
 
//사용 가능한 상황
// 
//    1. 클래스 또는 구조체
    struct [[deprecated("This struct is outdated")]] OldStruct { int a; };
//    2. 함수
    [[nodiscard]] int getValue() { return 42; }
//    3. 변수
    [[maybe_unused]] int unusedVariable = 10;

//Standard attributes
http://en.cppreference.com/w/cpp/language/attributes
http://egloos.zum.com/sweeper/v/3201377

/*
C++11부터 타입, 오브젝트, 각종 코드들(함수, 코드블럭 등등)에 대하여 
컴파일러에게 여러 힌트를 줄 수 있는 attribute가 정식 도입되었다.

    일종의 메타데이터인 힌트들로부터 
    컴파일러는 코드 흐름 제어의 변경, 컴파일 경고를 제공하거나 제거하는 등등의 ***
    특정한 동작들을 수행할 수 있게 된다.

Standard attribute의 전형적인 syntax는 다음과 같다.
(C#의 attributes와 다르게 [[ ... ]] 로 브라켓을 2개씩 써야함을 혼동하지 말아야 한다)

    // C++11부터...
    // attribute argument-list는 comma seperate 형태로 늘어 쓸 수 있다.
    [[ attribute argument-list ]]

    // C++17부터...
    // namespace와 attribute argument-list를 같이 쓸 수 있는 형태
    // ex) [[using CC: opt(1), debug]] 이는 [[CC::opt(1), CC::debug]]와 동일하다.
    [[ using attribute-namespace : attribute argument-list ]]

*/

//1. [[noreturn]] - C++11
// 
//  이 attribute는 컴파일러에게 코드 control flow 에서 caller 에게 돌아가지 않음을 의미
//  noreturn 함수 호출 이후의 하위 코드들은 실행되지 않기에 컴파일러는 코드를 날려버릴 수 있다.
//
//  함수가 결코 반환하지 않는 것을 표시하는 속성
//  예외 송출이나 std::exit, std::abort 의 랩퍼 함수에 붙인다.
//  이것에 의해 함수가 반환하지 않는 패스가 있는 경우의 경고를 억제한다.

#include <iostream>

[[noreturn]] void f()
{
    // blah...blah...blah
}

void g()
{
    f();

    // f() 수행이후 caller에게 흐름이 넘어오지 않으므로, 하위 코드들은 모두 dead-code
    // unreachable:
    // 따라서, 컴파일러는 이를 생성해 내지 않는다.    
    std::cout << "No! That's impossible" << std::endl;
}

// noreturn 예시

#include <iostream>

[[noreturn]] void exit()
{
    std::exit(0);
}

int func(int x)
{
    if (x > 0) {
        return x;
    }
    exit();     // if에 들어가지 않는 경우 return이 없지만 //이 함수는 반환하지 않는다.
}

int main()
{
    //'func': 모든 제어 경로에서 값을 반환하지는 않습니다.
}


//2. [[carries_dependency]] 속성   // C++11
//
//  함수, 함수 파라메터
//  병렬 프로그래밍의 atomic 조작에 있어서 
//  값에 의존하는 순서를 함수 전반에 전파하는 것을 나타내는 속성이다.
//  값 의존성을 명시적으로 표시하여 CPU / 컴파일러 최적화가 안전하게 수행되도록 돕는 속성.

#include <iostream>
#include <thread>

struct Foo {
    int num = 0;
};

std::atomic<Foo*> x(nullptr);

[[carries_dependency]] Foo* is_load() {
    return x.load(std::memory_order_consume);
}

int main()
{
    std::thread th([]() {
        x.store(new Foo{ 100 }, std::memory_order_release);
        });

    Foo* foo = is_load();
    if (foo) { std::cout << foo->num; }
    th.join();

    return 0;
}


//3. [[deprecated]] / [[deprecated("reason"]] - C++14
// 
//  사용은 가능하나, 가급적 쓰지 말기를 권고할 때 붙이는 atttribute이다.
//  클래스, 타입 별칭, 열거자, 함수, 템플릿 특수화, 변수, 비 정적 멤버 변수, 열거 형(C++17), 네임 스페이스(C++17)
//  대상의 기능이 비추천인 것을 나타내는 속성.
// 
//  API 개발 시 등에서 사용 되지 않는 기능 사용하면 사용자에게 경고로 나타낼 수 있다.
//  인수로 표시하는 경고문을 지정할 수 있다. deprecated("reason")
// 
// 컴파일시 아래와 같은 컴파일 note/warning이 발생한다.

// note: 'f' 선언을 참조하십시요
[[deprecated]] void f(int i)
{
    if (i > 0) throw "positive";
}

// note: 'g' 선언을 참조하십시요
[[deprecated("Will be removed in the next version")]] void g(int i)
{
    if (i > 0) throw "positive";
}

int main()
{
    // warning C4996: 'f': deprecated로 선언되었습니다.
    f(1);

    // warning C4996: 'g': Will be removed in the next version
    g(1);
}

//deprecated 속성 사용 예시 //C++14

#include <iostream>

[[deprecated("please use new_func() function")]]
void old_func() {}

void new_func() {}

int main()
{
    old_func(); // warning
    return 0;
}

//기본적으로 Visual Studio 및 sdl(보안 개발 수명 주기) 컴파일 플래그는 [[deprecated]] 오류로 처리


//4. [[fallthrough]] - C++17
// 
//  switch-case, switch문에서 통과하는 것을 명시하는 속성.
//  switch 문에서 이미 오랫동안 fallthrough 방식을 써 왔지만, 
//  이를 좀 더 명확하게 컴파일러에게 알림으로써 컴파일 경고가 나오지 않도록 하는 attribute 이다.
//  의도적인 통과 장소에 지정하는 것으로 경고를 억제한다.
//  다음 case/default 레이블 바로 직전에 위치시킬 것

void f(int n)
{
    void g(), h(), i();

    switch (n)
    {
    case 1:
    case 2:
        g();
        [[fallthrough]];
        // no warning on fallthrough
    case 3:
        h();
        // compiler may warn on fallthrough
    case 4:
        i();
        // ill-­formed, not before a case label
        [[fallthrough]];
    }
}

//fallthrough 속성 예시

#include <iostream>

int func(int i)
{
    int ret = 0;
    switch (i)
    {
    case 1:
        ret += 1;
        [[fallthrough]];    // 의도적인 통과
    case 2:
        ret += 2;
        break;
    }
    return ret;
}

int main()
{
    return 0;
}


//5. [[nodiscard]] - C++17
// 
//  컴파일러에게 값이 버려질 경우 컴파일 경고를 내 달라는 힌트를 준다.
//  즉, 이 값은 반드시 사용되어야 하니, 
//  그렇지 않을 경우(discarded - expression) 경고를 내라는 것이다.

struct [[nodiscard]] X
{
    int i;
};

X foo()
{
    return { 42 };
}

X x{ 42 };
X& foo2() { return x; }

[[nodiscard]] int bar()
{
    return 3;
}

int main()
{
    // warning: ignoring returned value of type 'X', declared with attribute nodiscard
    foo();

    // value가 아닌 reference이기에 컴파일 경고가 발생하지 않는다.
    foo2();

    // warning: ignoring return value of 'int bar()', declared with attribute nodiscard
    auto i = (bar(), 55);

    // void로 강제 타입 캐스팅을 할 경우엔 컴파일 경고(unused variable 'b')가 발생하지 않는다.
    (void)bar();

    return 0;
}


//6. [[maybe_unused]] - C++17
// 
//  [[nodiscard]] 반대
//  미사용 변수에 [[maybe_unused]] attribute를 붙이면, 
//  미사용에도 불구하고 컴파일러 경고가 발생하지 않게 된다.
//  클래스, 타입 별칭, 열거타입, 함수, 함수 매개 변수, 변수, 비 정적 멤버 변수, 열거자
//  사용하지 않는 것을 명시하는 속성.
//  의도적으로 사용 되지 않는 것에 지정하여 경고를 억제한다.

#include <cassert>

void func([[maybe_unused]] int _unused)
{
    // _unused는 사용되지 않는다
}

[[maybe_unused]] void ff(bool thing1, bool thing2)
{
    [[maybe_unused]] bool b = thing1 && thing2;

    // assert는 release 모드로 컴파일시 compiled-out 되므로, 윗 라인의 변수 b는 미사용이다.
    // [[maybe_unused]] attribute를 붙였기에 컴파일 경고가 발생하지 않는다.
    assert(b);
}

int main()
{
    ff(true, true);

    return 0;
}
