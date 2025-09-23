//스마트 포인터(shared_ptr, unique_ptr, weak_ptr) 의 형변환(casting)
// 
//		일반 포인터처럼 업캐스팅(자식 → 부모) 과 다운캐스팅(부모 → 자식) 이 모두 가능합니다.
//		단, 참조 카운트 관리 및 소유권 이전(unique_ptr) 이 있기 때문에, 형변환 시에는 주의가 필요

//	업캐스팅(자식 → 부모)		static_pointer_cast			안전(암시적 형변환 가능)
//	다운캐스팅(부모 → 자식)	dynamic_pointer_cast		런타임 타입 확인 필요(RTTI)

#include <iostream>
#include <memory>
using namespace std;

struct Item { virtual ~Item(); };
struct Weapon : Item {};

//shared_ptr 형변환 예시 --------------------------------------------------------------

int main()
{

    //업캐스팅 (static_pointer_cast)
    shared_ptr<Weapon> weapon = make_shared<Weapon>(...);
    shared_ptr<Item> item = static_pointer_cast<Item>(weapon); // 자식 → 부모

    //다운캐스팅(dynamic_pointer_cast)
    shared_ptr<Item> item = make_shared<Weapon>(...);
    shared_ptr<Weapon> weapon = dynamic_pointer_cast<Weapon>(item);
    if (weapon) {        cout << "변환 성공" << endl;    }
    else {        cout << "변환 실패" << endl;    }
    
    //위험한 캐스팅(static_pointer_cast로 다운캐스팅)
}

//weak_ptr
//  먼저 lock()으로 shared_ptr 변환 후 캐스팅
