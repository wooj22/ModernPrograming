#include <iostream>
#include <string>
#include <vector>

//중첩 의존 타입 이름을 식별하는 용도에서는 반드시 typename을 사용해야 한다.

template <class T>
inline void PRINT_ELEMENTS(const T& coll, const char* optcstr = "")
{
	typename T::const_iterator pos;		//typename

	std::cout << optcstr;
	for (pos = coll.begin(); pos != coll.end(); ++pos) {
		std::cout << *pos << ' ';
	}
	std::cout << std::endl;
}

// 전체 벡터를 출력하기 -------------------------
template <typename T>
void print_vector(std::vector<T>& vec)		
{
	for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end();	++itr)  //typename
	{
		std::cout << *itr << std::endl;
	}
}
int main() {
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	std::cout << "벡터 상태" << std::endl;
	print_vector(vec);
	std::cout << "----------------------------" << std::endl;

	return 0;
}

/*
template<typename T>
using Empty_t = typename Empty<T>::type;
*/
