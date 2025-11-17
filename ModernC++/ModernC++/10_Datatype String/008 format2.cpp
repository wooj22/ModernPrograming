//format specification
//		포멧 표시하기 
//		format-spec ::= [[fill]align][sign][#][0][width][.precision][type] 
// 
//		format specification 앞에는 반드시 콜론이 있어야 합니다.
//		argument id는 생략할 수도 있습니다


#include <iostream>
#include <format>			//C++20

int main()
{
	{
		auto s0 = std::format("{:6}", 42);		// s0 = "    42" //숫자
		auto s1 = std::format("{:6}", 'x');		// s1 = "x     " //문자
		std::cout << s0 << std::endl;
		std::cout << s1 << std::endl;

		auto s2 = std::format("{:<6}", 42);		// s2 = "42    "	//왼쪽 정렬
		auto s3 = std::format("{:>6}", 'x');	// s3 = "     x"	//오른쪽 정렬
		std::cout << s2 << std::endl;
		std::cout << s3 << std::endl;

		auto s4 = std::format("{:*<6}", 'x');	// s4 = "x*****"	//왼쪽 정렬 //부족한 문자는 *
		auto s5 = std::format("{:*>6}", 'x');	// s5 = "*****x"	//오른쪽 정렬
		auto s6 = std::format("{:*^6}", 'x');	// s6 = "**x***"	//가운데 정렬 

		char c = 120;
		auto s7 = std::format("{:6d}", c);		// s7 = "   120"
		auto s8 = std::format("{:6}", true);	// s8 = "true  "
	}

	{
		double inf = std::numeric_limits<double>::infinity();
		double nan = std::numeric_limits<double>::quiet_NaN();	//Not a Number
		auto s0 = std::format("{0:},{0:+},{0:-},{0: }", 1);   // s0 = "1,+1,1, 1"
		auto s1 = std::format("{0:},{0:+},{0:-},{0: }", -1);  // s1 = "-1,-1,-1,-1"
		auto s2 = std::format("{0:},{0:+},{0:-},{0: }", inf); // s2 = "inf,+inf,inf, inf"
		auto s3 = std::format("{0:},{0:+},{0:-},{0: }", nan); // s3 = "nan,+nan,nan, nan"
		std::cout << s0 << std::endl;
		std::cout << s1 << std::endl;
		std::cout << s2 << std::endl;
		std::cout << s3 << std::endl;
	}
	{
		char c = 120;
		auto s1 = std::format("{:+06d}", c);	// s1 = "+00120"
		auto s2 = std::format("{:#06x}", 0xa);  // s2 = "0x000a"
		auto s3 = std::format("{:<06}", -42);   // s3 = "-42   " (0 is ignored because of < alignment)
		std::cout << s1 << std::endl;
		std::cout << s2 << std::endl;
		std::cout << s3 << std::endl;

	}
}

//format-spec ---------------------------------------------------------------

//		format-spec ::= [[fill]align][sign][#][0][width][.precision][type]

//align은 정렬 방식
//		<, >, ^ 
//		각각 왼쪽 정렬, 오른쪽 정렬, 가운데 정렬입니다.  (=는 , 부호 뒤를 오른쪽 정렬, 숫자에만 사용 - 예정)

//fill은 정렬을 할 때 빈 공간을 어떤 문자로 채울지

//width - width는 최소 너비
//		생략될 경우 최소 너비가 지정되지 않은 것처럼 작동
//		align이 생략됐는데 width 앞에 0이 있을 경우 [[fill]align] 부분이 0=인 것처럼 작동
//		std::string str = std::format("{0:<} {0:0>5} {0:*^5} {0:0=5} {0:05} {1:<} {1:0>6} {1:*^6} {1:0=6} {1:06}", 7, -7);

//sign - sign은 부호의 표시 방법
//		숫자일 경우에만 사용
//		+, -, 공백 중 한 가지를 사용
//		각각 반드시 부호 표시, 음수일 때만 부호 표시, 양수일 때는 공백으로 음수일 때는 마이너스(-)로 표시
//		std::string str = std::format("{0:+}/{0:-}/{0: };{1:+}/{1:-}/{1: }", 7, -7);

//precision - precision은 수의 정밀도
//		실수일 경우에만 사용
//		std::string str = std::format("{0:.2} {0:.5}", 0.345);

//type - 해당 인수의 타입과 진법(수의 경우)
//		C format과 거의 같다.

//# - alternate form
//		x 타입에 대해 #을 사용하면 접두사로 0x 사용
