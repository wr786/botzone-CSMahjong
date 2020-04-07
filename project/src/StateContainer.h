#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <string>
#include <iostream>
#include <valarray>

using namespace std;

typedef pair<char, int> Mahjong; // 所有麻将牌均以“大写字母+数字”组合表示

// 从题目的输入request的0~9可知，在输入环节我们可以得到的信息有：
// 0. 我们的位置、当前的风圈 
// 1. 我们的起始手牌、四名玩家各人的花牌
// 2. 当前是哪个玩家的回合（可以通过各个摸牌操作来判断）
// 3. 各个玩家的鸣牌（可以通过吃碰杠来获得）
// 4. "弃牌堆"中的牌（被打出之后没有被吃碰杠、点炮的牌）

// 用于存放当前的局面
// 由于该部分很多函数很简单，就不费笔墨写注释了，也没有将实现分离到cpp中
class StateContainer {
private:
    int curPosition; // “我们”所处的位置，0是庄家。同样也可以在博弈树节点使用以判断敌我
    static int quan; // 圈风。因为在一把botzone游戏中，只考虑国标麻将的一局游戏，所以圈风应该是不变的
    valarray<Mahjong> inHand; // 用于存储手牌
    valarray<Mahjong> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
    int curTurnPlayer; // 当前是哪个玩家的回合
    valarray<Mahjong> chiOf[4]; // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
    valarray<Mahjong> pengOf[4]; // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
    valarray<Mahjong> gangOf[4]; // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
    valarray<Mahjong> discards; // 用于存放弃牌堆
public:
    StateContainer() {inHand.resize(13);}
    StateContainer(const StateContainer& other) {
        curPosition = other.curPosition;
        inHand = other.inHand;
        curTurnPlayer = other.curTurnPlayer;
        for(int i=0; i<4; i++) {
            flowerTilesOf[i] = other.flowerTilesOf[i];
            chiOf[i] = other.chiOf[i];
            pengOf[i] = other.pengOf[i];
            gangOf[i] = other.gangOf[i];
            discards[i] = other.discards[i];
        }
    }
    inline valarray<Mahjong>& getInHand() {return inHand;}
    inline valarray<Mahjong>& getFlowerTilesOf(int __idx) {return flowerTilesOf[__idx];}
    inline valarray<Mahjong>& getChiOf(int __idx) {return chiOf[__idx];}
    inline valarray<Mahjong>& getPengOf(int __idx) {return pengOf[__idx];}
    inline valarray<Mahjong>& getGangOf(int __idx) {return gangOf[__idx];}
    inline valarray<Mahjong>& getDiscards() {return discards;}
    inline void setCurPosition(int __curP) {curPosition = __curP;}
    inline int getCurPosition() {return curPosition;}
    inline void setCurTurnPlayer(int __curTP) {curTurnPlayer = __curTP;}
    inline int getCurTurnPlayer() {return curTurnPlayer;}
    inline void nxtPosition() {curPosition = (curPosition + 1) % 4;}
    inline void nxtTurn() {curTurnPlayer = (curTurnPlayer + 1) % 4;}
};

#endif