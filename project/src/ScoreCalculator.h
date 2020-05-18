#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#ifndef _PREPROCESS_ONLY
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <unordered_map>
#endif

#include "Majang.h"
#include "StateContainer.h"
#include "ShantenCalculator.h"

// 直接使用botzone上的内置算番器（因为我实在不知道怎么配置了
#ifdef _BOTZONE_ONLINE
#ifndef _PREPROCESS_ONLY
#include "MahjongGB/MahjongGB.h"
#endif
#else
#include "../utils/MahjongGB/MahjongGB.h"
#endif

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

    // 可能性计算器（被相似度计算器调用）
    static double ProbabilityCalc(const StateContainer& state,
        const Majang& aim
    );

    // 相似度计算器
    static double SimilarityCalc(const StateContainer& state,
        const UsefulTableT& aim
    );

    //利用算番器计算番数得分
    static double FanScoreCalculator(
        vector<pair<string, Majang> > pack,
        vector<Majang> hand,
        int flowerCount,
        Majang winTile,
        StateContainer state   
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

    static int fanCalculator(
        int tileAmount[70],
        vector<int> handAndPack,
        int quanfeng,
        int menfeng
    );

    static unordered_map<int, int> cntPlayedRecently;
    static void calcPlayedRecently(const StateContainer& state);
};

#endif