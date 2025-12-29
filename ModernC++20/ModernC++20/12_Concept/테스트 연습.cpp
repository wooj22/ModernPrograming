// int, float 타입만 허용하는 함수를 작성하세요.

#include <iostream>
#include <type_traits>
#include <concepts>
using namespace std;


int main()
{
	print_int_float(1);		//ok
	print_int_float(1.2f);	//ok
	print_int_float(1.5);	//error
	print_int_float(10L);	//error
}

/*

template <class T>
concept int_float = std::is_same_v<T,int> || std::is_same_v<T, float>;

template <int_float T>
void print_int_float(T n)
{
	cout << n << endl;
}

*/



// Player 클래스와 그 파생타입만 허용하는 함수를 작성하세요.

#include <iostream>
#include <type_traits>
#include <concepts>
using namespace std;

class Player { };
class Monster : public Player { };

template<typename T>
void funcPlayer(T a) {
}

int main()
{
	funcPlayer(Player());		//ok
	funcPlayer(Monster());		//ok
	funcPlayer(1.5);			//error
}

/*

template<typename T>
concept Players = std::derived_from<T, Player>;

template<Players T>
void funcPlayer(T a) {
}

*/