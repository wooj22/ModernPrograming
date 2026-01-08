export module myModule;

export const char* GetPharse() {
    return "Hello, Module";
}

import std;
using namespace std;

export void printModule() {
    cout << "Hello, Module";
}

/*
export module Module;
export import std.core;     

//불러와 여기서도 사용하고 그대로 외부로 export 
//import Module 만 하면 됨

export class Test
{
public:
    template<typename ...Args>
    static void print(Args&&... args)
    {
        (std::cout << ... << args) << std::endl;
    }
};
*/