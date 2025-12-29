//템플릿 메타 프로그래밍 (Template Meta programming) 예시

//Ratio(유리수를 오차 없이 표현해 주는 클래스) 로 덧셈을 수행하는 템플릿
//https://modoocode.com/221

#include <iostream>
#include <typeinfo>

template <int X, int Y>
struct GCD {
	static const int value = GCD<Y, X% Y>::value;
};

template <int X>
struct GCD<X, 0> {
	static const int value = X;
};

template <int N, int D = 1>
struct Ratio {
	typedef Ratio<N, D> type;	// 자기자신 this
	static const int num = N;	// 분자
	static const int den = D;	// 분모
};
template <class R1, class R2>
struct _Ratio_add {
	typedef Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den> type;
};

template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};

int main() {
	typedef Ratio<2, 3> rat;
	typedef Ratio<3, 2> rat2;
	typedef Ratio_add<rat, rat2> rat3;	//using rat3 = Ratio_add<rat, rat2>;  //C++11, typedef 대신에 좀 더 직관적인 using 이라는 키워드를 사용 

	std::cout << rat3::num << " / " << rat3::den << std::endl;

	return 0;
}

//모든 사칙연산들을 구현 ------------------------------------

#include <iostream>

template <int X, int Y>
struct GCD {
	static const int value = GCD<Y, X% Y>::value;
};

template <int X>
struct GCD<X, 0> {
	static const int value = X;
};

template <int N, int D = 1>
struct Ratio {
private:
	const static int _gcd = GCD<N, D>::value;

public:
	typedef Ratio<N / _gcd, D / _gcd> type;
	static const int num = N / _gcd;
	static const int den = D / _gcd;
};
template <class R1, class R2>
struct _Ratio_add {
	using type = Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den>;
};

template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_subtract {
	using type = Ratio<R1::num* R2::den - R2::num * R1::den, R1::den* R2::den>;
};

template <class R1, class R2>
struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_multiply {
	using type = Ratio<R1::num* R2::num, R1::den* R2::den>;
};

template <class R1, class R2>
struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_divide {
	using type = Ratio<R1::num* R2::den, R1::den* R2::num>;
};

template <class R1, class R2>
struct Ratio_divide : _Ratio_divide<R1, R2>::type {};

int main() {
	using r1 = Ratio<2, 3>;
	using r2 = Ratio<3, 2>;

	using r3 = Ratio_add<r1, r2>;
	std::cout << "2/3 + 3/2 = " << r3::num << " / " << r3::den << std::endl;

	using r4 = Ratio_multiply<r1, r3>;
	std::cout << "13 / 6 * 2 /3 = " << r4::num << " / " << r4::den << std::endl;
}


/*
//의존타입
//
//  템플릿 인자에 따라서 어떠한 타입이 달라질 수 있는 경우.  
//	의존타입의 경우 typename 키워드를 붙여서 그것이 타입이라는 것을 알려주어야 한다.
//  이유, 컴파일러는 어떤 식별자를 보았을 때 기본으로 '값' 이라고 생각합니다

	#include <iostream>

	template <int N>
	struct INT {
		static const int num = N;
	};

	template <typename a, typename b>
	struct add {
		typedef INT<a::num + b::num> result;
	};

	template <typename a, typename b>
	struct divide {
		typedef INT<a::num / b::num> result;
	};

	using one = INT<1>;
	using two = INT<2>;
	using three = INT<3>;

	template <typename N, typename d>
	struct check_div {
		// result 중에서 한 개라도 true 면 전체가 true
		static const bool result = (N::num % d::num == 0) ||
			check_div<N, typename add<d, one>::result>::result;
	};

	template <typename N>
	struct _is_prime {
		static const bool result = !check_div<N, two>::result;
	};

	template <>
	struct _is_prime<two> {
		static const bool result = true;
	};

	template <>
	struct _is_prime<three> {
		static const bool result = true;
	};

	template <typename N>
	struct check_div<N, typename divide<N, two>::result> {
		static const bool result = (N::num % (N::num / 2) == 0);
	};

	template <int N>
	struct is_prime {
		static const bool result = _is_prime<INT<N>>::result;
	};

	int main() {
		std::cout << std::boolalpha;
		std::cout << "Is  2 prime ? :: " << is_prime<2>::result << std::endl;
		std::cout << "Is 10 prime ? :: " << is_prime<10>::result << std::endl;
		std::cout << "Is 11 prime ? :: " << is_prime<11>::result << std::endl;
		std::cout << "Is 61 prime ? :: " << is_prime<61>::result << std::endl;
	}

*/


//단위(Unit) 라이브러리 
// 
//	단위가 맞지 않는 연산을 수행하는 코드가 있다면, 아예 컴파일 시에 오류를 발생시켜 버리는 것.
//	컴파일타임에 오류를 확인하는 안전한 코드를 작성한다.
//
//	값 + 물리적 단위(m, s, kg, rad 등)를 타입 수준에서 묶어 잘못된 계산을 컴파일 타임에 차단하는 라이브러리
//	핵심 철학은 하나입니다.
//	“단위 오류는 런타임 버그가 아니라 컴파일 에러여야 한다.”
//
//	ex) std::chrono , C++23 표준: std::units (공식 단위 라이브러리가 도입)
//
//	게임 / 엔진 개발에서 특히 중요한 이유 - 흔한 버그 해결
//		degrees ↔ radians 혼용
//		frame time(ms) ↔ physics step(s)
//		world unit ↔ meter 혼동


//타입을 알아서 추측해라!  auto 키워드 활용.
/*
	#include <iostream>
	#include <typeinfo>

	int sum(int a, int b) { return a + b; }

	class SomeClass {
		int data;
	public:
		SomeClass(int d) : data(d) {}
		SomeClass(const SomeClass& s) : data(s.data) {}
	};

	int main() {
		auto c = sum(1, 2);			// 함수 리턴 타입으로 부터 int 라고 추측 가능
		auto num = 1.0 + 2.0;		// double 로 추측 가능!

		SomeClass some(10);
		auto some2 = some;

		auto some3(10);				// SomeClass 객체를 만들까요?

		std::cout << "c 의 타입은? :: " << typeid(c).name() << std::endl;
		std::cout << "num 의 타입은? :: " << typeid(num).name() << std::endl;
		std::cout << "some2 의 타입은? :: " << typeid(some2).name() << std::endl;
		std::cout << "some3 의 타입은? :: " << typeid(some3).name() << std::endl;
	}
*/


//템플릿으로 라이브러리 구축
/*
	#include <iostream>
	#include <typeinfo>

	template <int X, int Y>
	struct GCD {
		static const int value = GCD<Y, X% Y>::value;
	};

	template <int X>
	struct GCD<X, 0> {
		static const int value = X;
	};

	template <int N, int D = 1>
	struct Ratio {
	private:
		const static int _gcd = GCD<N, D>::value;

	public:
		typedef Ratio<N / _gcd, D / _gcd> type;
		static const int num = N / _gcd;
		static const int den = D / _gcd;
	};
	template <class R1, class R2>
	struct _Ratio_add {
		using type = Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den>;
	};

	template <class R1, class R2>
	struct Ratio_add : _Ratio_add<R1, R2>::type {};

	template <class R1, class R2>
	struct _Ratio_subtract {
		using type = Ratio<R1::num* R2::den - R2::num * R1::den, R1::den* R2::den>;
	};

	template <class R1, class R2>
	struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};

	template <class R1, class R2>
	struct _Ratio_multiply {
		using type = Ratio<R1::num* R2::num, R1::den* R2::den>;
	};

	template <class R1, class R2>
	struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};

	template <class R1, class R2>
	struct _Ratio_divide {
		using type = Ratio<R1::num* R2::den, R1::den* R2::num>;
	};

	template <class R1, class R2>
	struct Ratio_divide : _Ratio_divide<R1, R2>::type {};

	template <typename U, typename V, typename W>
	struct Dim {
		using M = U;
		using L = V;
		using T = W;

		using type = Dim<M, L, T>;
	};

	template <typename U, typename V>
	struct add_dim_ {
		typedef Dim<
			typename Ratio_add<typename U::M, typename V::M>::type,
			typename Ratio_add<typename U::L, typename V::L>::type,
			typename Ratio_add<typename U::T, typename V::T>::type>
			type;
	};

	template <typename U, typename V>
	struct subtract_dim_ {
		typedef Dim<
			typename Ratio_subtract<typename U::M, typename V::M>::type,
			typename Ratio_subtract<typename U::L, typename V::L>::type,
			typename Ratio_subtract<typename U::T, typename V::T>::type>
			type;
	};

	template <typename T, typename D>
	struct quantity {
		T q;
		using dim_type = D;

		quantity operator+(quantity<T, D> quant) {
			return quantity<T, D>(q + quant.q);
		}

		quantity operator-(quantity<T, D> quant) {
			return quantity<T, D>(q - quant.q);
		}

		template <typename D2>
		quantity<T, typename add_dim_<D, D2>::type> operator*(quantity<T, D2> quant) {
			return quantity<T, typename add_dim_<D, D2>::type>(q * quant.q);
		}

		template <typename D2>
		quantity<T, typename subtract_dim_<D, D2>::type> operator/(
			quantity<T, D2> quant) {
			return quantity<T, typename subtract_dim_<D, D2>::type>(q / quant.q);
		}

		// Scalar multiplication and division
		quantity<T, D> operator*(T scalar) { return quantity<T, D>(q * scalar); }

		quantity<T, D> operator/(T scalar) { return quantity<T, D>(q / scalar); }

		quantity(T q) : q(q) {}
	};

	template <typename T, typename D>
	std::ostream& operator<<(std::ostream& out, const quantity<T, D>& q) {
		out << q.q << "kg^" << D::M::num / D::M::den << "m^" << D::L::num / D::L::den
			<< "s^" << D::T::num / D::T::den;

		return out;
	}

	int main() {
		using one = Ratio<1, 1>;
		using zero = Ratio<0, 1>;

		quantity<double, Dim<one, zero, zero>> kg(2);
		quantity<double, Dim<zero, one, zero>> meter(3);
		quantity<double, Dim<zero, zero, one>> second(1);

		// F 의 타입은 굳이 알 필요 없다!
		auto F = kg * meter / (second * second);
		std::cout << "2 kg 물체를 3m/s^2 의 가속도로 밀기 위한 힘의 크기는? " << F
			<< std::endl;
	}
*/