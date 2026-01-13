// Concept
//
// int, float 타입만 허용하는 함수를 작성하세요.( Templete Concept 사용 ) 

#include <iostream>
#include <type_traits>
#include <concepts>
using namespace std;

template<class T>
concept IntFloat = is_same_v<T, int> || is_same_v<T, float>;


template<IntFloat T>
void print_int_float(T t)
{

}

// print_int_float 구현

int main()
{
	print_int_float(1);		//ok
	print_int_float(1.2f);	//ok
	print_int_float(1.5);	//error
	print_int_float(10L);	//error
}
