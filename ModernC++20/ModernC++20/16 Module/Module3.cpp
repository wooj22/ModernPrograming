//모듈의 이름 Module Names

    //모듈의 이름이 "." 으로 결합되어야하고, 0이 아닌 이름을 써야 함.

    boost.asio.async_completion   //논리적 계층 구조를 이해하기 쉽습니다.

    boost_asio_async_completion     
    

//모듈 단위 ( Module Unit )

    C++ 소스를 캡슐화하는 Translation Unit이 있었습니다. (header와 cpp를 분리하는 것)
    C++ Module은 Module Unit이라는 새로운 유형의 Translation Unit을 도입한 것이다.

    Module Unit은 'module-declaration'이 포함된 translation unit 이다.
    최상위 레벨에 'Module line'이 포함된 모든 파일은 'Module Unit' 입니다.

//모듈 파티션

    Module Interface Unit					모듈 인터페이스 단위 : module-declaration 에 export 키워드가 포함된 모든 Module Unit
    Module Implementation Unit			    모듈 구현 단위

    Module Partition Interface Unit		    모듈 파티션 인터페이스 단위
    Module Partition Implementation Unit	모듈 파티션 구현 단위


//모듈, 네임스페이스 및 인수 종속 조회

//모듈 파티션
//	모듈 파티션은 모듈 전체의 모든 선언에 대한 소유권을 공유하는 것을 제외하고 모듈과 비슷합니다.
//	파티션 인터페이스 파일에서 내보낸 모든 이름은 
//      기본 인터페이스 파일에서 가져오고 다시 내보냅니다.
//	파티션의 이름은 모듈 이름 뒤에 콜론으로 시작해야 합니다.

//  ":" 대신 "."으로 나타내면, 다른 언어의 모듈 디자인과 혼동 우려.
//  C++ module은 hierarchy 구조가 아니기 때문.
//  speech.english와 speech.korean은 그저 speech의 서브 모듈일 뿐. 완전히 분리되어 있다.

//https://learn.microsoft.com/ko-kr/cpp/cpp/modules-cpp?view=msvc-170


//------------------------------------------------------------------------

export module speech;

export const char* GetPhraseEN() {
    return "Hello, Module!";
}

export const char* GetPhraseKR() {
    return "안녕, 모듈!";
}
//-----------------------------------------------------------

// speech_english.cpp           

export module speech:english;   //모듈 파티션

export const char* GetPhraseEN() {
    return "Hello, Module!";
}

// speech_korean.cpp            

export module speech:korean;    //모듈 파티션

export const char* GetPhraseKR() {
    return "안녕, 모듈!";
}
 
// speech.ixx

export module speech;           //기본 인터페이스 //다시 내보낸다.

export import : english;
export import : korean;

//-----------------------------------------------------------
//개선안
//implementation unit을 수정하여도 primary interface에 영향을 주지 않으므로, 빌드 시간이 절약
 
// speech.ixx

export module speech;

import : english;
import : korean;

export const char* GetPhraseEN();
export const char* GetPhraseKR();

// speech_english.cpp

module speech:english;

const char* GetPhraseEN() {
    return "Hello, Module!";
}

// speech_korean.cpp

module speech:korean;

const char* GetPhraseKR() {
    return "안녕, 모듈!";
}

