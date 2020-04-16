
//#pragma once

#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include <string>
#include <cstring>
#include <vector>
#include <utility>

#include "Majang.h"
#include "StateContainer.h"

#include "../utils/Mahjong-GB-CPP/MahjongGB/MahjongGB.h"

using namespace std;

//手牌得分用于出牌时的决策，通过比较出掉某一张牌后剩余13张牌的得分，可得到最优的出牌
//只考虑了自己怎么能赢，而没考虑与对手的博弈，这是一版极其自闭的评估函数。

//如何使用(仅供参考)：
//1.出牌时通过比较出掉某一张牌后剩余13张牌的得分与风险系数的乘积(用于评估对手对该牌的需要程度),得到最优出牌
//2.决策杠、吃、碰时通过比较操作前后得分的变化决定是否进行该操作.

class Calculator{
public:
    //返回一副牌的得分(番数得分和手牌得分的加权和)
    static double MajangScoreCalculator(
        vector<pair<string, Majang> > pack,
        //pack:玩家的明牌，每组第一个string为"PENG" "GANG" "CHI" 三者之一，第二个为牌（吃牌表示中间牌）
        vector<Majang> hand,
        //hand:玩家的暗牌
        int flowerCount,
        //flowerCount:补花数
        StateContainer state
        //StateContainer:牌库状态
    );

    //利用算番器计算番数得分
    static double FanScoreCalculator(
        vector<pair<string, Majang> > pack,
        vector<Majang> hand,
        int flowerCount,
        Majang winTile   
    );

    //一副牌的番数得分 
    static double MajangFanScore(
        vector<pair<string, Majang> > pack,
        vector<Majang> hand,
        int flowerCount,
        StateContainer state
    );

    //一副牌的手牌得分(赋予顺子、刻子、杠、碰、吃相应的得分)
    static double MajangHandScore(
        vector<pair<string, Majang> > pack, 
        vector<Majang> hand
    );

    static double HandScoreCalculator(
        int TileAmount[70]
    );
};

#endif