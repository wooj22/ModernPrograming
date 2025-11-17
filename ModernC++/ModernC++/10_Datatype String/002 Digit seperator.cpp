// Digit seperator //수 분리자 (숫자 구분자)
// C++14 이후 

#include <iostream>

int main() { 
    // C++14 이전까지는 아래처럼 큰 수를 알아보기가 어려웠다.
    int num1 = 1000000;

    // C++14 이후부터는 다음과 같이 single quote(')를 digit seperator로써 사용할 수 있다.
    int num2 = 1'000'000;

    // seperating 단위도 자유롭게 그냥 맘대로 가능 #1
    long hex = 0x1234'5678;
    // seperating 단위도 자유롭게 그냥 맘대로 가능 #2
    long oct = 00'01'02'03;

    double pi = 3.1415'9265'3589;    
}

// 비트마스크, 플래그 상수를 읽기 훨씬 쉽다. //값엔 영향 없음

#include <iostream>
#include <bitset>

int main() {
    constexpr auto MASK_PLAYER  = 0b0001'0000;
    constexpr auto MASK_ENEMY   = 0b0010'0000;
    constexpr auto MASK_POWERUP = 0b0100'0000;

    unsigned char state = 0;
    state |= MASK_PLAYER;
    state |= MASK_POWERUP;

    std::bitset<8> bits(state);
    std::cout << "State bits: " << bits << '\n';
}


//현대식(C++17~20 스타일) 플래그 관리 구조체
//
//    enum class로 타입 안전한 플래그 정의
//    operator|, operator& 오버로딩으로 비트마스크 연산 가능
//    constexpr, digit separator(숫자 구분자)로 가독성과 성능 유지
//    std::underlying_type_t로 안전한 형 변환