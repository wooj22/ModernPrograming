//사용자로부터 숫자를 입력받아 처리(두 배로 계산)하는 프로그램을 작성하세요.
// 
//  입력이 유효하면 입력을 정수로 변환해서 반환합니다.
//  입력이 잘못되었다면 std::nullopt를 반환하여 오류를 나타냅니다.
// 
//  입력 값을 이용해서 두배로 하는 계산을 수행하며, 
//  유효하지 않은 경우에는 기본 값 10을 이용해 계산을 수행합니다.

#include <iostream>
#include <optional>
#include <string>
#include <sstream>
/*
// 함수: 입력을 정수로 변환
std::optional<int> parseInput(const std::string& input) {
    std::istringstream stream(input);
    int value;
    if (stream >> value) {
        return value; // 유효한 입력
    }
    return std::nullopt; // 유효하지 않은 입력
}

// 함수: 입력 값을 두 배로 계산
int processValue(const std::optional<int>& value, int defaultValue) {
    return value.value_or(defaultValue) * 2; // 값이 없으면 기본값 사용
}
*/

int main() {
    std::string userInput;
    std::cout << "Enter a number: ";
    std::getline(std::cin, userInput);

    // 입력값을 정수로 변환 
    std::optional<int> parsedValue = parseInput(userInput);

    if (parsedValue) {
        std::cout << "You entered a valid number: " << *parsedValue << "\n";
    }
    else {
        std::cout << "Invalid input. Using default value of 10.\n";
    }

    //입력 값을 두 배로 계산해서 리턴 ( parsedValue 가 유효하지 않으면, 기본 값 : 10 )
    int result = processValue(parsedValue, 10);
    std::cout << "Result after processing: " << result << "\n";

    return 0;
}