
//-------------------------------------------------------------------------------
// 바운드 템플릿 프렌드 
//      클래스의 바깥에서 선언된 템플릿의 템플릿 특수화

#include <iostream>

template <class T> void Show(T&);           //1. 클래스 템플릿 앞에 함수 템플릿을 선언 //이전 버전

template <typename TT>
class ClassTemplate {
private:
    TT age = 0;
public:
    ClassTemplate(const TT& a) : age(a) { }

    friend void Show<>(ClassTemplate<TT>&); //3. friend 선언 <>에 의해 이들은 템플릿 특수화로 인식 ***
};

template <class T>
void Show(ClassTemplate<T>& a)              //2. 함수에 대해 다시 템플릿들을 프렌드로 선언
{
    std::cout << a.age << std::endl;
}

int main(void)
{
    ClassTemplate<int> a = ClassTemplate<int>(1);
    Show(a);

    //ClassTemplate<double> b = ClassTemplate<double>(1.5);
    //Show(b);
}