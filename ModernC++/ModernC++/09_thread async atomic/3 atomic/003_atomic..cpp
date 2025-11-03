//-------------------------------------------------------------------------------------------------
//const 멤버 함수를 스레드에 안전하게 작성하라 
//
//      동시적 문맥에서 쓰이지 않을 것이 확실한 경우가 아니라면, const 멤버 함수는 스레드에 안전하게 작성하라.

//예제 코드 

// 다항식을 대표하는 클래스를 만든다고 하자.

// 이 클래스가 유용하려면 다항식의 근을 계산하는 멤버 함수를 갖추어야 할 것이다.
// 그런 함수는 다항식을 수정하지 않을 것이므로, const로 선언하는 것이 자연스럽다.
// 다항식 근의 계산 비용이 클 수 있으므로, 꼭 필요할 때에만 계산하는 것이 바람직하다.
// 즉, 필요할 때에만 근(들)을 실제로 계산해서 캐시에 저장하고, 
// 그렇지 않을 때에는 그냥 캐시에 있는 값을 돌려주도록 구현하는 것이 바람직하다.

class Polynomial {
private:
    mutable bool rootsAreValid{ false };
    mutable std::vector<double> rootVals{}; // 다항식이 0으로 평가되는 값들을 담는 자료구조
public:
    RootsType roots(void) const 
    {
        if (!rootsAreValid) {           // 캐시가 유효하지 않으면 근들을 계산해서 rootVals에 저장해 둔다.
            //...
            rootsAreValid = true;   
        }
        return rootVals;
    }
};

// 만약 두 스레드가 하나의 Polynomial 객체에 대해 동시에 roots를 호출한다고 생각해 보자.

// 두 스레드 중 하나나 둘 다가 데이터 멤버 rootsAreValid와 rootVals를 수정하려 들 수 있다.
// 이 문제를 해결하는 가장 쉬운 방법은
// 통상적인 동기화 수단, 즉 뮤텍스(std::mutex)를 사용하는 것이다.

class Polynomial {
private:
    mutable std::mutex m;
    mutable bool rootsAreValid{ false };
    mutable std::vector<double> rootVals{};
public:
    RootsType roots(void) const
    {
        std::lock_guard<std::mutex> g(m);    // 뮤텍스를 잠근다.
        if (!rootsAreValid) {           
            rootsAreValid = true;       
        }
        return rootVals;
    }                                        // 뮤텍스를 푼다.

};

// 뮤텍스를 잠그고 푸는 멤버 함수들이 비const 이기 때문에 mutex도 mutable로 선언해야 한다.
// std::mutex를 복사하거나 이동할 수 없기 때문에,
// m 을 Polynomial에 추가하면 Polynomial의 복사와 이동 능력도 사라진다는 점을 주목하기 바란다.

//const 멤버 함수가 언제라도 동시적 실행 상황에 처할 것이라고 가정하는 것이 안전하며,
//따라서 const 멤버 함수는 항상 스레드에 안전하게 만드는 것이 바람직하다.


//-------------------------------------------------------------------------------------------------
// atomic vs mutex 
// std::atomic 변수는 뮤텍스에 비해 성능상의 이점이 있지만, 하나의 변수 또는 메모리 장소를 다룰 때에만 적합하다.

//예제 코드
 
// 멤버 함수의 호출 횟수를 세고 싶다면,
// std::atomic 카운터를 사용해서 비용을 줄일 수 있는 경우가 많다.
// (실제로 비용이 절감되는지는 프로그램이 실행되는 컴퓨터 하드웨어에 따라, 그리고 표준 라이브러리의 구체적인 뮤텍스 구현 방식에 따라 다를 수 있다)

// 다음은 std::atomic을 이용해서 멤버 함수의 호출 횟수를 세는 방법을 보여주는 예제 코드이다.

class Point {                                        // 2차원 점
public:
    ...
    double distanceFromOrigin(void) const noexcept
    {                                                
        ++callCount;                                // 원자적 증가
        return std::hypot(x, y);                    // std::hypot은 C++11의 새 함수
    }                                                 

private:
    mutable std::atomic<unsigned> callCount{ 0 };
    double x, y;
};

// std::mutex처럼 std::atomic도 복사와 이동이 불가능하다.

// 따라서 Point에 이 callCount를 도입하면 Point 역시 복사와 이동이 불가능해진다.

// std::atomic 변수에 대한 연산들이 뮤텍스를 획득하고 해제하는 것보다 비용이 싸다는 점에 현혹되어서 
// std::atomic을 남용하기 쉬우니 조심하기 바란다.


//-----------------------------------------------------------------------------
// 예를 들어 계산 비용이 큰 int 값을 캐시에 저장하는 클래스라면 
// 뮤텍스 대신 한 쌍의 std::atomic 변수들을 사용해볼 만하다.

class Widget {
public:
    ...
    int magicValue(void) const
    {
        if (cacheValid) return cacheValue;
        else {
            auto val1 = expensiveComputation1();
            auto val2 = expensiveComputation2();
            cacheValue = val1 + val2;                // !?
            cacheValid = true;                       // !?!?
            return cacheValue;
        }
    }

private:
    mutable std::atomic<bool> cacheValid{ false };
    mutable std::atomic<int> cacheValue;
};

// 이 코드가 작동하긴 하지만, 생각보다 비용이 클 수 있다.

// 1. 한 스레드가 Widget::magicValue를 호출한다.
// cacheValid가 false라고 관측하고, 비용이 큰 두 계산을 수행한 후 둘의 합을 cacheValue에 대입한다.

// 2. 그 시점에서 둘째 스레드가 Widget::magicValue를 호출하는데, 
// 역시 cacheValid가 false라고 관측해서 첫 스레드가 방금 마친 것과 동일한 비싼 계산들을 수행한다
// (이 '둘째 스레드'가 실제로는 여러 개의 다른 스레드들일 수도 있다).


//-----------------------------------------------------------------------------
// cacheValue와 cacheValid의 대입 순서를 반대로 바꾸면 이 문제가 해결될 것으로 생각할 수 있지만, 
// 여전히 cacheValid가 true로 설정되기 전에 여러 스레드가 val1과 val2를 계산하게 되는 상황이 생길 수 있으며,
// 상황이 더 나빠질 수도 있다.

class Widget {
public:
    ...
    int magicValue(void) const
    {
        if (cacheValid) return cacheValue;
        else {
            auto val1 = expensiveComputation1();
            auto val2 = expensiveComputation2();
            cacheValid = true;                       // !?
            cacheValue = val1 + val2;                // !?!?
            return cacheValue;
        }
    }

private:
    mutable std::atomic<bool> cacheValid{ false };
    mutable std::atomic<int> cacheValue;
};

// cacheValid가 false라고 할 때

// 1. 한 스레드가 Widget::magicValue를 호출해서, cacheValid가 true로 설정되는 지점까지 나아간다.

// 2. 그 시점에서 둘째 스레드가 Widget::magicValue를 호출해서 cacheValid를 점검한다. 
// 그것이 true임을 관측한 둘째 스레드는, 첫 스레드가 cacheValue에 값을 대입하기도 전에 cacheValue를 돌려준다.
// 따라서 그 반환값은 정확하지 않다.


// atomic vs mutex -----------------------------------------------------------------
// 
//      위에서 보았듯이, 동기화가 필요한 변수 하나 또는 메모리 장소 하나에 대해서는 
//      std::atomic을 사용하는 것이 적합하지만, 
//      둘 이상의 변수나 메모리 장소를 하나의 단위(unit)로서 조작해야 할 때에는 
//      뮤텍스를 꺼내는 것이 바람직하다.


// Widget::magicValue를 뮤텍스로 보호한다면 다음과 같은 모습이 될 것이다.

class Widget {
public:
    ...

    int magicValue(void) const
    {
        std::lock_guard<std::mutex> guard(m);        // m을 잠근다.

        if (cacheValid) return cacheValue;
        else {
            auto val1 = expensiveComputation1();
            auto val2 = expensiveComputation2();
            cacheValid = true;
            cacheValue = val1 + val2;
            return cacheValue;
        }
    }                                                // m을 푼다.

private:
    mutable std::mutex m;
    mutable int cacheValue;                // 이제는 atomic이 아님
    mutable bool cacheValid{ false };      // 이제는 atomic이 아님
};
