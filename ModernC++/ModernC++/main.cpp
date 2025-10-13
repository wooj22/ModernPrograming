
//---------------------------------------------------------------------------------
// array 배열을 전달해서 배열의 합을 구하려고 합니다. 
// error의 이유는? 어떻게 수정하면 될까요?

#include <iostream>
#include <array>
#include <numeric>

int sumArray(int arr[])		// 사실상 int sumArray(int * arr)
{
	int sum = 0;

	// 함수의 매개변수로는 배열 타입이 아닌, 배열 포인터(int*)가 전달되므로 
	// 범위 기반 for문에서 배열의 size를 알 수 없어서 에러가 발생한다.
	for (const auto& number : arr)		// error
		sum += number;

	return sum;
}

// 해결방안 1. 배열의 size를 함께 받아서 일반 for문으로 처리
// 해결방안 2. 템플릿으로 배열 참조 전달 T(&)[N]
//			  함수가 배열의 참조를 받고 컴파일 타임에 배열 크기를 자동 추론한다. -> 범위 기반 for문 사용 가능
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

	// 해결방안 3. std::array
	std::array<int, 5> arr2 = { 9, 7, 5, 3, 1 };
	int sum = std::accumulate(arr2.begin(), arr2.end(), 0);
	std::cout << sum;

	return 0;
}


//---------------------------------------------------------------------------------
//범위기반 for 문을 사용해서 배열의 요소를 1씩 더하는 코드를 작성 하세요.
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
// B 클래스인지 검사해서 맞다면 멤버 값을 출력하는 코드를 작성하세요.
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
