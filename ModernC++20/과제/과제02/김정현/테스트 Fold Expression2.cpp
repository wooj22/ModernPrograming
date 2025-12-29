//가변템플릿 활용 (Fold Expression)
// 
// 임의의 여러 벡터를 전달하면, 각 벡터의 갯수를 출력하는 함수를 작성하세요. 

#include <iostream>
#include <vector>
using namespace std;

//template<typename T>
//void returnsize(const vector<T>& vec)
//{
//	cout << size(vec) << " ";
//}
//
//
////do_many_things 템플릿 작성하기
//template<typename T, typename... Ts>
//void do_many_things(T vector, Ts ... vectors)
//{
//	(returnsize(vector), ..., returnsize(vectors));
//	cout << endl;
//}

template<typename... Ts>
void do_many_things(Ts ... vectors)
{
	((cout << size(vectors) << " "), ...);
	cout << endl;
}

int main() {
	vector<int> v1 = { 1,2 };
	vector<int> v2 = { 1,2,3,4,5 };
	vector<char> v3 = { 'a' };

	do_many_things(v1, v2);				// 2 5
	do_many_things(v1, v2, v3);			// 2 5 1

}
