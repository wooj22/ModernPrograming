
// 템플릿은 컴파일 타임에 모든것이 준비되어야 하므로 헤더 안에 구현까지 들어있어야 한다.

// -> 정확한 표현은 컴파일되기 전에 필요하다. #include 전처리로 해결할 수 있어야 한다.

//A.h

template <typename T>
class A
{
public:
	A();
	A(T);
	T foo();
private:
	T element = 0;
};

//A.cpp

template <typename T> A<T>::A() {}
template <typename T> A<T>::A(T e) { e = element; }
template <typename T> T A<T>::foo() { return element; }

//main ---------------------------------------

#include A.h

int main() {
	A<int> a;
}

//------------------------------------------------------------------------
//	C++에서는 템플릿도 선언과 구현을 나눌 수 있도록 hpp라는 파일 확장자를 지원합니다.
//	보통 IDE에선 헤더 파일로 인식합니다.
 
//A.hpp

template <typename T>
class A
{
public:
	A();
	A(T);
	T foo();
private:
	T element = 0;
};
template <typename T> A<T>::A() {}
template <typename T> A<T>::A(T e) { e = element; }
template <typename T> T A<T>::foo() { return element; }


//main ---------------------------------------

#include A.hpp

int main() {

}

//------------------------------------------------------------------------

#include A.h
#include A.cpp

int main() {

}

//------------------------------------------------------------------------

//A.h

template <typename T>
class A
{
public:
	A();
	A(T);
	T foo();
private:
	T element = 0;
};

#include A.cpp

//main ---------------------------------------

#include A.h

int main() {

}


//-------------------------------------------------------------------------------
.c
.h
.cc
.cpp
.c++
.cxx
.hpp
.hxx
.hh
.h++

//C++이 아닌 C에서는 .cpp 대신에 .c 확장자를 쓴다.
 
//VC++(비쥬얼 스튜디오 C++ 컴파일러)에서 .cpp 확장자와 .cxx 확장자는 똑같은 의미이다.
//본래 처음 C++가 만들어졌을 때, 파일 확장자는.c++를 사용하도록 되어있었다.
//그런데 특정 OS(운영체제)에서는 확장자 이름에 '+'를 사용할 수 없었기 때문에 '+' 대신에 'x'를 넣어.cxx라고 쓴 것이다.

//MS-DOS와 MS-Windows에서는.cpp를 사용하였는데 현재는 이것이 거의 표준처럼 되어있다.

//.hpp 또는.hxx 확장자는 왜 굳이 사용했을까 ?

//C++ 문법중에는 정의와 선언을 분리하기 어려운 상황이 몇 가지 있다.
//그 중 한가지가 바로 템플릿(template)을 구현할 때이다.
//템플릿의 타입이 컴파일시간에 지정되므로 헤더파일에 정의가 구현되어야 한다.
//그래서 이런 경우에는 특별히 C++ 문법을 썼음을 확실히 명시하기 위해.
//hpp, h++, .hxx 등을 사용하는 것이다.
 
//템플릿 정의의 경우.txx, .tpp, .tpl이라고 표시하기도 한다.
//인라인 함수 정의에는.ii, .ixx, .ipp, .inl을 쓰기도 한다.
