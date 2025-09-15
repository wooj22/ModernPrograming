#include <iostream>
using namespace std;

void TestFunc(int) {}

void main(void)
{
	//auto ------------------------------------------  
	//auto Ű���带 ����ϸ� �ʱ갪�� ���Ŀ� ���� �����ϴ� �ν��Ͻ�(����)�� ������ '�ڵ�'���� �����ȴ�

	//�ʱ�ȭ -----------------------------------------
	int a = 1;
	int a(1);				//C++
	int a{ 1 };				//C++11
	int b(a);				//copy
	int(10);				//�̸����� �ν��Ͻ�

	auto c(a);				// int
	//auto c = a;

	int x = int();			// x is an int, initialized to 0
	auto auto_x = x;


	//auto Ű����� �����Ϳ� �����ڸ� ���� �� �ִ�. ----------------------------------------------
	int n = 1.2;
	auto& b = n;			// &, * �� cv �״�� ����. 
	auto* c = &b;			// �����ʹ� * ������ �ʾƵ� �ν�, �����ڴ� �ٿ��߸� ������ �ν�


	// ����)  Widget Ŭ���� ��ü�� auto �����ͳ� ������ �޾� type Ȯ���ϱ�.

	class Widget {
	public:
		void Fn() {}
	};

	Widget x;

	// �Ʒ� ����� �ڷ����� �߷��� ������.

	auto o = x;				// (  )				//Widget  

	auto* a1 = &x;			// (  )				//Widget* 
	auto  a2 = &x;			// (  )				//Widget* 
	a2->Fn();

	auto& r1 = x;			// (  )				//Widget&   //������ �������� �����ؾ� ��. 
	auto r2 = x;			// (  )				//Widget  	
	r1.Fn();



	//Ÿ�� �߷�(type inference)-----------------------------------------------------------------
	//1. auto ��쿡��				-> &, const volatile ���� �߰� ������ ���� �ʴ´�.

	const int& crx = x;
	auto auto_crx1 = crx;				//???
	//const auto& auto_crx2 = crx;
	volatile int vx = 1024;
	auto avx = vx;						//???
	//volatile auto vavx = vx;

	//auto�� ������ ���� ��쿡��		-> *, const �� �� �о���δ� ***
	int i = 40;
	const int* pi = &i;
	auto p = pi;

	//Ÿ�� �߷�(type inference)-----------------------------------------------------------------
	//2. auto& ��쿡��				-> & ����, const �д´�. ������ ���� const ����.

	const int c = 0;
	auto& rc = c;						//??? //const int&


	//Ÿ�� �߷�(type inference)-----------------------------------------------------------------
	//3. auto&& ��쿡�� 				-> �������� &�� �������� &&�� �޴´� (���� ����)

	int d = 10;
	//auto& r = d;						//int&

	auto&& r1 = 5;						//int&&		//������
	auto&& r2 = d;						//int&		//������
	auto&& r3 = std::move(d);			//int&&		

	// rvalue ������ ���� ������ �Ʒ� ����


//r-value ���� -------------------------------------------------

	int d = 10;
	int& r = d;				//����
	int&& r1 = 5;			//�ӽð�ü�� ���� ����, ���
	int&& r2 = r;			//error //move() ���


///���� ����(universal reference)
//		���޵Ǵ� �Ű������� ���� �� �� �Ǵ� ���� �� ������ �۵��� �� �ִ�.
//		���� �� ������ ���� ������ ���� ū ���̴� ����(type)�� �߷��ϴ����� ���δ�.

	void f(Widget&& param);				//-- 1 ������ ����

	Widget&& var1 = Widget();			//-- 2 ������ ����

	auto&& var2 = var1;					//-- 3 ���� ����		auto&&

	template<typename T>
	void f(std::vector<T>&& param);		//-- 4 ������ ����

	template<typename T>
	void f(T&& param);					//-- 5 ���� ����		T&&


}

//auto Ȱ�� --------------------------------------------------------------------------------

	//1. �Լ��� ���� �� ���ϰ� ��� 

void(*pfTest)(int) = TestFunc;		//�Լ������� ��ü

auto pfTest(TestFunc);				//�� �ڵ� ����
//auto pfTest = TestFunc;	
//auto* pfTest = TestFunc;


//2. �迭�̳� ���� ó���� �� ���ϰ� ��� 

int buffer[5] = { 0,1,2,3,4 };

for (auto i : buffer)				//�� �ڵ� ���� //������� for��
{
	cout << i << endl;
}

//3. �Ʒ��� ���� for������ auto�� ����� �ڷ����� �߷��� ����� �� �ִ�.
auto arr = { 1, 2, 3, 4 };				// arr�� �ڷ�����?

for (auto number : arr)				// ������� for��
std::cout << number << '\n';

// �Լ����� auto ��� -----------------------------------------------------------------------

	//�Լ��� ��ȯ ��
	//	������ �Լ��� ��ȯ ������ �ʱ�ȭ �� ���� ��� ����  //���� �� ������ �ʱ�ȭ�� ���� �۵�

int add(int x, int y) { return x + y; }
auto sum = add(5, 6);

//C++ 14���� �Լ��� ���� Ÿ�� �߷� ***
//	C++ 14�� auto Ű���尡 �Լ��� ��ȯ Ÿ���� �ڵ����� �߷��� �� �ֵ��� Ȯ��Ǿ���.
auto Add(int x, int y) { return x + y; }		//�ٸ� �����ؼ� ���, ���� ���

//�Ű� ���� ?
//	auto Ű����� �Լ� �Ű� ������ �Բ� ����� �� ����.	***

void addAndPrint(auto x, auto y) { std::cout << x + y; }


// ����ü,Ŭ�������� auto ��� ---------------------------------------------------------------

	//auto Ű����� ����ü�� ����ü, Ŭ������ �����ϴ�.

class MyClass {
public:
	int n = 0;
};

void main() {
	auto x = MyClass();     //MyClass
}

//��� ������?
//		����ü�� Ŭ������ ��� �����δ� ��� �Ұ�  *** 
//		(�ش� ��ü �ڷ��� ũ�⸦ �𸣱� ����)

class MyClass {
public:
	auto n = 0;
};


// ���ٽĿ� ���� auto ��� -----------------------------------------------------------------------

#include <iostream>
using namespace std;

int main()
{
	auto test1 = [](int* a)->int& {return *a; };			//int& ����
	auto test2 = [](int* a) { return *a; };					//int ����

	int* p = nullptr;
	auto f1 = test1(p);			// f1�� �ڷ����� ???
	auto& f2 = test1(p);

	//�Լ�
	//1. ������ ���� ��
	//				�Լ��� ���ڰ� ���� ��ȣ�� -> �� ������ְ� �����ڷ��� &�� �ٿ���
	//2. ������ �ܿ���
	//				�ڷ����� ������� �ʾƵ�, return���� �������� auto �ڵ����� �����ڷ����� �Ǵ���

	return 0;
}


//auto ���� �Լ��� �Ķ���Ϳ� auto�� ����� �� �ִ�. (�Ϲ� �Լ��鿡���� �Ķ���Ϳ� auto�� ������) ***
{
	// generic lambda
	auto func = [](auto x, auto y) {return x + y; };
	cout << func(1.1, 5) << "  " << func(3.7, 23.1) << '\n';

	//���׸� ����, ���ø� ���� ����
