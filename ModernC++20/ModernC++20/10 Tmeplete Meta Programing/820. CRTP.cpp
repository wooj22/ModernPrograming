//C++ 템플릿 디자인 

//CRTP (Curiously Recurring Template Pattern; 기묘하게 재귀하는 템플릿 패턴)
//  
//      자신의 기본 클래스의 템플릿 인자로 파생 받는 기술, 템플릿과 상속을 활용
//      공통적인 요소를 상속을 활용해 구현 + 타입별로 적용 가능


// 자신을, 자신의 기본 클래스의 템플릿 인자로 파생시키기 ***
//      class Derived : public Base<Derived>


// 부모 클래스를 템플릿 클래스로 구현
template<class _Derived>
class Foo
{
protected:
    void impl()
    {
        // 상속 가능한 작업들..
    }
public:
    void call()
    {
        static_cast<_Derived*>(this)->impl();   // 어떤 impl()이 호출될지는 컴파일 타임에 결정됨 ***
    }
};

// 자식 클래스는 자신을 템플릿 파라미터로 넣은 부모 클래스를 상속받음 ***
class Bar : public Foo<Bar>
{
    friend Foo<Bar>;
protected:
    void impl()
    {
        // Foo::impl을 상속받아서 더 복잡한 작업을 수행
    }
};

/*
    Foo<Bar>::call()에서는 
    자연히 Bar::impl()을 호출하게 되고, 이를 통해 '다형성'을 성취할 수 있게 됩니다.

    이 기법을 사용할 경우
    virtual 함수가 없어지므로 모든 함수호출은 정적으로 바인딩되어, 간접 참조가 줄어들고,
    또한 컴파일 타임에 어떤 함수가 불릴지 알 수 있으므로, 추가적인 컴파일 타임 최적화가 가능해집니다.
*/
