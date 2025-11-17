// std::span
// 
//      연속적인 데이터 컨테이너를 참조하는 STL 
//      연속된 메모리 영역에 대한 비소유적 뷰를 제공합니다.
//      즉, 배열, std::vector, std::array 또는 원시 포인터와 크기 쌍을 다룰 수 있다.
// 
//      컴파일 단계에서 크기가 결정된 경우, 정적 길이를 가지며, 
//      실행 시간에 그 크기가 결정된다면, 동적 길이(dynamic_extent)를 가집니다.
//
//      소유하지 않음 → 원본 배열 / 벡터가 살아 있어야 함
//      복사 비용 거의 없음 → 포인터 + 크기 정보만 가지고 있음
//      읽기(real-only span) / 쓰기 가능(mutable span)
//      부분 뷰, 읽기 전용, 범위 기반 반복 지원, 함수 인자에 범용성 + 안전성 제공

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <numeric>
#include <ranges>
#include <span>
#include <vector>
#include <array>

int main(void)
{
    int arr[] = { 7,8,9 };
    std::vector<int> vec{ 1,2,3 };
    std::array<int, 3> ary{ 4,5,6 };


    std::span<int> span{ arr };     //arr, vector, array 모두 가능

    for (const auto& i : span) {
        std::cout << i << " ";
    }
    std::cout << std::endl;


    std::span<int> s4(arr, 2);    // 길이 지정 (arr[0], arr[1])

    return 0;
}

//// 연속적인 데이터 컨테이너를 받아 출력하는 템플릿을 만들기
template <typename T>
void print( const std::span<T>& span ) 
{
    for (const auto& i : span) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main(void) 
{
    std::vector<int> vecNums{ 1,2,3 };
    std::array<int, 3> arrStrs{ 4,5,6 };
    int arrNums[] = { 7,8,9 };
    std::string str = "Hello World!";

    print<int>(vecNums);        //
    print<int>(arrStrs);        //
    print<int>(arrNums);        //
    print<char>(str);           //

    return 0;
}

// 읽기 전용 span

int main(void)
{
    int arr[] = { 1, 2, 3, 4 };
    std::span<int> s(arr);        // mutable span
    std::span<const int> cs(arr); // read-only span

    //s를 통해 배열 요소를 직접 수정 가능
    //cs는 읽기만 가능, 수정 시 컴파일 오류

    //const std::span<T>        //span 자체를 바꿀 수 없음, 원소 수정 가능
    //const std::span<const T>  //완전 읽기 전용
}


//std::span, 왜 사용하는걸까 ?
//https://nx006.tistory.com/5

//C++의 데이터 컨테이너를 메모리 상의 저장 방식
//  연속적인 컨테이너(Sequential Type)과       - C-스타일 배열, std::array, std::vector, std::string 등
//  비연속적인 컨테이너(Non sequential Type)   - std::list, std::map, std::set, std::stack 등

//하나의 함수에 벡터, 스트링, 배열 등을 동시에 담을 수 있게 하려는 것일까요 ? 
// 그것도 맞는 말이지만, 이미 C++에는 템플릿이라는 강력한 기능이 있고, 
// template concept라는 아주 강력한 기능에 힘을 얻어 C++20부터 더 안전한 템플릿의 사용이 가능해졌습니다.

//std::span은 다음과 같은 주요한 기능 ***
//
//안전성(Safety) : 
//      std::span은 범위 확인을 제공하고 버퍼 오버플로우를 방지합니다.즉 일반 C-array나 포인터를 사용하는 것보다 더 안전합니다.
//쉬운 사용성(Easy to use) : 
//      std::span은 배열 등 여러 연속적인 메모리 컨테이너를 다루는데 사용하기 편리한 메소드들과 인터페이스를 제공합니다.
//상호 운용성(Interoperability) : 
//      std::span은 여러 연속적인 메모리 컨테이너와 배열과 함께 사용될 수 있습니다.그렇기 때문에 여러 STL의 알고리즘들과 함께 사용될 수 있습니다.
//성능(Performance) : 
//      std::span은 일반 어레이를 사용하는 것보다 살짝 더 빠르고 안전하게 메모리 블럭을 참조할 수 있게 설계됐습니다.


//안전성(Safety)
//std::span은 위에 예시에서 범위 기반 for-loop에서 알 수 있듯이 범위를 제공
//배열의 크기를 인자로 받아야 했지만, std::span을 사용한다면 그럴 필요가 없습니다.
//배열 포인터 사용보다 안전


//아래 코드를 std::span 을 사용하여 수정하세요.

void print(const int* arr, const int size)
{
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main(void)
{
    int arr[] = { 1, 2, 3, 4, 5 };

    print(arr, sizeof(arr) / sizeof(int));

    return 0;
}

/*

#include <iostream>
#include <span>
using namespace std;

void print(span<int> sp)
{
    for (auto e: sp) { std::cout << e << " "; }
    std::cout << std::endl;
}

int main(void)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    print(arr);
    return 0;
}
*/

//쉬운 사용성(Easy to use)
//size : span하는 대상의 사이즈를 반환합니다.
//begin, end : span하는 메모리의 각각 첫 번째, 마지막 + 1 번 째의 iterator를 반환합니다. (C++20)
//rbegin, rend : begin, end과 반대(reverse)로 각각 마지막, 첫 번째 - 1 번 째의 iterator를 반환합니다. (C++20)
//front, back : 각각 첫 번째, 마지막 번 째 데이터를 참조합니다.front()는* begin()과 결과가 똑같습니다. (C++20)
//subspan : span의 하위 범위를 가져옵니다.
//그 외에 C++20부터 dynamic_extent를 통해 동적 길이를 가지는 span을 생성할 수 있습니다.
//또한 C++23부터 std::mdspan을 통해 다차원 배열에 대한 span을 생성할 수 있습니다.

//-------------------------------------
#include <span>
#include <iostream>

using namespace std;

int main()
{
    int a[] = { 0,1,2 };
    span<int> mySpan(a);

    cout << "mySpan.subspan(1,2): ";
    for (auto& i : mySpan.subspan(1, 2))  //offset, count  //부분 뷰
    {
        cout << i;
    }
    cout << "\nmySpan.subspan<1,2>: ";
    for (auto& i : mySpan.subspan<1, 2>())
    {
        cout << i;
    }
    cout << "\nmySpan.subspan<1>: ";
    for (auto& i : mySpan.subspan<1>)   //끝까지 이동
    {
        cout << i;
    }
}

//-------------------------------------
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <numeric>
#include <ranges>
#include <span>

void display(std::span<const char> abc)
{
    const auto columns{ 20U };
    const auto rows{ abc.size() - columns + 1 };

    for (auto offset{ 0U }; offset < rows; ++offset) {
        std::ranges::for_each(
            abc.subspan(offset, columns),    //
            std::putchar
        );
        std::putchar('\n');
    }
}

int main()
{
    char abc[26];
    std::iota(std::begin(abc), std::end(abc), 'A');
    //데이터셋을 시퀸스(연속적인)한 값으로 채우고 싶을 때는 iota 알고리즘을 사용 //<numeric> 헤더 파일

    //for (auto e : abc) std::cout << e << "";

    display(abc);

}



//상호 운용성(Interoperability)
//코드의 재사용성을 줄이는 한편 여러 STL의 알고리즘들 혹은 함수들과 같이 사용될 수 있습니다.
// 
//심지어 직접 제작한 컨테이너에도 std::span을 적용할 수 있는데, 다음 조건만 만족하면 됩니다.
//  데이터가 연속된 메모리 공간에 저장될 것
//  데이터 포인터와 길이를 가질 것

#include <algorithm>
#include <numeric>
#include <ranges>
#include <span>
#include <iostream>
#include <vector>

template <typename T>
class MyContainer {
public:
    MyContainer(std::vector<T> data) : data_(data) {}

    T* data() { return data_.data(); }
    std::size_t size() { return data_.size(); }

private:
    std::vector<T> data_;
};

int main() {
    MyContainer<int> c = { {1, 2, 3, 4, 5} };
    std::span<int> s(c.data(), c.size());

    for (const auto& i : s) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}

https://en.cppreference.com/w/cpp/container/span
https://learn.microsoft.com/ko-kr/cpp/standard-library/span?view=msvc-170