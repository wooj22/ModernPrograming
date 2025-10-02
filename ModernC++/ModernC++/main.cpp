#include <iostream>
#include <vector>

struct A 
{
    std::string abc = "abc";

    // lvalue
    std::string& get()& { std::cout << "1";  return abc; }

	// rvalue
    std::string get()&& { std::cout << "2"; return std::move(abc); }

	// const lvalue
    std::string const& get() const& { std::cout << "3"; return abc; }

	// const rvalue
    std::string get() const&& { std::cout << "4"; return abc; }
};


int main()
{
    A a; 
    const A b;

    a.get();
    A().get();
    b.get();
    std::move(b).get();
}