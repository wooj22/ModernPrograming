//문자열 스트림(stringstream)
// 
//      문자열을 입력 스트림처럼 읽거나 출력 스트림처럼 작성할 수 있게 해줍니다.
 
//1) stringstream
//		헤더 #include <sstream>
//  	입출력 스트림 : 입력 스트림, 출력 스트림을 모두 할 수 있다.
//      istringstream, ostringstream


//2) istringstream
//      입력 스트림
//      문자열을 공백과 '\n'을 기준으로 여러 개의 다른 형식으로 차례대로 분리할 때 편리하다.
//      반복문 실행 시 자료형에 맞는 데이터가 없을 때까지 실행된다.

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    istringstream iss("test\n123 aaa 456");
    string s1, s2;
    int i1, i2;
    iss >> s1 >> i1 >> s2 >> i2; // 문자열을 파싱하고 변수형에 맞게 변환한다.

    cout << s1 << endl; // test
    cout << i1 << endl; // 123
    cout << s2 << endl; // aaa
    cout << i2 << endl; // 456
}
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string str1 = "1D2S#10S";
    string str2 = "1111DAWV2S#10S";

    istringstream iss1(str1);
    istringstream iss2(str2);
    int num1, num2;
    while (iss1 >> num1) cout << num1 << " ";
    cout << endl;
    while (iss2 >> num2) cout << num2 << " ";
    cout << endl;

    istringstream iss3(str1);
    istringstream iss4(str2);
    char ch1, ch2;
    while (iss3 >> ch1) cout << ch1 << " ";
    cout << endl;
    while (iss4 >> ch2) cout << ch2 << " ";
    cout << endl;
}

//3) ostringstream
//      출력 스트림
//      문자열을 조립하거나 특정 형식을 문자열로 변환하기 위해 사용한다.

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    ostringstream oss;
    string s1 = "abc", s2 = "gjw";
    int i1 = 19234;
    double d1 = 3.591;
    oss << s1 << "\n" << i1 << "\n" << s2 << "\n" << d1; // 문자열을 붙인다.
    cout << oss.str(); // 문자열을 꺼낸다.
}

//4) str(), clear() - 스트림 내용을 비우고 재사용.
//  str(string s) : stringstream에 저장된 문자열을 바꾼다.이때 s가 "" 일 경우 문자열을 삭제하는 것과 같다.
//  str() : stringstream이 저장하고 있는 문자열의 복사본을 반환한다.
//  clear() : stringstream 재사용하려면 clear()를 실행해야 한다.이때 저장된 문자열이 삭제되진 않는다.


//5) get(), unget()
//  get() : 커서를 뒤로 옮기면서 값을 반환한다.
//  unget() : 커서를 앞으로 다시 옮긴다.
{
    string str = "123abc";

    // get()
    stringstream ss1;
    ss1.str(str);
    cout << ss1.get() - '0'; // 1: -'0' 안해주면 아스키코드값이 나옴
    cout << ss1.get() - '0'; // 2

    // unget()
    stringstream ss2;
    ss2.str(str);
    char ch;
    ss2 >> ch; // 1
    ss2 >> ch; // 2
    ss2.unget();
    ss2 >> ch; // 1
}

//6) getline()
//  문자열을 공백이나 '\n'이 아닌 다른 문자를 기준으로 분리하고 싶을 때 사용한다.

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    string str = "gkg|qiew|789", token;
    stringstream ss(str);
    while (getline(ss, token, '|')) {
        cout << token << endl;
    }
}

// 실행 결과
// gkg
// qiew
// 789


//활용

// 문자열을 나누는 stringstream
#include <string> 
#include <sstream> 
#include <iostream> 
using namespace std;

int main()
{
    int num;
    string str = "123 456";
    stringstream stream;
    stream.str(str);
    while (stream1 >> num) cout << num << endl;
    //stream.str(""); //초기화
}

// String에서 Int형 뽑아내는 예시

#include <string> 
#include <sstream> 
#include <iostream> 
using namespace std;
int main()
{
    int num;
    string str = "123 456\n789 012";
    stringstream stream;
    stream.str(str);//초기화 ->stream에 str을 대입. 
    while (stream >> num)
    { //뽑아내고자 하는 int형 값을 출력한다. (num이 int형이기 때문에) 공백이나 \n이 나올때 까지 읽어드린 후 출력 
        cout << num << endl;
    }
}
//출력 //123 //456 //789 //12


// 날짜를 초로 바꾸기

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
    vector<long long> time;
    string str = "2019:06:30 12:00:30"; // 연 월 일 시 분 초 
    for (int i = 0; i < str.size(); i++)
        if (str[i] == ':') str[i] = ' ';

    long long num = 0;
    stringstream stream;
    stream.str(str);
    while (stream >> num)
        time.push_back(num);

    long long second = 0;
    second += time[0] * 365 * 24 * 60 * 60; // 연 
    second += time[1] * 30 * 24 * 60 * 60; // 월
    second += time[2] * 24 * 60 * 60; // 일
    second += time[3] * 60 * 60; // 시 
    second += time[4] * 60; // 분 
    second += time[5]; // 초 
    cout << second;
}
