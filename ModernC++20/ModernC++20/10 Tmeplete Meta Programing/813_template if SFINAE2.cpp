//타입의 종류에 따라 다르게 동작하는 함수 템플릿을 만드는 방법
//      if constexpr     
//      함수 오버로딩
//      enable_if (스피네)     


// type_traits (is_pointer) + if constexpr    - C++17 이후에서만 가능 ***

#include <type_traits>
#include <iostream>
using namespace std;

template<typename T>
void printVal(const T& v)
{
    if constexpr (is_pointer<T>::value)
    {
        cout << v << " : " << *v << endl;
    }
    else
    {
        cout << v << endl;
    }
}

int main()
{
    int n = 7;
    printVal(n);
    printVal(&n);
}


// type_traits + 함수 오버로딩 (trye_type / false_type)

#include <type_traits>
#include <iostream>
using namespace std;

template<typename T>
void printValImpl(const T& v, true_type)
{
    cout << v << " : " << *v << endl;
}

template<typename T>
void printValImpl(const T& v, false_type)
{
    cout << v << endl;
}

template<typename T>
void printVal(const T& v)
{
    printValImpl(v, is_pointer<T>());
}


int main()
{
    int n = 7;
    printVal(n);
    printVal(&n);
}


// type_traits + enable_if  사용 방법

#include <type_traits>
#include <iostream>
using namespace std;

template<typename T>
typename enable_if<is_pointer<T>::value>::type
printVal(const T& v)
{
    cout << v << " : " << *v << endl;
}

template<typename T>
typename enable_if<!is_pointer<T>::value>::type
printVal(const T& v)
{
    cout << v << endl;
}

int main()
{
    int n = 7;
    printVal(n);
    printVal(&n);
}