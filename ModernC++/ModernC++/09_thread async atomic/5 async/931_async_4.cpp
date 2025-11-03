//async는 
//		future 로 받으면, 따로 명시하지 않고 '자동 대기'
//		future 로 받지 않으면, 동기적으로 실행 ***

#include <iostream>
#include <thread>
#include <future>
using namespace std;

// async는 따로 명시하지 않고 자동 대기 -----------------------------------------------
//		thread와 async의 중요한 차이점은 소멸자가 끝나는 것을 알아서 대기해준다는 것이다.
//		thread는 join으로 대기. async는 따로 명시하지 않고 '자동 대기'이다.
//		이걸 thread를 쓸 때와 async를 쓸 때는 결과가 다르다. 작동 방식이 내부적으로 다르기 때문이다.

int main()
{

	auto f1 = std::async([] {
		cout << "async1 start" << endl;
		this_thread::sleep_for(chrono::seconds(2));
		cout << "asnyc1 end" << endl;
		});

	auto f2 = std::async([] {
		cout << "async2 start" << endl;
		this_thread::sleep_for(chrono::seconds(1));
		cout << "async2 end" << endl;
		});

	cout << "Main function" << endl;
}

// async (future 제거 했을 경우) -----------------------------------------------------
//		그냥 순서대로, 동기적으로 실행 ***

int main()
{
	// async는 future로 받지 않을 경우 sequential이라 생각하고 순서대로 진행이 된다. (주의할 것) ***

	std::async([] {
		cout << "async1 start" << endl;
		this_thread::sleep_for(chrono::seconds(2));
		cout << "asnyc1 end" << endl;
		});

	std::async([] {
		cout << "async2 start" << endl;
		this_thread::sleep_for(chrono::seconds(1));
		cout << "async2 end" << endl;
		});

	cout << "Main function" << endl;
}
