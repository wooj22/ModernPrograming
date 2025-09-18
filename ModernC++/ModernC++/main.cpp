#include <iostream>
#include <vector>
using namespace std;

class Player
{
	string name;

public:
	Player() : name("") {}
	Player(string n) : name(n) {}
	void Show() { cout << name << endl; }
};

int main() 
{
	vector<unique_ptr<Player>> v;
	v.push_back(make_unique<Player>("1"));
	v.push_back(make_unique<Player>("2"));
	v.push_back(make_unique<Player>("3"));

	v[0]->Show();
	v[1]->Show();
	v[2]->Show();

	vector<unique_ptr<Player>> v2(3);
	v2[0] = make_unique<Player>("1");
	v2[1] = make_unique<Player>("2");
	v2[2] = make_unique<Player>("3");

	v2[0]->Show();
	v2[1]->Show();
	v2[2]->Show();
}
