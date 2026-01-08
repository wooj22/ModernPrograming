//Module
//		기존의 #include 방식인 Translation Unit 방식과는 다른, 별개의 컴파일되는 소스 코드 파일의 집합
// 
//		'Header파일을 사용'하면서 생겨나는 많은 문제를 제거하거나 줄이고, 컴파일 시간을 단축한다.
//		선언된 모든 매크로, 전처리 지시문과 export 하지 않는 이름(names)들은 '표시되지 않으며', 
//		컴파일 할 때 영향을 주지 않습니다.
//		또한 '순서에 관계 없이' 가져올 수 있습니다. (include, import)
//
//      C++ module은 java 의 package나 php의 namespace, C#의 namespace와 동일한 역할을 합니다.

//기존의 #include는 단순히 문자열의 복사 붙여넣기 과정을 거칩니다.
//  
// 	    컴파일러는 같은 정보들을 여러번 작성합니다.
// 	    링커들은 이 정보들을 모두 엮어줘야 합니다 -> 이로 인해 빌드 처리량이 심하게 증가합니다. 
// 
//      또한 일관성이 보장되지 않습니다.
//  	버그를 추적하기가 힘듭니다. (ODR 위반)
//      % ODR( One Definition Rule )이란? : '하나의 정의 규칙', '원본 텍스트의 정확히 한 부분만 존재하는 것'
//	    구성요소간의 구분이 없고, 적용이 깨지기 쉽습니다.
//
//      C의 전처리기 기술은 구성요소를 분석/해석 하는데 정확할 수가 없습니다.
//      -> 모든 매크로들에 대해서 알아야만 합니다.

//기존 헤더 방식의 구조적 문제 :
//      중복 파싱 : 같은 헤더를 모든 번역 단위에서 반복 파싱
//      매크로 오염 : 전역 매크로, include 순서 의존성
//      컴파일 시간 증가
//      캡슐화 불가 : private 구현을 헤더에 노출해야 함

//module을 지원하면서 원하는 목표는 다음과 같습니다. ***
//		구성요소화
//		매크로들로부터의 격리화
//		빌드처리량 증가(Build throughput)
//		현대식 표현방식을 아는 개발자툴을 지원하기


//Header파일은 더 이상 존재하지 않고, cpp 파일만이 존재하며 
// 
//      module 키워드의 선언으로 원하는 코드들을 하나로 묶을 수 있으며, ***
//      export 키워드를 통해 사용할 코드를 선언합니다.
//      import 키워드를 통해 원하는 모듈의 코드를 사용할 수 있습니다. ***
// 
//  물론 얼마든지 import 하여도 반드시 단 한번만 참조합니다. (즉, 전처리문을 사용해서 중복을 방지할 필요가 없습니다.)

//기존 코드와 함께 사용하기 (절충안)
// 
//      module은 Header 파일과 함께 사용될 수 있습니다. 
//      module을 가져올 수 있으며, Header파일을 #include 할 수도 있습니다.
//      경우에 따라선, module로 Header파일을 가져올 수도 있습니다.


//예시 -------------------------------------------------------------------------------------
/*
    1. Project 속성 / "C/C++" / "언어"  에서 
        C++ 언어 표준을       - std:c++latest로 변경합니다.  ***
        모듈 사용 - 실험적 도 - 선택합니다. ***
        C++23/26에서 표준 라이브러리 모듈화 확대 ***

    2. C++ 모듈기능 라이브러리 설치 확인
        Visual Studio 2019 의 경우는
        Visual Studio Installer 에서 자신이 사용하는 Visual Studio 2019에 대해 수정을 선택하고,
        v143 빌드 도구용 C++ 모듈(x64/x86-실험적) 을 설치합니다.  ***

    3. Solution -> Project ->"소스 파일" 에서 
       -> 모듈을 선택한 후, "speech"라는 모듈을 생성합니다. ***

       기본적인 모든 모듈의 확장자는.ixx입니다. ***
*/

// speech.ixx ----------------------------------------------

export module speech;   //모듈의 이름(speech)과 경계를 정의.

export const char* GetPharse() {
    return "Hello, Module";
}

// main.cpp ------------------------------------------------

import std;
import speech;      //모듈의 사용

using namespace std;

int main() {
    cout << GetPharse() << endl;
}


//매우 간단한 예입니다.speech라는 모듈이 있습니다.

//main.cpp의 import를 통해 speech내의 정의된 단일 함수 'GetPharse'를 사용합니다.

//export는 모듈이 다른 소스 파일에서 보일 수 있도록 하는 것입니다.
//import는 export된 모듈이 단지 '번역 단위'에 의해 내 소스 파일에서 보일 수 있도록 하는 것입니다.

//module : 모듈의 이름을 지정
//         eg) module Math : 모듈의 이름은 'Math'이다. 
//import : 가져올 모듈의 이름을 지정     
//         eg) import Math : 가져올 대상 모듈의 이름은 'Math'이다.
//export : 모듈에서 내보낼 기능(함수)의 인터페이스를 지정
//         eg) export int sum(int, int) : 내보낼 함수의 이름은 sum이고 리턴 타입은 int, 인자는 int, int다.


//C++이 제공하는 표준 라이브러리 -------------------------------------------------------------------
// std.core
// std.regex
// std.filesystem
// std.memory
// std.threading  //<atomic>, <thread>, <condition_variable>, <future><mutex>, <shared_mutex> 

import std.core;
import std.memory;
import std.threading;

int main()
{
    std::thread t([] { std::cout << "func() called." << std::endl; });
    std::cout << "Main function" << std::endl;
    t.join();

    auto ptr = std::make_unique<int>(5);
    (*ptr)++;
    std::cout << "*ptr: " << *ptr << std::endl;
}

//인터페이스 / 구현 분리 예제 -------------------------------------------------------------------

// math.ixx(인터페이스)

export module math;

export int add(int, int);

// math.cpp(구현)

module math;

int add(int a, int b)
{
    return a + b;
}


//Global Module Fragment -----------------------------------------------------
//      모듈의 전역 부분 
//      기존 헤더와의 공존을 위한 영역:

module;                 // global module fragment
#include <cmath>
#include <vector>

export module math;

// module; 위     → 기존 전처리 영역
// STL은 아직 대부분 헤더 기반 → 실무에서 거의 필수


//Module + 템플릿 -------------------------------------------------------------

export module algo;

export template<typename T>
T max(T a, T b)
{
    return a > b ? a : b;
}

//템플릿도 정상 지원
//헤더-only 강제에서 벗어남 → 컴파일 시간 크게 감소



// Module은 include를 대체하는 기능이 아니라, 컴파일 모델을 교체하는 것이다. ***
// 
//  C++23/26에서 표준 라이브러리 모듈화 확대
//  C++26: 진짜 구조적 변화가 들어오는 단계
//  C++의 빌드 모델 자체가 바뀌는 장기 전환입니다
// 
//  게임 / 엔진 개발 관점(중요)
//      Unity / Unreal 기준 :
//          엔진 코어 : 아직 헤더 중심
//          툴 / 서버 / 빌드 파이프라인 : 모듈 도입 가치 높음
//          컴파일 시간 병목이 큰 곳부터 적용
//      "엔진 전체 모듈화"는 시기상조
//      "엔진 주변부 모듈화"는 지금이 적기


