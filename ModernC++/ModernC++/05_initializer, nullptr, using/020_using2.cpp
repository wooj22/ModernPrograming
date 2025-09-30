//예시
#include <stdlib.h>
#include <new>

template <typename T> struct MyAlloc        //Alloc 을 직접 정의한다.
{
    typedef T value_type;

    MyAlloc() { }
    template <typename U> MyAlloc(const MyAlloc<U>&) { }

    bool operator==(const MyAlloc&) const { return true; }
    bool operator!=(const MyAlloc&) const { return false; }

    T* allocate(const size_t n) const {
        if (n == 0) {
            return nullptr;
        }

        if (n > static_cast<size_t>(-1) / sizeof(T)) {
            throw std::bad_array_new_length();
        }

        void* const pv = malloc(n * sizeof(T));

        if (!pv) {
            throw std::bad_alloc();
        }

        return static_cast<T*>(pv);
    }

    void deallocate(T* const p, size_t) const {
        free(p);
    }
};


#include <vector>
#include <iostream>

using MyIntVector = std::vector<int, MyAlloc<int>>;         //using

int main()
{
    MyIntVector foov = { 1701, 1764, 1664 };

    for (auto a : foov) std::cout << a << " ";
    std::cout << "\n";

    return 0;
}