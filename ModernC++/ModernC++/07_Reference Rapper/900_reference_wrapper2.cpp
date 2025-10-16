//reference_wrapper
//		reference_wrapper<Ty>는 Ty 형식의 개체 또는 함수에 대한 '참조를 래핑'하며, 
//		해당 형식의 개체를 가리키는 포인터가 포함된 복사본을 생성/할당 가능하게 합니다.

//		도우미 함수 std::ref 및 std::cref를 사용하여 reference_wrapper 개체를 만들 수 있습니다.

/*
template <class Ty>
class reference_wrapper
{
	typedef Ty type;

	reference_wrapper(Ty&) noexcept;
	operator Ty&() const noexcept;
	Ty& get() const noexcept;

	template <class... Types>
	auto operator()(Types&&... args) const ->
		decltype(std::invoke(get(), std::forward<Types>(args)...));
};
*/

#include <iostream>
#include <functional>
using namespace std;

int main() {
	int i = 1;
	std::reference_wrapper<int> rwi(i);			//생성자는 저장된 값 ptr을 &val로 설정합니다.

	std::cout << "i = " << i << std::endl;
	std::cout << "rwi = " << rwi << std::endl;	//int& rwi =  i;

	rwi.get() = -1;								//get()
	std::cout << "i = " << i << std::endl;

	return (0);
}

//연산자 Ty& - *ptr를 반환
int main() {
	int i = 1;
	std::reference_wrapper<int> rwi(i);					//객체 전달

	std::cout << "i = " << i << std::endl;
	std::cout << "(int)rwi = " << (int)rwi << std::endl;	//*ptr를 반환

	return (0);
}

//operator() - 래핑된 참조를 호출
int neg(int val) {
	return (-val);
}

int main() {
	std::reference_wrapper<int(int)> rwi(neg);			//함수 전달

	std::cout << "rwi(3) = " << rwi(3) << std::endl;	//neg(3)

	return (0);
}

//result_type - 래핑된 참조의 약한 결과 형식, 함수 형식에서만 의미가 있습니다.
int neg(int val) {
	return (-val);
}

int main() {
	typedef std::reference_wrapper<int(int)> Mywrapper;
	Mywrapper rwi(neg);
	Mywrapper::result_type val = rwi(3);

	std::cout << "val = " << val << std::endl;

	return (0);
}
//type - 래핑된 참조 형식
int neg(int val) {
	return (-val);
}

int main() {
	int i = 1;
	typedef std::reference_wrapper<int> Mywrapper;
	Mywrapper rwi(i);
	Mywrapper::type val = rwi.get();

	std::cout << "i = " << i << std::endl;
	std::cout << "rwi = " << val << std::endl;

	return (0);
}