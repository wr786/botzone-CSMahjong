#include "ScoreCalculator.h"
#ifndef _PREPROCESS_ONLY
#include <iostream>
#endif
using namespace std;

//最终在决策时还应乘上出相应牌的风险系数(用于评估对手对该牌的需要程度)
double Calculator::MajangScoreCalculator(
    vector<pair<string, Majang> > pack,
    vector<Majang> hand,
    int flowerCount,
    StateContainer state
) {
    //参数实际应按游戏回合分段，这里先随便写了一个
    double k1=0.4;    // 手牌得分所占权重
    double k2=0.3;    // 自摸番数得分所占权重
    double k3=0.3;    // 点炮番数得分所占权重
    double k4=0.0;    // 复合上听数所占权重
    //freopen("D://out.txt","a",stdout);
    double r1 = MajangHandScore(pack, hand);
    double r2 = MajangFanScore(pack, hand, flowerCount, state, 0);

    double resultShanten = 0;   // 在shanten写好之后，将结果存入resultShanten

    int param1, param2, param3;
    mahjong::useful_table_t useful_table;
    //auto p = ShantenCalc(pack, hand, useful_table);
    //param1 = p.first;                               // shanten数
    //param2 = p.second;                              // effective tiles
    //param3 = SimilarityCalc(state, useful_table);   // similarity

    // 其实讲道理这里仅应该使用similarity一个参量
    // shanten数是离听牌的距离
    // 同样shanten数下，effective tiles越多，能减少shanten数的几率就越大
    // 但是，不是所有effective tiles被抽中的概率都相同，于是加权就得到similarity参量
    // 这是一层。可是，这一次减少shanten数的几率大，不代表最终达到听牌的几率也大呀，
    // 万一采取这种方式时再减少很困难怎么办呢，所以可能要应用搜索
    // 应用搜索还有一个好处，就是可以把番数评估直接加进结果中去，总共节省了两个参量有木有（
    // 感觉这样就突然和亚马逊棋像了起来，怕是可以用MinMax搜索或者MCTS
    // 工作量暴增.jpg

    // 在未应用多层搜索时，可以看出，shanten数应当有着相当大的（负）权重
    // 毕竟在没有其他信息的情况下，很难认为一个大shanten数反而更容易听牌
    // 另外，此时概率大概要取对数（？）
    // 所以暂时令
    //double k5=0.5;
    //if(param3 > 0) resultShanten = -(param1 - 1 - log(param3) * k5);	// 因为初始化是0，所以不用写else
    // param3是在[0,1)的，这意味着param1-1相当于param3变为e^2倍
    //cout<<r1<<" "<<r2<<endl;
    //计算点炮番数得分时，出牌的概率应考虑到博弈，还没有想清楚，先用自摸胡的算法计算点炮胡
    return r1 * k1 + r2 * (k2 + k3) + resultShanten * k4;
}

//参数c是用来使番数得分与手牌得分的数值相当
double Calculator::FanScoreCalculator(    
    vector<pair<string, Majang> > pack,//似乎可以直接用两位整数直接作为代表Majang的参数，从而节省时间与空间
    vector<Majang> hand,//似乎可以直接用两位整数直接作为代表Majang的参数，从而节省时间与空间
    int flowerCount,
    Majang winTile,
    StateContainer state
){  
    double k6=120.0;    //将Majang类调整为适用于算番器的接口    
    vector <pair<string,pair<string,int> > > p;
    for(unsigned int i=0;i<pack.size();++i){
        p.push_back(make_pair(pack[i].first,make_pair(pack[i].second.getTileString(),1)));
    }
    vector <string> h;
    for(unsigned int i=0;i<hand.size();++i){
        h.push_back(hand[i].getTileString());
    }
    //算番器啥时候初始化呢？
    MahjongInit();
    try{
        bool isJUEZHANG=state.getTileLeft(winTile.getTileInt())==0;
        bool isGANG=(StateContainer::lastRequest==36);
        bool isLast=state.isTileWallEmpty((state.getCurTurnPlayer()+1)%4);
        auto re=MahjongFanCalculator(p,h,winTile.getTileString(),flowerCount,1,isJUEZHANG,isGANG,isLast,state.getCurPosition(),StateContainer::quan);//算番器中有许多我未理解的参数,先用0代入——wym
        int r=0;
        for(unsigned int i=0;i<re.size();i++) r+=re[i].first;//这里暂且暴力地以求和的方式作为番数得分的计算公式
        return r*k6;
    }
    catch(const string &error){
        return 0;
    }
}

double Calculator::MajangFanScore(    
    vector<pair<string, Majang> > pack,
    vector<Majang> hand,
    int flowerCount,
    StateContainer state,
    int depth
){  
    double r=0;
    for(int i=11;i<=19;i++){
        if(state.getTileLeft(i)){
            StateContainer newstate(state);
            newstate.decTileLeft(i);            
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i),newstate);
        }
    }
    for(int i=21;i<=29;i++){
        if(state.getTileLeft(i)){
            StateContainer newstate(state);
            newstate.decTileLeft(i);
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i),newstate);
        }        
    }
    for(int i=31;i<=39;i++){
        if(state.getTileLeft(i)){
            StateContainer newstate(state);
            newstate.decTileLeft(i);
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i),newstate);
        }        
    }
    for(int i=41;i<=44;i++){
        if(state.getTileLeft(i)){
            StateContainer newstate(state);
            newstate.decTileLeft(i);
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i),newstate);
        }        
    }
    for(int i=51;i<=53;i++){
        if(state.getTileLeft(i)){
            StateContainer newstate(state);
            newstate.decTileLeft(i);
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i),newstate);
        }        
    }
    if(depth>=1) return r;
    for(int i=61;i<=68;i++){
      if(state.getTileLeft(i)){
           StateContainer newstate(state);
           newstate.decTileLeft(i);
           r+=(double)state.getTileLeft(i)/state.getTotalLeft()*MajangFanScore(pack,hand,flowerCount+1,newstate,depth+1);
       }
    }
    return r;    
}

//这里采用了将手牌hand和明牌pack合并起来计算的方式,若有必要,可以分开计算并赋上权值
//参数c是用来使番数得分与手牌得分的数值相当
double Calculator::MajangHandScore(
    vector<pair<string, Majang> > pack,
    vector<Majang> hand
) {
    double c = 1;
    double result = 0;
    int tileAmount[70];
    memset(tileAmount, 0, sizeof(tileAmount));
    for (unsigned int i = 0; i < hand.size(); i++) {
        tileAmount[hand[i].getTileInt()]++;
    }
    for (unsigned int i = 0; i < pack.size(); i++) {
        if (pack[i].first == "GANG") result += 16;
        else if (pack[i].first == "PENG") result += 9;
        else {
            result += 10;
        }
    }
    result += HandScoreCalculator(tileAmount);

    return result * c;
}

// 这是单层的，改进空间是升级成多层
double Calculator::SimilarityCalc(const StateContainer& state,
    const UsefulTableT& aim
){
    using namespace mahjong;
    vector<Majang> vct;
    for (tile_t i = 0; i < TILE_TABLE_SIZE; ++i)
    {
        if (aim[i])
        {
            auto mj = MahjongToMajang(i);
            vct.push_back(mj);
        }
    }
    double sim = 0;
    for (size_t i = 0; i < vct.size(); i++)
    {
        sim += ProbabilityCalc(state, vct[i]);
    }
    return sim;
}

double Calculator::ProbabilityCalc(const StateContainer& state,
    const Majang& aim
){
    const int playerIdx = state.getCurTurnPlayer();

    int OtherMingTilesCnt = 0;
    for (int i = 0; i < 4; ++i) {
        if (i != playerIdx) {
            // 他人鸣牌总数
            OtherMingTilesCnt += state.getPengOf(i).size() * 3;
            OtherMingTilesCnt += state.getChiOf(i).size() * 3;
            OtherMingTilesCnt += state.getGangOf(i).size() * 4;
        }
    }
    int allSecretCnt = 136 - OtherMingTilesCnt - 14;

    int thisMjCnt = 0;
    auto& MyMj = state.getInHand();
    for (auto& mj : MyMj) {
        // 自己手中的该麻将
        if (mj == aim)
            thisMjCnt++;
    }
    for (int i = 0; i < 4; ++i) {
        if (i != playerIdx) {
            // 他人鸣牌中的该麻将
            for (auto& mj : state.getPengOf(i)) {
                if (mj == aim)
                    thisMjCnt += 3;
            }
            for (auto& mj : state.getChiOf(i)) {
                if (mj == aim
                    || mj.getPrvMajang() == aim
                    || mj.getNxtMajang() == aim) {
                    thisMjCnt++;
                }
            }
            for (auto& mj : state.getGangOf(i)) {
                if (mj == aim)
                    thisMjCnt += 4;
            }
        }
    }

    double pRet = (4 - thisMjCnt) / (double)allSecretCnt;
    return pRet;
}

double SimilarityCalc(const StateContainer& state, 
    mahjong::useful_table_t useful_table
){
    // TO DO
    return 1.0;
}

//得分计算方法：对于每一张牌，若有手牌满足与之相隔,则+1;相邻,则+2;2张相同,则+2,3张相同,则+3,4张相同,则+4;
//未考虑缺色操作（若有某一花色的数量显然少于其他花色,则应直接打出此花色牌;正确性仍有待商榷,但在决策出牌时应考虑这一点)
double Calculator::HandScoreCalculator(
    int tileAmount[70]
) {
    double valueW = 0, valueB = 0, valueT = 0, valueF = 0, valueJ = 0;
    int sumW = 0, sumB = 0, sumT = 0, sumF = 0, sumJ = 0;
    double r = 0;
    for (int i = 11; i <= 19; i++) {
        if (tileAmount[i]) {
            double singleValue = 0;
            if (i >= 13) singleValue += tileAmount[i - 2] * 1;
            if (i >= 12) singleValue += tileAmount[i - 1] * 2;
            if (i <= 17) singleValue += tileAmount[i + 2] * 1;
            if (i <= 18) singleValue += tileAmount[i + 1] * 2;
            if (tileAmount[i] == 2) singleValue += 2;
            else if (tileAmount[i] == 3) singleValue += 3;
            else if (tileAmount[i] == 4) singleValue += 4;
            if(i==11||i==19) singleValue+=0.4;
            else if(i==12||i==18) singleValue+=0.8;
            else singleValue+=1.2;
            valueW += tileAmount[i] * singleValue;
            sumW += tileAmount[i];
        }
    }
    for (int i = 21; i <= 29; i++) {
        if (tileAmount[i]) {
            double singleValue = 0;
            if (i >= 23) singleValue += tileAmount[i - 2] * 1;
            if (i >= 22) singleValue += tileAmount[i - 1] * 2;
            if (i <= 27) singleValue += tileAmount[i + 2] * 1;
            if (i <= 28) singleValue += tileAmount[i + 1] * 2;
            if (tileAmount[i] == 2) singleValue += 2;
            else if (tileAmount[i] == 3) singleValue += 3;
            else if (tileAmount[i] == 4) singleValue += 4;
            if(i==21||i==29) singleValue+=0.4;
            else if(i==22||i==28) singleValue+=0.8;
            else singleValue+=1.2;
            valueB += tileAmount[i] * singleValue;
            sumB += tileAmount[i];
        }
    }
    for (int i = 31; i <= 39; i++) {
        if (tileAmount[i]) {
            double singleValue = 0;
            if (i >= 33) singleValue += tileAmount[i - 2] * 1;
            if (i >= 32) singleValue += tileAmount[i - 1] * 2;
            if (i <= 37) singleValue += tileAmount[i + 2] * 1;
            if (i <= 38) singleValue += tileAmount[i + 1] * 2;
            if (tileAmount[i] == 2) singleValue += 2;
            else if (tileAmount[i] == 3) singleValue += 3;
            else if (tileAmount[i] == 4) singleValue += 4;
            if(i==31||i==39) singleValue+=0.4;
            else if(i==32||i==38) singleValue+=0.8;
            else singleValue+=1.2;
            valueT += tileAmount[i] * singleValue;
            sumT += tileAmount[i];
        }
    }
    //箭牌和风牌可能要有特殊的地位*
    for (int i = 41; i <= 44; i++) {
        if (tileAmount[i]) {
            double singleValue = 0;
            // if(i>=43) singleValue+=tileAmount[i-2]*1;
            // if(i>=42) singleValue+=tileAmount[i-1]*2;
            // if(i<=42) singleValue+=tileAmount[i+2]*1;
            // if(i<=43) singleValue+=tileAmount[i+1]*2;
            if (tileAmount[i] == 2) singleValue += 2;
            else if (tileAmount[i] == 3) singleValue += 3;
            else if (tileAmount[i] == 4) singleValue += 4;
            valueF += tileAmount[i] * singleValue;
            sumF += tileAmount[i];
        }
    }
    for (int i = 51; i <= 53; i++) {
        if (tileAmount[i]) {
            double singleValue = 0;
            // if(i>=53) singleValue+=tileAmount[i-2]*1;
            // if(i>=52) singleValue+=tileAmount[i-1]*2;
            // if(i<=51) singleValue+=tileAmount[i+2]*1;
            // if(i<=52) singleValue+=tileAmount[i+1]*2;
            if (tileAmount[i] == 2) singleValue += 2;
            else if (tileAmount[i] == 3) singleValue += 3;
            else if (tileAmount[i] == 4) singleValue += 4;
            valueJ += tileAmount[i] * singleValue;
            sumJ += tileAmount[i];
        }
    }
    //手牌张数加成
    int sum = sumW + sumB + sumT + sumF + sumJ;
    valueW *= (1 + (double)sumW / sum);
    valueB *= (1 + (double)sumB / sum);
    valueT *= (1 + (double)sumT / sum);
    valueF *= (1 + (double)sumF / sum);
    valueJ *= (1 + (double)sumJ / sum);
    r = valueW + valueB + valueT + valueF + valueJ;
    return r;
}

