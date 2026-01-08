
// 예시 ----------------------------------------------------------------------------------
//      예전 해더파일을 불러오는 방법

module;                   // global module fragment ***

// 여기에 #include를 이용해 헤더를 불러왔다고 하더라도 
// 모듈을 가져다 쓰는 곳에서 include의 내용를 볼 수 없다.

#include <numeric>        // #include는 여기 들어간다 
#include <vector>

export module math;       // module declaration

export int add(int fir, int sec) {
    return fir + sec;
}

export int getProduct(const std::vector<int>& vec) {
    return std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());
}


// 예시 ---------------------------------------------------------------------------- 

// 파일: Module.ixx --------------------------

module;

#include <iostream> 

export module Module;
export class Test
{
public:
    template<typename ...Args>
    static void print(Args&&... args)
    {
        (std::cout << ... << args) << std::endl;
    }
};

// 파일: Main.cpp --------------------------

import Module;
import std.core;        //이것도 줄여보자.

int main()
{
    Test::print(std::string("Modules "), std::string("of "), std::string("C++"), '!');
}

//--------------------------------------------------------------------------------------
 
// 파일: Module.ixx
export module Module;       //module 임을 표시.
export import std.core;     //불러온 모듈을 그대로 export, 즉 import Module;만해도 같이 부름

export class Test
{
public:
    template<typename ...Args>
    static void print(Args&&... args)
    {
        (std::cout << ... << args) << std::endl;
    }
};

// 파일: Main.cpp
import Module;

int main()
{
    Test::print(std::string("Modules "), std::string("of "), std::string("C++"), '!');
    std::cout << "Feel free" << std::endl;
}




