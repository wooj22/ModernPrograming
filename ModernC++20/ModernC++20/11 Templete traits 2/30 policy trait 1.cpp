//속성 특질(property trait)
//		템플릿 파라미터의 속성을 결정하기 위해 사용
//		데이터형의 종류는 무엇인지, 혼합된 데이터형 연산에서 어떤 데이터형으로 데이터형 승격해야 할 것인지 등을 결정
// 
//정책 특질(policy trait)
//		특정 데이터형을 어떻게 취급해야하는 지 정의 하는 것
//		정캑 클래스의 개념과 유사
//		속성 특질은 데이터형 함수로 구현될 수 있는데 정책 특질은 일반적으로 멤버 함수 내에 정책으로 캡슐화된다.

//복사 교환과 이동
//성능을 개선하기 위해 특정 데이터형의 요소를 복사, 교환 이동하기 위한 최적의 연산을 선택하는 정책 특질 템플릿을 도입
//스마트 포인터를 개발할때 사용.

// traits/csmtraits.hpp template <typename T> 
class CSMtraits : public BitOrClassCSM<T, IsClassT<T>::No > { };

//BitOrClassCSM<>의 특수화를 대표하고 있다.( CSM 복사 교환 이동 copy swap move의 줄임말이다.) 
//두 번째 템플릿 파라미터는 다양한 연산을 구현할 때 비트 단위 복사가 안전하게 사용될수 있는지 나타낸다. 

//기번 템플릿과 비트 단위 복사를 하지 않는 안전한 부분 특수화

// traits/csm1.hpp 

#include <new> 
#include <cassert> 
#include <stddef.h> 
#include "rparam.hpp" 

// 기본 템플릿 primary template 
template<typename T, bool Bitwise>
class BitOrClassCSM;

// 안전한 복사를 위한 부분 특수화 partial specialization  
template<typename T>
class BitOrClassCSM<T, false> {
public:
    static void copy(typename RParam<T>::ResultT src, T* dst) {
        // 한 아이템을 다른 것으로 복사
        *dst = src;
    }

    static void copy_n(T const* src, T* dst, size_t n) {
        // n개의 아이템을 다른 n개로 복사 
        for (size_tk = 0; k < n; ++k) {
            dst[k] = src[k];
        }
    }

    static void copy_init(typename RParam<T>::ResultT src,
        void* dst) {
        // 아이템을 초기화 되지 않는 저장소로 복사
        ::new(dst) T(src);
    }

    static void copy_init_n(T const* src, void* dst, size_t n) {
        // n개의 아이템을 초기화되지 않는 저장소로 복사
        for (size_tk = 0; k < n; ++k) {
            ::new((void*)((char*)dst + k)) T(src[k]);
        }
    }

    static void swap(T* a, T* b) {
        // 두 아이템 교환
        T tmp(a);
        *a = *b;
        *b = tmp;
    }

    static void swap_n(T* a, T* b, size_t n) {
        // n개 아이템 교환
        for (size_tk = 0; k < n; ++k) {
            T tmp(a[k]);
            a[k] = b[k];
            b[k] = tmp;
        }
    }

    static void move(T* src, T* dst) {
        // 한 아이템을 다른 곳으로 이동 
        assert(src != dst);
        *dst = *src;
        src->~T();
    }

    static void move_n(T* src, T* dst, size_t n) {
        // n개의 아이템을 다른 n개로 이동 
        assert(src != dst);
        for (size_tk = 0; k < n; ++k) {
            dst[k] = src[k];
            src[k].~T();
        }
    }

    static void move_init(T* src, void* dst) {
        // 아이템을 초기화 되지 않은 저장소로 이동 
        assert(src != dst);
        ::new(dst) T(*src);
        src->~T();
    }

    static void move_init_n(T const* src, void* dst, size_t n) {
        // n개의 아이템을 초기화 되지 않은 저장소로 이동 
        assert(src != dst);
        for (size_tk = 0; k < n; ++k) {
            ::new((void*)((char*)dst + k)) T(src[k]);
            src[k].~T();
        }
    }
};

//복사할 수 있는 비트 단위 데이터형을 위한 특질을 구현하는 부분 특수화

// traits/csm2.hpp 

#include <cstring> 
#include <cassert> 
#include <stddef.h> 
#include "csm1.hpp" 

//객체의 빠른 비트단위 복사를 위한 부분 특수화 partial specialization 
template <typename T>
class BitOrClassCSM<T, true> : public BitOrClassCSM<T, false> {
public:
    static void copy_n(T const* src, T* dst, size_t n) {
        // n개 아이템을 다른 n개로 복사
        std::memcpy((void*)dst, (void*)src, n);
    }

    static void copy_init_n(T const* src, void* dst, size_t n) {
        // n개 아이템은 초기화 되지 않은 저장소로 복사
        std::memcpy(dst, (void*)src, n);
    }

    static void move_n(T* src, T* dst, size_t n) {
        // n개 아이템은 다른 n개의 아이템으로 이동
        assert(src != dst);
        std::memcpy((void*)dst, (void*)src, n);
    }

    static void move_init_n(T const* src, void* dst, size_t n) {
        // n개의 아이템을 초기화 되지 않는 저장소로 이동 
        assert(src != dst);
        std::memcpy(dst, (void*)src, n);
    }
};