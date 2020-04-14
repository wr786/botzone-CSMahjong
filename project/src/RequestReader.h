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

    // todo 接下来应该有能根据对应编号读入不同的信息并存放到StateContainer的方法，待补全
    // 返回值为int，代表这条request读取到了什么操作
    // 其中我们规定:
    // 0 -> 0, 1 -> 1, 2 -> 2 这三条就像原来一样，两个初始化，一个抽牌
    // 30 -> BUHUA, 31 -> DRAW, 32 -> PLAY
    // 33 -> PENG, 34 -> CHI, 35 -> GANG, 36 -> BUGANG
    static int readRequest(StateContainer& state) {
        int requestID, tmp;
        int ret = 0;
        readIn(requestID);
        // 这里因为request只有四种，所以直接上switch了
        switch (requestID) {
            case 0: { // 初始化
                readIn(tmp);
                state.setCurPosition(tmp);
                readIn(StateContainer::quan);
                state.setLastPlayed("I0"); // I0 -> Initialize 0
                ret = 0;
                break;
            }
            case 1: { // 初始手牌
                // 读取花牌数量
                for (int i = 0; i < 4; i++) {
                    readIn(tmp);
                    state.getFlowerTilesOf(i).resize(tmp);
                }
                // 读取手牌
                assert(state.getInHand().size() == 13);
                for (int i = 0; i < 13; i++) {
                    readIn(state.getInHand()[i]);
                    state.decTileLeft(state.getInHand()[i]);
                }
                // 读取花牌
                for (int i = 0; i < 4; i++) {
                    int lim = state.getFlowerTilesOf(i).size();
                    for (int j = 0; j < lim; j++) {
                        readIn(state.getFlowerTilesOf(i)[j]);
                        state.decTileLeft(state.getFlowerTilesOf(i)[j]);
                    }
                }
                state.setLastPlayed("I1"); // I1 -> Initialize 1
                ret = 1;
                break;
            }
            case 2: { // 我们抽牌
                valarray<Mahjong>& tmpInHand = state.getInHand();
                int pos = tmpInHand.size();
                tmpInHand.resize(pos+1);
                readIn(tmpInHand[pos]);
                state.setLastPlayed("D6"); // D6 -> Draw!
                state.incInHandCntOf(state.getCurPosition());
                state.setCurTurnPlayer(state.getCurPosition());
                state.decTileLeft(tmpInHand[pos]);
                ret = 2;
                break;
            }
            case 3: { // 其他情况
                ret = 30;
                int playerID; readIn(playerID);
                state.setCurTurnPlayer(playerID); // 这条request谁进行了操作，谁就是curTurnPlayer
                string op; readIn(op);
                if (op == "BUHUA") {
                    ret += 0;
                    valarray<Mahjong> &tmpHana = state.getFlowerTilesOf(playerID);
                    int pos = tmpHana.size();
                    tmpHana.resize(pos + 1);
                    readIn(tmpHana[pos]);
                    state.decTileLeft(tmpHana[pos]);
                    // 这里不进行setLastPlayed，因为不会轮到我们操作
                } else if (op == "DRAW") {
                    ret += 1;
                    state.incInHandCntOf(playerID);
                } else if (op == "PLAY") {
                    Mahjong tmpPlayed; readIn(tmpPlayed);
                    state.setLastPlayed(tmpPlayed);
                    state.decInHandCntOf(playerID);
                    valarray<Mahjong>& tmpTilePlayed = state.getTilePlayedOf(playerID);
                    int pos = tmpTilePlayed.size();
                    tmpTilePlayed.resize(pos + 1);
                    tmpTilePlayed[pos] = tmpPlayed;
                    state.decTileLeft(tmpPlayed);
                    if(playerID == state.getCurPosition()) {
                        // 是我们打出的这张牌,这时需要从我们的手牌中去除这张牌
                        valarray<Mahjong>& inHand = state.getInHand();
                        int lim = inHand.size();
                        for(int i=0; i<lim; i++) { //! 顺序查找删除会不会影响效率?可能是个可改进的地方
                            if(inHand[i] == tmpPlayed) {
                                swap(inHand[i], inHand[lim-1]);
                                break;
                            }
                        }
                        inHand.resize(pos-1);
                    }
                    ret += 2;
                } else if (op == "PENG") {
                    // todo 补全剩下四项
                    // 稍微休息一下，并作信息交换。
                    ret += 3;
                } else if (op == "CHI") {
                    ret += 4;
                } else if (op == "GANG") {
                    ret += 5;
                } else if (op == "BUGANG") {
                    ret += 6;
                } else {
                    assert("[ERROR] readOP failed!" == "");
                }
                break;
            }
            default: {
                assert("[ERROR] readRequestID failed!" == "");
                break;
            }
        }
        return ret;
    }
};

#endif
