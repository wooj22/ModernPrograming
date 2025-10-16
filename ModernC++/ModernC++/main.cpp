#include <iostream>
using namespace std;

struct Good
{
	Good() {}
	Good(Good&&) noexcept { std::cout << "move noexcept\n"; }
	Good(const Good&) noexcept { std::cout << "copy noexcept\n"; }
};

struct Bad
{
	Bad() {}
	Bad(Bad&&) { std::cout << "move\n"; }
	Bad(const Bad&) { std::cout << "copy\n"; }
};

int main()
{
	Good g; Bad b;

	Good g2 = std::move_if_noexcept(g);  // �μ��� noexcept��� move(g)
	Bad b2 = std::move_if_noexcept(b);   // �μ��� noexcept�� �ƴϸ� b
}