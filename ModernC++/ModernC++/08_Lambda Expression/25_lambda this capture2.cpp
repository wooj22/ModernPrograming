// 람다식 this 캡처

//다음과 같이 맴버 함수에서 this 포인터를 명시적으로 사용할 수 있습니다.

class Scale
{
private:
    int _scale;     // data member 

public:
    // capture "this" by reference
    void ApplyScale1(const vector<int>& v) const
    {
        for_each(v.begin(), v.end(), [this](int n) { cout << n * _scale << endl; });
    }

    // capture "this" by value (Visual Studio 2017 version 15.3 and later)
    void ApplyScale2(const vector<int>& v) const
    {
        for_each(v.begin(), v.end(), [*this](int n) { cout << n * _scale << endl; });
    }

    // this포인터를 암시적으로 캡처할 수도 있습니다. ***

    void ApplyScale3(const vector<int>& v) const
    {
        for_each(v.begin(), v.end(), [=](int n) { cout << n * _scale << endl; });
    }
};

//-------------------------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Scale
{
private:
    int _scale;     // data member 

public:
    explicit Scale(int scale) : _scale(scale) { }

    // Prints the product of each element in a vector object
    // and the scale value to the console.
    void ApplyScale(const vector<int>& v) const
    {
        for_each(v.begin(), v.end(), [=](int n) { cout << n * _scale << endl; });   //_scale
    }
};

int main()
{
    vector<int> values = { 1,2,3,4 };

    // Create a Scale object that scales elements by 3 and apply
    // it to the vector object. Does not modify the vector.
    Scale s(3);
    s.ApplyScale(values);        //출력 결과는?
}