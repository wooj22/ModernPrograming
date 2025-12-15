#include <iostream>


template <typename T>
void print(T a)
{
	std::cout << a << std::endl;
}

template<typename T, typename... Ts>
void print(T a, Ts... args)
{
	for (int i = 0; i < a; a++)
	{
		std::cout << args[i] << std::endl;
	}
}

int main()
{
	print(1);
	print(3, 4, 5);
}