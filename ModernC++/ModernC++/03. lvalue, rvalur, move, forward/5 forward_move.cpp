//예시 // 여러 방법으로 테스트 하기

#include <iostream>	
#include <vector>
#include <utility>

using namespace std;

class CustomVector
{
public:
	unsigned m_size = 0;		// 동적 배열의 사이즈가 될 멤버 변수
	int* ptr = nullptr;			// 동적 배열 포인터가 될 멤버 변수 (할당은 init 함수에서)

	CustomVector(const unsigned& _m_size, const int& _init = 0)
	{
		cout << "Constructor" << endl;
		init(_m_size, _init);
	}

	CustomVector(const CustomVector& l_input)		// L-value 만 받을 수 있다.
	{
		cout << "Copy construtor" << endl;
		// 깊은 복사 ----------------
		init(l_input.m_size);
		for (unsigned i = 0; i < m_size; ++i)
			ptr[i] = l_input.ptr[i];
	}

	CustomVector(CustomVector&& r_input)			// R-value 만 받을 수 있다.
	{
		cout << "Move construtor" << endl;
		// 얕은 복사 ----------------
		// 소유권 이전
		m_size = r_input.m_size;
		ptr = r_input.ptr;
		// 소유권 박탈
		r_input.m_size = 0;
		r_input.ptr = nullptr;
	}

	~CustomVector()
	{
		delete[] ptr;
	}

	void init(const unsigned& _m_size, const int& _init = 0)
	{
		m_size = _m_size;
		ptr = new int[m_size];
		for (unsigned i = 0; i < m_size; ++i)
			ptr[i] = _init;
	}
};

/*
복사 생성자  - const CustomVector&
	L-value 만 받을 수 있다.
	깊은 복사
		그저 동적 배열의 원소 내용들만 쫙 복사해준다.
		복사 대상이 된 객체와 복사로 생성된 객체는 별개의 존재. 그저 내용물만 복사 받았을 뿐.
		소유권 이전이 이루어지지 않음. 복사 대상이 된 객체의 소유권도 여전히 보장이 됨.

이동 생성자 - CustomVector&&
	R-value 만 받을 수 있다.
	얕은 복사
		아예 배열 자체의 소유권을 넘겨준다. 포인터만 복사하면 됨!
		소유권 이전이 이루어 진다.
		복사 대상이 된 객체의 소유권은 박탈 됨.
		A 에서 B 로 얕은 복사가 이루어졌다면 A 와 해당 메모리의 연결이 끊어지며
		동일한 메모리에 대한 소유는 이제 B 가 가지게 된다.
*/

void doSomething(CustomVector& vec)			// L-value
{
	cout << "Pass by L-reference" << endl;
	CustomVector new_vec(vec);				// copy 생성
}

void doSomething(CustomVector&& vec)		// R-value
{
	cout << "Pass by R-reference" << endl;
	CustomVector new_vec(std::move(vec));	// move 생성 //R-value로 vec을 받았더라도 std::move로서 넘겨주어야 한다. 
}

template<typename T>
void doSomethingTemplate_X(T vec)
{
	doSomething(vec);	// R-value, L-value를 구분해서 컴파일 하지 못하고 그냥 다 L-value로 처리해버린다.
}

template<typename T>
void doSomethingTemplate_O(T&& vec)
{
	doSomething(std::forward<T>(vec)); // 올바르게 R-value, L-value를 구분해서 컴파일 한다.
}

int main()
{
	{
		CustomVector my_vec(10, 1024);
		CustomVector temp(my_vec);						// my_vec 은 L-value
		cout << my_vec.m_size << endl;
	}
	{
		CustomVector my_vec(10, 1024);
		CustomVector temp(std::move(my_vec));			// std::move(my_vec) 은 R-value
		cout << my_vec.m_size << endl;
	}

	{
		CustomVector my_vec(10, 1024);
		doSomething(my_vec);							// L-value 전달
		doSomething(CustomVector(10, 8));				// R-value 전달  //임시객체
	}
	{
		CustomVector my_vec(10, 1024);
		doSomethingTemplate_X(my_vec);					// L-value
		doSomethingTemplate_X(CustomVector(10, 8));		// R-value
	}
	{
		CustomVector my_vec(10, 1024);
		doSomethingTemplate_O(my_vec);					// L-value
		doSomethingTemplate_O(CustomVector(10, 8));		// R-value
	}
}