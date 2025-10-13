// Manager Class, STL, Smart Pointer 활용하기
// Weapon, Armor, Ring 등 카테고리 별로 구분되는 아이템을 관리하려고 합니다. (상속, 다형성)
// 추가, 삭제, 검색, 출력, 정렬, 합성 기능을 구현하세요.

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

/* Item class */
// member : id, name, level, grade
class Item
{
public:
	int		id = 0;
	string	name = "";
	int		level = 0;
	char	grade = 'A';

	Item(int id, string name, int level, char grade) : id(id), name(name), level(level), grade(grade) {}
	virtual ~Item() {}
};

class Weapon : public Item
{
public:
	int attack = 0;
	Weapon(int id, string name, int level, char grade) : Item(id, name, level, grade) {}
};

class Armor : public Item
{
public:
	int defence = 0;
	Armor(int id, string name, int level, char grade) : Item(id, name, level, grade) {}
};

class Ring : public Item
{
public:
	int magic = 0;
	Ring(int id, string name, int level, char grade) : Item(id, name, level, grade) {}
};

// grade
enum class Grade
{
	S, A, B, C
};

/* ItemManager class */
// 추가, 삭제, 검색, 출력, 정렬, 합성
class ItemManager
{
private:
	vector<shared_ptr<Item>> items;
	int id_counter = 0;

public:
	template<class T, class...Args>
	void AddItem(Args&&...args)
	{
		items.emplace_back(make_shared<T>(forward<Args>(args)...));
		id_counter++;
	}

	void RemoveItemById(int id)
	{
		items.erase(
			remove_if(items.begin(), items.end(),
				[&](auto& item) { return item->id == id; }),
			items.end()
		);
	}

	void RemoveItemByName(const string& name)
	{
		items.erase(
			remove_if(items.begin(), items.end(),
				[&](auto& item) { return item->name == name; }),
			items.end()
		);
	}

	shared_ptr<Item> FindItem(int id)
	{
		auto it = find_if(items.begin(), items.end(),
			[&](auto& item) { return item->id == id; });

		return (it != items.end()) ? *it : nullptr;
	}

	void ShowItems()
	{
		for_each(items.begin(), items.end(), [](auto& a) { cout << a->id << " " << a->name << " " << a->grade << endl; });
		cout << endl;
	}

	void SortingItems()
	{
		sort(items.begin(), items.end(), [](auto& a, auto& b) { return a->name < b->name;   });
	}

	// 같은 등급의 아이템 2개를 합성하여 상위등급의 아이템 하나로 만드는 시스템을 만드세요.
	// 합성후 네임은 재료1을 따르며, 레벨은 1로 초기화되고, 재료가 되는 아이템은 삭제 됩니다.
	void MergeItems(int id1, int id2)
	{
		shared_ptr<Item> item1 = FindItem(id1);
		shared_ptr<Item> item2 = FindItem(id2);

		if (item1 == nullptr || item2 == nullptr || item1->grade != item2->grade)
		{
			cout << "합성 불가." << endl;
			return;
		}

		int		id = id_counter + 1;
		string	name = item1->name;
		int		level = 1;
		char	grade;

		if (item1->grade == 'S')		grade = 'S';
		else if (item1->grade == 'A')	grade = 'S';
		else if (item1->grade == 'B')	grade = 'A';
		else							grade = 'B';

		RemoveItemById(id1);
		RemoveItemById(id2);
		AddItem<Item>(id, name, level, grade);
		cout << "합성 결과 : " << id << ", " << name << ", " << level << ", " << grade << endl;
	}
};


int main() {

	// Item 목록을 만들고, 동적할당 하세요.	
	//	포인터 동적할당	// Item** ItemList = new Item*[N];
	//	동적배열 		// vector<Item*> ItemList;
	//	스마트포인터 		// vector<unique_ptr<Item>> ItemList;

	// ItemManager
	ItemManager itemManager;

	// 아이템 추가
	itemManager.AddItem<Weapon>(1, "단검", 1, 'A');
	itemManager.AddItem<Weapon>(2, "단검", 2, 'A');
	itemManager.AddItem<Armor>(3, "갑옷", 1, 'B');
	itemManager.AddItem<Ring>(4, "반지", 2, 'B');
	itemManager.AddItem<Ring>(5, "반지", 3, 'S');
	itemManager.ShowItems();

	// 단검 아이템 제거
	itemManager.RemoveItemByName("단검");
	itemManager.ShowItems();

	// 아이템 추가
	itemManager.AddItem<Weapon>(6, "단검", 1, 'A');
	itemManager.AddItem<Weapon>(7, "단검", 2, 'B');
	itemManager.AddItem<Armor>(8, "갑옷", 2, 'B');
	itemManager.ShowItems();

	// 정렬
	itemManager.SortingItems();
	itemManager.ShowItems();

	// 합성
	itemManager.MergeItems(7, 8);
	itemManager.ShowItems();
}