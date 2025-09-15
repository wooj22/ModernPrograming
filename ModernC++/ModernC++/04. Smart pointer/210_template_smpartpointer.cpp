//연습) 템플릿으로 스마트 포인터 구현

#include <iostream>
#include <cstring>

using namespace std;

template <typename T>
class Smart_Pointer
{
private:
	T* ptr;
public:
	Smart_Pointer(T* _ptr);
	~Smart_Pointer();
	T& operator*() const;
	T operator->() const;

};

template <typename T> Smart_Pointer<T>::Smart_Pointer(T* _ptr) : ptr(_ptr) {  }
template <typename T> Smart_Pointer<T>::~Smart_Pointer() { delete ptr; }
template <typename T> T& Smart_Pointer<T>::operator*() const {	return *ptr;}
template <typename T> T Smart_Pointer<T>::operator->() const{	return ptr;}

int main()
{
	Smart_Pointer<int> sp(new int);
	*sp = 1;
	cout << *sp << endl;
}