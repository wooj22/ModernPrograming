//range 라이브러리  //C++20
// 
//		자료구조(std::list, std::vector ... )에 
//		범위기반 알고리즘을 제공하는 편리하고 간단한 라이브러리 

//		C++11에서는 auto 키워드와 ranged for를 사용해서 길고 번거로운 iterator 를 정리했다.
//      C++20에서는 range 라이브러리로 더 편리하게 표현.
//      //https://en.cppreference.com/w/cpp/ranges


//ranges 함수, ranges 알고리즘은 
//	네임스페이스의 해당 stl 알고리즘과 거의 동일합니다.
//	차이점은 
//	    개념 적용 제약 조건이 있고, 
//	    범위 인수 또는 더 많은 iterator-sentinel 인수 쌍을 허용한다는 것입니다.
//	    컨테이너에서 직접 작업할 수 있으며, 쉽게 함께 연결할 수 있습니다.


#include <ranges>               //#include
#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

    //오름차순 출력 후 출력하세요.

    std::sort(v.begin(), v.end());

    std::vector<int>::iterator it;
    for ( it = begin(v); it != end(v); it++) std::cout << *it << " ";
    std::cout << std::endl;


    //auto 키워드와 ranged for를 사용 ***
    for (auto n : v) std::cout << n << " "; 
    std::cout << std::endl;


    //ranges 사용 ***

    std::ranges::sort(v);
    std::ranges::for_each(v, [](int n) {std::cout << n << " "; });

    //Wow! STL 사용할때보다 간결. 
}



//Ranges는 객체입니다. 어떠한 객체의 집합들입니다. -------------------------------------------
//
//		아이템들의 추상적인 집합 (범위)
//		순회 가능할 것
//		begin(), end()를 사용 할수 있을 것
//
//		임의의 타입이 range 네임스페이스 안에 있는 begin과 end의 인자로 사용 할 수 있으면, range라고 합니다.

//Range라고 할 수 있는 것들 :
//		stl 컨테이너
//		배열 
//		C++20에서 추가된 다양한 view 들


//C++20 표준에서 제공하는 concept을 이용해 'range 여부'를 알아낼 수 있다.

#include <iostream>
#include <ranges>
#include <vector>

/*

template < typename T>
concept range = requires(T & t)
{
	std::ranges::begin(t);
	std::ranges::end(t);
};

*/

int main()
{
	std::cout << std::ranges::range<int>;                // false
	std::cout << std::ranges::range<int[5]>;             // true
	std::cout << std::ranges::range<std::vector<int>>;   // true

}


//iterator로 STL의 모든 작업을 할 수 있는데 왜 사용할까요? -------------------------------------------
//
//	편의성과 간결함 : 
//      우리가 begin과 end를 제공하여 작성했던 함수들의 매개변수들이 대폭 줄어듭니다.
//	지연된 연산 가능 (lazy operation) : 
//      불필요한 계산은 회피합니다. 필요할 때만 계산합니다.
//	조합성 : 
//      '파이프 구문( | )'를 이용하여 계산식을 나타내며, 계산들을 조합하여 나타낼 수 있습니다.
//		연산들을 손쉽게 연결 할 수 있음, 직관적인 표현 가능


//Range의 기본 사용법

// 짝수 요소중에 3개만 선택해서 역순 출력하기

/*
// 기존 알고리즘 사용

#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

    std::vector<int> v2;
    std::copy_if(v.begin(), v.end(), std::back_inserter(v2), [](int a) { return a % 2 == 0; });
    //for (auto e : v2) std::cout << e << std::endl; //2,4,6,8,0

    v2.erase(v2.begin() + 3, v2.end());
    //for (auto e : v2) std::cout << e << std::endl; //2,4,6

    std::sort(v2.begin(), v2.end(), std::greater<int>());
    for (auto e : v2) std::cout << e << std::endl; //6,4,2
}

*/

#include <vector>
#include <ranges>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

    // 짝수 요소중에 3개만 선택하기 
    auto r = v 
        | std::views::filter([](int a) { return a % 2 == 0; }) 
        | std::views::take(3);    //

    //벡터 v가 입력 값이 되어 오른쪽 filter에게 넘어 갑니다.
    //filter는 v의 모든 요소에 대해서 filter에 등록된 람다를 적용해
    //      결과값이 true인 요소들만 오른쪽의 take에게 넘깁니다.
    //take는 필터링 된 요소들에 대해 
    //      가장 앞에 있는 3개만 선택해서 r 이라는 객체를 만듭니다.

    std::cout << "output : ";    
    for (auto n : r) std::cout << n << " ";  std::cout << std::endl;

    // 역순으로 만들기

    std::ranges::reverse(r);            //

    std::cout << "reverse : ";
    for (auto n : r) std::cout << n << " "; std::cout << std::endl;

    //vector v -----------------------------------------------

    std::cout << "original : ";
    for (auto n : v) std::cout << n << " "; std::cout << std::endl;

    //원본 v 가 변한 것을 알 수 있다.
    //r 은 벡터 v의 복사본을 가지고 있는 것이 아니라 참조를 가지고 있다. ***
}

//range 연산의 결과는 ------------------------------------------------------------

#include <vector>
#include <ranges>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    auto r = v | std::views::take(3);

    std::cout << typeid(r).name() << std::endl;    //take_view 클래스의 객체를 리턴 ***

    //이 외에도 filter_view, transform_view, ref_view 등 많은 뷰가 있다 ***


    //게으른(지연된) 연산은 이 뷰를 가리키는 말.
    //객체를 생성 할 때 람다를 실행하는 것이 아니라, 일단 값을 들고 있다가 실제 호출 될 때 연산 ***
    //뷰의 결과를 다음 뷰의 입력으로, 또 그 결과를 다음 뷰의 입력으로 ... 
    //이런식으로 뷰 끼리 계속 연결해서 계산

    //뷰클래스 템플릿을 만들어 주는 함수객체들을 range adapter object 라고 한다.
}

//Range를 사용하는 방법 -----------------------------------------------------------------------

#include <vector>
#include <iostream>
#include <algorithm>
#include <ranges>

int main()
{
    //view class template을 직접 생성		
    {
        std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
        std::ranges::filter_view    view1(v, [](int n) { return n % 2 == 0; });
        std::ranges::take_view      view2(view1, 3);
        std::ranges::reverse_view   view3(view2);
    }

    //range adapter object 사용
    {
        std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
        auto view1 = std::views::filter(v, [](int n) { return  n % 2 == 0; });
        auto view2 = std::views::take(view1, 3);
        auto view3 = std::views::reverse(view2);
    }

    //파이프 연산자 사용
    {
        std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
        auto view3 = v | std::views::filter([](int n) { return  n % 2 == 0; })
            | std::views::take(3)
            | std::views::reverse;

        // 인자가 없다면 그냥 객체의 이름을 사용한다. 함수처럼 ()를 붙여 주면 컴파일 실패한다. 
        // 다시 한번 말하지만 함수가 아니라 객체다.
    }
}

//연습) 백터를 공백(' ')을 넣어 스트림 출력하기

#include <iostream>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4 };

    //-----------------------------------------
    std::ranges::for_each(v, [](int n) {
        std::cout << n << ' ';
        });
    std::cout << std::endl;

    //----------------------------------------- view
    auto printable = v | std::views::transform([](int x) {
        return std::to_string(x) + " ";
        });

    std::ranges::for_each(printable, [](const std::string& s) {
        std::cout << s;
        });
    std::cout << std::endl;

    return 0;
}


//컨테이너를 range 로 변환하기. range 출력하기
#include <ranges>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

template<class Rng>
    requires std::is_base_of_v<std::ranges::view_interface<Rng>, Rng>
std::ostream& operator<<(std::ostream& os, Rng& rng)
{
    auto it = std::ranges::begin(rng);
    const auto e = std::ranges::end(rng);
    if (it == e) return os << "[]";
    os << '[' << *it;
    while (++it != e) os << "," << *it;
    os << ']';
    return os;
}

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto r = std::ranges::views::all(v);            //ref_view 로 변환

    std::cout << r;
}
