//std::optional::emplace 사용
// 
//		std::optional에 값을 직접 생성하여 저장하는 기능을 제공
//		기존에 저장된 값을 제거하고 새로운 값을 생성.
//		객체의 생성자 호출을 통해 값을 초기화.
//		std::optional이 비어 있더라도 새로운 값을 생성.

#include <iostream>
#include <optional>
#include <string>

int main() {
	std::optional<std::string> opt;

	// emplace를 사용하여 값을 생성
	opt.emplace("Hello, Optional!");			//new string("Hello, Optional!");

	std::cout << "Value: " << *opt << "\n";

	// 기존 값을 제거하고 새로운 값 생성
	opt.emplace("New Value");

	std::cout << "Updated Value: " << *opt << "\n";

	return 0;
}

//emplace의 장점
//	재사용 가능성 : 기존 값 제거 후 재생성.
//	비용 절감 : 객체를 복사하지 않고 직접 생성.
//	편리함 : 생성자에 인수를 바로 전달하여 객체를 생성.



//사례) 객체를 선택적으로 담는 클래스를 만들기 -----------------------------------------

// optional 없이 처리한다면 아주 복잡해진다.

using T = int;

struct S {
	bool is_initialized = false;
	alignas(T) unsigned char maybe_T[sizeof(T)];

	void construct_the_T(int arg) {
		assert(!is_initialized);
		new (&maybe_T) T(arg);
		is_initialized = true;
	}

	T& get_the_T() {
		assert(is_initialized);
		return reinterpret_cast<T&>(maybe_T);
	}

	~S() {
		if (is_initialized) {
			get_the_T().~T(); // destroy the T
		}
	}
	// ... 많은 코드 ...
};

// optional 사용 --------------------------------------------

#include <iostream>
#include <cassert>
#include <optional>
using namespace std;

using T = int;	// some object type

struct S {
	optional<T> maybe_T;

	void construct_the_T(int arg) {
		// 반복해 초기화하는 것을 막지 않아도 된다.
		// optional의 emplace 멤버는
		// 담고 있는 객체가 무엇이든 소멸하고 새로운 것을 담는다.
		maybe_T.emplace(arg);
	}

	T& get_the_T() {
		assert(maybe_T);
		return *maybe_T;
		// return maybe_T.value();  // maybe_T를 초기화하지 않았을 때 예외 발생이 더 좋으면
	}
};
