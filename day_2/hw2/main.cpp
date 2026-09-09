#include <iostream>
#include <string>
#include <fstream>
#include "DataFrame1.hpp"

// 1) 명령어 종류를 enum 으로 정의
enum class Command {
    PUSH_BACK,   // push_back <값>
    INSERT,      // insert <index> <값>
    ERASE,       // erase <index>
    AT,          // at <index>
    CLEAR,       // clear
    SIZE,        // size
    EMPTY,       // empty
    PRINT,       // print
    FILE_OPEN,   // 파일 내용 불러오기
    FILE_OUT,    // 파일로 내보내기
    HELP,        // help
    QUIT,        // quit
    UNKNOWN      // 그 외
};

// 2) 입력 문자열 -> enum 으로 변환
Command parse(const std::string& s) {
    if (s == "push_back" || s == "pb")  return Command::PUSH_BACK;
    if (s == "insert"    || s == "ins") return Command::INSERT;
    if (s == "erase"     || s == "er")  return Command::ERASE;
    if (s == "at")                      return Command::AT;
    if (s == "clear")                   return Command::CLEAR;
    if (s == "size")                    return Command::SIZE;
    if (s == "empty")                   return Command::EMPTY;
    if (s == "print"     || s == "p")   return Command::PRINT;
    if (s == "file_open")               return Command::FILE_OPEN;
    if (s == "file_out")                return Command::FILE_OUT;
    if (s == "help"      || s == "h")   return Command::HELP;
    if (s == "quit" || s == "exit" || s == "q") return Command::QUIT;
    return Command::UNKNOWN;
}

// 현재 배열 상태를 한 줄로 출력
void print_state(cdh<int>& v) {
    std::cout << "  => size=" << v.size() << ", 내용 = { ";
    for (int x : v) std::cout << x << " ";
    std::cout << "}\n";
}

void print_help() {
    std::cout <<
        "----- 사용 가능한 명령어 -----\n"
        "  push_back <값>        맨 뒤에 추가\n"
        "  insert <index> <값>   index 위치에 삽입\n"
        "  erase <index>         index 원소 삭제\n"
        "  at <index>            index 원소 값 출력\n"
        "  clear                 전부 비우기\n"
        "  size                  개수 출력\n"
        "  empty                 비었는지 확인\n"
        "  print                 현재 내용 출력\n"
        "  file_open             파일 내용 불러오기\n"
        "  file_out              현재 내용 파일로 내보내기\n"
        "  help                  이 도움말\n"
        "  quit                  종료\n"
        "-----------------------------\n";
}

int main() {
    cdh<int> v;
    print_help();

    std::string cmd;
    // 3) 명령어를 하나 읽을 때마다 처리 + 갱신 결과 출력
    while (std::cout << "\n> " && std::cin >> cmd) {
        Command c = parse(cmd);

        switch (c) {
            case Command::PUSH_BACK: {
                int value;
                if (!(std::cin >> value)) { std::cout << "  [오류] 값을 입력하세요\n"; break; }
                v.push_back(value);
                std::cout << "  push_back(" << value << ")";
                print_state(v);
                break;
            }
            case Command::INSERT: {
                int index, value;
                if (!(std::cin >> index >> value)) { std::cout << "  [오류] index 와 값을 입력하세요\n"; break; }
                if (index < 0 || (size_t)index > v.size()) {
                    std::cout << "  [오류] index 범위는 0 ~ " << v.size() << "\n"; break;
                }
                v.insert(v.begin() + index, value);
                std::cout << "  insert(" << index << ", " << value << ")";
                print_state(v);
                break;
            }
            case Command::ERASE: {
                int index;
                if (!(std::cin >> index)) { std::cout << "  [오류] index 를 입력하세요\n"; break; }
                if (v.empty() || index < 0 || (size_t)index >= v.size()) {
                    std::cout << "  [오류] 삭제할 수 없는 index\n"; break;
                }
                v.erase(v.begin() + index);
                std::cout << "  erase(" << index << ")";
                print_state(v);
                break;
            }
            case Command::AT: {
                int index;
                if (!(std::cin >> index)) { std::cout << "  [오류] index 를 입력하세요\n"; break; }
                if (index < 0 || (size_t)index >= v.size()) {
                    std::cout << "  [오류] index 범위 밖\n"; break;
                }
                std::cout << "  at(" << index << ") = " << v.at(index) << "\n";
                print_state(v);
                break;
            }
            case Command::CLEAR:
                v.clear();
                std::cout << "  clear()";
                print_state(v);
                break;
            case Command::SIZE:
                std::cout << "  size = " << v.size() << "\n";
                print_state(v);
                break;
            case Command::EMPTY:
                std::cout << "  empty = " << (v.empty() ? "true" : "false") << "\n";
                print_state(v);
                break;
            case Command::PRINT:
                print_state(v);
                break;
            case Command::FILE_OPEN:
                v.file_open();
                std::cout << "  file_open()";
                print_state(v);
                break;
            case Command::FILE_OUT:
                v.file_out();
                std::cout<<"  file_out()";
                print_state(v);
                
                break;
            case Command::HELP:
                print_help();
                break;
            case Command::QUIT:
                std::cout << "종료합니다.\n";
                return 0;
            default:
                std::cout << "  [오류] 알 수 없는 명령어: " << cmd << "  (help 입력)\n";
                break;
        }
    }
    return 0;
}