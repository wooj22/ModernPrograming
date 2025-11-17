//regex_match 부분 매칭 뽑아내기
//      첫 번째에 검색을 하고픈 문자열을, 
//      두 번째에 일치된 패턴을 보관할 match 객체를, 
//      마지막 인자로 실제 정규 표현식 객체를 전달

#include <iostream>
#include <regex>
#include <vector>

//패턴을 만족하는 문자열 인지 검색하는 작업 ----------------------------------------

int main() {
    std::vector<std::string> phone_numbers = { 
        "010-1234-5678", "010-123-4567", "011-1234-5567", 
        "010-12345-6789", "123-4567-8901", "010-1234-567" };

    std::regex re("[01]{3}-(\\d{3,4})-\\d{4}");

    std::smatch match;                  // 매칭된 결과를 string 으로 보관

    for (const auto& number : phone_numbers) {
        if (std::regex_match(number, match, re)) {
            for (size_t i = 0; i < match.size(); i++) {
                std::cout << "Match : " << match[i].str() << std::endl;
            }
            std::cout << "-----------------------\n";
        }
    }
}

//smatch 이므로 match[i].str() 은 std::string 
//cmatch 였다면 match[i].str() 는 const char* 




