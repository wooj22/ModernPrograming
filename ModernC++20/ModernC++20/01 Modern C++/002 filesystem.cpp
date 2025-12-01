//C++ 17 파일 시스템 라이브러리 ***
 
//<fstream> 의 경우, 
//      파일 하나가 주어지면 해당 파일의 데이터를 읽어내는 역할을 하지만
//      그 외에 파일에 관한 정보(파일 이름, 위치, 등등) 에 관한 데이터를 수정할 수는 없다.

//<filesystem> 경우, 
//      파일에 관한 정보(파일 메타데이타)에 대한 접근을 도와주는 역할을 수행한다. 
//      파일 자체를 읽는 일은 수행하지 않는다.

#include <iostream>
#include <filesystem>               //
namespace fs = std::filesystem;

int main()
{
    std::filesystem::path p("./some_file"); //현재 프로그램이 실행되고 있는 위치

    std::cout << "Does " << p << " exist? " << std::boolalpha << std::filesystem::exists(p) << std::endl;
    std::cout << "Is   " << p << " file? " << std::filesystem::is_regular_file(p) << std::endl;
    std::cout << "Is   " << p << " directory? " << std::filesystem::is_directory(p) << std::endl;

    //-------------------------------------------------------------------------
    std::cout << "내 현재 경로 : " << fs::current_path() << std::endl;
    std::cout << "상대 경로 : " << p.relative_path() << std::endl;
    std::cout << "절대 경로 : " << fs::absolute(p) << std::endl;
    //std::cout << "공식적인 절대 경로 : " << fs::canonical(p) << std::endl;

    //canonical 의 경우 
    //  해당 파일의 경로를 가장 짧게 나타낼 수 있는 '공식적인 절대 경로'를 제공합니다.
    //  canonical 을 거치면 항상 동일한 절대 경로가 되어 관리가 쉬워진다.
    // 
    //  위 모든 함수들의 경우 입력 받는 경로에 파일이 존재하지 않는다면 모두 예외를 throw 합니다.
    //  따라서 위 함수들을 호출하기 전에 반드시 exist 를 통해서 파일이 존재하는지 확인해야 합니다.
    //
    //  만약에 예외를 처리하고 싶지 않다면 
    //  마지막 인자로 발생한 오류를 받는 std::error_code 객체를 전달하면 됩니다.
    //  이 경우, 예외를 던질 상황이 생기면 예외를 던지는 대신에 error_code 객체에 발생한 오류를 설정합니다.
    //
    //참고로 filesystem 에서 예외를 던지는 함수들의 경우 
    //이 처럼 마지막 인자로 error_code 를 받는 오버로딩이 제공됩니다.
}

//사용 예시)

//디렉토리 안에 모든 파일들 순회하기 ---------------------------------------------------------

    #include <filesystem>
    #include <iostream>
    namespace fs = std::filesystem;

    int main() {
      fs::directory_iterator itr(fs::current_path() / "a");  //현재 경로에 /a 를 추가
      while (itr != fs::end(itr)) {
        const fs::directory_entry& entry = *itr;
        std::cout << entry.path() << std::endl;
        itr++;
      }
    }
    //------------------------------------------------------
    #include <iostream>
    namespace fs = std::filesystem;

    int main() {
      for (const fs::directory_entry& entry :
           fs::directory_iterator(fs::current_path() / "a")) {
        std::cout << entry.path() << std::endl;
      }
    }
    //------------------------------------------------------
    #include <filesystem>
    #include <iostream>
    namespace fs = std::filesystem;

    int main() {
      for (const fs::directory_entry& entry :
           fs::recursive_directory_iterator(fs::current_path() / "a")) {
        std::cout << entry.path() << std::endl;
      }
    }

//디렉토리 만들기 ---------------------------------------------------------
//    fs::path p("./a");
//    fs::create_directory(p);

    #include <filesystem>
    #include <iostream>
    namespace fs = std::filesystem;

    int main() {
      fs::path p("./a/c");
      std::cout << "Does " << p << " exist? [" << std::boolalpha << fs::exists(p)
                << "]" << std::endl;

      fs::create_directory(p);

      std::cout << "Does " << p << " exist? [" << fs::exists(p) << "]" << std::endl;
      std::cout << "Is " << p << " directory? [" << fs::is_directory(p) << "]"
                << std::endl;
    }
    //생성하는 디렉토리의 부모 디렉토리는 반드시 존재 하고 있어야 합니다

//부모 디렉토리들까지 한꺼번에 만들기 ---------------------------------------------------------
//    fs::path p("./a/c");
//    fs::create_directories(p);

    #include <filesystem>
    #include <iostream>

    namespace fs = std::filesystem;

    int main() {
      fs::path p("./c/d/e/f");
      std::cout << "Does " << p << " exist? [" << std::boolalpha << fs::exists(p)
                << "]" << std::endl;

      fs::create_directories(p);

      std::cout << "Does " << p << " exist? [" << fs::exists(p) << "]" << std::endl;
      std::cout << "Is " << p << " directory? [" << fs::is_directory(p) << "]"
                << std::endl;
    }

//파일과 폴더 복사/삭제하기

    #include <filesystem>
    #include <iostream>

    namespace fs = std::filesystem;

    int main() {
      fs::path from("./a");
      fs::path to("./c");

      fs::copy(from, to, fs::copy_options::recursive);
    }

    //copy_options
    //
    //skip_existing : 이미 존재하는 파일은 무시 (예외 안던지고)
    //overwrite_existing : 이미 존재하는 파일은 덮어 씌운다.
    //update_existing : 이미 존재하는 파일이 더 오래되었을 경우 덮어 씌운다.


//파일 / 디렉토리 삭제하기 ---------------------------------------------------------
//    fs::remove(p);

    #include <filesystem>
    #include <iostream>

    namespace fs = std::filesystem;

    int main() {
      fs::path p("./a/b.txt");
      std::cout << "Does " << p << " exist? [" << std::boolalpha
                << std::filesystem::exists(p) << "]" << std::endl;
      fs::remove(p);
      std::cout << "Does " << p << " exist? [" << std::boolalpha
                << std::filesystem::exists(p) << "]" << std::endl;
    }
    
    //-------------------------------

    #include <filesystem>
    #include <iostream>

    namespace fs = std::filesystem;

    int main() {
      fs::path p("./c/b");

      std::error_code err;
      fs::remove(p, err);  // 실패
      std::cout << err.message() << std::endl;

      fs::remove_all(p);  // 성공!
    }

    // 삭제할 때 마다 반복자를 초기화

    #include <filesystem>
    #include <iostream>

    namespace fs = std::filesystem;

    int main() {
      fs::path p("./a");
      while (true) {
        bool is_modified = false;
        for (const auto& entry : fs::directory_iterator("./a")) {
          const std::string ext = entry.path().extension();
          if (ext == ".txt") {
            fs::remove(entry.path());
            is_modified = true;
            break;
          }
        }

        if (!is_modified) {
          break;
        }
      }
    }


