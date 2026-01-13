// if constexpr
// 
// 아래 코드를 검토하고, 질문에 답 하세요.

template <typename T>
void print(const T& v) {
    if constexpr (std::is_pointer_v<T>)
        std::cout << *v;
    else
        std::cout << v;
}

//질문

1. 왜 if constexpr 가 필요한가 ?
std::is_pointer_v<T>의 값을 컴파일 타임 상수로 선언하여,
조건을 만족하지 않는 경우 컴파일 타임에 오류가 발생시키게 하기 위함입니다.
if constexpr의 결과가 true라면 else에 해당하는 문장은 컴파일 되지 않습니다.


2. 일반 if 로 바꾸면 어떤 문제가 생기는가 ?
컴파일 시간에 참, 거짓 결과를 알 수 없으며, 모든 구문이 컴파일됩니다.

