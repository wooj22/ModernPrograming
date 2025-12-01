#include <iostream>
#include <fstream>		// ofstream, ifstream  ///C++ 파일 입출력
using namespace std;

struct USERINFO {
	char name[20];
	int age;
};

void main()
{
	USERINFO man = { "홍길동", 20 };

	ofstream fout;
	fout.open("myfile.dat");
	fout << man.name << " " << man.age << endl;		//쓰기 //텍스트
	fout.close();

	USERINFO man2;

	ifstream fin;
	fin.open("myfile.dat");
	if (fin.fail()) { cout << "파일 오픈에 실패했습니다." << endl; return; }

	fin >> man2.name >> man2.age;					//읽기 //텍스트
	fin.close();

	cout << man2.name << " " << man2.age << endl;
}

/*
// 이진파일로 바꿔보자 -----------------------

#include <iostream>
#include <fstream>
using namespace std;

struct USERINFO {
	char name[20];
	int age;
};

void main()
{
	USERINFO man = { "홍길동", 20 };

	ofstream fout;
	fout.open("myfile.dat");

	//fout << man.name << " " << man.age << endl;
	fout.write((char *)&man,sizeof(man));			//쓰기 //바이너리

	fout.close();

	USERINFO man2; // = { "", 10 };

	ifstream fin;
	fin.open("myfile.dat");
	if (fin.fail()) { cout << "파일 오픈에 실패했습니다." << endl; return; }

	//fin >> man2.name >> man2.age;
	fin.read((char*)&man2, sizeof(man));			//읽기 //바이너리
	cout << man2.name << " " << man2.age << endl;

	fin.close();
}
*/