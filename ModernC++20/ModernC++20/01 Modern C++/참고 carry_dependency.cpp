#include <atomic>
#include <iostream>

void print(int* val)
{
    std::cout << *val << std::endl;
}

void print2(int* val [[ carry_dependency ]] )
{
    std::cout << *val << std::endl;
}

int main()
{
    int x{ 42 };
    std::atomic<int*> p = &x;
    int* local = p.load(std::memory_order_consume);

    if (local)
    {
        // 종속성이 명시적이므로 컴파일러는 local이 // 역참조되었으며 
        //펜스(일부 아키텍처)를 피하기 위해 종속성 체인이 보존되어야 한다는 것을 알고 있습니다.
        std::cout << *local << std::endl;
    }
    if (local)
    {
        // print의 정의는 불투명합니다(인라인되지 않은 경우). // 따라서 컴파일러는 
        //print에서* p를 읽어서 올바른 값을 반환하도록 보장하기 위해 펜스를 실행해야 합니다.            
        print(local);
    }
    if (local)
    {
        // 컴파일러는 print2도 불투명하더라도 
        //매개변수에서 역참조된 값까지의 종속성이 명령 스트림에서 유지되고 펜스가 필요하지 않다고 가정할 수 있습니다(일부 아키텍처에서는).
        //분명히 print2의 정의는 실제로 이 종속성을 유지해야 하므로 속성은 print2에 대해 생성된 코드에도 영향을 미칩니다.
        print2(local);
    }
}