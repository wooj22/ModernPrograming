//lambda expression
//		람다는 함수 객체를 만드는데 굉장히 유용한 방법이다.

/*
//람다에 관련된 용어들 정리하고 넘어가자.

람다 표현식(lambda expression)은

    단순한 표현식이다. 이는 소스코드의 일부이다. 익명 함수를 만든다.
    std::find_if(container.begin(), container.end(), [](int val) { return 0 < val && val < 10; });
    이 코드에서[](...) { ~ } 부분이 람다 표현식이다.

클로져(closure)는

    람다에 의해 런타임에 생성되는 객체이다. (닫힌 람다식)
    캡쳐 모드에 따라 클로져는 캡쳐된 데이터의 복사본 또는 레퍼런스를 갖고 있게 된다.

    std::find_if(container.begin(), container.end(), [](int val){ return 0 < val && val < 10; });
    위 코드의 std::find_if의 호출에서 런타임에 세 번째 인자(람다 표현식으로 정의된)로 넘어가는 객체가 바로 클로져다.

클로져 클래스(closure class)는

    클로져가 인스턴스화된 클래스다.
    각각의 람다는 컴파일러가 고유한 클로져 클래스를 만들게 한다.
    람다 표현식 내부의 문장(statement)들은
    그 람다 표현식으로 인해 생성되는 클로져 클래스의 멤버 함수 속의 실행 가능한 명령문(instruction)이 된다.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
    //람다로부터 생성된 클로져는 복사가 가능하다.
    //따라서 하나의 클로져 타입에 대해 여러 개의 클로져가 존재할 수도 있다.

    int x;
    auto c1 = [x](int y) { return x * y > 10; };  //c1 람다에 대한 복사본
    auto c2 = c1;
    auto c3 = c2;

    return 0;
}

/*
// lambda와 closure --------------------------------------------------------
//
//      lambda는 closure가 아니다.
//      단지 lambda를 이용하여 closure의 특성을 구현해 낼 수 있는 것
//      함수객체 형태로 closure 구현. (함수객체가 아니다.)
//		클로저는 람다의 인스턴스.
//		auto 키워드를 사용하면 람다의 클로저를 아주 간단하게 저장할 수 있다.
//		auto로 저장한 클로저 객체는 상수화가 이루어져 변경이 불가능하므로 컴파일러에서 inline 화를 가능케 한다.

*/

#include <iostream>
#include <functional>

std::function<void(void)> closureWrapper1()
{
    int x = 10;
    return [x]() {std::cout << "Value in the closure: " << x << std::endl; };
}

std::function<void(void)> closureWrapper2()
{
    int x = 10;
    return [&x]() {x += 1; std::cout << "Value in the closure: " << x << std::endl; };
}

int main()
{
    int x = 10;
    auto func0 = [&x]() {x += 1; std::cout << "Value in the closure: " << x << std::endl; };  //클로저
    std::function<void(void)> func1 = closureWrapper1();        //std::function 래퍼 오브젝트
    std::function<void(void)> func2 = closureWrapper2();        //std::function 래퍼 오브젝트
    func0();
    func0();
    func0();
    std::cout << "-------------------------" << std::endl;
    func1();
    func1();
    func1();
    std::cout << "-------------------------" << std::endl;
    func2();
    func2();
    func2();
}

//스콧 마이어(Scott Meyers) 
// "람다와 클로저의 차이는 클래스와 클래스 인스턴스 사이의 차이점과 동일하다"
//  클래스는 오직 소스 코드에만 존재하며 런타임에 존재하지 않습니다. 
//  클래스 인스턴스만이 런타임에 존재합니다.
// 
//C++에서는 람다 표현식이 인스턴스화 된 것을 클로저라 합니다.

//람다 식은
//함수에 인수로 호출되거나 전달되는 위치에서 바로 익명 함수개체 (클로저)를 정의하는 편리한 방법

