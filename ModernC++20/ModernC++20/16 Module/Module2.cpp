//VC 20++  //프로젝트에서  'C++ 모듈 인터페이스 단위(.ixx)'를 선택하여 파일을 생성한다.

// ModuleA.ixx 모듈 인터페이스 파일

export module ModuleA;      // 내보낼 모듈의 이름 지정

namespace Foo
{
    export int MyIntFunc()  // 모듈에서 내보낼 기능(함수)의 인터페이스를 지정
    {
        return 0;
    }

    export double MyDoubleFunc()
    {
        return 0.0;
    }

    void InternalMyFunc()   // 모듈 내부에서만 사용하는 함수
    {
    }
}

//아래 예제와 같이 기존 .h, .cpp 구조 처럼 나눠서 작성할 수도 있다. -------------------------------------

// ModuleA.ixx  //선언만 있는 모듈 인터페이스 파일

export module ModuleA;      // 내보낼 모듈의 이름 지정

namespace Foo
{
    export int MyIntFunc();

    export double MyDoubleFunc();

    void InternalMyFunc();
}

// ModuleA.cpp  //모듈 구현 파일

module ModuleA;         // 시작 부분에 모듈 선언을 배치하여 파일 내용이 명명된 모듈(ModuleA)에 속하도록 지정

namespace Foo
{
    int MyIntFunc()     // 구현에서는 export 키워드가 빠진다.
    {
        return 0;
    }

    double MyDoubleFunc()
    {
        return 0.0;
    }

    void InternalMyFunc()
    {
    }
}


//module은 각 컴파일러마다 각각 다른 방식으로 작성된다 ***
//
//  cl.exe는 비주얼 스튜디오의 컴파일러 이름이다.
//  cl.exe는 모듈을 선언하기 위해 확장자가 ixx인 모듈 인터페이스 파일을 사용한다.
//  module, import 및 export 선언은 C++20에서 사용할 수 있으며 
//  C++20 컴파일러를 사용한다는 스위치 활성화가 필요하다(/std:c++latest )
//
//  gcc의 경우 모듈을 선언하기 위해 .cpp 파일을 사용하지만 
//  컴파일 시 - fmodules - ts 옵션을 이용
//  gcc 버전 11이상이 필요


//모듈은 어떻게 빠른 컴파일 속도를 제공하는가 ? ***
//
//  모듈의 경우는 일단 모듈이 컴파일 되고 나면 
//  각 빌드 단위(cpp)에서 템플릿 함수를 생성하고 컴파일하는 것이 아니라 
//  단순히 모듈에 기술된 내용을 링크만 함으로써 
//  컴파일에 소모되는 시간을 대폭 감소 시킬 수 있다.


// 전처리 시 #include와 달리 모듈은 한번만 가져오므로 빌드 시간을 단축할 수 있다.
// #define과 달리 모듈은 가지고 오는 순서에 상관 없이 항상 동일한 결과를 가진다.

