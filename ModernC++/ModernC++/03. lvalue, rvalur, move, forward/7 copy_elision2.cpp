// 여러 방법으로 테스트 하기

#include <iostream>
#include <vector>
#include <cstring>
#pragma warning(disable:4996)

class Coo
{
private:
    char* data;
public:
    Coo(const char* data)
    {
        this->data = new char[1000000];
        std::strcpy(this->data, data);
        std::cout << "Call Coo(char * data)    [data:" << this->data << "] / this : [" << this << ']' << std::endl;
    }
    Coo(const Coo& ref)
    {
        this->data = new char[1000000];
        std::strcpy(this->data, ref.data);
        std::cout << "Call Coo(const Coo& ref) [data:" << this->data << "] / this : [" << this << ']' << std::endl;
    }
    Coo(Coo&& ref) noexcept : data(ref.data)
    {
        ref.data = nullptr;
        std::cout << "Call Coo(Coo&& ref)      [data:" << this->data << "] / this : [" << this << ']' << std::endl;
    }
    ~Coo()
    {
        if (this->data != nullptr)
        {
            std::cout << "Call ~Coo()              [data:" << this->data << "] / this : [" << this << ']' << std::endl;
            delete[] this->data;
        }
        else
        {
            std::cout << "Call ~Coo()              / this : [" << this << ']' << std::endl;
        }
    }

    void ShowData(void)
    {
        if (this->data == nullptr)
            std::cout << "data : " << std::endl;
        else
            std::cout << "data : " << this->data << std::endl;
    }
};

Coo FuncNrvo(void)
{
    Coo s("sssss");
    return s;
}
Coo FuncNrvoS(int a)
{
    Coo s("sssss");
    Coo z("zzzzz");
    if (a == 100)   return s;
    else            return z;
}

Coo FuncRvo(void)
{
    return Coo("sssss");
}
Coo FuncRvoS(int a)
{
    if (a == 100)   return Coo("sssss");
    else            return Coo("zzzzz");
}

int main(void)
{

    //어차피 사라질 객체들이므로, 
    //객체 내의 깊은 복사가 필요한 부분은 그냥 사라질 객체 내의 str 변수의 메모리 주소만 보존하여 가지고 와서 갱신해주고, 
    //객체는 소멸 시켜버리면 된다.
    //그래서 나온 개념이 r-value 레퍼런스와 이동 생성자이다.

    const int& lref = 100;              // const int& // r-value 보관을 위해 const 동원
    //lref = 101;                       // 변경 불가
    std::cout << lref << std::endl;
    std::cout << "--------------------------" << std::endl;
    int&& rref = 100;                   // int&&  //r-value 레퍼런스
    rref = 101;
    std::cout << rref << std::endl;
    std::cout << std::endl;


    std::cout << "1. 일반 생성자 호출" << std::endl;
    {
        Coo a = "aaaaa";
        Coo b("bbbbb");
    }
    std::cout << std::endl;

    std::cout << "2. 복사 생성자 호출" << std::endl;
    {
        Coo a = "aaaaa";
        Coo b(a);
        //Coo b = a;
    }
    std::cout << std::endl;

    std::cout << "3. 이동 생성자 호출" << std::endl;
    {
        Coo a = "aaaaa";
        Coo b(std::move(a));
    }
    std::cout << std::endl;


    std::cout << "4. 임시 변수 r-value의 생성 - 라인이 끝나면 소멸된다." << std::endl;
    {
        Coo("ccccc");
        //std::cout << "라인이 넘어감" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "5. l-value 에 r-value 대입 - 생성과 동시에 초기화 및 라인이 끝났음에도 소멸되지 않음." << std::endl;
    {
        Coo e(Coo("ddddd"));
        std::cout << "&e : " << &e << std::endl;
        //std::cout << "라인이 넘어감" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "6. r-value를 const & 를 통해서 가리킴 - 라인이 끝났음에도 소멸되지 않음." << std::endl;
    {
        const Coo& f(Coo("eeeee"));
        std::cout << "&f : " << &f << std::endl;
        //std::cout << "라인이 넘어감" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "7. l-value를 r-value화 하여 생성과 동시에 초기화." << std::endl;
    {
        Coo a = "aaaaa";
        Coo i(std::move(a));
        std::cout << "&i : " << &i << std::endl;
        i.ShowData();
        a.ShowData();
        //std::cout << "라인이 넘어감" << std::endl;
    }
    std::cout << std::endl;


    std::cout << "8. 그냥 FuncNrvo()만 호출" << std::endl;
    {
        FuncNrvo();
        //std::cout << "라인이 넘어감" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "9. 그냥 FuncNrvoS()만 호출" << std::endl;
    {
        FuncNrvoS(19);
        //std::cout << "라인이 넘어감" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "10. 그냥 FuncRvo()만 호출" << std::endl;
    {
        FuncRvo();
        //std::cout << "라인이 넘어감" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "11. 그냥 FuncRvoS()만 호출" << std::endl;
    {
        FuncRvoS(19);
        //std::cout << "라인이 넘어감" << std::endl;
    }
    std::cout << std::endl;



    std::cout << "12. FuncNrvo() 함수의 반환으로 생성과 동시에 초기화." << std::endl;
    {
        Coo g(FuncNrvo());
        std::cout << "&g : " << &g << std::endl;
        //std::cout << "라인이 넘어감" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "13. FuncNrvoS() 함수의 반환으로 생성과 동시에 초기화." << std::endl;
    {
        Coo h(FuncNrvoS(11));
        std::cout << "&h : " << &h << std::endl;
        //std::cout << "라인이 넘어감" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "14. FuncRvo() 함수의 반환으로 생성과 동시에 초기화." << std::endl;
    {
        Coo j(FuncRvo());
        std::cout << "&j : " << &j << std::endl;
        //std::cout << "라인이 넘어감" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "15. FuncRvoS()함수의 반환으로 생성과 동시에 초기화." << std::endl;
    {
        Coo k(FuncRvoS(19));
        std::cout << "&k : " << &k << std::endl;
        //std::cout << "라인이 넘어감" << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
