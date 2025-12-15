//예시 

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
using namespace std;

// 전달 받은 가변인수 ts만큼 range를 조회해서 카운트를 구합니다.
template<typename R, typename ... Ts>
auto matches(const R& range, Ts ... ts)
{
    return (std::count(std::begin(range), std::end(range), ts) + ...);
}

// 전달 받은 가변인수 모두를 set에 삽입하고 모두 성공했는지 반환 받습니다.
template<typename T, typename ... Ts>
bool insert_all(T& set, Ts ... ts) {
    // set.insert의 반환 값을 pair<iterator, bool>의 값을 가짐
    return (set.insert(ts).second && ...);
}

void main()
{
    //첫번째 인자 컨테이너에 매칭 되는, 가변 인자의 수를 리턴하는 함수  // +
    vector<int> v{ 1,2,3,4,5 };
    cout << matches(v, 2, 5) << '\n';                       // 2 반환
    cout << matches(v, 100, 200) << '\n';                   // 0 반환
    cout << matches("abcdefg", 'x', 'y', 'z') << '\n';      // 0 반환
    cout << matches("abcdefg", 'a', 'd', 'f') << '\n';      // 3 반환

    //Set 에 가변인자를 insert 하고, 모두 성공했는지 확인  // &&
    set<int> my_set{ 1, 2, 3 };
    cout << insert_all(my_set, 4, 5, 6) << '\n';        // true
    cout << insert_all(my_set, 7, 8, 2) << '\n';        // false => 2 값을 insert 중복으로 false

}