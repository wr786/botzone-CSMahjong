#pragma once

#ifndef REQUESTREADER_H
#define REQUESTREADER_H

#include <cstdio>
#include <cctype>
#include <string>
#include <cassert>
#include "Mahjong.h"
#include "StateContainer.h"

using namespace std;

class Reader{
public:
    static void readIn(string& str);                            // 读取string
    static void readIn(int& x);                                 // 读取int
    static void readIn(Mahjong& tile);                          // 读取Mahjong

    // todo 接下来应该有能根据对应编号读入不同的信息并存放到StateContainer的方法，待补全
    static void readRequest(StateContainer& state) {
        int requestID = -1;
        // 这里因为request只有九种，所以直接上switch了
        switch (readIn(requestID) ;requestID) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            default:
                assert("[ERROR] readRequestID failed!" == "");
                break;
        }
    }
};

#endif
