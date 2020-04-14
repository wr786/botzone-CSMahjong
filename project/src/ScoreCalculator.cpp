#include <ScoreCalculator.h>
#include <../utils/Mahjong-GB-CPP/MahjongGB/MahjongGB.h>
#include <../utils/Mahjong-GB-CPP/MahjongGB/MahjongGB.cpp>


//最终在决策时还应乘上出相应牌的风险系数(用于评估对手对该牌的需要程度)
double MahjongScoreCalculator(
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
double FanScoreCalculator(    
    vector<pair<string, Mahjong> > pack,//似乎可以直接用两位整数直接作为代表mahjong的参数，从而节省时间与空间
    vector<Mahjong> hand,//似乎可以直接用两位整数直接作为代表mahjong的参数，从而节省时间与空间
    int flowerCount,
    string winTile
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
    auto re=MahjongFanCalculator(p,h,winTile,1,0,0,0,0,0,0);//算番器中有许多我未理解的参数,先用0代入——wym
    int r;
    for(int i=0;i<re.size();i++) r+=re[i].first;//这里暂且暴力地以求和的方式作为番数得分的计算公式
    return r*c;
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
            StateContainer newstate=state;//摸到花牌后state应发生修改,应在StateContainer.h里提供相应的修改方法——wym
            newstate.getTileLeft[i]--;
            newstate.getTotalLeft--;
            r+=(double)state.getTileLeft(i)/state.getTotalLeft()*MahjongFanScore(pack,hand,flowerCount+1,newstate);
        }
    }
    return r;    
}

//这里采用了将手牌hand和明牌pack合并起来计算的方式,若有必要,可以分开计算并赋上权值
//参数c是用来使番数得分与手牌得分的数值相当
double MahjongHandScore(    
    vector<pair<string, Mahjong> > pack,
    vector<Mahjong> hand
){  
    double c=1;
    int TileAmount[70];
    memset(TileAmount,0,sizeof(TileAmount)); 
    for(int i=0;i<hand.size();i++){
        TileAmount[hand[i].getTileNum]++;
    }
    for(int i=0;i<pack.size();i++){
        if(pack[i].first=="GANG") TileAmount[pack[i].second.getTileNum]=4;
        else if(pack[i].first=="PENG") TileAmount[pack[i].second.getTileNum]=3;
        else{
            int TileN=pack[i].second.getTileNum;
            TileAmount[TileN-1]++;
            TileAmount[TileN]++;
            TileAmount[TileN+1]++;
        }
    }
    double result=HandScoreCalculator(TileAmount);
    return result*c;
}

//得分计算方法：对于每一张牌，若有手牌满足与之相隔,则+1;相邻,则+2;2张相同,则+2,3张相同,则+3,4张相同,则+4;
//未考虑缺色操作（若有某一花色的数量显然少于其他花色,则应直接打出此花色牌;正确性仍有待商榷,但在决策出牌时应考虑这一点)
double HandScoreCalculator(
    int TileAmount[70]
){  
    double valueW=0,valueB=0,valueT=0,valueF=0,valueJ=0; 
    int sumW=0,sumB=0,sumT=0,sumF=0,sumJ=0;
    double r=0;
    for(int i=11;i<=19;i++){
        if(TileAmount[i]){
            double singleValue=0;
            if(i>=13) singleValue+=TileAmount[i-2]*1;
            if(i>=12) singleValue+=TileAmount[i-1]*2;
            if(i<=17) singleValue+=TileAmount[i+2]*1;
            if(i<=18) singleValue+=TileAmount[i+1]*2;
            if(TileAmount[i]==2) singleValue+=2;
            else if(TileAmount[i]==3) singleValue+=3;
            else if(TileAmount[i]==4) singleValue+=4;
            valueW+=TileAmount[i]*singleValue;
            sumW+=TileAmount[i];
        }
    }
    for(int i=21;i<=29;i++){
        if(TileAmount[i]){
            double singleValue=0;
            if(i>=23) singleValue+=TileAmount[i-2]*1;
            if(i>=22) singleValue+=TileAmount[i-1]*2;
            if(i<=27) singleValue+=TileAmount[i+2]*1;
            if(i<=28) singleValue+=TileAmount[i+1]*2;
            if(TileAmount[i]==2) singleValue+=2;
            else if(TileAmount[i]==3) singleValue+=3;
            else if(TileAmount[i]==4) singleValue+=4;
            valueB+=TileAmount[i]*singleValue; 
            sumB+=TileAmount[i];           
        }     
    }
    for(int i=31;i<=39;i++){
        if(TileAmount[i]){
            double singleValue=0;
            if(i>=33) singleValue+=TileAmount[i-2]*1;
            if(i>=32) singleValue+=TileAmount[i-1]*2;
            if(i<=37) singleValue+=TileAmount[i+2]*1;
            if(i<=38) singleValue+=TileAmount[i+1]*2;
            if(TileAmount[i]==2) singleValue+=2;
            else if(TileAmount[i]==3) singleValue+=3;
            else if(TileAmount[i]==4) singleValue+=4;
            valueT+=TileAmount[i]*singleValue;
            sumT+=TileAmount[i];
        }      
    }
    //箭牌和风牌可能要有特殊的地位*
    for(int i=41;i<=44;i++){
        if(TileAmount[i]){
            double singleValue=0;
            if(i>=43) singleValue+=TileAmount[i-2]*1;
            if(i>=42) singleValue+=TileAmount[i-1]*2;
            if(i<=42) singleValue+=TileAmount[i+2]*1;
            if(i<=43) singleValue+=TileAmount[i+1]*2;
            if(TileAmount[i]==2) singleValue+=2;
            else if(TileAmount[i]==3) singleValue+=3;
            else if(TileAmount[i]==4) singleValue+=4;
            valueF+=TileAmount[i]*singleValue;
            sumF+=TileAmount[i];
        }            
    }
    for(int i=51;i<=53;i++){
        if(TileAmount[i]){
            double singleValue=0;
            if(i>=53) singleValue+=TileAmount[i-2]*1;
            if(i>=52) singleValue+=TileAmount[i-1]*2;
            if(i<=51) singleValue+=TileAmount[i+2]*1;
            if(i<=52) singleValue+=TileAmount[i+1]*2;
            if(TileAmount[i]==2) singleValue+=2;
            else if(TileAmount[i]==3) singleValue+=3;
            else if(TileAmount[i]==4) singleValue+=4;
            valueJ+=TileAmount[i]*singleValue;
            sumJ+=TileAmount[i];
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


