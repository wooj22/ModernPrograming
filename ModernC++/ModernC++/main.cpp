
//---------------------------------------------------------------------------------
// array �迭�� �����ؼ� �迭�� ���� ���Ϸ��� �մϴ�. 
// error�� ������? ��� �����ϸ� �ɱ��?

#include <iostream>
#include <array>
#include <numeric>

int sumArray(int arr[])		// ��ǻ� int sumArray(int * arr)
{
	int sum = 0;

	// �Լ��� �Ű������δ� �迭 Ÿ���� �ƴ�, �迭 ������(int*)�� ���޵ǹǷ� 
	// ���� ��� for������ �迭�� size�� �� �� ��� ������ �߻��Ѵ�.
	for (const auto& number : arr)		// error
		sum += number;

	return sum;
}

// �ذ��� 1. �迭�� size�� �Բ� �޾Ƽ� �Ϲ� for������ ó��
// �ذ��� 2. ���ø����� �迭 ���� ���� T(&)[N]
//			  �Լ��� �迭�� ������ �ް� ������ Ÿ�ӿ� �迭 ũ�⸦ �ڵ� �߷��Ѵ�. -> ���� ��� for�� ��� ����
template<class T, size_t N>
int sumArrayTemplate(T(&arr)[N])
{
	int sum = 0;
	for (const auto& number : arr)
		sum += number;

	return sum;
}


int main()
{
	int arr[5] = { 9, 7, 5, 3, 1 };
	std::cout << sumArray(arr);
	std::cout << sumArrayTemplate(arr);

	// �ذ��� 3. std::array
	std::array<int, 5> arr2 = { 9, 7, 5, 3, 1 };
	int sum = std::accumulate(arr2.begin(), arr2.end(), 0);
	std::cout << sum;

	return 0;
}


//---------------------------------------------------------------------------------
//������� for ���� ����ؼ� �迭�� ��Ҹ� 1�� ���ϴ� �ڵ带 �ۼ� �ϼ���.
#include <iostream>
int main()
{
	int buff[10] = { 1,2,3,4,5 };

	//code
	for (auto& b : buff) b++;

	for (auto e : buff) std::cout << e << " "; std::cout << "\n";

	return 0;
}


//---------------------------------------------------------------------------------
// B Ŭ�������� �˻��ؼ� �´ٸ� ��� ���� ����ϴ� �ڵ带 �ۼ��ϼ���.
#include <iostream>

struct A { virtual void vf() {} };
struct B : public A { int m = 100; };

void memberPrint(A* a)
{
	B* bptr = dynamic_cast<B*>(a);
	if (bptr) std::cout << bptr->m;
}

int main() {
	A a;
	B b;
	memberPrint(&a);
	memberPrint(&b);
}
