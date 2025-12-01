//예시 // 템플릿을 이용해서, 읽기 쉬운 타입 이름을 얻어보자

#include <map>
#include <vector>
#include <string>
#include <iostream>

template<class _Type> std::string readable_name();

inline std::string readable_name_impl(size_t* dummy) { return "size_t"; }
inline std::string readable_name_impl(int* dummy) { return "int"; }
inline std::string readable_name_impl(int** dummy) { return "int*"; }
inline std::string readable_name_impl(bool* dummy) { return "bool"; }
inline std::string readable_name_impl(char* dummy) { return "char"; }
inline std::string readable_name_impl(float* dummy) { return "float"; }
inline std::string readable_name_impl(double* dummy) { return "double"; }
//...

template<class _Ty, class _1>
inline std::string readable_name_impl(std::vector<_Ty, _1>* dummy)
{
    return "std::vector<" + readable_name<_Ty>() + ">";   //재귀적으로 readable_name을 호출하여 _Ty의 타입 이름을 얻어냅니다.
}

template<class _KeyTy, class _ValTy>
inline std::string readable_name_impl(std::pair<_KeyTy, _ValTy>* dummy)
{
    return "std::pair<" + readable_name<_KeyTy>() + ", " + readable_name<_ValTy>() + ">";
}

template<class _KeyTy, class _ValTy, class _1, class _2>
inline std::string readable_name_impl(std::map<_KeyTy, _ValTy, _1, _2>* dummy)
{
    return "std::map<" + readable_name<_KeyTy>() + ", " + readable_name<_ValTy>() + ">";
}

template<class _Type>
inline std::string readable_name()
{
    return readable_name_impl((_Type*)nullptr);
}

int main() {

    std::cout << readable_name<char>() << std::endl;
    std::cout << readable_name<double>() << std::endl;
    std::cout << readable_name<int*>() << std::endl;
    
    std::cout << readable_name<std::map<size_t, size_t>>() << std::endl; // std::map<size_t, size_t> 출력
    
    std::cout << readable_name<std::vector<std::vector<double>>>() << std::endl; // std::vector<std::vector<double>> 출력
    return 0;
}