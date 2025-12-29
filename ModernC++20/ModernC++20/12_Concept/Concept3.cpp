//Concepts 사용 예

//system_clock 의 concept 를 확인해보세요.

#include <iostream>
#include <concepts>
#include <chrono>
using namespace std;

string timeToString(chrono::system_clock::time_point& t)
{
	time_t time = chrono::system_clock::to_time_t(t);
	char buf[256];
	ctime_s(buf, sizeof(buf), &time);		//현재시간을 문자열로 변환   
	//printf("현재 시각: % s", buf);

	string time_str = buf;
	time_str.resize(time_str.size() - 1);
	return time_str;
}


// WallClock concept 정의		// 템플릿 인자가 clock 타입인가? is_steady 스태틱 콘스트 멤버가 false 인가
template <class _Clock>
concept WallClock = true == chrono::is_clock_v<_Clock> && false == _Clock::is_steady;

// SteadyClock concept 정의		// 템플릿 인자가 clock 타입인가? is_steady 스태틱 콘스트 멤버가 true 인가
template <class _Clock>
concept SteadyClock = true == chrono::is_clock_v<_Clock> && true == _Clock::is_steady;

template <class _Clock> requires WallClock<_Clock>
void print()
{
	//std::cout << _Clock::now() << std::endl;

	chrono::system_clock::time_point t = _Clock::now();
	std::cout << timeToString(t) << endl;
}

template <class _Clock> requires SteadyClock<_Clock>
void print()
{
	std::cout << _Clock::now().time_since_epoch().count() << std::endl;
}

int main()
{
	std::cout << chrono::system_clock::now() << std::endl;
	// steady_clock 인지 여부에 따라 다르게 표현하고 싶다.

	print<chrono::system_clock>();

	print<chrono::steady_clock>();

	return 0;
}
