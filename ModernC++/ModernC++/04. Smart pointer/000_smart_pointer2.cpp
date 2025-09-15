//�޸� ���� ����
//  ù ��°�� �޸𸮸� ����� �Ŀ� �������� ���� ���, �������� ���Ҵ��ϴ� ���.
//  �� ��°�� �߻� ������ ������, �̹� ������ �޸𸮸� �ٽ� �����ϴ� ���

/*
// double free ����
        Data* data = new Data();
        Date* data2 = data;
        delete data;          // data �� ���� : ��� �� ������ �Ҹ���Ѿ���.
        delete data2;         // data2 �� ���� : ���� ��� �� ������ �Ҹ���Ѿ���
*/

//C++ ���� �ڿ��� �����ϴ� ���
//  RAII ���� ***
//      - Resource Acquisition Is Initialization  
//      - �ڿ��� ȹ���� �ʱ�ȭ�� 
//      ���ÿ� �Ҵ�� �޸𸮴� �ڵ����� �����Ǵ� ���� �̿��� ������ ���� - �ڿ� ������ �����ϰ�

#include <iostream>
#include <memory>

class MyString
{
public:
    char* c = nullptr;

    MyString(size_t len) { c = new char[len]; }
    ~MyString() { delete[] c; }                     //RAII ����
};

int main()
{
    // �ݵ�� delete �ʿ�
    {
        char* c = new char[100];
        strcpy_s(c, 14, "Hello, world!");
        //throw 0;  //���� �߻��ϸ� memory leak
        delete[] c;
    }

    //RAII �������� �ٲٸ�, delete ���� ��ü �����Ͽ� ���
    {
        MyString s(100);
        //throw 0;  //���� �߻��ϸ� ��ü �Ҹ�� �Ҹ��� ȣ��
        strcpy_s(s.c, 14, "Hello, world!");
    }

}

