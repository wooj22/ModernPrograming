//가변인자 템플릿의 활용 

//튜플 갯수, 요소 얻기

#include <iostream>
using namespace std;

template <typename T>
void xtuple_size(const T& a)
{
	cout << T::N << endl;
}

// tuple (primary template) ----------------------------------
template <typename ...Types> class xtuple;

// empty tuple (specialization)
template <> class xtuple<> {};

// recursive tuple definition (partial specialization)
template <typename T, typename ... Types>
class xtuple<T, Types...> : private xtuple<Types ...>
{
public:
	xtuple() {}
	xtuple(const T& a, Types ... args) : first_(a), xtuple<Types...>(args...)
	{}

	enum { N = 1 + sizeof...(Types) };

public:
	T first_;
};


// tuple_element ---------------------------------------------
template <size_t N, typename xtuple>
struct xtuple_element;

// type of the first element
template <typename T, typename ... Types>
struct xtuple_element<0, xtuple<T, Types...>>
{
	using Type = T;
	using TupleType = xtuple<T, Types...>;
};

// recursive tuple_element definition
template <size_t N, typename T, typename ... Types>
struct xtuple_element<N, xtuple<T, Types...>>
	: public xtuple_element<N - 1, xtuple<Types...>>
{};


template <size_t N, typename ... Types>
inline typename xtuple_element<N, xtuple<Types...>>::Type&
Get(xtuple<Types...>& t)
{
	using TupleType = xtuple_element<N, xtuple<Types...>>::TupleType;
	return ((TupleType&)t).first_;
}

//------------------------------------------------------
int main(int argc, char* argv[])
{
	xtuple<int, char, double> t(1, 'a', 3.4);
	xtuple_size(t); //< 3


	auto c = Get<1>(t);
	cout << c << endl; //< a


	return 0;
}
