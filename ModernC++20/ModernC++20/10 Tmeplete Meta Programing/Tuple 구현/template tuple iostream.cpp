//std::iostream 으로 std::tuple 입출력하기

#include <iostream>
#include <tuple>
#include <sstream>

using namespace std;

template < typename ... Elems, size_t ... Idx >
istream& istreamget_impl(istream& is, tuple< Elems... >& tup, const index_sequence< Idx... >)
{
    int dummy[sizeof...(Elems)] = { (is >> get< Idx >(tup), 0)... };
    return is;
}

template < typename ... Elems >
istream& operator>>(istream& is, tuple< Elems... >& tup)
{
    istreamget_impl(is, tup, make_index_sequence< sizeof...(Elems) >());
    return is;
}

template < typename ... Elems, size_t ... Idx >
ostream& ostreamput_impl(ostream& os, tuple< Elems... >& tup, const index_sequence< Idx... >)
{
    int dummy[sizeof...(Elems)] = { (os << get< Idx >(tup) << ' ', 0)... };
    return os;
}

template < typename ... Elems >
ostream& operator<<(ostream& os, tuple< Elems... >& tup)
{
    ostreamput_impl(os, tup, make_index_sequence< sizeof...(Elems) >());
    return os;
}

int main()
{
    stringstream ss;
    tuple<int, double, string> tup;
    ss << "48 1.5 Hello?\n";
    ss >> tup;
    cout << tup;
    // output : 48 1.5 Hello?
}
