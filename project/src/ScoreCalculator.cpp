#include "ScoreCalculator.h"

//最终在决策时还应乘上出相应牌的风险系数(用于评估对手对该牌的需要程度)
double Calculator::MahjongScoreCalculator(
    vector<pair<string, Mahjong> > pack,
    vector<Mahjong> hand,
    int flowerCount,
    StateContainer state
){
    //参数实际应按游戏回合分段，这里先随便写了一个
    int k1=0.5;    // 手牌得分所占权重
    int k2=0.3;    // 自摸番数得分所占权重
    int k3=0.2;    // 点炮番数得分所占权重
    double r1=MahjongHandScore(pack,hand);
    double r2=MahjongFanScore(pack,hand,flowerCount,state);
    //计算点炮番数得分时，出牌的概率应考虑到博弈，还没有想清楚，先用自摸胡的算法计算点炮胡
    return r1*k1+r2*(k2+k3);
}

//参数c是用来使番数得分与手牌得分的数值相当
double Calculator::FanScoreCalculator(    
    vector<pair<string, Mahjong> > pack,//似乎可以直接用两位整数直接作为代表mahjong的参数，从而节省时间与空间
    vector<Mahjong> hand,//似乎可以直接用两位整数直接作为代表mahjong的参数，从而节省时间与空间
    int flowerCount,
    Mahjong winTile
){  
    double c=1;
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
    auto re=MahjongFanCalculator(p,h,winTile.getTileString(),1,flowerCount,1,0,0,0,0);//算番器中有许多我未理解的参数,先用0代入——wym
    int r=0;
    for(int i=0;i<re.size();i++) r+=re[i].first;//这里暂且暴力地以求和的方式作为番数得分的计算公式
    return r*c;
}

double Calculator::MahjongFanScore(    
    vector<pair<string, Mahjong> > pack,
    vector<Mahjong> hand,
    int flowerCount,
    StateContainer state
){  
    double r=0;
    for(int i=11;i<=19;i++){
        if(state.getTileLeft(i)){
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Mahjong(i));
        }
    }
    for(int i=21;i<=29;i++){
        if(state.getTileLeft(i)){
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Mahjong(i));
        }        
    }
    for(int i=31;i<=39;i++){
        if(state.getTileLeft(i)){
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Mahjong(i));
        }        
    }
    for(int i=41;i<=44;i++){
        if(state.getTileLeft(i)){
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Mahjong(i));
        }        
    }
    for(int i=51;i<=53;i++){
        if(state.getTileLeft(i)){
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Mahjong(i));
        }        
    }
    for(int i=61;i<=68;i++){
        if(state.getTileLeft(i)){
            StateContainer newstate=state;//摸到花牌后state应发生修改,应在StateContainer.h里提供相应的修改方法——wym
//            newstate.getTileLeft(i)--;
//            newstate.getTotalLeft()--;
            newstate.decTileLeft(i);
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*MahjongFanScore(pack,hand,flowerCount+1,newstate);
        }
    }
    return r;    
}

//这里采用了将手牌hand和明牌pack合并起来计算的方式,若有必要,可以分开计算并赋上权值
//参数c是用来使番数得分与手牌得分的数值相当
double Calculator::MahjongHandScore(    
    vector<pair<string, Mahjong> > pack,
    vector<Mahjong> hand
){  
    double c=1;
    int tileAmount[70];
    memset(tileAmount,0,sizeof(tileAmount)); 
    for(int i=0;i<hand.size();i++){
        tileAmount[hand[i].getTileInt()]++;
    }
    for(int i=0;i<pack.size();i++){
        if(pack[i].first=="GANG") tileAmount[pack[i].second.getTileInt()]=4;
        else if(pack[i].first=="PENG") tileAmount[pack[i].second.getTileInt()]=3;
        else{
            int TileN=pack[i].second.getTileInt();
            tileAmount[TileN-1]++;
            tileAmount[TileN]++;
            tileAmount[TileN+1]++;
        }
    }
    double result=HandScoreCalculator(tileAmount);
    return result*c;
}

//得分计算方法：对于每一张牌，若有手牌满足与之相隔,则+1;相邻,则+2;2张相同,则+2,3张相同,则+3,4张相同,则+4;
//未考虑缺色操作（若有某一花色的数量显然少于其他花色,则应直接打出此花色牌;正确性仍有待商榷,但在决策出牌时应考虑这一点)
double Calculator::HandScoreCalculator(
    int tileAmount[70]
){  
    double valueW=0,valueB=0,valueT=0,valueF=0,valueJ=0; 
    int sumW=0,sumB=0,sumT=0,sumF=0,sumJ=0;
    double r=0;
    for(int i=11;i<=19;i++){
        if(tileAmount[i]){
            double singleValue=0;
            if(i>=13) singleValue+=tileAmount[i-2]*1;
            if(i>=12) singleValue+=tileAmount[i-1]*2;
            if(i<=17) singleValue+=tileAmount[i+2]*1;
            if(i<=18) singleValue+=tileAmount[i+1]*2;
            if(tileAmount[i]==2) singleValue+=2;
            else if(tileAmount[i]==3) singleValue+=3;
            else if(tileAmount[i]==4) singleValue+=4;
            valueW+=tileAmount[i]*singleValue;
            sumW+=tileAmount[i];
        }
    }
    for(int i=21;i<=29;i++){
        if(tileAmount[i]){
            double singleValue=0;
            if(i>=23) singleValue+=tileAmount[i-2]*1;
            if(i>=22) singleValue+=tileAmount[i-1]*2;
            if(i<=27) singleValue+=tileAmount[i+2]*1;
            if(i<=28) singleValue+=tileAmount[i+1]*2;
            if(tileAmount[i]==2) singleValue+=2;
            else if(tileAmount[i]==3) singleValue+=3;
            else if(tileAmount[i]==4) singleValue+=4;
            valueB+=tileAmount[i]*singleValue; 
            sumB+=tileAmount[i];           
        }     
    }
    for(int i=31;i<=39;i++){
        if(tileAmount[i]){
            double singleValue=0;
            if(i>=33) singleValue+=tileAmount[i-2]*1;
            if(i>=32) singleValue+=tileAmount[i-1]*2;
            if(i<=37) singleValue+=tileAmount[i+2]*1;
            if(i<=38) singleValue+=tileAmount[i+1]*2;
            if(tileAmount[i]==2) singleValue+=2;
            else if(tileAmount[i]==3) singleValue+=3;
            else if(tileAmount[i]==4) singleValue+=4;
            valueT+=tileAmount[i]*singleValue;
            sumT+=tileAmount[i];
        }      
    }
    //箭牌和风牌可能要有特殊的地位*
    for(int i=41;i<=44;i++){
        if(tileAmount[i]){
            double singleValue=0;
            if(i>=43) singleValue+=tileAmount[i-2]*1;
            if(i>=42) singleValue+=tileAmount[i-1]*2;
            if(i<=42) singleValue+=tileAmount[i+2]*1;
            if(i<=43) singleValue+=tileAmount[i+1]*2;
            if(tileAmount[i]==2) singleValue+=2;
            else if(tileAmount[i]==3) singleValue+=3;
            else if(tileAmount[i]==4) singleValue+=4;
            valueF+=tileAmount[i]*singleValue;
            sumF+=tileAmount[i];
        }            
    }
    for(int i=51;i<=53;i++){
        if(tileAmount[i]){
            double singleValue=0;
            if(i>=53) singleValue+=tileAmount[i-2]*1;
            if(i>=52) singleValue+=tileAmount[i-1]*2;
            if(i<=51) singleValue+=tileAmount[i+2]*1;
            if(i<=52) singleValue+=tileAmount[i+1]*2;
            if(tileAmount[i]==2) singleValue+=2;
            else if(tileAmount[i]==3) singleValue+=3;
            else if(tileAmount[i]==4) singleValue+=4;
            valueJ+=tileAmount[i]*singleValue;
            sumJ+=tileAmount[i];
        }                        
    }
    //手牌张数加成
    int sum=sumW+sumB+sumT+sumF+sumJ;
    valueW*=(1+(double)sumW/sum);
    valueB*=(1+(double)sumB/sum);
    valueT*=(1+(double)sumT/sum);  
    valueF*=(1+(double)sumF/sum);
    valueJ*=(1+(double)sumJ/sum);
    return valueW+valueB+valueT+valueF+valueJ;          
}

