#pragma once

#ifndef REQUESTREADER_H
#define REQUESTREADER_H

#include <cstdio>
#include <cctype>
#include <string>
#include <valarray>
#include <cassert>
#include "Mahjong.h"
#include "StateContainer.h"

using namespace std;

class Reader{
public:
    static void readIn(string& str);                            // 读取string
    static void readIn(int& x);                                 // 读取int
    static void readIn(Mahjong& tile);                          // 读取Mahjong

    // 能根据对应编号读入不同的信息并存放到StateContainer
    // 返回值为int，代表这条request读取到了什么操作
    // 其中我们规定:
    // 0 -> 0, 1 -> 1, 2 -> 2 这三条就像原来一样，两个初始化，一个抽牌
    // 30 -> BUHUA, 31 -> DRAW, 32 -> PLAY
    // 33 -> PENG, 34 -> CHI, 35 -> GANG, 36 -> BUGANG
    static int readRequest(StateContainer& state);              // 用于读取一条request
};

#endif
