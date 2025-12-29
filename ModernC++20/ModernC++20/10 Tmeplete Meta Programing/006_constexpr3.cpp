//연습) constexpr 함수 사용 -------------------------------------------------------------
// 
// 컴파일 도중에 3n의 크기를 갖는 array를 만들어 보자

#include <iostream>
#include <array>
using namespace std;
/*
constexpr int pow(int base, int exp) noexcept		// pow는 결코 예외를 던지지 않는 constexpr 함수
{
	auto result = 1;
	for (int i = 0; i < exp; ++i) result *= base;
	return result;

	//return (exp == 0 ? 1 : base * pow(base, exp - 1));	//C++98 //문장 제한의 경우
}
*/
int main()
{
	auto base = 2;
	auto exp = 3;
	auto baseToExp = pow(base, exp);				// 실행시점에서 값들을 구한다. 2^3

	constexpr auto numConds = 3;
	std::array<int, pow(2, numConds)> results;		// 정적배열
	cout << results.size();

	//std::pow() 는 부동소수점 타입, constexpr이 아니다->만들자
}


// constexpr 객체 만들기 ---------------------------------------------------------

#include <iostream>

class Point {
public:
	constexpr Point(double xVal = 0, double yVal = 0) noexcept
		: x(xVal), y(yVal)
	{}

	constexpr double xValue(void) const noexcept { return x; }
	constexpr double yValue(void) const noexcept { return y; }

	//void setX(double newX) noexcept { x = newX; }		// C++11 //void는 리터럴 타입이 아니다 //constexpr 멤버 함수는 암묵적으로 const로 선언
	//void setY(double newY) noexcept { y = newY; }
	constexpr void setX(double newX) noexcept { x = newX; }	// C++14 //제한 사라짐
	constexpr void setY(double newY) noexcept { y = newY; }	// C++14

private:
	double x, y;
};

// 가운데 값인 Point 객체를 돌려준다.
constexpr Point midpoint(const Point& p1, const Point& p2) noexcept
{
	return { (p1.xValue() + p2.xValue()) / 2,(p1.yValue() + p2.yValue()) / 2 };   // constexpr 함수들을 호출
}

// 원점을 기준으로 p와 대칭인 Point 객체를 돌려준다 (C++14)
constexpr Point reflection(const Point& p) noexcept
{
	Point result;						// 비const Point를 생성
	result.setX(-p.xValue());
	result.setY(-p.yValue());
	return result;						// 그 복사본을 반환
}

int main()
{
	constexpr Point p1(9.4, 27.7);        // 이전과 동일
	constexpr Point p2(28.8, 5.3);

	constexpr auto mid = midpoint(p1, p2);
	constexpr auto reflectedMid = reflection(mid);
}
