//아래의 코드에서 문법적인 오류가 발생하는 부분은 ?

class MyClass
{
private:
	int Value;
public:
	MyClass(int value = 0) : Value(value) {}
	int Get() const { return Value; }
	void Add(const MyClass& other) {
		Value += other.Value;	    //1
	}
};

int main()
{
	MyClass& r = MyClass(100);		//2
	MyClass* p = new MyClass;		//3
	r.Add(*p);						//4
	return 0;
}

//① 1     ② 2    ③ 3    ④ 4
