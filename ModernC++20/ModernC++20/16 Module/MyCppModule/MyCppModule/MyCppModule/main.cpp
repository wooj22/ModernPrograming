
import std;
import myModule;

using namespace std;

int main() {
    cout << GetPharse() << endl;

    printModule();
}


//C++ 에서 제공하는 표준 라이브러리 모듈
//std.core;
//std.regex;
//std.filesystem;
//std.memory;
//std.threading;


/*
    import std.core;
    import std.memory;
    import std.threading;

    int main()
    {
        std::thread t([] { std::cout << "func() called." << std::endl; });
        std::cout << "Main function" << std::endl;
        t.join();

        auto ptr = std::make_unique<int>(5);
        (*ptr)++;
        std::cout << "*ptr: " << *ptr << std::endl;
    }
*/

/*
    import Module;

    int main()
    {
        Test::print(std::string("Modules "), std::string("of "), std::string("C++"), '!');
        std::cout << "Feel free" << std::endl;
    }
*/