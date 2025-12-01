//언바운드 템플릿 프렌드
//    템플릿을 클래스 안에 선언함으로써, 언바운드 프렌드 함수를 생성할 수 있습니다.
//    이때 모든 함수 템플릿의 특수화는 모든 클래스 템플릿 특수화에 대해 프렌드입니다

#include <iostream>

template <typename TT>
class ClassTemplate {
private:
	int age = 0;
public:
	ClassTemplate(const TT& a) { age = a; }

	template<typename C>			//템플릿을 클래스 안에 선언
	friend void Show(C&);
};

template<class T>
void Show(T& a) {
	std::cout << a.age;
}

int main(void) {
	ClassTemplate<int> a = ClassTemplate<int>(1);
	Show(a);
}

/*
//friend 선언과 동시에 정의도 가능합니다.

	#include <iostream>

	template <typename TT>
	class ClassTemplate {
	private:
		int age = 0;
	public:
		ClassTemplate(const TT& a) {
			age = a;
		}

		template<typename C>
		friend void Show(C& a) {
			std::cout << a.age;
		}
	};


	int main(void) {
		ClassTemplate<int> a = ClassTemplate<int>(1);
		Show(a);
	}
*/