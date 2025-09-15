//연습) 참조카운트

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

//share_ptr  
//  값 전달, 복사에 의한 임시객체 생성, 함수 종료시 생성된 임시객체 소멸 등 참조카운트 영향을 받음
// 
//  하지만 아래 매개변수를 const std::shared_ptr<Car>& 로 받는다면,
//  임시 객체가 생기지 않아서 참조 카운트가 올라가지 않는다.

class Car { };

void function(std::shared_ptr<Car> _car)
{
}

int main()
{
    std::shared_ptr<Car> Car1(new Car());       // 최초 생성시 초기 참조 카운트는 당연히 '1'
    std::shared_ptr<Car> Car2(Car1);            // 복사 -> 참조 카운트 '2'

    //cout << Car1.use_count() << endl;
    //cout << Car2.use_count() << endl;

    std::shared_ptr<Car> Car3 = Car1;           // 대입 -> 참조 카운트 '3'

    //cout << Car1.use_count() << endl;
    //cout << Car2.use_count() << endl;
    //cout << Car3.use_count() << endl;

    function(Car3);                             // 호출 후
    cout << Car3.use_count() << endl;           // ??

    // function( std::shared_ptr<Car> _car ), 값에 의한 전달, 복사에 의한 임시객체 생성, 참조 카운트 증가 -> '4'
    // 함수 호출 후엔 임시객체 소멸되므로 참조 카운트 감소 -> '3'


    Car3.reset();                               // reset 후
    cout << Car1.use_count() << endl;           // ??
    cout << Car2.use_count() << endl;           // ??
    cout << Car3.use_count() << endl;           // ??

    // reset 함수는 shared_ptr이 참조하는 객체를 새로운 녀석으로 바꿀 수 있는 함수이다.
    // 내부적으로 shared_ptr::swap 함수가 사용됨
    // 인자를 주지 않으면 참조 포기가 되는 것이다. 따라서 참조 카운트 감소 -> '2'


    const std::shared_ptr<Car>& Car4 = Car1;    // 참조 후
    cout << Car4.use_count() << endl;           // ??

    return 0;

    // 함수 반환시 남아있던 shared_ptr 모두 소멸 -> 참조 카운트 '0'
    // 이제 shared_ptr이 참조하고 있던 Car* 에 대해 delete가 호출됨.
}

/*

//참조 객체의 형변환
//      shared_ptr 비멤버 함수를 통해 shared_ptr이 참조하고 있는 객체의 형 변환을 수행할 수 있다.

    #include <iostream>
    #include <memory>       // for shared_ptr
    #include <vector>
    using namespace std;

    class Car { };
    class Truck : public Car { };

    int main()
    {
        // Truck 타입의 객체를 Car 타입의 객체를 참조하는 shared_ptr에 초기화
        shared_ptr<Car> pCar(new Truck());

        shared_ptr<Truck> pTruck = static_pointer_cast<Truck>(pCar);

        // shared_ptr<Car>가 참조하고 있던 객체를 Truck 타입으로 static_cast 하여 대입.
        // 대입 하였기에 참조 카운트는 '2'

        std::cout << pCar.use_count() << std::endl;
        std::cout << pTruck.use_count() << std::endl;

    }


*/