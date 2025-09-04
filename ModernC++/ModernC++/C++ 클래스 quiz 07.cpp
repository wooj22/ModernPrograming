// 상속 클래스의 형식 변환 // 잘못된 코드에 X 표시하세요.

#include <iostream>

class Parent { };
class Child :public Parent { };

int main()
{
    Parent   parent;
    Child    child;


    Parent  obj11 = child;  
    Child   obj21 = parent; 

    Parent* obj1 = &child;      //1 (  )
    Child*  obj2 = &parent;     //2 (  )

    Parent& obj3 = child;       //3 (  )
    Child&  obj4 = parent;      //4 (  )

    return 0;
}

