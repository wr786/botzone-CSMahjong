#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#ifndef _PREPROCESS_ONLY
#include <valarray>
#include <vector>
#include <algorithm>
#endif

// 使用Majang类
#include "Majang.h"

using namespace std;

//typedef pair<char, int> Majang; // 所有麻将牌均以“大写字母+数字”组合表示

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
    int curTurnPlayer;                  // 当前是哪个玩家的回合
//    valarray<Majang> inHand;           // 用于存储手牌
//    valarray<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
//    valarray<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
//    valarray<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
//    valarray<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
////    valarray<Majang> discards;       // 用于存放弃牌堆
//    valarray<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
    vector<Majang> inHand;           // 用于存储手牌
    vector<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
    vector<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
    vector<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
    vector<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
//    valarray<Majang> discards;       // 用于存放弃牌堆
    vector<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
    int secretGangCntOf[4];           // 用于记录"暗杠"的数量，通过输入数据我们可以判断出某名玩家有几个暗杠，但我们不知道暗杠的是什么
    // 下面这个lastPlayed还没确定好到底怎么用，想好的时候再改吧
    Majang lastPlayed;                 // 用于记录上个回合被打出的麻将牌，如果不是麻将牌类型的话则为其他操作（具体见RequestReader::readRequest
    int tileLeft[70];                   // 用于记录各种类型牌所剩余的没出现的数量
    int totalLeft;                      // 没出现过的牌的总数（初始144）
    int inHandCnt[4];                   // 用于记录四名玩家的手牌数量(虽然不知道有没有用)

public:
    static int quan;                    // 圈风。因为在一把botzone游戏中，只考虑国标麻将的一局游戏，所以圈风应该是不变的
    static int lastRequest;             // 上回合的操作,用于算番器的isGANG,采取博弈算法时应换一种存储方式

    explicit StateContainer(int curP=0, int curT=0);
    StateContainer(const StateContainer& other);

//    [[nodiscard]] valarray<Majang>& getInHand();                               // 获取手牌
//    [[nodiscard]] valarray<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
//    [[nodiscard]] valarray<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
//    [[nodiscard]] valarray<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
//    [[nodiscard]] valarray<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
////    [[nodiscard]] valarray<Majang>& getDiscards();                             // 获取弃牌堆
//    [[nodiscard]] valarray<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌
//
//    [[nodiscard]] const valarray<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
//    [[nodiscard]] const valarray<Majang>& getFlowerTilesOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getChiOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getPengOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getGangOf(int idx) const;
////    [[nodiscard]] const valarray<Majang>& getDiscards() const;
//    [[nodiscard]] const valarray<Majang>& getTilePlayedOf(int idx) const;

    [[nodiscard]] vector<Majang>& getInHand();                               // 获取手牌
    [[nodiscard]] vector<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
    [[nodiscard]] vector<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
    [[nodiscard]] vector<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
    [[nodiscard]] vector<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
    [[nodiscard]] vector<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌

    [[nodiscard]] const vector<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
    [[nodiscard]] const vector<Majang>& getFlowerTilesOf(int idx) const;
    [[nodiscard]] const vector<Majang>& getChiOf(int idx) const;
    [[nodiscard]] const vector<Majang>& getPengOf(int idx) const;
    [[nodiscard]] const vector<Majang>& getGangOf(int idx) const;
    [[nodiscard]] const vector<Majang>& getTilePlayedOf(int idx) const;

    void decTileLeft(int idx);                                                  // 在减少idx对应的牌的数量的同时，减少总数的数量
    void decTileLeft(Majang mj);                                               // 同上
    [[nodiscard]] const int & getTileLeft(int idx) const;                       // 获得idx对应的牌的剩余数量
    [[nodiscard]] const int & getTotalLeft() const;                             // 获得所有牌的剩余数量

    void incSecretGangCntOf(int idx);                                           // 给某名玩家的暗杠数量+1
    [[nodiscard]] int getSecretGangCntOf(int idx) const;                        // 获取某名玩家的暗杠数量

    void setCurPosition(int curP);                                              // 设置“我们"当前的编号（座位
    [[nodiscard]] int getCurPosition() const;                                   // 获得我们当前的编号
    void setCurTurnPlayer(int curTP);                                           // 设置当前回合行动的玩家
    [[nodiscard]] int getCurTurnPlayer() const;                                 // 获得当前回合行动的玩家的编号
    void setLastPlayed(const Majang& lastTile);                                // 设置上一个被打出来的麻将
    [[nodiscard]] const Majang& getLastPlayed() const;                         // 获得上一个被打出来的麻将的常引用
    void setInHandCntOf(int idx, int cnt);                                      // 将idx号玩家的手牌数量设置为cnt
    [[nodiscard]] int getInHandCntOf(int idx) const;                            // 获取idx号玩家的手牌数量
    void incInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量+1
    void decInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量-1

    void deleteFromInHand(const Majang& toDelete);                             // 从手牌中去除toDelete   //? 可能是一个优化点

    void nxtPosition();                                                         // 将当前的编号（座位）移动到下一个，！应该不常用
    void nxtTurn();                                                             // 进入下一回合
};

#endif