// 템플릿 별칭 예시

// vector 에 커스텀 allocator 사용하기 -------------------

#include <iostream>
#include <vector>
using namespace std;

template <typename T> struct MyAlloc {
    typedef T value_type;

    MyAlloc() { }
    template <typename U> MyAlloc(const MyAlloc<U>&) { }

    bool operator==(const MyAlloc&) const { return true; }
    bool operator!=(const MyAlloc&) const { return false; }

    T* allocate(const size_t n) const {
        if (n == 0) { return nullptr; }
        if (n > static_cast<size_t>(-1) / sizeof(T)) {
            throw std::bad_array_new_length();
        }
        void* const pv = malloc(n * sizeof(T));
        if (!pv) { throw std::bad_alloc(); }
        return static_cast<T*>(pv);
    }

    void deallocate(T* const p, size_t) const {
        free(p);
    }
};

// 템플릿 별칭이 가능하기 전엔, 템플릿 구조체안으로 별칭을 숨겨야했다.
template <typename T>
struct xvector {
	typedef vector<T, MyAlloc<T>> type;
};

int main() 
{
    xvector<int>::type idList{ 1, 2, 3 };       //xvector<int>::type
}

// 템플릿 별칭 사용해서 간략히 표현하세요 ***
/*
    template <typename T>
    using xvector = vector<T, MyAlloc<T>>;
 
    int main() 
    {
        xvector<int> idList{ 1, 2, 3 };             //type 필요 없음
    }
*/