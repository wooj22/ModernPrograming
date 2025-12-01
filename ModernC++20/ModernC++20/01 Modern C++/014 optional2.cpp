//C++ 17에 추가된 유용한 클래스 중에 optional이 있습니다.
//		해당 객체는 값을 리턴할 때 값이 없음을 표현하기에 유용합니다

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <optional>
using namespace std;

void maybe_take_an_int(optional<int> potential_value = nullopt) // 'potential_value = {}'와 같다
{}

optional<int> maybe_return_an_int() {
	optional<int> o = {};
	o = 1;						//값이 있을때와 없을때 비교하세요 ***
	return o;
}

int main()
{
	optional<int> o = maybe_return_an_int();
	if (o.has_value()) { }										//has_value()
	if (o) { }													// bool로 변환한다  1	

	if (o) {
		cout << "The value is: " << *o << '\n';
		cout << "The value is: " << o.value() << '\n';			//value()
	}

	//값이 없을때 접근하면 bad_optional_access 예외가 발생
	// -> value_or

	cout << "The value might be: " << o.value_or(42) << '\n';	//value_or()

	//value_or 멤버 함수는 
	//optional 객체의 값이 없을 때 예외가 아니라 지정한 대체 값(fallback value)을 반환한다
}


//value_or() -----------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include <optional>
#include <iostream>
#include <cstdlib>

std::optional<const char*> maybe_getenv(const char* n)
{
	if (const char* x = std::getenv(n))    //환경변수 //_dupenv_s
		return x;
	else
		return {};
}
int main()
{
	std::cout << maybe_getenv("MYPWD").value_or("(none)") << '\n';

	//*this 에 값이 있으면 현재 값 , 그렇지 않으면 default_value
}


//optional 사용의 이점
//
//	‘기본 값 반환’ 방법과 달리 값이 있을 때와 없을 때를 쉽게 구별할 수 있다.
//	예외 처리를 사용하지 않고 값이 없음을 알릴 수 있다. (예외가 빈번하게 발생하면 처리 비용이 너무 크다)
//	반환한 반복자와 비교할 ‘끝(end)’ 반복자를 드러내지 않아도 되므로 
//  호출하는 쪽에 구현 상세를 노출하지 않을 수 있다.

