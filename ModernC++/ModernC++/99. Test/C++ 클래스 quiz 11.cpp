//다음 코드에서 func()의 정의를 올바르게 클래스 외부에서 작성하려면 ?

template<typename T>
class MyClass {
public:
    void func();
};

① template<typename T> void func() { }
② template<typename T> void MyClass::func() { }
③ template<typename T> void MyClass<T>::func() { }
④ template<typename T> void MyClass<T>::func<T>() { }
