
//Recursive lambda ---------------------------------------------------------
// 
//	lamba 함수 역시 함수의 특성을 모두 가지고 있으므로, 재귀(recursive)가 가능하다.


#include <iostream>
#include <functional>
using namespace std;

int main(int argc, char* argv[])
{
    // function을 사용하였음에 주의하라
    function<int(int)> Factorial = [&Factorial](int num) -> int
        {
            return num <= 1 ? 1 : num * Factorial(num - 1);
        };

    // 5 * 4 * 3 * 2 * 1 = 120
    int fact5 = Factorial(5);
    cout << fact5 << endl;

    return 0;
}


//람다 식 중첩
//      람다 식을 다른 람다 식 안에 중첩할 수 있습니다.

#include <iostream>

int main()
{
    using namespace std;

    // The following lambda expression contains a nested lambda
    // expression.
    int timestwoplusthree = [](int x) { return [](int y) { return y * 2; }(x)+3; }(5);

    // Print the result.
    cout << timestwoplusthree << endl;      //출력은 ???
}


//고차 람다 함수
//      고차 함수는 다른 람다 식을 '인수'로 취하거나 람다 식을 '반환'하는 람다 식입니다. 

#include <iostream>
#include <functional>

int main()
{
    using namespace std;

    // The following code declares a lambda expression that returns
    // another lambda expression that adds two numbers.
    // The returned lambda expression captures parameter x by value.
    auto addtwointegers = [](int x) -> function<int(int)> {
        return [=](int y) { return x + y; };
        };

    // The following code declares a lambda expression that takes another
    // lambda expression as its argument.
    // The lambda expression applies the argument z to the function f
    // and multiplies by 2.
    auto higherorder = [](const function<int(int)>& f, int z) {
        return f(z) * 2;
        };

    // Call the lambda expression that is bound to higherorder.
    auto answer = higherorder(addtwointegers(7), 8);

    // Print the result, which is (7+8)*2.
    cout << answer << endl;
}


//템플릿이 있는 람다 식 사용
//      람다 식이 형식화되기 때문에 C++ 템플릿과 함께 사용할 수 있습니다. 

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

// Prints to the console each element in the vector object.
template <typename T>
void print_all(const vector<T>& v)
{
    for_each(v.begin(), v.end(), [](const T& n) { cout << n << endl; });
}

int main()
{
    // Create a vector of signed integers with a few elements.
    vector<int> v;
    v.push_back(34);
    v.push_back(-43);
    v.push_back(56);

    // 여러 타입의 벡터에 대해 그 요소를 출력하는 하는 함수 템플릿을 작성하라.
    print_all(v);


}


// 여러 타입의 벡터에 대해 그 요소의 부호를 바꾸는 함수 템플릿을 작성하라.
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
    vector<int> v1 = { 1,2,3 };
    vector<long> v2 = { 1L,2L,3L };
    negate_all(v1);
    negate_all(v2);
}

/*
// Negates each element in the vector object. Assumes signed data type.
template <typename T>
void negate_all(vector<T>& v)
{
    for_each(v.begin(), v.end(), [](T& n) { n = -n; });
}
*/