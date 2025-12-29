// if constexpr -----------------------------------------------------------------------

	//타입에 따라 형태가 달라지는 함수를 짜고 싶다면, if 문은 템플릿 특수화, 템플릿 타입 유추를 통해 구현.
	//if constexpr 로 처리 가능.
	//if constexpr 은 조건이 반드시 bool 로 타입 변환될 수 있어야 하는 컴파일 타임 상수식이어야만 합니다. ***
	//if constexpr 이 참이라면 else 에 해당하는 문장은 컴파일 되지 않고 (완전히 무시), 따라서 오류 발생 안함.

	#include <iostream>
	#include <type_traits>

	template <typename T>
	void show_value(T t) 
	{
		if constexpr (std::is_pointer<T>::value) {				//std::is_pointer_v<T>
			std::cout << "포인터 이다 : " << *t << std::endl;
		} else {
			std::cout << "포인터가 아니다 : " << t << std::endl;
		}
	}

	int main() 
	{
		int x = 3;		show_value(x);	
		int* p = &x;	show_value(p);
	}

	//참고로, if constexpr 대신 템플릿 타입 유추를 이용하면 다음과 같이 작성

	template <typename T>
	void show_value(T t) {  std::cout << "포인터가 아니다 : " << t << std::endl;	}
	template <typename T>
	void show_value(T* t) {  std::cout << "포인터 이다 : " << *t << std::endl; }



// if constexpr 예제 ----------------------------------------------------------------------
	
	// int*가 인자로 넘겨질 경우 else { return t; }는 버려진다. // 즉, 컴파일 대상에서 제외된다.
	template <typename T>
	auto get_value(T t)
	{
		if constexpr (std::is_pointer_v<T>)
			return *t;
		else
			return t;
	}

	// if constexpr 없이는 아래와 같이 작성해야만 했다 --------------------------

	// SFINAE (Substitution Failure Is Not An Error)

		template <typename T, std::enable_if_t<std::is_pointer<T>{}>* = nullptr>
		auto get_value(T t)	{
			return *t;
		}

		template <typename T, std::enable_if_t<!std::is_pointer<T>{}>* = nullptr>
		auto get_value(T t)	{
			return t;
		}

	// Tag dispatching (이벤트나 메시지를 다른 부분으로 전달하는 메커니즘)

		template <typename T>
		auto get_value(T t, std::true_type)	{
			return *t;
		}

		template <typename T>
		auto get_value(T t, std::false_type) {
			return t;
		}

		template <typename T>
		auto get_value(T t)	{
			return get_value(t, std::is_pointer<T>{});
		}


// if constexpr 예제	   // recursive templates 단순화

	// without if constexpr
		template <int N1>
		constexpr auto sum()	//재귀 종료용
		{
			return N1;
		}

		template <int N1, int N2, int... Ns>
		constexpr auto sum()
		{
			return N1 + sum<N2, Ns...>();
		}

	// with if constexpr
		template <int N, int... Ns>
		constexpr auto sum()
		{
			if constexpr (sizeof...(Ns) == 0)
				return N;
			else
				return N + sum<Ns...>();
		}

	int main()
	{
		int x = sum<1, 2, 5>();
		return 0;
	}

// if constexpr 예제   // decomposite value  //분해하기


	//without if constexpr
	//		private에 위치한 멤버 타입이 늘어나면 늘어날 수록 더 괴로워진다

	class MyClass
	{
	private:
		int a;
		float b;
		std::string c;
		std::vector<int> d;
	public:
		template <std::size_t N>
		auto get();
	};

	template <>
	auto MyClass::get<0>(){	return a;}

	template <>
	auto MyClass::get<1>(){	return b;}

	template <>
	auto MyClass::get<2>(){	return c;}

	template <>
	auto MyClass::get<3>(){	return d;}

	//with if constexpr

	class MyClass
	{
	private:
		int a;
		float b;
		std::string c;
		std::vector<int> d;
	public:
		template <std::size_t N>
		constexpr auto get()
		{
			if constexpr (N == 0) return a;
			else if constexpr (N == 1) return b;
			else if constexpr (N == 2) return c;
			else if constexpr (N == 3) return d;
		}
	};

