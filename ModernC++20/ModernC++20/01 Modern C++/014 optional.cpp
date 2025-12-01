//C++ 17에 추가된 유용한 클래스 중에 optional이 있습니다.
//		해당 객체는 값을 리턴할 때 '값이 없음'을 표현하기에 유용합니다

#include <optional>
#include <utility>
#include <iostream>
using namespace std;

std::optional<int> getValue(bool isTrue)    // 특정 기능을 수행하는 함수
{       
    if (isTrue) {                           // 기능을 성공적으로 마쳤다면
        return 100;                         // 그 결과 값을 반환한다.    
    }
    else {                                  // 기능을 실패했다면
        return std::nullopt;                // 실패했음을 알려준다. <utility> 에 선언됨.
    }
}

int main(void)
{
    auto ret = getValue(true);

    cout << ret.has_value() << endl;        // true - 수행 결과 성공 여부 
    cout << ret.value() << endl;            // 100 - 수행 결과 값

    auto ret2 = getValue(true);
    if (ret2) {                            //operator bool() 이 오버로딩되어 있음
        cout << "성공" << endl;
    }

    auto ret3 = getValue(false);
    cout << ret3.has_value() << endl;      // false  
    cout << ret3.value() << endl;          // std::bad_optional_access 에러 발생

    return 0;
}

// if/switch 문에서 초기화문(init statement) 활용

#include <optional>
#include <iostream>

std::optional<int> findValue(bool cond) {
    if (cond) return 100;
    return std::nullopt;
}

int main() {
    if (std::optional<int> value = findValue(true); value) { // ← 초기화문
        std::cout << *value << "\n"; // 100
    }
    else {
        std::cout << "no value\n";
    }
}


//std::optional의 장점
//  값이 없는 상태를 명시적으로 처리 가능.
//  런타임 오류(예: null 포인터 참조) 예방.
//  읽기 쉽고 유지보수에 용이한 코드 작성.

