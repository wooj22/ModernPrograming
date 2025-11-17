//string_view	//c++ 17
// 
//		문자열에 대한 '참조'를 가질 뿐 내용을 가지지 않는 참조 객체입니다.
// 
//		basic_string_view 는 내부적으로 문자열 포인터와 사이즈를 저장하는 변수만을 가집니다.
//		문자나 std::string 타입보다 '가볍게' 동작 할 수 있습니다.
//		원본 데이터를 수정 할 수 없고 '읽기 전용'으로만 사용 가능합니다. 
//		(const_point 형태로 보유하기 때문)
//
//		string_view 자체는 원본 데이터를 수정 할 수 없지만, 
//		바라보고 있는 '원본 데이터'가 수정되면 string_view 문자열 데이터도 수정됩니다.
//		string_view를 사용 도중에는 호출하는 입장에서 '원본 데이터'가 수정되지 않을 것을 보장해줘야 합니다


#include <iostream>
#include <string>
using namespace std;

using namespace std::literals::string_view_literals;	//"..."sv를 쓰려면 아래를 선언해야.

int main()
{
	//string

	string name = "Niels Stroustrup";
	string s = name.substr(6, 10);		// s = "Stroustrup";

	name.replace(0, 5, "nicholas");		// name = "nicholas Stroustrup";
	name[0] = toupper(name[0]);			// name = "Nicholas Stroustrup";​

	if (name == "Nicholas Stroustrup")	// 허용
	{
		cout << name << endl;
	}

	//c_str()

	printf("printf를 선호한다면 : %s\n", name.c_str());


	//--------------------------------------------------------------

	auto p1 = "Dog";		// C 스타일 문자열: const char* 로 할당
	auto s1 = "Cat"s;		// std::string 으로 할당
	auto sv = "Cat"sv;		// std::string_view 으로 할당

	//string_view : {begin(), size()}

	string str1 = "test1";
	string_view sv1(str1);
	string_view sv2 = str1;
	string_view sv3 = "test2";

	auto func1 = [](string_view sv_arg) { cout << sv_arg << endl; };
	string str2("test2");
	func1(str2);
	func1("test3");

	//비교 == !=
	string str4("test6");
	string str5("test7");
	string_view sv4(str4);

	if (sv4 == str5) { cout << "sv4 == str5" << endl; }
	else { cout << "sv4 != str5" << endl; }

	if (sv4 == "test6") { cout << "sv4 == \"test6\"" << endl; }

	//assign
	string_view sv5 = "test8";
	string str6(sv5);
	string str7; str7.assign(sv5);
	cout << str6 << endl;
	cout << str7 << endl;
}


//c++ 문자열 처리

//표준 라이브러리 
//	string 타입으로 만들고 싶은 문자열 리터럴에는 접미가 s 를
//	string_view 타입으로 만들고 싶은 문자열 리터럴에는 접미사 sv
 
//	최적화된 성능을 원하면 at() 대신 반복자 or [] 를 사용.
//	string 입력은 오버플로우 되지 않는다.
//	string 을 C 스타일로 표현해야 할 경우에만 c_str() 을 사용.
//	문자열을 수치로 변환할 때는 stringstream 이나 (to<X>같은) 제네릭 값 추출 함수를 사용.
 
//	여러 방식으로 저장된 문자시퀀스를 읽어야 한다면 string_view 를 
//	인자로 써야 한다면 std::span  // 연속적인 데이터 컨테이너를 참조하는 STL. C++17


//string_view 장점 ----------------------------------------------------------
// 
//	- 다양한 타입의 문자 시퀀스에 적용 가능. (함수 파라미터 범용성 향상)
// 
//	- C 스타일 문자열을 인자로 받을 때, 임시 string 객체 생성 안 됨. (복사 비용 최소화)
// 
//	- 부분 문자열 쉽게 전달.	​(부분 문자열 처리 용이)

string cat(string_view sv1, string_view sv2)
{
	string res1(sv1);
	string res2(sv2);
	return res1 + res2
}
int main()
{
	string s = cat("Edward", "Stephen"sv);
	//string s = cat("Edward"s, "Stephen"sv);
	cout << s;
}

#include <string_view>

int main()
{
	std::string str = "Hello, World!";
	std::string_view sv1(str);          // std::string에서 생성
	std::string_view sv2("Literal");    // const char*에서 생성
	std::string_view sv3(str.c_str(), 5); // 길이 지정 가능 ("Hello")

	//문자열 슬라이싱
	std::string_view sv = "Hello, World!";
	std::string_view hello = sv.substr(0, 5);
	std::string_view world = sv.substr(7);  // length 생략 시 끝까지
	std::cout << hello << " " << world << "\n"; // Hello World!
	//.substr()는 새로운 문자열 생성이 아니라 뷰만 생성 → 효율적

	//반복자 & 범위 기반 for
	for (char c : std::string_view("Example"))
		std::cout << c << ' ';
}



//string_view 단점 ----------------------------------------------------------
// 
//	문자열에 참조인 관계로, 원본 문자열이 메모리 상에 존재하지 않으면 예상치 못한 문제가 발생

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//"..."sv를 쓰려면 아래를 선언해야.
using namespace std::literals::string_view_literals;

int main()
{
	//예로 아래와 같은 코드는 이상없이 test9를 출력합니다.
	string str8 = "test9";

	vector<string_view> test_vec1;	test_vec1.push_back(str8); //
	cout << test_vec1[0] << endl;


	//하지만 아래와 같은 코드는 test10 이 아닌 문자열을 출력할 수 있다. 
	string str9 = "test10";

	vector<pair<int, string_view>> test_vec2;
	test_vec2.push_back( make_pair(1, str9) );	//make_pair(1, str9) -> pair<int,string>()

	for (auto& iter : test_vec2)
	{
		cout << iter.first << endl;
		cout << iter.second << endl;
	}

	//이는 중간에 생성되는 '임시 객체'로 인하여 최종 객체의 참조가 잘못되기 때문입니다. ***


	//string의 c_str()처럼 
	//string_view는 data()라는 참조하고 있는 버퍼에 대한 포인터를 리턴합니다.

	string_view sv6 = "test11";
	cout << sv6.data() << endl;
	
	//하지만 
	//이 data() 함수의 리턴값은 C++ 표준에 따르면 '널로 끝나는 문자열'이 아닌 관계로 
	//널로 끝나는 문자열을 필요로 하는 C API 와 같은 함수에서는 사용해서는 안됩니다. ***
	// 
	//물론 C++ string_view의 구현에 따라 널로 끝나는 문자열을 리턴하는 경우도 있지만, 
	//표준에서 널로 끝나는 문자열이 아닌 관계로 
	//호환성이나 차후 C++ 업데이트 등을 고려할 때 
	//널로 끝나는 문자열을 필요로 하는 곳에서는 data()를 사용해서는 안됩니다.
}


/*
C++17 - string_view의 주의점

string_view 클라스 --- 문자열에 대한 읽기 전용 뷰.
	std::string와 같이 null 종단 문자열 이외도 올바르게 다룰 수 있다. 
	null 종단 문자를 도중에 포함 할 수 있다.

string_view 클래스는 참조한 문자열의 소유권을 관리하지 않는다.
	옛스러운 raw pointer 와 비슷한 dangling 뷰에 아주 주의해야 한다.

'함수 파라메타' 타입에 있어서는 string_view 이용은 안전.
	null 종단 문자열(const char*) 혹은 문자열(const std::string&)로의 뷰를 통일적, 효율적으로 다룰 수 있다.
	함수 구현에서 소유권이 필요로 된다면 std::string에 저장(＝문자열 실체를 복사) 한다.
	std::string과는 다르고, string_view::data 멤버 함수는 null 종단 문자열을 보증하지 않기 때문에 
	null 종단 문자열을 요구하는 레거시 API 호출 용도로는 적합하지 않다.

'함수 반환 값' 타입이나 '클래스 데이터 멤버'로서 string_view 이용에는 충분히 유의한다. 
	dangling 뷰 위험이 있다.
	참조처 오브젝트의 생존 기간(lifetime)을 문서화 한다.

'임시 문자열 오브젝트'를 가리키는 string_view 변수를 명시적으로 만들지 않는다.
	지역 변수에는 string_view 타입이 아닌 auto&& 이용을 검토해야 한다.

	{
		// 문자열 타입 string을 반환하는 함수
		std::string f();

		std::string_view s1 = f();
		// NG: 함수 반환 값(임시 문자열 오브젝트)는 파괴 되기 때문, 이 시점에서 s1은 댕글링 뷰가 된다

		auto&& s2 = f();
		// OK: 함수 반환 값(임시 문자열 오브젝트) 우측 값 참조 타입으로 넘기면
		// 이 생존 기간은 변수 s2의 스코프가 끝날 때까지 연장 된다.
	}

*/