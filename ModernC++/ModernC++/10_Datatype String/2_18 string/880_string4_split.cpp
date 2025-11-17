//문자열 분리하기 //strtok_s

// strtok_s -----------------------------------------------------------------

#include <iostream> 
using namespace std;

int main()
{    
    char str1[] = "192.168.152.0";

    char* context = NULL;
    char* token = strtok_s(str1, ".", &context); //context에는 분리 후 남은 것.
    cout << token << endl;
    while (token)
    {
        token = strtok_s(NULL, ".", &context);
        if (token != NULL) cout << token << endl;
    }
}

// substr -------------------------------------------------------------------

int main()
{
	string IPAddress = "192.168.152.0";
    char delimiter = '.';

    string as = IPAddress;
    size_t previous = 0, current;
    current = as.find(delimiter); //find 함수는 해당 위치부터 문자열을 찾지 못할 경우 npos를 반환한다.
    while (current != string::npos)
    {
        // 첫 인자의 위치부터 두번째 인자 길이만큼 substring을 반환
        string substring = as.substr(previous, current - previous);
        cout << substring << endl;
        previous = current + 1;
        
        current = as.find(delimiter, previous); //previous 부터  deli 이 나오는 위치를 찾는다.
    }
    //마지막 문자열 출력
    cout << as.substr(previous, current - previous);
}
