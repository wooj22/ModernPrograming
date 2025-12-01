//일반화된 복사 생성자(Generic copy constructor)
//      클래스 템플릿의 멤버 함수 템플릿으로 구현하는 복사 생성자.
// 
//      U(int)가 T(double)로 복사(대입) 가능하다면 Complex<U>도 Complex<T>에 복사(대입) 가능해야 한다.
//      friend class로 선언되어야 한다. ( 접근해야 할 멤버가 private 또는 protected인 경우 )

#include<iostream>

template<typename T> class Complex
{
    T re, im;
public:
    Complex(T a = {}, T b = {}) : re(a), im(b) {}
    //T getReal() const;
    //static int cnt;
    //template<typename U> T func(const U& c);

    // 일반화된 복사 생성자 선언
    template<typename U>
    Complex(const Complex<U>& c);

    template<typename> friend class Complex;
};

// 일반화된 복사 생성자 구현부
template<typename T> template<typename U>
Complex<T>::Complex(const Complex<U>& c) : re(c.re), im(c.im)
{
}

int main()
{
    Complex<int> c1(1, 1);
    Complex<int> c2 = c1;
    Complex<double> c3 = c1;
}

//주의, 진짜 복사 생성자는 아니다.