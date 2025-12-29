//std::iter_swap
//      두 반복자가 가리키고 있는 원소들의 값을 서로 바꾼다

#include <algorithm>
#include <iostream>
#include <vector>

void print_vec(const std::vector<int>& v) {
    std::cout << "[";
    for (auto i : v) {
        std::cout << i << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    std::vector<int> v = { 1, 2, 3, 4, 5 };
    print_vec(v);

    // 2 와 3 을 바꾼다.
    std::iter_swap(v.begin() + 1, v.begin() + 2);

    print_vec(v);
}


//원소들을 선택 정렬하는 함수를 iter_swap 을 통해 만들어본다.

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

template <class ForwardIt>
void selection_sort(ForwardIt begin, ForwardIt end) {
    for (ForwardIt i = begin; i != end; ++i)
        std::iter_swap(i, std::min_element(i, end));
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-10, 10);
    std::vector<int> v;
    generate_n(back_inserter(v), 20, bind(dist, gen));

    std::cout << "Before sort: ";
    for (auto e : v) std::cout << e << " ";

    selection_sort(v.begin(), v.end());

    std::cout << "\nAfter sort: ";
    for (auto e : v) std::cout << e << " ";
    std::cout << '\n';
}


// swap: 두 객체의 값을 서로 바꾼다.
// 
// swap_ranges : 두 범위 내의 원소들을 서로 바꾼다.