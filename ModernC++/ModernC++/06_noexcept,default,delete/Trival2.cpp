//trivial과 non-trivial의 차이는 단순히 컴파일러 속성 차원이 아니라,
//“메모리를 그대로 복사해도 안전한가?” 로도 명확히 구분됩니다.

#include <iostream>
#include <cstring>      // memcpy
#include <type_traits>  // is_trivially_copyable
using namespace std;

struct Trivial {
    int x;
    double y;
};

struct NonTrivial {
    int* data;
    NonTrivial(int val) : data(new int(val)) {}
    ~NonTrivial() {
        cout << "~NonTrivial: deleting " << *data << endl;
        delete data;
    }
};

int main() {
    cout << boolalpha;
    cout << is_trivially_copyable_v<Trivial> << endl;
    cout << is_trivially_copyable_v<NonTrivial> << endl << endl;

    cout << "===== [ Trivial memcpy 복사 ] =====" << endl;
    Trivial a{ 10, 3.14 };
    Trivial b;
    memcpy(&b, &a, sizeof(Trivial));  // 안전한 복사
    cout << "a: " << a.x << ", " << a.y << endl;
    cout << "b: " << b.x << ", " << b.y << endl << endl;

    cout << "===== [ NonTrivial memcpy 복사 ] =====" << endl;
    NonTrivial n1(42);
    NonTrivial n2{ 0 }; // dummy
    memcpy(&n2, &n1, sizeof(NonTrivial)); // 얕은 복사 ( 위험! )

    cout << "n1.data: " << n1.data << " -> " << *n1.data << endl;
    cout << "n2.data: " << n2.data << " -> " << *n2.data << endl;

    cout << "main 끝 - 소멸자 호출 시작" << endl;
}


//trivial 타입은 “비트 단위 복사 = 논리적 복사”가 동일하다.
//non-trivial 타입은 “비트 단위 복사 ≠ 논리적 복사” 이다.
//
//따라서 memcpy는 오직 trivial 타입에서만 사용해야 하며,
//그 외에는 반드시 복사 생성자 / 대입 연산자를 통해 복사해야 합니다.
