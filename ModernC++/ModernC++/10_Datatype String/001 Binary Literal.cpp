// Binary Literal  //C++14

//2진수(binary)
//      0b 또는 0B를 이진수 앞에 붙여 사용한다.

#include <iostream>

int main() { 
    // 대입
    int bin = 0b11111100;
    unsigned int n = 0b1111u;   // 15 (unsigned)

    // 조건문
    if (bin == 0b1001) { }

    // switch-case
    switch (bin)
    {
    case 0b1001:
        break;
    case 0b1101:
        break;
    }

    // enum
    enum class BitsMask
    {
        CELAR = 0b00,
        SET = 0b01
    };
}

//16진수, 8진수
//      0x10, 010

#include <iostream>
int main() {

    int a1 = 10;
    int a2 = 0b10;
    int a3 = 0x10;
    int a4 = 010;

    std::cout << a1 << std::endl;   //출력은?
    std::cout << a2 << std::endl;
    std::cout << a3 << std::endl;
    std::cout << a4 << std::endl;

    return 0;
}

//10진수 ↔ 이진수 변환

#include <bitset>
#include <iostream>

int main() {

    int num = 42;
    std::bitset<8> bits(num); // 8비트 표현
    std::cout << bits << '\n'; // 00101010

    std::string s = "1101";
    std::bitset<8> bits(s);
    std::cout << bits.to_ulong() << '\n'; // 13
}

//고정 길이 비트 처리
//  std::bitset<N> : 고정 크기의 비트 집합
//  내부적으로 unsigned long long 기반
//  .to_string() / .to_ulong() / .to_ullong() 변환 함수 지원

#include <bitset>
#include <iostream>

int main() {
    std::bitset<8> bits(0b10110010);

    bits.flip(0);         // 0번째 비트 반전
    bits.set(3, true);    // 3번째 비트 1로 설정
    bits.reset(6);        // 6번째 비트 0으로

    std::cout << bits << '\n';       // 수정된 비트
    std::cout << bits.count() << '\n'; // 1의 개수
}
