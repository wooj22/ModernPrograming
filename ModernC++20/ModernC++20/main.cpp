#include<iostream>
using namespace std;

struct [[deprecated("this struct is outdated")]] OldStruct { int a; };
[[nodiscard]] int getValue() { return 42; }
[[maybe_unused]] int unusedVariable = 10;