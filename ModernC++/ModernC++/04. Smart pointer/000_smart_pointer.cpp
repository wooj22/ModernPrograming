//����Ʈ ������(smart pointer)
//		std ���ӽ����̽��� �����ְ� <memory> ������Ͽ� ���� ǥ�� ������
//  
//		C++������ �޸� ����(memory leak)�κ��� ���α׷��� �������� �����ϱ� ���� ����Ʈ �����͸� ����
// 
//		����Ʈ ������(smart pointer)�� ������ó�� �����ϴ� Ŭ���� ���ø�����, 
//		����� ���� �޸𸮸� '�ڵ�����' ������ �ݴϴ� ***

//C++11���ʹ� ������ ���� ���ο� ����Ʈ �����͸� �����Ѵ�.
//		unique_ptr	- ��Ÿ�� ������
//		shared_ptr	- ���� �ڿ� ����
//		weak_ptr	- shared_ptr ����

#include <iostream>
using namespace std;

class Foo {
public:
	Foo() { cout << "����" << endl; }
	~Foo() { cout << "�Ҹ�" << endl; }
};

int main(void)
{
	// �����Ҵ� -------------------------------------
	
	Foo* ptr = new Foo();
	delete ptr;

	// ����Ʈ ������ --------------------------------

	unique_ptr<Foo> sptr(new Foo());				//C++ 11 unique_ptr

	//unique_ptr<Foo> sptr = make_unique<Foo>();	//C++ 14 

	//�������� �ʾƵ� �ڵ����� �Ҹ�ȴ�. ***


	//�� ������ �۵��Ѵ� ***
	cout << "before" << endl;
	{
		unique_ptr<Foo> ptr2 = make_unique<Foo>();
	}
	cout << "After" << endl;

	return 0;
}
