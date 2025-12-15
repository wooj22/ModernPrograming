// common_type sample
//      다양한 타입의 데이타 여러개를 인자로 받아 '공통타입'으로 변환
//      type 멤버는 매개 변수 목록의 모든 형식을 변환할 수 있는 '공용 형식'이 된다. 

#include <iostream>
#include <type_traits>

struct Base {};
struct Derived : Base {};

int main()
{
    typedef std::common_type<unsigned char, short, int>::type NumericType;      //공용형식은 int   
    typedef std::common_type<float, double>::type FloatType;                    //공용형식은 double
    typedef std::common_type<const int, volatile int>::type ModifiedIntType;    //공용형식은 int
    typedef std::common_type<Base, Derived>::type ClassType;                    //공용형식은 Base

    std::cout << std::boolalpha;
    std::cout << "Test for typedefs of common_type int" << std::endl;
    std::cout << "NumericType: " << std::is_same<int, NumericType>::value << std::endl;
    std::cout << "FloatType: " << std::is_same<int, FloatType>::value << std::endl;
    std::cout << "ModifiedIntType: " << std::is_same<int, ModifiedIntType>::value << std::endl;
    std::cout << "ClassType: " << std::is_same<int, ClassType>::value << std::endl;

    std::cout << "---------------------------" << std::endl;
    std::cout << "Test for typedefs of common_type Base" << std::endl;
    std::cout << "NumericType: " << std::is_same<Base, NumericType>::value << std::endl;
    std::cout << "FloatType: " << std::is_same<Base, FloatType>::value << std::endl;
    std::cout << "ModifiedIntType: " << std::is_same<Base, ModifiedIntType>::value << std::endl;
    std::cout << "ClassType: " << std::is_same<Base, ClassType>::value << std::endl;

    return 0;
}

/*
 
// 아래에서 common_type 을 기입하세요.

#include <iostream>
#include <type_traits>

struct Base {};
struct Derived : Base {};

int main()
{
    typedef std::common_type<unsigned char, short, int>::type NumericType;      //공용형식은 (    ) 

    typedef std::common_type<float, double>::type FloatType;                    //공용형식은 (    ) 

    typedef std::common_type<const int, volatile int>::type ModifiedIntType;    //공용형식은 (    ) 

    typedef std::common_type<Base, Derived>::type ClassType;                    //공용형식은 (    ) 

    //std::cout << std::boolalpha;
    //std::cout << "NumericType:     " << std::is_same<int, NumericType>::value << std::endl;
    //std::cout << "FloatType:       " << std::is_same<double, FloatType>::value << std::endl;
    //std::cout << "ModifiedIntType: " << std::is_same<int, ModifiedIntType>::value << std::endl;
    //std::cout << "ClassType:       " << std::is_same<Base, ClassType>::value << std::endl;

    return 0;
}

*/