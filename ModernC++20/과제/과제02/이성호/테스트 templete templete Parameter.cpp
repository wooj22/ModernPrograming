// 템플릿 템플릿 파라미터 

#include <iostream>
#include <list>
#include <vector>

// std::list 와 값을 받아 해당 리스트에 값을 추가하는 코드를 작성하세요.     
//
// addToContainer()

template<template<typename...> class Container, typename T>
void addToContainer(Container<T>& list, T value)
{
	list.push_back(value);
}


int main() {

	// int 타입의 std::list
	std::list<int> intList;

	// list에 값 추가
	addToContainer(intList, 5);
	addToContainer(intList, 10);
	addToContainer(intList, 15);

	for (auto& e : intList) std::cout << e << std::endl;
}
