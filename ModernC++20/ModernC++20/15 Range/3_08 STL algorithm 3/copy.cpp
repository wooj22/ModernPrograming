//copy 함수는 
//	    first 부터 last 전 까지의 모든 원소들을 d_first 부터 시작하는 곳에 복사한다.
//copy_if 의 경우 
//	    pred 가 true 를 리턴하는 원소만 복사하게 된다.이 때 원소들의 상대적인 순서는 유지된다.

#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

int main()
{
    std::vector<int> from_vector(10);
    // 0 부터 9 까지 원소들을 from_vector 에 집어넣는다.
    std::iota(from_vector.begin(), from_vector.end(), 0);               //iota

    std::vector<int> to_vector;
    // from_vector 의 원소들을 to_vector 에 복사한다.
    std::copy(from_vector.begin(), from_vector.end(), std::back_inserter(to_vector));   //copy
    std::cout << "to_vector contains: ";

    // or, alternatively,
    //  std::vector<int> to_vector(from_vector.size());
    //  std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
    // either way is equivalent to
    //  std::vector<int> to_vector = from_vector;

    std::cout << "to_vector contains: ";

    // to_vector 의 원소들을 표준 출력 객체(std::cout) 에 전달한다. 

    std::copy(to_vector.begin(), to_vector.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    // odd numbers 
    std::cout << "odd numbers in to_vector are: ";

    std::copy_if(to_vector.begin(), to_vector.end(), std::ostream_iterator<int>(std::cout, " "),
        [](int x) { return x % 2 != 0; });
    std::cout << '\n';

    // these multiples of 3
    std::cout << "to_vector contains these multiples of 3: ";

    to_vector.clear();
    std::copy_if(from_vector.begin(), from_vector.end(), std::back_inserter(to_vector),
        [](int x) { return x % 3 == 0; });

    for (const int x : to_vector)
        std::cout << x << ' ';
    std::cout << '\n';
}

//copy_backward: 범위 내의 원소들을 뒤에서 부터 복사한다.하지만 원소들 간의 상대적 순서는 유지. 
//          (즉 마지막 원소 부터 복사하되, 마지막 원소는 맨 마지막 칸에 넣는다.)

//reverse_copy : 범위 내의 원소들을 거꾸로 복사한다.

//copy_n : 특정 개수의 원소만 복사한다.

//fill : 특정 값으로 범위를 채운다.

//remove_copy, remove_copy_if : 특정 조건을 만족하는 원소들만 빼고 복사한다.


//std::ranges --------------------------------------------------------------------------

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main()
{
    std::vector<int> source(10);
    std::iota(source.begin(), source.end(), 0);

    std::vector<int> destination;

    std::ranges::copy(source.begin(), source.end(), std::back_inserter(destination));

    // or, alternatively,
    //  std::vector<int> destination(source.size());
    //  std::ranges::copy(source.begin(), source.end(), destination.begin());
    //  std::vector<int> destination = source;

    std::cout << "destination contains: ";

    std::ranges::copy(destination, std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    std::cout << "odd numbers in destination are: ";

    std::ranges::copy_if(destination, std::ostream_iterator<int>(std::cout, " "),
        [](int x) { return (x % 2) == 1; });
    std::cout << '\n';
}