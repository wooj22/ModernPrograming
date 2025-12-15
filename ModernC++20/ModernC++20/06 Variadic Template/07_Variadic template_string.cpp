//가변 길이 템플릿 (Variadic template)

//문자열 합치기 예제 --------------------------------------

#include <cstring>
#include <iostream>
#include <string>
using namespace std;

size_t GetStringSize(const char* s) { return strlen(s); }
size_t GetStringSize(const string& s) { return s.size(); }

template <typename Str, typename... Strs>
size_t GetStringSize(const Str& s, Strs... strs) {
	return GetStringSize(s) + GetStringSize(strs...);
}

void AppendToString(string* concat_str) { return; }

template <typename Str, typename... Strs>
void AppendToString(string* concat_str, const Str& s, Strs... strs) {
	concat_str->append(s);  // 모두 추가가능
	AppendToString(concat_str, strs...);
}

template <typename Str, typename... Strings>
string StrCat(const Str& s, Strings... strs)
{
	size_t total_size = GetStringSize(s, strs...); // 먼저 합쳐질 문자열의 총 길이를 구한다.

	string concat_str;
	concat_str.reserve(total_size);	// reserve 를 통해 미리 공간을 할당해 놓는다.

	concat_str = s;
	AppendToString(&concat_str, strs...);

	return concat_str;
}

int main() {
	// string 과 const char* 을 혼합해서 사용 가능하다.
	cout << StrCat(string("this"), " ", "is", " ", string("a"),
		" ", string("sentence"));
}

