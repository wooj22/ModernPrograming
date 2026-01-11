#include <iostream>
#include <vector>
using namespace std;

struct Person {
    std::string name;
    int score;
};

int main() {

    // 이름과 점수를 저장하는 벡터
    std::vector<Person> people = {
        {"Alice", 90},
        {"Bob", 85},
        {"Charlie", 90},
        {"Dave", 70},
        {"Eve", 60},
        {"Frank", 85}
    };

    // 점수를 내림차순으로 정렬하고,
    // 랭킹 계산한 후 (동일 점수에 동일 랭킹 부여한다.)
    // <이름, 랭킹> 을 map 에 저장하고,
    // 결과를 출력하세요.

    //랭킹:
    //    1 Alice    90
    //    1 Charlie  90
    //    3 Bob      85
    //    3 Frank    85
    //    5 Dave     70
    //    6 Eve      60

    return 0;
}
