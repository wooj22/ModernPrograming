//std::format 연습   //C++20 //C++ 버전은 latest로 변경

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <format>           //
using namespace std;

int main()
{    
    //안녕, OO씨. 나이는 OO살이군요    
    //"철수", 17
    printf("안녕, %s씨. 나이는 %d살이군요\n", "철수", 17);
    std::cout << "안녕, " << "철수" << "씨. 나이는 " << 17 << "살이군요" << std::endl;

    std::cout << std::format("안녕, {}씨. 나이는 {}살이군요\n", "철수", 17);


    //출력 결과는? ----------------------------------------
    std::string str3 = std::format("{{}}");


    //주어진 인수 16, 14, 30 를 아래 예시처럼 출력하세요 ----------------------------------
    //예시) 16+14=30

    std::string str2 = std::format("{0}+{1}={2}", 16, 14, 30);
    std::string str1 = std::format("{}+{}={}", 16, 14, 30);
    cout << str1 << endl;


    //아래처럼 출력하세요 ----------------------------------
    //출력
    //a = ****9****, b = **5**    
    int a = 9;
    int b = 5;

    //std::string str4 = std::format("a = {0:*^9}, b = {1:*^5}", a, b);
    //cout << str4 << endl;


    //아래와 같은 출력이 나오도록 Vector3 클래스를 만들어 보세요 -------------------------
    //출력
    //( 1.00, 1.00, 1.00 )

    Vector3 pos;
    pos.x = 1;
    pos.y = 1;
    pos.z = 1;
    cout << pos.toString() << endl;
}

/*

class Vector3
{
public:
    float x, y, z;
public:
    std::string toString() {
        return std::format("( {:.2f}, {:.2f}, {:.2f} )", x, y, z);
    }
};

*/