//범위기반 for문 (Range-based for) 에서의 초기화 문 //C++20

#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main()
{
	//범위기반 for문 (Range-based for) 

	vector<int> v = {};
	for (auto e : v = { 1,2,3 }) {
		cout << e << endl;
	}

	//범위기반 for문 (Range-based for) 에서의 초기화 문 //C++20

	for (vector<int> v = { 1,2 }; auto& x : v)
	{
		cout << x << endl;
	}

	//map의 value 를 출력 ( 범위기반 for문 사용 ). 초기화 문으로 변경해보세요. 
	map<int, int> mymap = { {1,1}, {2,2} };

	for (auto&& [first, second] : mymap)		//구조화된 바인딩
	{
		// use first and second
	}

/*
	for (map<int, int> mymap = { {1,1}, {2,2} }; auto&& [first, second] : mymap)
	{
		// use first and second
		cout << second << endl;
	}
*/
}



//초기화문(init - statement)이 편리한 이유
// 
//		지역 변수를 선언·초기화하는 시점을 분기 로직과 밀착시켜, 코드의 범위·가독성·안전성을 크게 높여주기 때문

//1. 변수의 ‘필요한 범위’를 최소화(스코프 제한)

	if (auto it = m.find(key); it != m.end()) {
		use(*it);
	}
	// it 은 여기서 소멸 → 스코프 오염 없음

//2. “찾고 바로 확인” 같은 패턴을 다루기 쉬움
	//map에서 검색 → 있으면 처리
	//파일 열기 → 성공하면 처리
	//lock에서 guard 선언 → 영역 보호
	//unique_ptr / maybe 타입 검사

	if (auto file = std::ifstream(path); file.is_open()) {
		// file 사용
	}

//3. 나중에 ‘초기화를 깜빡’하는 실수를 원천적으로 제거

	if (auto v = compute(); v > 0) {
	}

//4. RAII 사용 시 실무적으로 매우 효율적

	if (std::lock_guard<std::mutex> lock(m); needWork) {
		// lock 보호 영역
	} // 여기서 자동 unlock

//5. 오버헤드를 없애줌 (최적화 친화적)

	//변수의 정확한 생명주기

//6. switch 와도 잘 맞음 (C++17+)

	switch (auto n = getStatus(); n) {
	case 0: ...
	case 1: ...
	}