#include <iostream>
#include <set>
#include <utility>
#include <type_traits>
#include <functional>
#include <optional>
#include <string>
#include <ranges>
#include <algorithm>
using namespace std;

template<class T>
concept range = requires(T & t)
{
	std::ranges::begin(t);
	std::ranges::end(t);
};


int main()
{
	
}

