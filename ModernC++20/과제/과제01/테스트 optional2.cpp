// optional 활용

//문제: 간단한 데이터베이스 검색
//사용자 정보를 관리하는 간단한 데이터베이스가 있다고 가정합니다.각 사용자는 고유 ID와 이름을 가지고 있습니다.
//아래와 같은 조건을 만족하는 프로그램을 작성하세요 :

//사용자 검색 함수 :
//  사용자 ID로 이름을 검색하는 함수 std::optional<std::string> findUserName(int userId)를 작성하세요.
//  ID가 데이터베이스에 존재하면 해당 사용자의 이름을 반환하고, 그렇지 않으면 std::nullopt를 반환하세요.

//메인 프로그램 :
//  사용자로부터 ID를 입력받아 이름을 출력합니다.
//  ID가 존재하지 않는 경우 "사용자를 찾을 수 없습니다."를 출력합니다.


#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

// 데이터베이스: ID 와 이름 매핑
std::unordered_map<int, std::string> database = {
    {1, "Alice"},
    {2, "Bob"},
    {3, "Charlie"}
};

// 사용자 검색 함수
std::optional<std::string> findUserName(int userId)
{
    if (database.find(userId) != database.end())
        return database[userId];
    else
        return std::nullopt;
}

int main()
{
    int userId;
    std::cout << "검색할 사용자 ID를 입력하세요: ";
    std::cin >> userId;

    //사용자 ID로 이름을 데이터베이스에서 검색해서 
    //값이 있는 경우에는 '이름'을 출력하고
    //없는 경우에는 '찾을 수 없다'는 출력을 하세요.

    if (std::optional<std::string> userName = findUserName(userId); userName)
        std::cout << "사용자 이름 : " << *userName << std::endl;
    else
        std::cout << "사용자를 찾을 수 없습니다." << std::endl;
}
