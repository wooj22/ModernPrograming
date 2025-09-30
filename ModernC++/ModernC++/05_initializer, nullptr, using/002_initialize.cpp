//초기화 종류 --------------------------------------------------------------

#include <iostream>
using namespace std;

int main()
{

}

// 0 초기화 (기본값)
//		0 초기화는 변수를 암시적으로 형식으로 변환된 0으로 설정하는 것입니다.
// 
//		숫자 변수는	0(또는 0.0 또는 0.0000000000 등)으로 초기화됩니다.
//		char 변수는	'\0'로 초기화됩니다.
//		포인터는		nullptr로 초기화됩니다.
//		배열, POD 클래스, 구조체 및 공용 구조체에는 해당 멤버가 0 값으로 초기화됩니다.

struct my_struct {
	int i;
	char c;
};

int g;									// zero-initialized to 0

int main() {
	static float f1;					// zero-initialized to 0.000000000

	double d{};							// zero-initialized to 0.00000000000000000
	int* ptr{};							// initialized to nullptr
	char s_array[3]{ 'a', 'b' };		// the third char is initialized to '\0'
	int int_array[5] = { 8, 9, 10 };	// the fourth and fifth ints are initialized to 0

	my_struct a_struct{};				// i = 0, c = '\0'
}

//기본 초기화
//	기본 생성자를 사용하는 클래스, 구조체 및 공용 구조체에 대한 기본 초기화입니다.
//	초기화 식이 없거나 new 키워드를 사용하여 '기본 생성자'를 호출할 수 있습니다.

int main() {
	MyClass mc1;
	MyClass* mc3 = new MyClass;
}

//상수 변수의 기본 초기화
//		상수 변수는 이니셜라이저와 함께 선언해야 합니다.

class MyClass {
	int a;
};

int main() 
{
	//const int i2;		// compiler error C2734: const object must be initialized if not extern
	//const char c2;	// same error
	const MyClass mc1;	// compiler error C4269: 'const automatic data initialized with compiler generated default constructor produces unreliable results
}

//정적 변수의 기본 초기화
//		이니셜라이저 없이 선언된 정적 변수는 '0으로 초기화'됩니다.

class MyClass {
private:
	int m_int;
	char m_char;
};

int main() {
	static int int1;		// 0
	static char char1;		// '\0'
	static bool bool1;		// false
	static MyClass mc1;     // {0, '\0'}
}

//값 초기화
//		명명된 값이 빈 중괄호 초기화를 사용하여 초기화됩니다.
//		익명의 임시 개체가 빈 괄호나 중괄호를 사용하여 초기화됩니다.
//		객체가 키워드와 빈 괄호 또는 중괄호를 사용하여 new 초기화됩니다.

class BaseClass {
private:
	int m_int;
};

int main() {
	BaseClass bc{};						// class is initialized
	BaseClass* bc2 = new BaseClass();	// class is initialized, m_int value is 0
	int int_arr[3]{};					// value of all members is 0
	int a{};							// value of a is 0
	double b{};							// value of b is 0.00000000000000000


//복사 초기화
//		복사 초기화는 하나의 개체를 다른 개체로 초기화하는 것입니다

#include <iostream>
using namespace std;

class MyClass {
public:
	MyClass(int myInt) {}
	void set_int(int myInt) { m_int = myInt; }
	int get_int() const { return m_int; }
private:
	int m_int = 7;				// copy initialization of m_int

};

class MyException : public exception {};

int main() {
	int i = 5;					// copy initialization of i
	MyClass mc1{ i };
	MyClass mc2 = mc1;			// copy initialization of mc2 from mc1
	MyClass mc1.set_int(i);		// copy initialization of parameter from i
	int i2 = mc2.get_int();		// copy initialization of i2 from return value of get_int()

	try {
		throw MyException();
	}
	catch (MyException ex) {	// copy initialization of ex
		cout << ex.what();
	}
}

//직접 초기화
//		직접 초기화는(비어 있지 않은) 중괄호 또는 괄호를 사용한 초기화입니다.
//		복사 초기화와는 달리 명시적 생성자를 호출할 수 있습니다. 

class BaseClass {
public:
	BaseClass(int n) :m_int(n) {} // m_int is direct initialized
private:
	int m_int;
};

class DerivedClass : public BaseClass {
public:
	// BaseClass and m_char are direct initialized
	DerivedClass(int n, char c) : BaseClass(n), m_char(c) {}
private:
	char m_char;
};

int main() {
	BaseClass bc1(5);
	DerivedClass dc1{ 1, 'c' };
	BaseClass* bc2 = new BaseClass(7);
	BaseClass bc3 = static_cast<BaseClass>(dc1);

	int a = 1;
	function<int()> func = [a]() {  return a + 1; }; // a is direct initialized
	int n = func();
}

//목록 초기화
//	목록 초기화는 변수가 중괄호로 묶인 이니셜라이저 목록을 사용하여 초기화될 때 발생합니다.

class MyClass {
public:
	MyClass(int myInt, char myChar) {}
private:
	int m_int{ 3 };
	char m_char;
};

class MyClassConsumer {
public:
	void set_class(MyClass c) {}
	MyClass get_class() { return MyClass{ 0, '\0' }; }
};

struct MyStruct {
	int my_int;
	char my_char;
	MyClass my_class;
};

int main() {
	MyClass mc1{ 1, 'a' };
	MyClass* mc2 = new MyClass{ 2, 'b' };
	MyClass mc3 = { 3, 'c' };

	MyClassConsumer mcc;
	mcc.set_class(MyClass{ 3, 'c' });
	mcc.set_class({ 4, 'd' });

	MyStruct ms1{ 1, 'a', { 2, 'b' } };
}

//집합체 초기화
//	일종의 배열 또는 클래스 형식(대개 구조체 또는 공용 구조체) 목록 초기화
//	중괄호로 묶은 초기화 목록으로 구성되며, 등호가 있을 수도 있고 없을 수도 있습니다.

#include <iostream>
using namespace std;

struct MyAggregate {
	int myInt;
	char myChar;
};

struct MyAggregate2 {
	int myInt;
	char myChar = 'Z'; // member-initializer OK in C++14
};

int main() {
	MyAggregate agg1{ 1, 'c' };
	MyAggregate2 agg2{ 2 };
	cout << "agg1: " << agg1.myChar << ": " << agg1.myInt << endl;
	cout << "agg2: " << agg2.myChar << ": " << agg2.myInt << endl;

	int myArr1[]{ 1, 2, 3, 4 };
	int myArr2[3] = { 5, 6, 7 };
	int myArr3[5] = { 8, 9, 10 };

	cout << "myArr1: ";
	for (int i : myArr1) {
		cout << i << " ";
	}
	cout << endl;

	cout << "myArr3: ";
	for (auto const& i : myArr3) {
		cout << i << " ";
	}
	cout << endl;
}

//공용 구조체 및 구조체 초기화

struct MyStruct {
	int myInt;
	char myChar;
};
union MyUnion {
	int my_int;
	char my_char;
	bool my_bool;
	MyStruct my_struct;
};

int main() {

	MyStruct ms1{ 'a' };            // myInt = 97, myChar = '\0'
	MyStruct ms2{ 1 };              // myInt = 1, myChar = '\0'
	MyStruct ms3{};                 // myInt = 0, myChar = '\0'
	MyStruct ms4{ 1, 'a' };           // myInt = 1, myChar = 'a'
	MyStruct ms5 = { 2, 'b' };      // myInt = 2, myChar = 'b'

	MyUnion mu1{ 'a' };		// my_int = 97, my_char = 'a', my_bool = true, {myInt = 97, myChar = '\0'}
	MyUnion mu2{ 1 };		// my_int = 1, my_char = 'x1', my_bool = true, {myInt = 1, myChar = '\0'}
	MyUnion mu3{};			// my_int = 0, my_char = '\0', my_bool = false, {myInt = 0, myChar = '\0'}
	MyUnion mu4 = mu3;		// my_int = 0, my_char = '\0', my_bool = false, {myInt = 0, myChar = '\0'}
	//MyUnion mu5{ 1, 'a', true };  // compiler error: C2078: too many initializers
	//MyUnion mu6 = 'a';            // compiler error: C2440: cannot convert from 'char' to 'MyUnion'
	//MyUnion mu7 = 1;              // compiler error: C2440: cannot convert from 'int' to 'MyUnion'


}

//집합체가 포함된 집합체 초기화

struct MyStruct {
	int myInt;
	char myChar;
};

int main() {
	int intArr1[2][2]{ { 1, 2 }, { 3, 4 } };
	int intArr3[2][2] = { 1, 2, 3, 4 };
	MyStruct structArr[]{ { 1, 'a' }, { 2, 'b' }, {3, 'c'} };
}


//참조 초기화

int iVar;
long lVar;

int main()
{
	long& LongRef1 = lVar;        // No conversion required.
	long& LongRef2 = iVar;        // Error C2440
	const long& LongRef3 = iVar;  // OK			//rvalue 값 할당

	LongRef1 = 23L;               // Change lVar through a reference.
	LongRef2 = 11L;               // Change iVar through a reference.
	LongRef3 = 11L;               // Error C3892
}

//참조 형식 변수는 다음에서만 이니셜라이저 없이 선언될 수 있습니다.
/*
	함수 선언(프로토타입).
	int func(int&);

	함수 반환 형식 선언.
	int& func(int&);

	참조 형식 클래스 멤버의 선언.
	class c { public:   int& i; };

	명시적으로 지정된 extern 변수의 선언입니다.
	extern int& iVal;
*/