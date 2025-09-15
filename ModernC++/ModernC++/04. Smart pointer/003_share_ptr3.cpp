//배열 형태를 shared_ptr로 사용하기

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class A {
    int n = 0;
public:
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
    A(int a) :n(a) { }
    void func() { cout << n << endl; }
};

int main()
{
    //배열 형태를 shared_ptr로 사용하기 -------------------------------------------

    //C++17 이전엔 배열 형태를 shared_ptr로 사용하고자 할 때는 지우는 방법을 정의해 줘야 한다.
    std::shared_ptr<int> sp(new int[10], std::default_delete<int[]>());
    std::shared_ptr<int> sp(new int[10], [](int* p) { delete[] p; });   //람다형태로 표현할 때

    //unique_ptr은 배열을 표현할 수 있습니다.
    std::unique_ptr<int[]> up(new int[10]); // this will correctly call delete[]


    //클래스 배열 형태를 shared_ptr로 사용 

    //A a[3] = { A(1), A(2), A(3) };
    //a[0].func();
    //a[1].func();
    //a[2].func();

    std::shared_ptr<A[]> spi(new A[3]);        // C++17 이상에서 동작합니다. 배열을 표현
    //A* p = spi.get(); p[0].func();

    /*
        shared_ptr<A> array(new A[10]);                              //delete 로 삭제되는 문제
        shared_ptr<A> array(new A[10], [](A* a) { delete[] a; });    //deleter 지정
        shared_ptr<A> array(new A[10], [](auto a) { delete[] a; });  //C++14 제네릭 람다
        shared_ptr<A[]> spi(new A[3]);                               //C++17
    */


    //vector 사용하기 -----------------------------------------------------

    //std::vector< shared_ptr<A> > spVec;
    //spVec.push_back(shared_ptr<A>(new A));
    //spVec.push_back(shared_ptr<A>(new A));
    //spVec.push_back(shared_ptr<A>(new A));

    //spVec[0]->func();
}

