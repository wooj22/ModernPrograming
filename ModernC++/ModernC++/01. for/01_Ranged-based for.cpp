//범위 기반 for문 (ranged-based for statement)
//		알아서 처음부터 끝까지 순회를 해주는 반복문 //C++11 
//		C# 에서의 foreach

#include <iostream>
#include <vector>
using namespace std;

void main()
{
	int arr[10] = { 1, 2, 3, 4, 5 };
	
	for (int i = 0; i < 10; ++i)		//기존의 for문
	{
		cout << arr[i] << endl;
	}

	for (int elem : arr)				//범위 기반 for 문 
	{
		cout << elem << endl;
	}

	//문제) 범위 기반 for 문  //배열의 맴버가 각각 자동으로 할당됨
	int arr[] = { 1, 2, 3, 4 };
	for (int num : arr)					
		std::cout << num << ' ';
	std::cout << '\n';


	//문제) 범위기반 for문으로 출력해보세요.-----------------
	int fibonacci[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };

	for (int number : fibonacci)
		std::cout << number << ' ';
	std::cout << std::endl;

	//auto 키워드를 사용해서 C++이 자료형을 추론하도록 하는 것이 이상적이다.
	for (auto number : fibonacci)
		std::cout << number << ' ';
	std::cout << std::endl;


	//성능상의 이유로 ranged-based for 루프에서 참조 또는 const 참조를 사용하는 게 좋다. ***

	int array[5] = { 9, 7, 5, 3, 1 };
	for (auto element : array)
		std::cout << element << ' ';

	for (auto& element : array)			//배열 요소에 대한 참조이므로 값이 복사되지 않는다
		std::cout << element << ' ';

	for (const auto& element : array)   //읽기 전용으로 사용하려면 const
		std::cout << element << ' ';

	//참조, const & 를 사용하면
	//		복사비용이 들지 않고 배열의 값을 이용할 수 있고, 
	//		배열의 값을 변경하지 않는 걸 보장할 수 있게 된다.



	//문제) 일반적인 for 문 ------------------------------------
	//	   범위기반 for 문으로 수정하세요. ( &, const )

	const int num = 5;
	int scores[num] = { 84, 92, 76, 81, 56 };  //최댓값 출력하기

	int maxScore = 0;
	for (int i = 0; i < num; ++i)
		if (scores[i] > maxScore) 
			maxScore = scores[i];
	std::cout << "The best score was " << maxScore << '\n';
	
	
	//int maxScore = 0;
	//for (const auto& score : scores)       //const auto&
	//	if (score > maxScore) 
	//		maxScore = score;
	//std::cout << "The best score was " << maxScore << '\n';

}
