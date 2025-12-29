//가변템플릿 활용 (Fold Expression)

// 100 에서, 임의의 가변 데이타를 빼는 함수 구현하기 ***

#include <iostream>

template <typename Int, typename... Ints>
Int diff_from(Int base, Ints... values)
{
	return base - (values + ...);
}

int main()
{
	std::cout << diff_from(100, 1) << std::endl;				// 100 - 1		= 99
	std::cout << diff_from(100, 1, 4) << std::endl;				// 100 - 1 - 4	= 95
	std::cout << diff_from(100, 1, 2, 3, 4, 5) << std::endl;	//85
}
