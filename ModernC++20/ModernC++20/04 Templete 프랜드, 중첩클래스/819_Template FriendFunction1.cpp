// 템플릿과 프랜드 선언 // friend function

//템플릿의 프렌드를 3가지로 분류할 수 있습니다.
//
//  템플릿이 아닌 프렌드
//  바운드 템플릿 프렌드 (클래스가 구체화될 때 클래스의 데이터형에 의해 프렌드의 데이터형이 결정됩니다.)
//  언바운드 템플릿 프렌드 (프렌드의 모든 특수화가 그 클래스의 각 특수화에 대해 프렌드들입니다.)


// 템플릿이 아닌 프렌드 // 클래스의 바깥에서 선언된 함수에 대한 friend

#include <iostream>

template <typename TT>
class ClassTemplate {
private:
    TT age = 0;
public:
    ClassTemplate(const TT& a) : age(a) { }

    friend void Show(ClassTemplate<int>&);     // 외부 Show 함수 //int
};

void Show(ClassTemplate<int>& a) {
    std::cout << a.age << std::endl;
}

int main(void)
{
    ClassTemplate<int> a = ClassTemplate<int>(1);
    Show(a);

    //ClassTemplate<double> b = ClassTemplate<double>(1.5);
    //Show(b);
}
