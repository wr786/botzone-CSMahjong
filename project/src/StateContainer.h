
#pragma once

#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <valarray>

// 使用Mahjong类
#include "Mahjong.h"

using namespace std;

//typedef pair<char, int> Mahjong; // 所有麻将牌均以“大写字母+数字”组合表示

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
    int curPosition;                    // “我们”所处的位置，0是庄家。同样也可以在博弈树节点使用以判断敌我
    static int quan;                    // 圈风。因为在一把botzone游戏中，只考虑国标麻将的一局游戏，所以圈风应该是不变的
    valarray<Mahjong> inHand;           // 用于存储手牌
    valarray<Mahjong> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
    int curTurnPlayer;                  // 当前是哪个玩家的回合
    valarray<Mahjong> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
    valarray<Mahjong> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
    valarray<Mahjong> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
    valarray<Mahjong> discards;         // 用于存放弃牌堆
    valarray<Mahjong> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
    int secretGangCntOf[4]{};           // 用于记录"暗杠"的数量，通过输入数据我们可以判断出某名玩家有几个暗杠，但我们不知道暗杠的是什么
    Mahjong lastPlayed;                 // 用于记录上个回合被打出的麻将牌，如果为"N0"则上回合是其他操作（比如其他玩家抽牌、补花

public:
    explicit StateContainer(int curP=0, int curT=0);
    StateContainer(const StateContainer& other);

    [[nodiscard]] valarray<Mahjong>& getInHand();                               // 获取手牌
    [[nodiscard]] valarray<Mahjong>& getFlowerTilesOf(int idx);                 // 获取花牌
    [[nodiscard]] valarray<Mahjong>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
    [[nodiscard]] valarray<Mahjong>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
    [[nodiscard]] valarray<Mahjong>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
    [[nodiscard]] valarray<Mahjong>& getDiscards();                             // 获取弃牌堆
    [[nodiscard]] valarray<Mahjong>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌

    [[nodiscard]] const valarray<Mahjong>& getInHand() const;                   //  获取手牌的常引用，下同上
    [[nodiscard]] const valarray<Mahjong>& getFlowerTilesOf(int idx) const;
    [[nodiscard]] const valarray<Mahjong>& getChiOf(int idx) const;
    [[nodiscard]] const valarray<Mahjong>& getPengOf(int idx) const;
    [[nodiscard]] const valarray<Mahjong>& getGangOf(int idx) const;
    [[nodiscard]] const valarray<Mahjong>& getDiscards() const;
    [[nodiscard]] const valarray<Mahjong>& getTilePlayedOf(int idx) const;

    [[nodiscard]] int getSecretGangCntOf(int idx) const;                        // 获取某名玩家的暗杠数量

    void setCurPosition(int curP);                                              // 设置“我们"当前的编号（座位
    [[nodiscard]] int getCurPosition() const;                                   // 获得我们当前的编号
    void setCurTurnPlayer(int curTP);                                           // 设置当前回合行动的玩家
    [[nodiscard]] int getCurTurnPlayer() const;                                 // 获得当前回合行动的玩家的编号
    void setLastPlayed(const Mahjong& lastTile);                                // 设置上一个被打出来的麻将
    [[nodiscard]] const Mahjong& getLastPlayed() const;                         // 获得上一个被打出来的麻将的常引用

    void nxtPosition();                                                         // 将当前的编号（座位）移动到下一个，！应该不常用
    void nxtTurn();                                                             // 进入下一回合
};

#endif