#include "ScoreCalculator.h"
#ifndef _PREPROCESS_ONLY
#include <iostream>
#include <ctime>
#endif
using namespace std;

unordered_map<int, int> Calculator::cntPlayedRecently;

//最终在决策时还应乘上出相应牌的风险系数(用于评估对手对该牌的需要程度)
double Calculator::MajangScoreCalculator(
    vector<pair<string, Majang> > pack,
    vector<Majang> hand,
    int flowerCount,
    StateContainer state,
    mahjong::tile_t form_flag=0x01,
    int shanten=20
) {    
    double k1,k2,k3;
    //参数实际应按游戏回合分段，这里先随便写了一个
    if(state.getTileWallLeftOf(state.getCurPosition())<=15){
        k1=0.2;    // 手牌得分所占权重
        k2=0.5;    // 番数得分所占权重   
        k3=0.3;    // 复合上听数所占权重
    }
    else if(state.getTileWallLeftOf(state.getCurPosition())<=18){
        k1=0.3;    // 手牌得分所占权重
        k2=0.3;    // 番数得分所占权重   
        k3=0.4;    // 复合上听数所占权重          
    }
    else{
        //前几手抓牌shanten不太准
        k1=0.5;    // 手牌得分所占权重
        k2=0.3;    // 番数得分所占权重   
        k3=0.2;    // 复合上听数所占权重        
    }

    int num=0;
    for(int i:{0,1,2,3}){
        if(i!=state.getCurPosition()&&state.getTileWallLeftOf(i)<=8) num++;
    }
    bool dianpao=num>=2;
    //freopen("D://out.txt","w",stdout);
    double r1 = MajangHandScore(pack, hand,dianpao,state);
    double r2 = MajangFanScore(pack, hand, flowerCount, state);

    double resultShanten = 0;   // 在shanten写好之后，将结果存入resultShanten

    int param1, param2;
    double param3;
    mahjong::useful_table_t useful_table;
    auto p = ShantenCalc(pack, hand, useful_table,form_flag);
    param1 = p.first;                               // shanten数
    param2 = p.second;                              // effective tiles
    param3 = SimilarityCalc(state, useful_table);   // similarity

    if(param1>shanten) return -1e5; //shanten数变大则必不打这张牌
    
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
    double k4=0.5;

    if(param3 > 0) resultShanten = -(param1 - 1 - log(param3) * k4);	// 因为初始化是0，所以不用写else
    // param3是在[0,1)的，这意味着param1-1相当于param3变为e^2倍    
    double k5=20;
    if(form_flag!=0x01) k5=30;  //这时候要加大shanten的占比
    double r3=k5*resultShanten;


    //printf("r1:%f r2:%f r3:%f\n",r1,r2,r3);

    //计算点炮番数得分时，出牌的概率应考虑到博弈，还没有想清楚，先用自摸胡的算法计算点炮胡
    return r1 * k1 + r2 * k2  + r3 * k3;
}

//参数c是用来使番数得分与手牌得分的数值相当
double Calculator::FanScoreCalculator(    
    vector<pair<string, Majang> > pack,//似乎可以直接用两位整数直接作为代表Majang的参数，从而节省时间与空间
    vector<Majang> hand,//似乎可以直接用两位整数直接作为代表Majang的参数，从而节省时间与空间
    int flowerCount,
    Majang winTile,
    StateContainer state    
){  
    double k6=40;    //将Majang类调整为适用于算番器的接口    
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
        return r*k6*3;
    }
    catch(const string &error){
        int tileAmount[70];
        memset(tileAmount,0,sizeof(tileAmount));
        vector<int> handAndPack;
        int quanfeng=StateContainer::quan;
        int menfeng=state.getCurPosition();
        for(auto i:pack){
            if(i.first=="CHI"){
                tileAmount[i.second.getTileInt()]++;
                handAndPack.push_back(i.second.getTileInt());
                tileAmount[i.second.getTileInt()+1]++;
                handAndPack.push_back(i.second.getTileInt()+1);
                tileAmount[i.second.getTileInt()-1]++;
                handAndPack.push_back(i.second.getTileInt()-1);
            }
            else if(i.first=="PENG"){
                tileAmount[i.second.getTileInt()]+=3;
                handAndPack.push_back(i.second.getTileInt());
                handAndPack.push_back(i.second.getTileInt());
                handAndPack.push_back(i.second.getTileInt());
            }
            else {
                tileAmount[i.second.getTileInt()]+=4;
                handAndPack.push_back(i.second.getTileInt());
                handAndPack.push_back(i.second.getTileInt());
                handAndPack.push_back(i.second.getTileInt());
                handAndPack.push_back(i.second.getTileInt());
            }
        }
        for(auto i:hand){
            handAndPack.push_back(i.getTileInt());
            tileAmount[i.getTileInt()]++;
        }
        tileAmount[winTile.getTileInt()]++;
        handAndPack.push_back(winTile.getTileInt());
        int r=fanCalculator(tileAmount,handAndPack,quanfeng,menfeng);
        if(state.getTileWallLeftOf(state.getCurPosition())<=16){
            return 0;
        }
        else{
            return r*k6;
        }
    }
}

double Calculator::MajangFanScore(    
    vector<pair<string, Majang> > pack,
    vector<Majang> hand,
    int flowerCount,
    StateContainer state
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
    return r;    
}

//这里采用了将手牌hand和明牌pack合并起来计算的方式,若有必要,可以分开计算并赋上权值
//参数c是用来使番数得分与手牌得分的数值相当
double Calculator::MajangHandScore(
    vector<pair<string, Majang> > pack,
    vector<Majang> hand,
    bool dianpao,
    const StateContainer & state
) { 
    double c = 1;
    double result = 0;
    int tileAmount[70];
    memset(tileAmount, 0, sizeof(tileAmount));
    for (unsigned int i = 0; i < hand.size(); i++) {
        tileAmount[hand[i].getTileInt()]++;
    }
    //各个数值都翻了倍，原因是吃碰杠后handscore会明显减少，然而这是不科学的
    for (unsigned int i = 0; i < pack.size(); i++) {
        if (pack[i].first == "GANG") result += 32;
        else if (pack[i].first == "PENG") result += 18;
        else {
            result += 20;
        }
    }
    result += HandScoreCalculator(tileAmount,dianpao,state);
    return result * c;
}




//得分计算方法：对于每一张牌，若有手牌满足与之相隔,则+1;相邻,则+2;2张相同,则+2,3张相同,则+3,4张相同,则+4;
//未考虑缺色操作（若有某一花色的数量显然少于其他花色,则应直接打出此花色牌;正确性仍有待商榷,但在决策出牌时应考虑这一点)
double Calculator::HandScoreCalculator(
    int tileAmount[70],
    bool dianpao,
    const StateContainer & state
) {
    double kw=1;
    double valueW = 0, valueB = 0, valueT = 0, valueF = 0, valueJ = 0;
    int sumW = 0, sumB = 0, sumT = 0, sumF = 0, sumJ = 0;
    double r = 0;
    for (int i = 11; i <= 19; i++) {
        if (tileAmount[i]) {
            double singleValue = 0;
            if (i >= 13) singleValue += tileAmount[i - 2] * 1;
            if (i >= 12) singleValue += tileAmount[i - 1] * 3;
            if (i <= 17) singleValue += tileAmount[i + 2] * 1;
            if (i <= 18) singleValue += tileAmount[i + 1] * 3;
            if (i>=12&&i<=18&&tileAmount[i-1]&&tileAmount[i+1]) singleValue+=min(tileAmount[i-1],min(tileAmount[i],tileAmount[i+1]))*3;
            if (i<=17&&tileAmount[i+1]&&tileAmount[i+2]) singleValue+=min(tileAmount[i+2],min(tileAmount[i],tileAmount[i+1]))*3;
            if (i>=13&&tileAmount[i-1]&&tileAmount[i-2]) singleValue+=min(tileAmount[i-2],min(tileAmount[i],tileAmount[i-1]))*3;
            if (tileAmount[i] == 2) singleValue += 2;
            else if (tileAmount[i] == 3) singleValue += 3;
            else if (tileAmount[i] == 4) singleValue += 4;
            //if(i==11||i==19) singleValue+=0.4;
            //else if(i==12||i==18) singleValue+=0.8;
            //else singleValue+=1.2;

            if(dianpao&&cntPlayedRecently[i]) {
                // 防止点炮，给被打出来过的牌减权，相当于给没被打出来的牌加权
                // 因为一般来说，被打出来的牌，就是没有被人听的牌（不然人早胡了
                singleValue -= kw*cntPlayedRecently[i];
            }

            valueW += tileAmount[i] * singleValue;
            sumW += tileAmount[i];
        }
    }
    for (int i = 21; i <= 29; i++) {
        if (tileAmount[i]) {
            double singleValue = 0;
            if (i >= 23) singleValue += tileAmount[i - 2] * 1;
            if (i >= 22) singleValue += tileAmount[i - 1] * 3;
            if (i <= 27) singleValue += tileAmount[i + 2] * 1;
            if (i <= 28) singleValue += tileAmount[i + 1] * 3;
            if (i>=22&&i<=28&&tileAmount[i-1]&&tileAmount[i+1]) singleValue+=min(tileAmount[i-1],min(tileAmount[i],tileAmount[i+1]))*3;
            if (i<=27&&tileAmount[i+1]&&tileAmount[i+2]) singleValue+=min(tileAmount[i+2],min(tileAmount[i],tileAmount[i+1]))*3;
            if (i>=23&&tileAmount[i-1]&&tileAmount[i-2]) singleValue+=min(tileAmount[i-2],min(tileAmount[i],tileAmount[i-1]))*3;
            if (tileAmount[i] == 2) singleValue += 2;
            else if (tileAmount[i] == 3) singleValue += 3;
            else if (tileAmount[i] == 4) singleValue += 4;
            //if(i==21||i==29) singleValue+=0.4;
            //else if(i==22||i==28) singleValue+=0.8;
            //else singleValue+=1.2;

            if(dianpao&&cntPlayedRecently[i]) {
                // 防止点炮，给被打出来过的牌减权，相当于给没被打出来的牌加权
                // 因为一般来说，被打出来的牌，就是没有被人听的牌（不然人早胡了
                singleValue -= kw*cntPlayedRecently[i];
            }

            valueB += tileAmount[i] * singleValue;
            sumB += tileAmount[i];
        }
    }
    for (int i = 31; i <= 39; i++) {
        if (tileAmount[i]) {
            double singleValue = 0;
            if (i >= 33) singleValue += tileAmount[i - 2] * 1;
            if (i >= 32) singleValue += tileAmount[i - 1] * 3;
            if (i <= 37) singleValue += tileAmount[i + 2] * 1;
            if (i <= 38) singleValue += tileAmount[i + 1] * 3;
            if (i>=32&&i<=38&&tileAmount[i-1]&&tileAmount[i+1]) singleValue+=min(tileAmount[i-1],min(tileAmount[i],tileAmount[i+1]))*3;
            if (i<=37&&tileAmount[i+1]&&tileAmount[i+2]) singleValue+=min(tileAmount[i+2],min(tileAmount[i],tileAmount[i+1]))*3;
            if (i>=33&&tileAmount[i-1]&&tileAmount[i-2]) singleValue+=min(tileAmount[i-2],min(tileAmount[i],tileAmount[i-1]))*3;
            if (tileAmount[i] == 2) singleValue += 2;
            else if (tileAmount[i] == 3) singleValue += 3;
            else if (tileAmount[i] == 4) singleValue += 4;
            //if(i==31||i==39) singleValue+=0.4;
            //else if(i==32||i==38) singleValue+=0.8;
            //else singleValue+=1.2;

            if(dianpao&&cntPlayedRecently[i]) {
                // 防止点炮，给被打出来过的牌减权，相当于给没被打出来的牌加权
                // 因为一般来说，被打出来的牌，就是没有被人听的牌（不然人早胡了
                singleValue -= kw*cntPlayedRecently[i];
            }

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
            if((i-1)%4==state.getCurPosition()) singleValue+=1.7;
            if((i-1)%4==StateContainer::quan) singleValue+=1.7;
            if(dianpao&&cntPlayedRecently[i]) {
                // 防止点炮，给被打出来过的牌减权，相当于给没被打出来的牌加权
                // 因为一般来说，被打出来的牌，就是没有被人听的牌（不然人早胡了
                singleValue -= kw*cntPlayedRecently[i];
            }

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

            if(dianpao&&cntPlayedRecently[i]) {
                // 防止点炮，给被打出来过的牌减权，相当于给没被打出来的牌加权
                // 因为一般来说，被打出来的牌，就是没有被人听的牌（不然人早胡了
                singleValue -= kw*cntPlayedRecently[i];
            }

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
int Calculator::fanCalculator(
    int tileAmount[70],
    vector<int> handAndPack,
    int quanfeng,
    int menfeng
){  
    int fan=0;
    //考虑的番型
    bool yaojiuke=true;
    bool laoshaofu=true;
    bool lianliu=true;
    bool xixiangfeng=true;
    bool yibangao=true;
    bool shuangtongke=true;
    bool jianke=true;
    bool quanfengke=true;
    bool menfengke=true;
    //记录以multiset中元素为中间元素的顺子和刻字
    sort(handAndPack.begin(),handAndPack.end());   
    multiset<int> shunzi[4];
    multiset<int> totalshunzi;
    set<int> kezi;
    //在这里shunzi和kezi的计算是有重复的
    for(auto item:handAndPack){
        if(item/10<=3){
            if(item%10>=2&&item%10<=8){
                if(tileAmount[item-1]&&tileAmount[item+1]){
                    totalshunzi.insert(item);
                    if(yibangao&&totalshunzi.count(item)==2){
                        fan++;
                        yibangao=false;
                    }
                    shunzi[item/10].insert(item);
                }
            }
        }
        if(tileAmount[item]==3){
            if(kezi.count(item)==0){
                kezi.insert(item);
                if(yaojiuke&&item%10==1||item%10==9){
                    fan++;
                    yaojiuke=false;
                }
                if(jianke&&item/10>=5&&item/10<=6){
                    fan++;
                    jianke=false;
                }
                if(quanfengke&&item==40+quanfeng+1){
                    fan++;
                    quanfengke=false;
                }
                if(menfengke&&item==40+menfeng+1){
                    fan++;
                    menfengke=false;
                }
            }
        }
    }
    
    for(int i=1;i<=3;i++){
        if(laoshaofu&&shunzi[i].count(2)&&shunzi[i].count(8)){
            laoshaofu=false;
            fan++;
        }
        if(lianliu){
            for(int item:shunzi[i]){
                if(shunzi[i].count(item+3)){
                    fan++;
                    lianliu=false;
                    break;
                }
            }
        }
    }

    for(int item:totalshunzi){
        if(xixiangfeng){
            int i1,i2;
            if(item<=20){i1=item+10;i2=item+20;}
            else if(item<=30){i1=item+10;i2=item-10;}
            else {i1=item-10;i2=item-20;}
            if(totalshunzi.count(i1)||totalshunzi.count(i2)){
                fan++;
                xixiangfeng=false;
                break;
            }
        }
    }

    for(int item:kezi){
        if(shuangtongke){
            int i1,i2;
            if(item<=20){i1=item+10;i2=item+20;}
            else if(item<=30){i1=item+10;i2=item-10;}
            else {i1=item-10;i2=item-20;}
            if(kezi.count(i1)||kezi.count(i2)){
                fan++;
                shuangtongke=false;
                break;
            }
        }
    }
    return fan;
}

void Calculator::calcPlayedRecently(const StateContainer &state) {
    for(int i=0; i<4; i++) {
        const vector<Majang>& tilePlayed = state.getTilePlayedOf(i);
        int len = tilePlayed.size();
        int depth = min(5, len);
        for(int idx=len-depth; idx<len; idx++) {
            cntPlayedRecently[tilePlayed[idx].getTileInt()] += 1;
        }
    }
}

