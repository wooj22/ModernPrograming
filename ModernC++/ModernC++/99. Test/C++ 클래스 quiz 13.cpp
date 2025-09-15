//예문의 코드를 컴파일하면 a = 3; 부분에서 컴파일 에러가 발생한다.
//에러를 수정하기 위해 빈 칸에 들어가야 할 것으로 적당한 것은 ?

class A
{
public:
	int val;
	______________________     //
};

int main()
{
	A a;
	a = 3;      //
	return 0;
}


//① A(const A& rhs) { }
//② A(int rhs) { }
//③ void operator=(int& n) { val = n; }
//④ void operator=(int n) { val = n; }
