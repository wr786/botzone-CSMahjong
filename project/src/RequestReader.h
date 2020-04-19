#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef REQUESTREADER_H
#define REQUESTREADER_H

#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <valarray>
#include <cassert>
#include "Majang.h"
#include "StateContainer.h"
#ifdef _BOTZONE_ONLINE
#include "MahjongGB/MahjongGB.h"
#endif

using namespace std;

class Reader{
public:
    static void readIn(string& str);                            // 读取string
    static void readIn(int& x);                                 // 读取int
    static void readIn(Majang& tile);                          // 读取Majang

    // 能根据对应编号读入不同的信息并存放到StateContainer
    // 返回值为int，代表这条request读取到了什么操作
    // 其中我们规定:
    // 0 -> 0, 1 -> 1, 2 -> 2 这三条就像原来一样，两个初始化，一个抽牌
    // 30 -> BUHUA, 31 -> DRAW, 32 -> PLAY
    // 33 -> PENG, 34 -> CHI, 35 -> GANG, 36 -> BUGANG
    static int readRequest(StateContainer& state);              // 用于读取一条request
};

#endif
