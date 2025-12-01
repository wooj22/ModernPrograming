//C++20 - 수학 상수
//C++20에 수학 상수들이 constexpr, 변수 템플릿을 사용한 모던한 형태로 도입
//https://blog.naver.com/kmc7468/221843531555


#include<iostream>
#include <numbers>      //

using namespace std;
using namespace std::numbers;

int main() {
    cout << pi << '\n'; // double
    cout << e_v<float> << '\n'; // float
    cout << sqrt2_v<long double> << '\n'; // long double
}


//numbers 헤더 파일을 include
//std::numbers 네임스페이스에 정의


// 이름       값           수학상수             
// e         2.71828...   자연상수             
// log2e     1.44269...   e의이진로그          
// log10e    0.43429...   e의상용로그          
// pi        3.14159...   원주율               
// ln2       0.69314...   ln 2 (2의 자연로그)  
// ln10      2.30258...   ln 10 (10의 자연로그)
// sqrt2     1.41421...   제곱근 2             
// sqrt3     1.73205...   제곱근 3             
// phi       1.61803...   황금비               


//해당 상수들의 타입은 double이고, 
// 
//만약 다른 타입의 상수가 필요하다면 pi_v<float>, e_v<long double>과 같이 
//상수 이름 뒤에 _v를 붙인 뒤 템플릿 인수로 원하는 타입을 넘겨주시면 됩니다.

