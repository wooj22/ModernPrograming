//optional  //C++ 17
//		해당 객체는 값을 리턴할 때 값이 없음을 표현하기에 유용

#include <iostream>
#include <vector>
#include <optional>
using namespace std;

class test_optional
{
private:
	vector<int> data_{ 10, 20, 30 };

public:

	int getByIndex1(int index)				//기존 표현 방식
	{
		if (index < 0 || data_.size() <= index) {
			return -1;
		}
		return data_[index];
	}

	optional<int> getByIndex2(int index)	//optional 로 바꿔 처리해 보세요.
	{
		if (index < 0 || data_.size() <= index)	{
			return std::nullopt;			//
		}
		return data_[index];
	}
};

int main(int argc, char* argv[])
{
	test_optional test;

	int ret1 = test.getByIndex1(3);
	if (ret1 == -1)								//임의값을 정해야 한다.
	{
		cout << "data is not found " << endl;
	}

	optional<int> ret2 = test.getByIndex2(3);
	if (!ret2.has_value()) {					//has_value()
		cout << "data is not found " << endl;
	}

	optional<int> ret3 = test.getByIndex2(4);
	if (ret3 == std::nullopt) {					//std::nullopt
		cout << "data is not found " << endl;
	}

	optional<int> ret4 = test.getByIndex2(1);
	if (ret4.has_value()) {
		cout << ret4.value() << endl;
	}

	//auto ret4 = test.getByIndex2(1);
	//if (ret4) cout << ret4.value() << endl;
	
}