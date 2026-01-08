//모듈 ---------------------------------------------------------------------------------
https://en.cppreference.com/w/cpp/language/modules

// helloworld.cpp
export module helloworld;  // 모듈 선언
import <iostream>;         // 임포트 선언

export void hello() {      // 내보내기 선언
    std::cout << "Hello world!\n";
}

// main.cpp
import helloworld;  // 임포트 선언

int main() {
    hello();
}

//Module declarations ----------------------------------------------------------------

//번역 단위에는 모듈 선언이 있을 수 있으며, 제공된 경우 번역 단위의 첫 번째 선언이어야 합니다

export module A;   // 명명된 모듈 'A'에 대한 기본 모듈 인터페이스 단위를 선언합니다.
module A;          // 명명된 모듈 'A'에 대한 모듈 구현 단위 선언
export module A.B; // 명명된 모듈 'A.B'에 대한 기본 모듈 인터페이스 단위를 선언합니다.
module A.B;        // 명명된 모듈 'A.B'에 대한 모듈 구현 단위 선언


//선언 및 정의 내보내기 ----------------------------------------------------------------

export module A;   // 명명된 모듈 'A'에 대한 기본 모듈 인터페이스 단위를 선언합니다.

// hello()는 'A'를 가져오는 번역 단위에서 볼 수 있습니다.
export char const* hello() { return "hello"; }

// world()는 표시되지 않습니다.
char const* world() { return "world"; }

// one()과 zero()가 모두 표시됩니다.
export {
    int one() { return 1; }
    int zero() { return 0; }
}

// 네임스페이스 내보내기도 작동합니다. hi::english() 및 hi::french()가 표시됩니다.
export namespace hi {
    char const* english() { return "Hi!"; }
    char const* french() { return "Salut!"; }
}

//Global module fragment (전역 모듈 조각) ----------------------------------------------------
//      모듈 단위는 접두사로 사용할 수 있습니다.
//      전역 모듈 조각, 가져올 때 헤더 파일을 포함하는 데 사용할 수 있습니다
//      (특히 헤더 파일이 전처리 매크로를 구성으로 사용하는 경우).

/////// A.cpp('A'의 기본 모듈 인터페이스 단위)
module;

// _POSIX_C_SOURCE를 정의하면 표준 헤더에 기능이 추가됩니다. // POSIX 표준에 따릅니다.
#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>

export module A;

import <ctime>;

// 시연용(불량 랜덤성의 원인). 대신 C++ <random>을 사용하십시오.
export double weak_random() {
    std::timespec ts;
    std::timespec_get(&ts, TIME_UTC); // <ctime>에서
    // POSIX 표준에 따라 <stdlib.h>에 제공됩니다.
    srand48(ts.tv_nsec);
    // drand48()은 0과 1 사이의 난수를 반환합니다.
    return drand48();
}

/////// main.cpp(모듈 단위 아님)
import <iostream>;
import A;

int main() {
    std::cout << "Random value between 0 and 1: " << weak_random() << '\n';
}


//Private module fragment (개인 모듈 조각) ---------------------------------------------
//   모듈 인터페이스 단위의 부분을 끝냅니다.

export module foo;
export int f();

module :private;    // 모듈 인터페이스 유닛의 다음 부분을 끝냅니다.
                    // 다른 번역 단위의 동작에 영향을 줄 수 있습니다.
                    // 개인 모듈 조각을 시작합니다.

int f() {           // foo의 임포터에서 접근할 수 없는 정의
    return 42;
}

// Module partitions -----------------------------------------------------------------

export module A:B; // Declares a module interface unit for module 'A', partition ':B'.

//모듈 파티션은 정확히 하나의 모듈 단위를 나타냅니다
//모듈 파티션은 '이름이 같은 모듈'의 모듈 단위로 가져올 수 있습니다. 

///////  A.cpp  ----------------------

export module A;     // primary module interface unit

export import :B;    // Hello() is visible when importing 'A'.
import :C;           // WorldImpl() is now visible only for 'A.cpp'.
// export import :C; // ERROR: Cannot export a module implementation unit.

// World() is visible by any translation unit importing 'A'.
export char const* World()
{
    return WorldImpl();
}

/////// A-B.cpp ----------------------

export module A:B; // partition module interface unit

// Hello() is visible by any translation unit importing 'A'.
export char const* Hello() { return "Hello"; }

/////// A-C.cpp ----------------------

module A:C; // partition module implementation unit

// WorldImpl() is visible by any module unit of 'A' importing ':C'.
char const* WorldImpl() { return "World"; }

/////// main.cpp ----------------------

import A;
import <iostream>;

int main()
{
    std::cout << Hello() << ' ' << World() << '\n';
    // WorldImpl(); // ERROR: WorldImpl() is not visible.
}


// Module ownership ------------------------------------------------------------------------

//선언이 명명된 모듈에 첨부되고 내보내지 않으면 선언된 이름에 module linkage 가 있습니다

export module lib_A;

int f() { return 0; } // f has module linkage
export int x = f();   // x equals 0


export module lib_B;

int f() { return 1; } // OK, f in lib_A and f in lib_B refer to different entities
export int y = f(); // y equals 1


//둘 다 외부 링크로 이름을 선언하면 프로그램이 잘못 구성됩니다. (약한 소유권 모델, 강한 소유권 모델)

export module lib_A;

export constexpr int f() { return 0; } // f has external linkage


export module lib_B;

export constexpr int f() { return 1; }
// In the   weak ownership model:  multiple definitions of f; the linker may pick either
// In the strong ownership model:  OK, f in lib_A and f in lib_B are different entities

