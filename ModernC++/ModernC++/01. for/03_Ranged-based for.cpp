#include <iostream>
using namespace std;

//범위기반 for 문 테스트

void main()
{
	// 주의 : 배열을 초기화 하고 싶을 때
	int buff[10] = { 1,2,3,4,5 };

	for (auto x : buff) x = 0;		//???

	for (auto& x : buff) x = 0;		//참조를 통해 그 값을 정확히 가리키게 해야 합니다

	for (size_t i = 0; i < 10; i++)	std::cout << buff[i] << ' ';
	std::cout << '\n';



	// 포인터로 할당 후 초기화 하려고 합니다.
	int* buff = new int[10];
	for (auto x : buff)		// 포인터에서 사용 불가 //배열의 크기를 알지 못하기 때문 //해결책??
	{
		x = 0;
	}	

	//for (size_t i = 0; i < 10; i++)  //for 문 사용하면 가능  
	//{
	//	buff[i] = i;
	//}

	//범위기반 for 문 사용 하려면  -> std::vector 를 사용
	//std::vector v( buff, buff+10 );
}

//std::vector 를 사용하는 방법 ----------------------------------------
	#include <iostream>
	#include <vector>

	int main() {
		std::vector<int> buff(10); // 원소를 10개 생성
		for (auto x : buff)
			std::cout << x << std::endl;
		return 0;
	}

//포인터를 배열로 강제 변환하는 방법 ----> reinterpret_cast ------------

	#include <iostream>
	int main()
	{
		typedef int Array[5];
		int* buff = new int[5]{1,2,3,4,5};
		//std::cout << buff[0] << std::endl;
		//std::cout << buff[1] << std::endl;

		Array& arr = reinterpret_cast<Array&>(buff);
		int* p = reinterpret_cast<int*>(arr[0]);
		for (size_t i = 0; i < 5; i++) { std::cout << *(p++) << "\n"; }


		for (auto x : reinterpret_cast<Array&>(buff))
		{
			std::cout << x << std::endl;
			//int* p = reinterpret_cast<int*>(x); std::cout << *p << std::endl;
		}

		return 0;
	}
	//reinterpret_cast 로 변환가능, 하지만 메모리 그대로 적용 ( 32비트로 테스트)


/*
	//포인터로 변환된 배열에서 범위 기반 for 루프를 사용할 수 없다. (배열의 크기를 알지 못함)
	//마찬가지로, 동적 배열은 같은 이유로 범위 기반 for 루프와 작동하지 않는다.

	#include <iostream>
	int sumArray(int array[])				//포인터 선언이다.
	{
		int sum = 0;
		for (const auto& number : array)	//error
			sum += number;
		return sum;
	}

	int main()
	{
		int array[5] = { 9, 7, 5, 3, 1 };
		std::cout << sumArray(array);
		return 0;
	}

	// 해결 방법은? -------------------- 

	#include <iostream>
	#include <vector>
	using namespace std;

	int sumArray(vector<int> v)				//vector
	{
		int sum = 0;
		for (const auto& number : v)
			sum += number;
		return sum;
	}

	int main()
	{
		vector<int> v = { 9, 7, 5, 3, 1 };	//vector
		std::cout << sumArray(v);
		return 0;
	}
*/


//범위 기반 for 문을 사용하려면 -----------------------------------------------------------------
// 
//		begin 함수와 end 함수, 그리고 증가 연산자가 구현이 되어있어야 합니다. ***
// 
//		기본 컨테이너들(vector, list...) 에 대해선 이미 구현이 되어있지만
//		사용자 정의 타입에서는 구현을 해주셔야 사용 가능합니다.
//		기본적으로 begin, end, 그리고 증가 연산자를 구현하여야 합니다.
		
	#include <iostream>
	#include <vector>
	using namespace std;

	struct Node {
		int num;
		Node* next;
	};

	class Mylist {
	private:
		Node* head;
		Node* tail;
		Node* now;

	public:
		Node* begin() { return head; }
		Node* end() { return tail; }

		Mylist& operator++() { now = now->next; return *this; };	// 전위증가
		Mylist operator++(int) {								    // 후위증가
			Mylist tmp = *this;
			now = now->next; 
			return tmp; };  
	};

	int main()
	{
		Mylist ls;

		for (const auto e : ls)		//가능하려면 ???
		{
			cout << e.next << " ";
		}
	}

