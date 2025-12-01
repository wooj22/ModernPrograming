//템플릿 복사 생성자
//		템플릿 생성자는 절대로 복사 생성자가 될 수 없기 때문에, 
//		이러한 템플릿의 존재가 복사 생성자의 암시적인 선언을 제한하지 않는다.
//
//		템플릿 생성자는 복사 생성자를 포함하여 다른 템플릿 생성자의 오버로드에 포함되고 
//		아마도 다른 생성자보다 더 잘 어울린다면 객체를 복사하는데 사용될 것이다.

#include<iostream>
using namespace std;

template<typename T, size_t size>
class fixed_vector
{
public:
	//타입정의
	typedef T* iterator;
	typedef const T* const_iterator;

	//기본 생성자
	fixed_vector() { }

	//템플릿 복사 생성자
	template<typename O, size_t osize>
	fixed_vector(const fixed_vector<O, osize>& other)
	{
		copy(other.begin(), other.begin() + min(size, osize),
			begin());
	}

	//템플릿 복사 할당 연산자
	template<typename O, size_t osize>
	fixed_vector<T, size>& operator=(const fixed_vector<O, osize>& other)
	{
		copy(other.begin(), other.begin() + min(size, osize),
			begin());
		return *this;
	}

	//컨테이너 기본연산
	iterator begin() { return v_; }
	iterator end() { return v_ + size; }
	const_iterator begin() const { return v_; }
	const_iterator end() const { return v_ + size; }

private:
	T v_[size];	//멤버변수
};

int main() {

}

//컴파일러가 암시적 버전을 생성하므로 
//사실 여전히 같은 복사생성자와 복사 할당 연산자를 원래 코드에서 가지고 있습니다.
//우리가 한것은 예전 버전을 대체한 것이 아니라 생성과 할당을 동적으로 확장한 것입니다

//템플릿 복사 생성자와 템플릿 복사 할당 연산자는 복사 생성자와 복사 할당 연산자가 아님을 유의
/*
struct X
{
	template<typename T> 
	X(const T&);			// 복사 생성자 아님 T 는 X가 될 수 없음
	template<typename T>
	operator=(const T&);	// 복사 할당 연산자 아님, T는 X가 될 수 없음
};
*/
