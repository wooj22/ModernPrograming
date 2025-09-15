//C++ ���� �ڿ��� �����ϴ� ���

//RAII ���� 
//      - Resource Acquisition Is Initialization  
//      - �ڿ��� ȹ���� �ʱ�ȭ�� 
//      ���ÿ� �Ҵ�� �޸𸮴� �ڵ����� �����Ǵ� ���� �̿��� ������ ���� - �ڿ� ������ �����ϰ�

//����Ʈ ������(smart pointer)
//    ������ '��ü' �� ���� �ڽ��� �Ҹ� �� �� �ڽ��� ����Ű�� �ִ� �����͵� ���� delete �ϰ�
//    �Ҹ��ڵ� �ȿ� �� ����� �ڿ��� �����ϴ� ��ƾ


//unique_ptr �� �����غ��� ------------------------------------------------------------
//    Ư�� ��ü�� ������ �������� �ο��ϴ� ������ ��ü

#include <iostream>
#include <memory>

class A             //RAII - �ڿ��� ȹ���� �ʱ�ȭ�� 
{
    int* data;
public:
    A() {
        std::cout << "�ڿ� ȹ����!" << std::endl;
        data = new int[100];
    }
    ~A() {
        std::cout << "�ڿ� ������!" << std::endl;
        delete[] data;
    }
    void some() { std::cout << "�Ϲ� �����Ϳ� �����ϰ� ��밡��!" << std::endl; }
};

class A_SPtr;        //�ڵ����� ������ �����ǵ��� ����Ʈ ������ Ŭ������ �ۼ��ϼ���.

void ex()
{
    A* p = new A();
    delete p;                       //delete �ʿ��ϴ�.


    //A_SPtr ���
    A_SPtr sp(new A());           //�����Ͽ� �־��ָ�, ��ü�Ҹ�� �ڵ� ���� ***
    //A_SPtr sp = new A();
    sp->some();


    //unique_ptr �� �̷� ����� �پ��� Ÿ�Կ� ��밡�ɵ��� ���ø�ȭ �� ��

    std::unique_ptr<A> pa(new A());
    pa->some();                     //�����͸� �ٷ�� �Ͱ� �Ȱ��� ���
}

int main() { ex(); }


/*

class A_SPtr        //�ڵ����� ������ �����ǵ��� ����Ʈ ������ Ŭ������ �ۼ��ϼ���.
{
    A* data;
public:
    A_SPtr(A* d) : data(d) { }
    ~A_SPtr() { delete data; }

    A& operator*() const { return *data; }
    A* operator->() const { return data; }
};


//�ڵ����� ������ �����ǵ��� ����Ʈ ������ �ۼ�  //���ø����� �����ϼ���.

template<typename T>
class SPtr        
{
    T* data;
public:
    SPtr(T* d) : data(d) { }
    ~SPtr() { delete data; }

    SPtr(const SPtr& d) = delete;

    T& operator*() const { return *data; }
    T* operator->() const { return data; }
};

*/