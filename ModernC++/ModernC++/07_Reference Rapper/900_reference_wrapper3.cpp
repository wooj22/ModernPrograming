//std::reference_wrapper 와  
//      도우미 역할인 std::ref, std::cref
//      일반 객체를 참조 형태로 리턴해주는 역할

#include <functional>
#include <iostream>

int main() {
    int i = 1;
    std::reference_wrapper<int> rwi(i);

    std::cout << "i = " << i << std::endl;
    std::cout << "rwi = " << rwi << std::endl;
    rwi.get() = -1;
    std::cout << "i = " << i << std::endl;

    return (0);
}

//-------------------------------------------------------------------------
#include <iostream>
#include <functional>
using namespace std;

void printNumber(int i) {
    cout << i << endl;
}

int main() {
    int n = 4;
    std::function<void()> print1 = std::bind(&printNumber, n);
    std::function<void()> print2 = std::bind(&printNumber, std::ref(n));    //내부에선 ptr이 n을 가리키고 있는 상태

    n = 5;
    print1();    // 4 를 출력
    print2();    // 5 를 출력
}

//-------------------------------------------------------------------------
// T의 타입은 int 입니다. 
// 그러나 ++는 std::ref 의 타겟의 참조가 될 _t.operator int&() 에 반영
// operator Ty&() 때문에 std::reference_wrapper<int>에서 int& 로의 암시적 변환

#include <functional>
#include <iostream>

template <typename T>
void func(T _t) {
    _t++;
}

int main() {
    int i = 1;
    std::cout << i << std::endl;    // 1
    func(i);
    std::cout << i << std::endl;    // 1
    func(std::ref(i));
    std::cout << i << std::endl;    // 2
}

//-------------------------------------------------------------------------
//ref() 와 T& 의 차이
//
    T x;    auto r = ref(x);
    T x;    T& y = x;

//참조한 것과 참조를 포장한 것의 차이, reference_wrapper는 스마트 포인터와 달리 소유권 개념 없음.

#include <iostream>
#include <functional>  // for reference_wrapper
using namespace std;

int main()
{
    int n = 1;
    int m = 2;
    reference_wrapper<int> r = n;
    r = m;                                  //
    r.get() = 3;

    cout << n << endl;
    cout << m << endl;

    //---------------------------------------------

    int x = 5, y = 7, z = 8;
    
    int& arr[]{ x,y,z };                    // error: declaration of 'arr' as array of references

    reference_wrapper<int> arr[]{ x,y,z };  // ok

    for (auto a : arr)
        cout << a << " ";
    return 0;
}

//-------------------------------------------------------------------------
#include <iostream>
#include <type_traits>
#include <functional>
using namespace std;

int main()
{
    cout << boolalpha;
    int x = 5, y = 7;
    reference_wrapper<int> r = x;           //  auto r = ref(x);

    cout << is_same<int&, decltype(r.get())>::value << "\n";  //r.get() 의 타입

    cout << (&x == &r.get()) << "\n";       // 주소

    r = y;                                  // y 로 변경. 이제 r 은 y 참조
    cout << (&y == &r.get()) << "\n";       // r is not same as T&, but r.get() is same 

    r.get() = 70;
    cout << y;

    return 0;
}


//컨테이너에서 사용할 수 있도록 참조를 둘러싼 편리한 래퍼로 생각할 수 있습니다.

    std::vector<std::reference_wrapper<T>> vec;     // OK - does what you want
    std::vector<T&> vec2;                           // Nope! Will not compile


//펑터 자체 대신 펑터를 참조하는 참조 래퍼를 전달하면 해당 복사를 방지 할 수 있습니다
//  reference_wrappers 오버로드 operator() 이므로 참조하는 함수 객체처럼 호출할 수 있습니다.
//  일반적인 참조와 달리 복사(및 할당) reference_wrappers는 pointer를 할당합니다
// 
//일반 포인터와의 차이점
//  추가적인 수준의 구문적 간접 지정은 없습니다. 암시적 변환 연산자 가 있으며 래핑된 객체처럼 호출
//  포인터와 달리 null 상태가 아닙니다. 그것들은 참조 또는 다른 reference_wrapper 것으로 초기화되어야 합니다
//
//유사점은 얕은 복사 의미 체계입니다. 
//  포인터와 reference_wrappers를 다시 할당 할 수 있습니다.

//주의점
//
//    reference_wrapper는 실제로 참조를 “소유”하지 않습니다.
//    즉, 원본 객체가 사라지면 dangling reference가 됩니다.
//    참조를 저장하는 것이므로 수명 관리에는 여전히 주의해야 합니다.

