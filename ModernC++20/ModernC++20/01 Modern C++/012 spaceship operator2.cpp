/*

3중 비교 연산자 구현 방식 ***

비교 범주(comparison category)
비교 범주는 3가지 성질의 성립 여부를 체크해야 합니다.

	관계 연산자 성질
		T는 여섯가지 비교 연산자(== , != , <, <= , >, >= )를 모두 지원해야 합니다.

	동치(equivalent) 성질
		T의 객체 A와 B가 동치일 때는 f(A) 와 f(B)의 결과도 동일 해야 합니다.
		f는 전달받은 인수를 읽기 전용으로 사용한다고 가정합니다.	즉 동치인 값은 구별 할 수 없습니다.

	비교 가능 성질
		T의 모든 값은 비교 가능 해야 합니다.
		A와 B에 대해서 A < B, A == B, A > B 중에 하나가 참이어야 합니다.
		예를 들어 부동소수점은 Nan을 가질 수 있는데 이 값은 비교 가능 성질을 충족하지 못합니다.


	비교 범주 성질			std::strong_ordering  std::weak_ordering  std::partial_ordering
	관계 연산자 성질			성립                  성립	               성립
	비교 가능 성질			성립                  성립
	동치(equivalent)성질		성립


	특징						strong_ordering		weak_ordering				partial_ordering
	비교 가능성				항상 비교 가능		항상 비교 가능				일부 비교 불가능한 경우 가능
	대칭성					항상 대칭적			대칭적 (동등성 포함)			대칭적이거나 비교 불가능 가능
	동등성(equivalence)		엄격한 동일성(==)		동등성(equivalence) 지원		동등성 및 비교 불가능
	결정성(deterministic)	항상 결정적			항상 결정적					비교 불가능한 경우 포함
	예시						숫자 비교			대소문자를 무시한 문자열		부동소수점(NaN 포함) 비교


3중 비교 연산자 리턴 값

	3중 비교 연산자는 문맥에 따라서 
	std::strong_ordering, std::weak_ordering, std::partial_ordering 를 리턴합니다.
	(예를 들어 객체가 가지고 있는 변수들이 비교 범주를 얼마나 충족하느냐에 따라서 달라짐)

	3종류의 객체들의 구현내용을 확인해 보면 다음과 같은 단순한 구조로 되어 있습니다.

	구조체이며 _Compare_t(signed char) 형식의 `_Value`라는 하나의 멤버 변수를 가집니다.
	리터럴 0과 비교하는 operator들이 선언되어 있습니다.
	자주 사용하는 불변 객체(less, greater, equal, equivalent, unordered)를 전역 상수로 등록하여 최적화 합니다.
		less : -1
		greater : 1
		equal : 0
		equivalent : 0
		unordered : -128
	_Value에 대한 설정 조건은 첫번째 인자를 기준으로 두번째 인수와의 관계에 따라서 다름과 같이 설정 됩니다.
		작다면 less(-1)
		같으면 equal(0), equivalent(0)
		크다면 greater(1)
		알수 없다면 unordered(-128)

표현식 재작성
c++ 20에서는 표현식 재작성이라는 개념이 적용 됩니다.

	기존 코드	  변경 코드
	a > b         (a <=> b) > 0
	a >= b        (a <=> b) >= 0
	a < b         (a <=> b) < 0
	a <= b        (a <=> b) <= 0


컴파일 시점 비교
컴파일러에 의해서 생성되는 3중 비교 연산자는 constexpr 이므로 
문맥에 따라서 컴파일 시점에 사용 할 수 있습니다.

3중 비교 연산자도 컴파일 시점에 수행 될 수 있습니다.

	struct MyInt {
		int value;
		// 생성자를 constexpr로 지정합니다.
		explicit constexpr MyInt(int val) : value{ val } {}
		auto operator<=>(const MyInt& rhs) const = default;
	};

	int main()
	{
		// 인자를 리터럴로 전달 받았으므로 D1, D2 컴파일 시점에 사용 가능
		constexpr MyInt D1(2017);
		constexpr MyInt D2(2020);

		// operator<=> 수식도 constexpr 이므로 컴파일 시점 사용 가능
		constexpr bool res = (D1 < D2);

		cout << boolalpha;
		cout << "D1 < D2 : " << res << '\n';

		return 0;
	}


어휘순 비교
컴파일러가 생성한 3중 비교 연산자는 어휘순 비교를 사용합니다.
어휘순 비교란 모든 기반 클래스의 모든 비정적(non-static) 멤버들을 선언 순서대로 비교 하는 것을 말합니다.


최적화된 == 연산자와 != 연산자
비교 연산을 할 때 문자열이나 벡터 같은 형식들에 대해서는 최적화할 여지가 있습니다.
전체 비교전에 객체의 길이를 먼저 비교 한 후에 다르다면 false를 리턴하는 최적화를 진행 할 수 있습니다.

*/