//�Ű������� auto ����ϱ�

//�Ű������� auto ��� �Ұ�, VC++20 ����

//�ڵ����� ���ø� �ۼ� , VC++20

#include <iostream>
using namespace std;

auto add_int(auto t1, auto t2) -> decltype(t1 + t2)
{
	return { t1 + t2 };
}

int main()
{
	//���ø�
	cout << add_int(1.1, 1.1) << endl;

	//����
	auto add = [](auto t1, auto t2) {return t1 + t2; };
	cout << add(1.1, 1.1) << endl;

}
