#include <ScoreCalculator.h>
#include <../utils/Mahjong-GB-CPP/MahjongGB/MahjongGB.h>
#include <../utils/Mahjong-GB-CPP/MahjongGB/MahjongGB.cpp>


double MahjongScoreCalculator(
    vector<pair<string, Mahjong> > pack,
    vector<Mahjong> hand,
    int flowerCount,
    StateContainer state
){
    double r1=MahjongHandScore(pack,hand);
    double r2=MahjongFanScore(pack,hand,flowerCount,state);
    //计算点炮番数得分时，出牌的概率应考虑到博弈，还没有想清楚，先用自摸胡的算法计算点炮胡
    return r1*k1+r2*(k2+k3);
}

double FanScoreCalculator(    
    vector<pair<string, Mahjong> > pack,//似乎可以直接用两位整数直接作为代表mahjong的参数，从而节省时间与空间
    vector<Mahjong> hand,//似乎可以直接用两位整数直接作为代表mahjong的参数，从而节省时间与空间
    int flowerCount,
    string winTile
){  

    //将Mahjong类调整为适用于算番器的接口
    vector <pair<string,pair<string,int> > > p;
    for(int i=0;i<pack.size();++i){
        p.push_back(make_pair(pack[i].first,make_pair(pack[i].second.getTileString(),1)));
    }
    vector <string> h;
    for(int i=0;i<hand.size();++i){
        h.push_back(hand[i].getTileString());
    }
    //算番器啥时候初始化呢？
    MahjongInit();
    auto re=MahjongFanCalculator(p,h,winTile,1,0,0,0,0,0,0);//算番器中有许多我未理解的参数,先用0代入——wym
    int r;
    for(int i=0;i<re.size();i++) r+=re[i].first;//这里暂且暴力地以求和的方式作为番数得分的计算公式
    return r*k4;
}

double MahjongFanScore(    
    vector<pair<string, Mahjong> > pack,
    vector<Mahjong> hand,
    int flowerCount,
    string winTile,
    StateContainer state
){  
    double r=0;
    for(int i=11;i<=19;i++){
        if(state.getTileLeft(i)){
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Mahjong(i).getTileString());
        }
    }
    for(int i=21;i<=29;i++){
        if(state.getTileLeft(i)){
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Mahjong(i).getTileString());
        }        
    }
    for(int i=31;i<=39;i++){
        if(state.getTileLeft(i)){
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Mahjong(i).getTileString());
        }        
    }
    for(int i=41;i<=44;i++){
        if(state.getTileLeft(i)){
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Mahjong(i).getTileString());
        }        
    }
    for(int i=51;i<=53;i++){
        if(state.getTileLeft(i)){
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Mahjong(i).getTileString());
        }        
    }
    for(int i=61;i<=68;i++){
        if(state.getTileLeft(i)){
            StateContainer newstate;//摸到花牌后state应发生修改,应在StateContainer.h里提供相应的修改方法——wym

            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*MahjongFanScore(pack,hand,flowerCount+1,newstate);
        }
    }
    return r;    
}

//比如：有一个刻子,+0.4;有一个顺子,+0.4;有一个对子,+0.2；具体的值要结合实战和番数得分.
double MahjongHandScore(
    vector<pair<string, Mahjong> > pack,
    vector<Mahjong> hand
){

}