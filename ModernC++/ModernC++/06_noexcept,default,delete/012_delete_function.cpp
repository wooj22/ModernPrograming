#include <iostream>

//정의되지 않은 비공개 함수보다 삭제된 함수를 선호하라.

//어떤 함수의 사용을 막고 싶으면
//	    1.함수를 private로 선언하고 함수의 정의를 만들지 않는 방법		//C++98 private
//	    2.사용을 막을 함수 선언의 끝에 "= delete"를 붙이는 것			//C++11 delete 
// 
//사용을 막아둔 함수를 사용하려고 했을 경우, 
//      C++98은 링크 시점에 가서야 발견되지만, 
//      C++11의 삭제된 함수는 컴파일 시점에 발견될 수 있다.

//삭제된 함수(deleted function)

class A {
public:
    void Func() = delete;
};

//삭제된 함수는 private이 아니라 public으로 선언하는 것이 관례이다
//      함수의 접근성과 함수 사용하지 않음을 구분

//예시) C++11 표준에 명시된 basic_ios의 일부분
//      입출력 스트림 객체의 복사를 금지하기 위해 복사 생성자와 복사 대입 연산자를 삭제함.
/*
    template <class charT, class traits = char_traits<charT> >
    class basic_ios : public ios_base {
    public:
        basic_ios(const basic_ios&) = delete;
        basic_ios& operator=(const basic_ios&) = delete;
    }
*/


// 비멤버 함수의 경우도 사용 가능 ------------------------------------------

bool isLucky(int number) { return true; }

// 암묵적 변환을 방지하기 위한 목적
//bool isLucky(char) = delete;    // char을 배제
//bool isLucky(bool) = delete;    // bool을 배제
//bool isLucky(double) = delete;    // double과 float를 배제

int main()
{
    if (isLucky(7)) {}
    if (isLucky('a')) {}    //int로 변환
    if (isLucky(true)) {}   //int로 변환
    if (isLucky(3.5)) {}    //int로 변환

    return 0;
}


//템플릿 인스턴스의 경우 -------------------------------------------------

template <typename T>
void processPointer(T* ptr) {}

// 원치 않는 템플릿 인스턴스화 방지
template <>
void processPointer<char>(char*) = delete;        // char* 타입의 포인터로는 호출불가
template <>
void processPointer<const char>(const char*) = delete;  //const char* 타입 호출불가


/*

//클래스 안의 함수 템플릿의 일부 인스턴스화를 방지하려는 목적인 경우

// C++98 접근방식(private 선언)은 안됨

    class Widget {
    public:
        template <typename T>
        void processPointer(T* ptr) {}
    private:
        template <>                //오류! //템플릿 특수화는 이름공간 범위내 작성 (구버전)
        void processPointer<void>(void*) {}
    };

// = delete 사용은 가능

    class Widget {
    public:
        template <typename T>
        void processPointer(T* ptr) {}
    };
    template <>
    void Widget::processPointer<void>(void*) = delete; //OK

*/


// 복사생성이 안되도록 클래스를 수정하세요 ------------

#include <iostream>

class Widget {
public:
private:
};

int main()
{
    Widget w;
    Widget w2(w);       //
}

/*
    #include <iostream>

    class Widget {
    public:
        Widget() = default;
        Widget(const Widget& a) = delete;                   //
        Widget& operator=(const Widget& a) = delete;        //
    private:
    };

    int main()
    {
        Widget w;
        //Widget w2(w);       
    }
*/