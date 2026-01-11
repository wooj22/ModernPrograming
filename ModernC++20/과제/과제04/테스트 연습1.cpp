
// 짝수 요소중에 3개만 선택해서 역순 출력하라 ( ranges )
// 	    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

    // 짝수 요소중에 3개만 선택해서 역순 출력

    std::vector<int> v2;
    std::copy_if(v.begin(), v.end(), std::back_inserter(v2), [](int a) { return a % 2 == 0; });    
    //for (auto e : v2) std::cout << e << std::endl; //2,4,6,8,0

    v2.erase(v2.begin() + 3, v2.end());        
    //for (auto e : v2) std::cout << e << std::endl; //2,4,6

    std::sort(v2.begin(), v2.end(), std::greater<int>());
    for (auto e : v2) std::cout << e << std::endl;  //6,4,2
}



// 최고 점수 3개를 골라 순서대로 출력하라 -----------------------------------
// std::ranges::sort, std::views::take

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <ranges>
using namespace std;

int main()
{
    std::vector<int> v = { 10, 5, 6, 1, 3, 7, 7 };

  
}


// 문자열을 ',' 기준으로 분리한 후, 각 문자열의 크기를 출력하라. --------------
// std::views::split, std::views::transform

#include <string>
#include <ranges>
#include <iostream>

int main()
{
    std::string str = "hello,hi,good";   //출력: 5 2 4


}