//람다를 사용한 예시. //배열 소트하기 // 람다사용

#include<iostream>
using namespace std;

template <class T>
void simple_sort(int* arr, int n, T cmp) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (cmp(arr[i], arr[j]))
                arr[i] ^= arr[j] ^= arr[i] ^= arr[j];
        }
    }
}

void print(int* arr, int n) {
    for (int i = 0; i < 5; i++) cout << arr[i] << " ";
    cout << endl;
}

int main(void) {
    int arr[5] = { 10, 5, 41, 100, 2 };

    simple_sort(arr, 5, [](int a, int b) { return (a < b ? true : false); });
    print(arr, 5);

    simple_sort(arr, 5, [](int a, int b) { return (a > b ? true : false); });
    print(arr, 5);

    return 0;
}

// 컴파일 과정에서 람다라는 객체를 생성한다. 

// 인라인화 가능 
// auto로 저장한 클로저 객체는 상수화가 이루어져 변경이 불가능하므로 컴파일러에서 inline화를 가능케 한다. ***

// 포인터를 사용해 간접 전달이 되거나 명확하게 명시되어 있지 않으면 (람다를 담을 변수가 상수화 되지 않으면) 
// 일반함수 처럼. 인라인화 불가.

#include<iostream>
#include<functional>

int main(void) {

    auto f1 = [](int a, int b) {                            //인라인화 OK!!
        return a + b;
    };


    int(*f2)(int, int) = [](int a, int b) {                 //인라인화 Fail!!
        return a + b;
    };
    //함수 포인터의 경우 변경이 가능하므로 컴파일러에서 이 코드를 inline 형태로 바꿔줄 수 없고 캡처도 지정할 수 없다.


    std::function<int(int, int)> f3 = [](int a, int b) {    //인라인화 Fail!!
        return a + b;
    };
    //std::function<>은 모든 함수를 담을 수 있도록 설계되어있다, f3 변경가능.

    return 0;
}​

//https://en.cppreference.com/w/cpp/language/lambda
//https ://docs.microsoft.com/ko-kr/cpp/cpp/lambda-expressions-in-cpp?view=msvc-160


/*

// lambda와 closure --------------------------------------------------------
//
//      lambda는 closure가 아니다.
//      단지 lambda를 이용하여 closure의 특성을 구현해 낼 수 있는 것
//      함수객체 형태로 closure 구현.

//      '람다'라는 것은 람다 표현식의 준말이고, 그저 표현식일 뿐이다.
//      람다 표현식에 대한 런타임 결과는 오브젝트의 생성이다.  그러한 오브젝트를 클로져라고 한다.
//      각 람다 표현식은 컴파일 과정에서 고유한 클래스를 만들어내고,
//      그 클래스 타입의 오브젝트(클로져)가 (런타임에서) 생성된다.
//
// closure
//      일급 객체 함수(first-class functions)의 개념을 이용하여
//      유효범위(scope)에 묶인 변수를 바인딩 하기 위한 일종의 기술
//      기능상으로, 클로저는 함수를 저장한 레코드(record).
//      클로저는 자신이 생성될 때의 환경(Lexical environment)을 기억하는 함수다.

*/