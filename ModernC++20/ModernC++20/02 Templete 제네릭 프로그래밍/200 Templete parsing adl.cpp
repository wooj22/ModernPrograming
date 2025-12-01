//Koenig Algorithm
//ADL(Argument Dependent Lookup)
//      인수에 의존해 이름 공간을 검색하는 기능
//		함수가 사용하는 인수가 소속된 이름공간을 검색해, 해당 함수를 호출해 준다,

/*
	#include <iostream>
	#include <algorithm>

	namespace foo
	{
		struct Bar { int data; };

		void init(Bar& bar)
		{
			bar.data = 42;
		}
	}
	int main()
	{
		//using foo::init;    
		//using namespace foo;    

		foo::Bar bar;
		init(bar);								//foo::init 아닌데도 잘 됨.
		std::cout << bar.data << std::endl;
		return 0;
	}

	//컴파일러는 init(bar)에서 bar가 Bar 클래스의 객체이고 Bar는 foo에 있다는 걸 알 수 있으므로
	//init을 foo에서도 찾는다.
*/

//프로그래머에게 편리함을 더해주지만, 때론 찾기 힘든 버그를 발생시킬 우려

#include <iostream>
#include <algorithm>
namespace foo { 
	struct Bar { int data; };
	void swap(Bar& a, Bar& b)
	{
		std::cout << "foo::swap" << std::endl;
		int temp = a.data;
		a.data = b.data;
		b.data = temp;
	} 
}
int main() 
{
	 foo::Bar bar1, bar2;
	 bar1.data = 42; 
	 bar2.data = 777;
	 std::cout << bar1.data << ' ' << bar2.data << std::endl;
	 using std::swap;
	 swap(bar1, bar2);		//어떤 함수를 사용하는가? // Call foo::swap not std::swap.
	 std::cout << bar1.data << ' ' << bar2.data << std::endl;
	 return 0;
 }

//ADL이 우선시되는 상황 때문

#include <iostream>
#include <algorithm>

namespace foo {
	struct Bar { int data; };
	void init(Bar& bar) { bar.data = 42; }		//1
}
void init(foo::Bar& bar) { bar.data = 777; }	//2

int main()
{
	foo::Bar bar;
	init(bar);		// Error! call of overloaded 'init(foo::Bar&)' is ambiguous.
	std::cout << bar.data << std::endl;
	return 0;
}

//오류를 수정해 보세요.		
// 
//	::init(bar) or foo::init(bar)


//--------------------------------------------------------------------------------------
//ADL과 명시적 템플릿 인자 
//ADL(Argument Dependent Lookup)이란 인수에 의존해 이름 공간을 검색하는 기능

#include <iostream>    
using namespace std;

namespace N
{
	class X { };
	template<int I> void select(X*) { cout << I << endl; }
}

void g(N::X* xp)
{
	select<3>(xp);      // Error ADL아님	 //C++14
}	

int main() {
}

//컴파일러는 <3>이 템플릿 인자 목록이라고 결정하기 전까지는 
//xp가 함수 호출 인자라고 결정할 수 없기 때문에 ADL로 select()를 찾지 못한다 
//뿐만 아니라 컴파일러는 select()가 템플릿이라는 것을 알기 전까지는 
//이것이 템플릿 인자 목록 이라고 결정내릴 수 없다

//C++20 빌드 성공
/*
	#include <iostream>
	using namespace std;

	namespace N
	{
		class X { };
		template<int I> void select(X*) { cout << I << endl; }
	}

	void g(N::X* xp)
	{
		select<3>(xp);     // C++20에서는 ADL 규칙이 변경되었으며, 명시적인 템플릿 인수는 ADL을 방지하지 않습니다. 
	}

	int main() {

		N::X x;
		g(&x);
	}
*/
