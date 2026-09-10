#include <iostream>
#include <string>
#include <fstream>
#include "dataframe1.hpp"     // std::vector 안 씀! 헤더는 그대로

// 1) 명령어 종류
enum class Command {
    PUSH_BACK, INSERT, ERASE, AT, CLEAR, SIZE, EMPTY, PRINT,
    FILE_OPEN, FILE_OUT,
    NEW, CHANGE, DELETE, ADD, LIST,   // 다중 객체용
    HELP, QUIT, UNKNOWN
};

// 2) 입력 문자열 -> enum
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
    if (s == "new")                     return Command::NEW;
    if (s == "change"    || s == "cd")  return Command::CHANGE;
    if (s == "delete"    || s == "del") return Command::DELETE;
    if (s == "add")                     return Command::ADD;
    if (s == "list"      || s == "ls")  return Command::LIST;
    if (s == "help"      || s == "h")   return Command::HELP;
    if (s == "quit" || s == "exit" || s == "q") return Command::QUIT;
    return Command::UNKNOWN;
}

// 객체 하나를 " * v0 [ ... ], size=n " 형태로 출력
void print_one(size_t idx, cdh<int>& v, bool isCurrent) {
    std::cout << (isCurrent ? " * " : "   ")
              << "v" << idx << " [ ";
    for (int x : v) std::cout << x << " ";
    std::cout << "], size=" << v.size() << "\n";
}

// 전체 객체 출력  (바깥 컨테이너 타입이 cdh<cdh<int>> 로 바뀜)
void print_all(cdh<cdh<int>>& frames, size_t cur) {
    std::cout << "  ---- 전체 객체 (" << frames.size() << "개, * = 현재) ----\n";
    for (size_t i = 0; i < frames.size(); i++)
        print_one(i, frames.at(i), i == cur);   // frames[i] -> frames.at(i)
    std::cout << "  ------------------------------------------\n";
}

void print_help() {
    std::cout <<
        "----- 사용 가능한 명령어 -----\n"
        "  [현재 객체 조작]\n"
        "  push_back <값>        맨 뒤에 추가\n"
        "  insert <index> <값>   index 위치에 삽입\n"
        "  erase <index>         index 원소 삭제\n"
        "  at <index>            index 원소 값 출력\n"
        "  clear                 현재 객체 비우기\n"
        "  size / empty / print  개수 / 빈지 / 내용\n"
        "  file_open / file_out  파일 입출력\n"
        "  [다중 객체]\n"
        "  new                   새 객체 생성(그리로 전환)\n"
        "  change <index>        조작 대상 객체 전환\n"
        "  delete <index>        객체 삭제\n"
        "  add <i> <j>           v[i] + v[j] 결과를 새 객체로 생성\n"
        "  list                  전체 객체 목록\n"
        "  help / quit\n"
        "-----------------------------\n";
}

int main() {
    cdh<cdh<int>> frames;           // ← 내가 만든 cdh 로 컨테이너를 만든다
    frames.push_back(cdh<int>());   // 시작 시 객체 1개(v0)
    size_t cur = 0;                 // 현재 조작 대상 index

    print_help();

    std::string cmd;
    while (std::cout << "\n[v" << cur << "] > " && std::cin >> cmd) {
        Command c = parse(cmd);
        cdh<int>& v = frames.at(cur);   // frames[cur] -> frames.at(cur)

        switch (c) {
            case Command::PUSH_BACK: {
                int value;
                if (!(std::cin >> value)) { std::cout << "  [오류] 값을 입력하세요\n"; break; }
                v.push_back(value);
                std::cout << "  push_back(" << value << ")\n";
                print_all(frames, cur);
                break;
            }
            case Command::INSERT: {
                int index, value;
                if (!(std::cin >> index >> value)) { std::cout << "  [오류] index 와 값을 입력하세요\n"; break; }
                if (index < 0 || (size_t)index > v.size()) {
                    std::cout << "  [오류] index 범위는 0 ~ " << v.size() << "\n"; break;
                }
                v.insert(v.begin() + index, value);
                std::cout << "  insert(" << index << ", " << value << ")\n";
                print_all(frames, cur);
                break;
            }
            case Command::ERASE: {
                int index;
                if (!(std::cin >> index)) { std::cout << "  [오류] index 를 입력하세요\n"; break; }
                if (v.empty() || index < 0 || (size_t)index >= v.size()) {
                    std::cout << "  [오류] 삭제할 수 없는 index\n"; break;
                }
                v.erase(v.begin() + index);
                std::cout << "  erase(" << index << ")\n";
                print_all(frames, cur);
                break;
            }
            case Command::AT: {
                int index;
                if (!(std::cin >> index)) { std::cout << "  [오류] index 를 입력하세요\n"; break; }
                if (index < 0 || (size_t)index >= v.size()) {
                    std::cout << "  [오류] index 범위 밖\n"; break;
                }
                std::cout << "  at(" << index << ") = " << v.at(index) << "\n";
                break;
            }
            case Command::CLEAR:
                v.clear();
                std::cout << "  clear()\n";
                print_all(frames, cur);
                break;
            case Command::SIZE:
                std::cout << "  size = " << v.size() << "\n";
                break;
            case Command::EMPTY:
                std::cout << "  empty = " << (v.empty() ? "true" : "false") << "\n";
                break;
            case Command::PRINT:
                print_one(cur, v, true);
                break;
            case Command::FILE_OPEN:
                v.file_open();
                std::cout << "  file_open()\n";
                print_all(frames, cur);
                break;
            case Command::FILE_OUT:
                v.file_out();
                std::cout << "  file_out()\n";
                break;

            // ---------------- 다중 객체 ----------------
            case Command::NEW: {
                frames.push_back(cdh<int>());
                cur = frames.size() - 1;
                std::cout << "  new() -> v" << cur << " 생성 및 전환\n";
                print_all(frames, cur);
                break;
            }
            case Command::CHANGE: {
                int index;
                if (!(std::cin >> index)) { std::cout << "  [오류] index 를 입력하세요\n"; break; }
                if (index < 0 || (size_t)index >= frames.size()) {
                    std::cout << "  [오류] 객체 index 범위는 0 ~ " << frames.size() - 1 << "\n"; break;
                }
                cur = index;
                std::cout << "  change -> 현재 객체 v" << cur << "\n";
                print_all(frames, cur);
                break;
            }
            case Command::DELETE: {
                int index;
                if (!(std::cin >> index)) { std::cout << "  [오류] index 를 입력하세요\n"; break; }
                if (index < 0 || (size_t)index >= frames.size()) {
                    std::cout << "  [오류] 객체 index 범위 밖\n"; break;
                }
                if (frames.size() == 1) {
                    std::cout << "  [오류] 마지막 객체는 삭제할 수 없습니다\n"; break;
                }
                frames.erase(frames.begin() + index);
                if (cur >= frames.size())      cur = frames.size() - 1;
                else if ((size_t)index < cur)  cur--;
                std::cout << "  delete(v" << index << ")\n";
                print_all(frames, cur);
                break;
            }
            case Command::ADD: {
                int i, j;
                if (!(std::cin >> i >> j)) { std::cout << "  [오류] 두 객체 index 를 입력하세요\n"; break; }
                if (i < 0 || j < 0 ||
                    (size_t)i >= frames.size() || (size_t)j >= frames.size()) {
                    std::cout << "  [오류] 객체 index 범위 밖\n"; break;
                }
                // 안쪽 cdh<int> 의 operator+ 로 새 객체 생성
                frames.push_back(frames.at(i) + frames.at(j));
                cur = frames.size() - 1;
                std::cout << "  add: v" << i << " + v" << j
                          << " -> v" << cur << " 생성\n";
                print_all(frames, cur);
                break;
            }
            case Command::LIST:
                print_all(frames, cur);
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