// regex_match - 완전히 매칭이 된다면 true 를 리턴

#include <iostream>
#include <regex>
#include <vector>

int main()
{
    // 주어진 파일 이름들.
    std::vector<std::string> file_names = { 
        "db-123-log.txt", 
        "db-124-log.txt", 
        "not-db-log.txt", 
        "db-12-log.txt", 
        "db-12-log.jpg" };

    std::regex re("db-\\d*-log\\.txt");     // \d - 숫자

    for (const auto& file_name : file_names) {
        std::cout << file_name << ": " 
            << std::boolalpha       // std::boolalpha 는 bool 을 0 과 1 대신에 false, true 로 표현.
            << std::regex_match(file_name, re) << '\n';
    }
}

//정규 표현식을 처리하는 엔진 역시 여러가지 종류
// 
//디폴트로 std::regex::ECMAScript
//std::regex re("db-\\d*-log\\.txt");
//std::regex re("db-\\d*-log\\.txt", std::regex::grep);
// 
//std::regex::icase 를 전달한다면 대소 문자를 구분하지 않게 됩니다
//std::regex re("db-\\d*-log\\.txt", std::regex::grep | std::regex::icase);


/*
//전화번호를 받는 정규 표현식 -----------------------------------------

//  (숫자)-(숫자)-(숫자)꼴로 있어야 합니다.
//  맨 앞자리는 반드시 3 자리이며 0 과 1 로만 이루어져 있어야 합니다.
//  가운데 자리는 3 자리 혹은 4 자리 여야 합니다.
//  마지막 자리는 4 자리 여야 합니다.

#include <iostream>
#include <regex>
#include <vector>

int main() 
{
    std::vector<std::string> phone_numbers = { 
        "010-1234-5678", "010-123-4567", "011-1234-5567", 
        "010-12345-6789", "123-4567-8901", "010-1234-567" };

    std::regex re("[01]{3}-\\d{3,4}-\\d{4}");

    for (const auto& number : phone_numbers) {
        std::cout << number << ": " << std::boolalpha
            << std::regex_match(number, re) << '\n';
    }
}
*/