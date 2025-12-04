//static_assert 활용
// 
// 사용자가 정수가 아닌 값을 입력을 전달했을 때, 
// 컴파일 에러 메시지가 표시되도록 template을 작성하세요.  

#include <concepts>
#include <iostream>
#include <assert.h>
#include <type_traits>

template <typename T>
void process(T value) {
	static_assert(std::is_integral_v<T>, "T must be an integral type");
}

int main()
{
    process(5);         // 통과
    process(3.14);      // 컴파일 에러 : "T must be an integral type"
}