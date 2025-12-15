//템플릿 분기문  // SFINAE, enable_if 


//함수가 템플릿 버전, 정수 버전, 가변인자 버전 세 개가 있을 때 
//함수 찾는 순서 
//      1. 1순위 정확한 매칭 ( Exactly matching )
//      2. 2순위 템플릿 ( template )
//      3. 3순위 가변 인자 ( Variable argument )

#include <iostream>
#include <functional>
using namespace std;

template<typename T>
void foo(T t) { cout << "T" << endl; }              //템플릿

void foo(int n) { cout << "int" << endl; }          //매칭

void foo(...) { cout << "..." << endl; }            //가변 인자

int main()
{
    foo(7);
}


//SFINAE -----------------------------------------------------------------------
//      - Substitution failure is not an error
//      함수 템플릿을 사용 시 T의 타입이 결정되고 함수를 생성(Instantiation)할 때 
//      리턴 타입이나 함수 인자 등에서 치환에 실패하면 
//      컴파일 에러가 아니라 함수 후보에서 제외한다.
//      동일한 이름의 다른 함수가 있다면 다른 함수를 사용하게 됨.

template<typename T>
typename T::type foo(T t)  //int::type 은 없다. //문법 오류 //함수 후보에서 이 템플릿 함수를 제외
{
    cout << "T" << endl;
    return 0;
}

void foo(...) { cout << "..." << endl; }

int main()
{
    foo(7);     //어떤 함수를 사용할까? // error?

    // 가변인자 함수보다 템플릿 함수가 우선순위가 높아서 먼저 참조하게 되지만 
    // 리턴 타입에서 int 타입::type은 존재하지 않으므로 만족할 수 없으므로 
    // 후보군에서 제외되고 가변인자 버전의 함수가 사용됨
}


//enable_if 와 같이 SFINAE 활용하기 ----------------------------------------------------

//enable_if 구현
// 
//  enable_if 개념 예시 : 1번째 인자가 true일 경우만 type이 정의됨. ***
//      enable_if<true, int>::type   -> int     
//      enable_if<false, int>::type  -> error   
//      enable_if<true>::type        -> void

#include <iostream>

template<bool b, typename T = void>
struct enable_if { };

template<typename T>                //부분특수화
struct enable_if<true, T> {
    typedef T type;
};

int main()
{
    enable_if<true, int>::type t1;  // int

    enable_if<true>::type t2;       // void - void로는 실제 변수 정의가 안됨
    enable_if<false, int>::type t3; // 에러. type이 없음
    enable_if<false>::type t4;      // 에러. type이 없음
}

//enable_if 사용 ---------------------------------------------------------------------
// 
//      특정 타입으로 템플릿을 제한하여 사용하고 싶거나 타입별로 분기를 한다거나 할 때 사용
//      <type_traits> 사용하면 됨 *** 

//예시) 정수일때만 동작하는 함수를 만들고 싶을 때 

// enable_if 위치 //함수 리턴 타입에 사용해서 의도적 실패를 만든다.

#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
typename enable_if<is_integral<T>::value, T>::type    //  T가 is_integral 이면, T가 정상 컴파일
add(T a, T b) { return a + b; }

void add(...) { cout << "..." << endl; }

int main()
{
    cout << add(1, 2);
}


// enable_if 위치 //템플릿 인자에 enable_if를 추가하는 방법

#include <iostream>
using namespace std;

template<typename T, typename enable_if<is_integral<T>::value>::type* = nullptr>
void foo(T a)
{
    cout << "foo<T>" << endl;
}

int main()
{
    foo(1);             // int 이므로 ok
    foo(1.5);           // double 이므로 컴파일 에러
}


//클래스의 생성자의 경우에는 리턴값이 없기 때문에 위와 같은 방법으로는 사용할 수가 없다. 
//타입이 생성조차 안되게 하고 싶으면 어떻게 할까?

// enable_if 위치 //생성자 파라미터에서 enable_if를 사용하여 타입 체크하면 된다.

#include <iostream>
using namespace std;

template<typename T>
class Test {
public:
    Test(typename enable_if<is_integral<T>::value>::type* = nullptr) { } 
};

int main()
{
    Test<int> t1;       // int 이므로 ok
    Test<double> t2;    // double 이므로 컴파일 에러
}
