
// 템플릿과 상속 활용 - 싱글톤 만들기
// CRTP (Curiously Recurring Template Pattern; 기묘하게 재귀하는 템플릿 패턴) - 과제

#include <iostream>
#include <cassert>

template < typename T >
class TemplateSingleton
{
protected:
    TemplateSingleton() {    }
    virtual ~TemplateSingleton() {    }

public:
    static T* GetInstance()
    {
        if (m_pInstance == NULL) m_pInstance = new T;
        return m_pInstance;
    };

    static void Destroy()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = NULL;
        }
    };

private:
    static T* m_pInstance;
};

template <typename T> T* TemplateSingleton<T>::m_pInstance = 0;


// 사용법

class CObject : public TemplateSingleton<CObject>
{
    CObject() { std::cout << "CObject()" << std::endl; }
    ~CObject() { std::cout << "~CObject()" << std::endl; }
public:
    void MyMethod() {}
};

int main()
{
    CObject::GetInstance()->MyMethod();
    CObject::GetInstance()->Destroy();
}

//객체 생성 문제, 상속 문제, 스레드 처리 문제 등 해결하기.