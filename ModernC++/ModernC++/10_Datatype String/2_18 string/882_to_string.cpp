//문자열 변환 //C++

#include <iostream>
#include <string>
using namespace std;

int main() {

	// int ---> string
	int i = 10;		string s = to_string(i);	//

	// string ---> int
	string s = "123";	int i = stoi(s);		//


	//---------------------------------------------------

	// 1. string -> int 
	string a = "1234", b = "1a2b3c";
	cout << stoi(a) << "\n";	
	cout << stoi(a, nullptr, 8) << "\n";		// 8진수 1234를 -> 10진수로 변환


	// 2. string 문자열에서 숫자만 구분하여 출력하기
	for (int i = 0; i < b.size(); i++) {
		if (b[i] >= '0' && b[i] <= '9') cout << b[i] - '0';
	}
	cout << "\n";

	// 3. int -> string --------------------------------
	int num = 4321;
	string s = to_string(num);
	string r = "결과 = ";

	r += num;
	cout << r << "\n";

	r = "결과 = ";
	r += s;
	cout << r << "\n";

	return 0;
}

// stoi --------------------------------------------------
{
	string str_i  = "22";
	string str_li  = "2144967290";
	string str_f  = "3.4";
	string str_d  = "2.11";

	//int i = str_i;    //error
	int i        = stoi(str_i);
	long int li  = stol(str_li);
	float f      = stof(str_f);
	double d     = stod(str_d);

	//C++ cout
	cout  << "stoi : " << i     << endl;
	cout  << "stol : " << li  << endl;
	cout  << "stof : " << f     << endl;
	cout  << "stod : " << d     << endl;

	cout  << endl;
	//C, C++ printf
	printf("stoi : %d\n", i);
	printf("stol : %ld\n", li);
	printf("stof : %f\n", f);
	printf("stod : %lf\n", d);


//함수원형1: int   stoi(const string& str, size_t* idx = 0, int base = 10);
//함수원형2: float stof(const string& str, size_t* idx = 0);

	//mixed string
	string str1  = "33Block";

	//test1
	int num1  = stoi(str1);
	cout  << " - num1 : " << num1  << endl;
	cout  << endl;

	//test2
	size_t sz;
	int num2  = stoi(str1, &sz);
	cout  << "test2. stoi(str1, &sz);" << endl;
	cout  << " - str1 : " << str1  << endl;
	cout  << " - num2 : " << num2  << endl;
	cout  << " - sz : " << sz  << endl;
	cout  << " - str1[sz] : " << str1[sz] << endl;
	cout  << " - str1.substr(sz) : " << str1.substr(sz) << endl;
	cout  << endl;

	//test3
	string str2  = "";
	cout  << "test3. stoi(str2, nullptr, base);" << endl;

	//string binary -> int
	str2  = "1110";
	cout  << " - stoi(1110, nullptr, 2) : " << stoi(str2, nullptr, 2) << endl;

	//string hex -> int
	str2  = "0x14";
	cout  << " - stoi(0x14, nullptr, 16) : " << stoi(str2, nullptr, 16) << endl;
}


/*
	// int ---> string -----------------------------------
	string s1; int i1 = 12; s1 = to_string(i1);
	cout << s1 << endl;

	// string ---> int -----------------------------------
	string s2 = "123"; int i2; i2 = stoi(s2);
	cout << i2 << endl;

	// const char* ---> int ------------------------------
	const char* str = "1234"; int i3 = atoi(str);
	cout << i3 << endl;

	// const char* ---> string ---------------------------
	string s3; const char* chp1 = "abc"; s3 = chp1;
	cout << s3 << endl;

	// string ---> const char* ---------------------------
	string s4 = "abc"; const char* str4; str4 = s4.c_str();
	cout << str4 << endl;
*/