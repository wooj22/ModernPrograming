//가변 템플릿 재귀를 이용한 반복

#include <iostream>
#include <typeinfo>

void handleValue(int value) { std::cout << "Integer: " << value << std::endl; }
void handleValue(double value) { std::cout << "Double: " << value << std::endl; }
void handleValue(std::string_view value) { std::cout << "String: " << value << std::endl; }

void processValues() // Base case to stop recursion
{ /* Nothing to do in this base case */
}

template<typename T1, typename... Tn>
void processValues(T1 arg1, Tn... args)
{
	handleValue(arg1);
	processValues(args...);					//재귀
}

int main()
{
	processValues(1, 2, 3.56, "test", 1.1f);
}

//processValues(1, 2, 3.56, "test", 1.1f);
//handleValue(1);
//processValues(2, 3.56, "test", 1.1f);
//handleValue(2);
//processValues(3.56, "test", 1.1f);
//handleValue(3.56);
//processValues("test", 1.1f);
//handleValue(test");
//processValues(1.1f);
//handleValue(1.1f);
//processValues();


/*

// non-const 레퍼런스를 사용하면서 리터럴값을 사용하게 하려면 
//		포워드 레퍼런스(forwarding references)를 사용
//		std::forward는 <utility> 헤더에 정의

	template<typename T1, typename... Tn>
	void processValues(T1&& arg1, Tn&&... args)
	{
		handleValue(std::forward<T1>(arg1));
		processValues(std::forward<Tn>(args)...);
	}


//가변 인수 템플릿을 인스턴스화할 때 반드시 템플릿 인수를 지정하게 하려면

	template<typename T1, typename... Types>
	class MyVariadicTemplate { };

	//인수없이 인스턴스화하려고 시도하면 컴파일 에러가 발생

*/
