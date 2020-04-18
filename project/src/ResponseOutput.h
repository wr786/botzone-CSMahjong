#ifndef _BOTZONE_ONLINE
#define pragma once
#endif

#ifndef RESPONSEOUTPUT_H
#define RESPONSEOUTPUT_H

#include <string>
#include <cstring>
#include <vector>

#include "Majang.h"
#include "StateContainer.h"
#include "ScoreCalculator.h"

using namespace std;

class Output{
public:
    static void Response(int request, StateContainer state);     //由局面状态(state)和上一步操作(request)得到输出
    static bool judgeHu(vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& winTile,bool isZIMO);   //判断是否胡了
    static bool judgeGang(int tileAmout[70],vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& newTile,StateContainer state,int status);    //判断能否杠,status=2表示为摸牌后，status=3表示对手出牌后;如果能,再判断是否要杠
    static bool judgeBuGang(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& newTile);   //摸牌后判断能否补杠,如果能,再判断是否要杠
    static bool judgePeng(int tileAmout[70], const Majang& newTile);    //对手出牌后判断能否碰
    static int judgeChi(int tileAmout[70], const Majang& newTile);     //对手出牌后判断能否吃,返回值1,2,3分别表示表示吃的牌是组成刻子中的第1,2,3张.
    static const pair<double,Majang> getBestPlay(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand);   //返回最优的出牌及此时的评估值
    static const Majang getBestCP(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& newTile,int pos); //判断是否要吃(c)碰(p),若要则返回之后打出的Majang,否则Majang值为1;pos为0表示要进行的操作为碰或杠,否则表示吃时newTile的位置
};

#endif