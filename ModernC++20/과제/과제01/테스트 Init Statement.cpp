// auto, Init statement, Structured binding 사용하기

#include <iostream>
#include <set>
#include <utility>
using namespace std;

int main()
{
    pair<string, int> itemsToAdd[3]{ {"hello", 1}, { "world", 2 }, { "world", 2 } };
    set<pair<string, int>> mySet;

    // itemsToAdd 배열의 값들을 mySet에 추가(insert)하고, 
    // 성공적으로 추가되었는지 확인 출력하는 코드를 작성하라.

	for (const auto& item : itemsToAdd) {
		auto [iter, inserted] = mySet.insert(item);
		if (inserted) {
			cout << "Inserted: (" << item.first << ", " << item.second << ")\n";
		}
		else {
			cout << "Duplicate not inserted: (" << item.first << ", " << item.second << ")\n";
		}
	}
}

