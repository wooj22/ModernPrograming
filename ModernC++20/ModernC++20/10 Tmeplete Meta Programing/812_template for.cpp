//템플릿 반복문 //재귀 활용 ----------------------------------------

#include <iostream>
#include <type_traits>
using namespace std;

template<int N> struct Factorial
{
	//enum { value = N * Factorial<N-1>::value };
	static constexpr int value = N * Factorial<N - 1>::value;
};
template<> struct Factorial<1>		// 재귀의 종료를 위해 특수화(Specialization)
{
	//enum { value = 1 };
	static constexpr int value = 1;
};

int main()
{
	int n = Factorial<5>::value; // 5 * 4 * 3 * 2 * 1 => 120
	// 5 * Factorial<4>::value
	// 4 * Factorial<3>::value
	// 3 * Factorial<2>::value
	// 2 * Factorial<1>::value
	// 1

	cout << n << endl;
}


//템플릿 반복문 // 함수를 n번 반복하는 템플릿 만들기 --------------------

#include <iostream>
#include <functional>
using namespace std;

template<int n> void doLoop(std::function<void()> fn)
{
    fn();
    doLoop< n-1 >(fn);
}
template<> void doLoop<0>(std::function<void()> fn)  //특수화
{
}

int main()
{
    doLoop<10>(
        []() { printf("Good!\n"); }
    );

    return 0;
}

//Loop Unrolling
//      반복문을 실행 시간에 처리하지 않고, 컴파일 시간에 일렬로 펼쳐놓는 방식으로 처리
//      꼭 필요할 때만 사용. 컴파일러의 판단에 따라 자동으로 언롤링 함.

#include <iostream>
template<int i>
class Loop
{
public:
    template<typename FuncType>
    static inline void run(FuncType func) {
        Loop<i - 1>::run(func);
        func(i);
    }
};

template<>
class Loop<0>
{
public:
    template<typename FuncType>
    static inline void run(FuncType /* func */) { }
};


void doWork(int i) { std::cout << "doWork(" << i << ")\n"; }

int main()
{
    Loop<3>::run(doWork);
}

//튜플 출력하는 예시   //constexpr if 사용

#include <iostream>

template<typename TupleType, int n = std::tuple_size<TupleType>::value>
void tuplePrint(const TupleType& t)
{
    if constexpr (n > 1) {
        tuplePrint<TupleType, n - 1>(t);                //재귀
    }
    std::cout << std::get<n - 1>(t) << std::endl;
}

int main()
{
    std::tuple t1{ 167, "Testing", false, 2.3 };
    tuplePrint(t1);
}