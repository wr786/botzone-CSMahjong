
#pragma once

#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include <string>
#include <vector>
#include <utility>

#include <mahjong.h>
#include <StateContainer.h>

using namespace std;

//手牌得分用于出牌时的决策，通过比较出掉某一张牌后剩余12张牌的得分，可得到最优的出牌
//只考虑了自己怎么能赢，而没考虑与对手的博弈，这是一版极其自闭的评估函数。


//参数实际应按游戏回合分段，这里先随便写了一个
#define k1 0.5    // 手牌得分所占权重
#define k2 0.3    // 自摸番数得分所占权重
#define k3 0.2    // 点炮番数得分所占权重
#define k4 0.1    // 番数和转化为番数得分的系数


//返回一副牌的得分(番数得分和手牌得分的加权和)
double MahjongScoreCalculator(
    vector<pair<string, Mahjong> > pack,
    //pack:玩家的明牌，每组第一个string为"PENG" "GANG" "CHI" 三者之一，第二个为牌（吃牌表示中间牌）
    vector<Mahjong> hand,
    //hand:玩家的暗牌
    int flowerCount,
    //flowerCount:补花数
    StateContainer state
    //StateContainer:牌库状态
);

//利用算番器计算番数得分
double FanScoreCalculator(
    vector<pair<string, Mahjong> > pack,
    vector<Mahjong> hand,
    int flowerCount,
    Mahjong winTile   
);

//一副牌的番数得分 
double MahjongFanScore(
    vector<pair<string, Mahjong> > pack,
    vector<Mahjong> hand,
    int flowerCount,
    StateContainer state
);

//一副牌的手牌得分(赋予顺子、刻子、杠、碰、吃相应的得分)
double MahjongHandScore(
    vector<pair<string, Mahjong> > pack,
    vector<Mahjong> hand
);


#endif