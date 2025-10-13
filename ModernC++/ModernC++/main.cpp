#include <iostream>
#include <array>
using namespace std;

class Point
{
private:
	double x, y;

public:
	constexpr Point(double xVal = 0, double yVal = 0) noexcept
		: x(xVal), y(yVal) {}

	constexpr double getX() const noexcept { return x; }
	constexpr double getY() const noexcept { return y; }
	constexpr void setX(double newX) noexcept { x = newX; }
	constexpr void setY(double newY) noexcept { y = newY; }
};

constexpr Point midpoint(const Point& p1, const Point& p2) noexcept
{
	return { (p1.getX() + p2.getX()) / 2, (p1.getY() + p2.getY()) / 2 };
}

int main()
{
	Point p1(0.4, 27.7);
	Point p2(9.4, 7.7);
	constexpr Point mid = midpoint(Point(9.4, 27.7), Point(0.4, 7.7));
}