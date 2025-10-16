// trivial / non-trivial

C++ ��ü�� �Ҹ���, ���� ������, ���� ������, �����ڰ�
�󸶳� �ܼ��ϰ�(��, �������Ϸ��� �ܼ� �޸� ���� �������Ρ�) �۵��ϴ°�
����, �޸� ��ġ, POD - like Ÿ�� ���� ��� ���������� ����

//1. trivial�� �ǹ�

�ܼ���, ��������� ������
�����Ϸ��� �ƹ��� �߰� ���� ���� �ܼ��� �޸𸮸� �����ϰų� �ʱ�ȭ �ϴ� ������ �����ϴ� �Լ�
ȣ���ص� ��Ÿ�� �ڵ尡 �������� ����(inlineȭ �Ǿ� �����)

//2. non-trivial�� �Ǵ� ����

����ڰ� �ش� �Լ��� ���� ������ ���({} ����)
�ش� Ŭ������ ��� Ŭ����(base) �� �����ų�
����� non - trivial�� Ÿ���� ������ ��
���� �Ҹ���, ���� �Լ��� ���� ��

//�� �� ���
//  trivial : �����Ϸ��� �ƹ� ���۵� �� �ϴ� ��¥ �⺻ ����.
//  non - trivial : ����ڰ� ���� ������ ����. (���� ����, ���, �����Լ� ��)


//3. �Ҹ��� �������� ����

#include <type_traits>
#include <iostream>

struct A {};                        // implicit destructor
struct B { ~B() = default; };       // explicitly defaulted
struct C { ~C() {} };               // user-defined (empty body)
struct D { virtual ~D() = default; }; // virtual destructor

int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_trivially_destructible_v<A> << '\n'; // true
    std::cout << std::is_trivially_destructible_v<B> << '\n'; // true
    std::cout << std::is_trivially_destructible_v<C> << '\n'; // false
    std::cout << std::is_trivially_destructible_v<D> << '\n'; // false
}

//4. = default�� trivial�� �����ұ� ?

    //�����ϴ� ���
    struct A {
        ~A() = default;             // Ŭ���� ���� ���� // trivial, noexcept(true)
    };

    //�������� �ʴ� ���
    struct B {
        ~B();
    };
    inline B::~B() = default;       // Ŭ���� �ܺο��� default // non-trivial (������ noexcept�� true)
    
 
//5. �ǹ��� �ǹ�

����	                trivial	        non - trivial
�޸� ����	        �ܼ� ���� �Ҹ�	���� �ڵ� ����
����	                ����	            �ణ ����
memcpy / memmove	����      	    �������� ����
POD ����	            ����	            �Ұ���
���� ����ȭ	        ����	            ���� ����

