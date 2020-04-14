#include "RequestReader.h"
#include <cassert>

void Reader::readIn(string &str) {
    str = ""; // 初始化
    unsigned char c = getchar();
    while(isspace(c)) c = getchar();
    while(!isspace(c)) {
        str += c;
        c = getchar();
    }
}

void Reader::readIn(int &x) {
    x = 0;
    unsigned char c = getchar();
    while(isspace(c)) c = getchar();
    while(!isspace(c)) {
        x = x * 10 + c - '0';
        c = getchar();
    }
}

void Reader::readIn(Mahjong &tile) {
    string tmp;
    readIn(tmp);
    tile.resetFromString(tmp);
}
