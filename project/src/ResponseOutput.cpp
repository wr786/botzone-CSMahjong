
#include "ResponseOutput.h"

#ifndef _PREPROCESS_ONLY
#include <iostream>
#endif

using namespace std;

void Output::Response(int request, StateContainer state){
    //接口不同,把valarray转化vector(优化后去掉此步骤)
    vector<Majang> hand;
    for(size_t i=0;i<state.getInHand().size();i++) hand.push_back(state.getInHand()[i]);
    vector<pair<string,Majang> > pack;
    for(size_t i=0;i<state.getChiOf(state.getCurPosition()).size();i++) pack.push_back(make_pair("CHI",state.getChiOf(state.getCurPosition())[i]));
    for(size_t i=0;i<state.getPengOf(state.getCurPosition()).size();i++) pack.push_back(make_pair("PENG",state.getPengOf(state.getCurPosition())[i]));
    for(size_t i=0;i<state.getGangOf(state.getCurPosition()).size();i++) pack.push_back(make_pair("GANG",state.getGangOf(state.getCurPosition())[i]));

    Calculator::calcPlayedRecently(state); // 应该是在这个时候就可以进行计算了

    //注意：若此回合为抽牌后,此时应比正常情况多出1张手牌
    int tileAmount[70];

    memset(tileAmount,0,sizeof(tileAmount));

    //! 这里显然可以优化，可能还有很多相似的地方，我就先不找了
//    for(size_t i=0;i<hand.size();i++){
    for(const auto item: hand)
        tileAmount[item.getTileInt()]++;

    bool isLast=state.isTileWallEmpty((state.getCurTurnPlayer()+1)%4);
    bool myEmpty=state.isTileWallEmpty((state.getCurPosition()));
    //如果是抽牌
    if(request==2){
        //此时手牌中最后一个元素即为抽到的牌
        if(judgeHu(pack,hand,hand.back(),state,true)){
            printf("HU");
        } 
        else if(!myEmpty&&!isLast&&judgeBuGang(state,pack,hand,hand.back())){
            printf("BUGANG %s",hand.back().getTileString().c_str());
        }
        else if(!myEmpty&&!isLast&&judgeGang(tileAmount,pack,hand,hand.back(),state,2)){
            printf("GANG %s",hand.back().getTileString().c_str());
        }
        else{
            Majang Tileplay=getBestPlay(state,pack,hand).second;            

            printf("PLAY %s",Tileplay.getTileString().c_str());
        }
    }

    //如果有别人打出的牌
    else if((request==32||request==33||request==34)&&state.getCurTurnPlayer() != state.getCurPosition()){            
        Majang lastTile=state.getLastPlayed();//被打出的牌
        //HU
        if(judgeHu(pack,hand,lastTile,state,false)){
            printf("HU");
        }
        //GANG 
        else if(!myEmpty){
            int pos=-2;
            Majang MajangPlay = getBestCP(state,pack,hand,lastTile,pos);
            if(MajangPlay.getTileInt()==1) printf("PASS");
            else{
                if(pos==-1) printf("GANG");
                else if(pos==0) printf("PENG %s",MajangPlay.getTileString().c_str());
                else if(pos==1) printf("CHI %s %s",lastTile.getNxtMajang().getTileString().c_str(),MajangPlay.getTileString().c_str());
                else if(pos==2) printf("CHI %s %s",lastTile.getTileString().c_str(),MajangPlay.getTileString().c_str());
                else printf("CHI %s %s",lastTile.getPrvMajang().getTileString().c_str(),MajangPlay.getTileString().c_str());                
            }
        }  
        /*   
        else if(!myEmpty&&!isLast&&judgeGang(tileAmount,pack,hand,lastTile,state,3)){
            printf("GANG");
        }
        //PENG
        else if(!isLast&&judgePeng(tileAmount,lastTile)){
            int pos=0;
            Majang MajangPlay = getBestCP(state,pack,hand,lastTile,pos);
            if(MajangPlay.getTileInt()==1){
                printf("PASS");
            }
            else{            
                printf("PENG %s",MajangPlay.getTileString().c_str());
            }
        }
        //chi
        else if(!isLast&&(state.getCurTurnPlayer()+1)%4==state.getCurPosition()&&chi){
            Majang MajangPlay=getBestCP(state,pack,hand,lastTile,chi); 
            if(MajangPlay.getTileInt()==1){
                printf("PASS");
            }           
            else{
                if(chi==1) printf("CHI %s %s",lastTile.getNxtMajang().getTileString().c_str(),MajangPlay.getTileString().c_str());
                else if(chi==2) printf("CHI %s %s",lastTile.getTileString().c_str(),MajangPlay.getTileString().c_str());
                else printf("CHI %s %s",lastTile.getPrvMajang().getTileString().c_str(),MajangPlay.getTileString().c_str());
            }
        }
        */
        else{
            printf("PASS");
        }
    }

    //抢杠和
    else if(request==36&&judgeHu(pack,hand,state.getLastPlayed(),state,false)){
        printf("HU");
    }

    //其余情况直接输出"pass"即可
    else{
        printf("PASS");
    }
}

bool Output::judgeHu(
    vector<pair<string,Majang> > pack,
    vector<Majang> hand,
    const Majang& winTile,
    StateContainer state,
    bool isZIMO 
){
    //cout << "[DEBUG] judgingHu\n";
    //再次转换接口(可优化)
    vector <pair<string,pair<string,int> > > p;
    for(unsigned int i=0;i<pack.size();++i){
        p.push_back(make_pair(pack[i].first,make_pair(pack[i].second.getTileString(),1)));
    }
    //cout << "[DEBUG] p Generate Successed.\n";
    vector <string> h;
    //如果是摸牌,要把手牌中已经加入的摸牌去掉
    if(isZIMO){
        for(unsigned int i=0;i<hand.size()-1;++i){
            h.push_back(hand[i].getTileString());
        }
    }
    else{
        for(unsigned int i=0;i<hand.size();++i){
            h.push_back(hand[i].getTileString());
        }        
    }
    //cout << "[DEBUG] h Generate Successed.\n";
    //算番器啥时候初始化呢？
    MahjongInit();
    //cout << "[DEBUG] Mahjong Init Successed.\n";
    try{
        bool isJUEZHANG=state.getTileLeft(winTile.getTileInt())==0;
        bool isGANG=(StateContainer::lastRequest==36);
        bool isLast=state.isTileWallEmpty((state.getCurTurnPlayer()+1)%4);

        auto re=MahjongFanCalculator(p,h,winTile.getTileString(),0,isZIMO,isJUEZHANG,isGANG,isLast,state.getCurPosition(),StateContainer::quan);
        int r=0; 
        //cout << "[DEBUG] judgeHu Successed!\n";
        for(unsigned int i=0;i<re.size();i++) {
        	r+=re[i].first;
        	// cout << "[DEBUG] " << re[i].second << " | " << re[i].first << endl;
        }
        return r >= 8;  // 这里简化了一下
    }catch(const string &error){
        return false;
    }
}

int Output::judgeChi(
    int TileAmount[70],
    const Majang& newTile
){
    if(newTile.getTileInt()/10<=3){
        if(newTile.getTileNum()<=7&&TileAmount[newTile.getTileInt()+1]&&TileAmount[newTile.getTileInt()+2]) return 1;
        else if(newTile.getTileNum()>=2&&newTile.getTileNum()<=8&&TileAmount[newTile.getTileInt()-1]&&TileAmount[newTile.getTileInt()+1]) return 2;
        else if(newTile.getTileNum()>=3&&TileAmount[newTile.getTileInt()-1]&&TileAmount[newTile.getTileInt()-2]) return 3;
        else return 0;
    }
    //风牌、箭牌不能吃，吗？
    else
        return 0;
}


bool Output::judgePeng(
    int tileAmout[70],
    const Majang& newTile
){
    if(tileAmout[newTile.getTileInt()]==2) return true;
    else return false;
}


bool Output::judgeGang(
    int tileAmout[70],
    vector<pair<string,Majang> > pack,
    vector<Majang> hand,
    const Majang& newTile,
    StateContainer state,
    int status
){
    //cout << "[DEBUG] judgingGang\n";    // 没位置加判断是否成功
    if(status==3){
        if(tileAmout[newTile.getTileInt()]==3){
            //先得到不杠时的评估值
            double maxResult1=Calculator::MajangScoreCalculator(pack,hand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);
            //杠后修改pack,hand;
            for(unsigned int i=0;i<hand.size();i++){
                if(hand[i].getTileInt()==newTile.getTileInt()){
                    hand.erase(hand.begin()+i);
                    i--;
            }
        }
            pack.push_back(make_pair("GANG",newTile));
            double maxResult2=Calculator::MajangScoreCalculator(pack,hand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);
            if(maxResult2-maxResult1>=1e-5) return true;
            else return false;
        }
        else return false;
    }
    else if(status==2){
        if(tileAmout[newTile.getTileInt()]==4){
            //如果不杠,则要打出一张牌,找到所有出牌中的评估最大值
            double maxResult1=getBestPlay(state,pack,hand).first;
            //杠后修改pack,hand;
            for(unsigned int i=0;i<hand.size();i++){
                if(hand[i].getTileInt()==newTile.getTileInt()){
                    hand.erase(hand.begin()+i);
                    i--;
            }
            pack.push_back(make_pair("GANG",newTile));
            double maxResult2=Calculator::MajangScoreCalculator(pack,hand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);
            if(maxResult2-maxResult1>=1e-5) return true;
            else return false;
            }            
        }
        else return false;        
    }
    return false;
}


bool Output::judgeBuGang(
    StateContainer state,
    vector<pair<string,Majang> > pack,
    vector<Majang> hand,
    const Majang& newTile
){
    //cout << " judgingBuGang\n";
    for(unsigned int i=0;i<pack.size();i++){ 
        if(pack[i].first=="PENG"&&pack[i].second.getTileInt()==newTile.getTileInt()){
            //如果不杠,则要打出一张牌,找到所有出牌中的评估最大值
            double maxResult1=getBestPlay(state,pack,hand).first;
            //如果杠,先把手牌中的这张牌去掉,再在pack中去掉peng,增加gang
            for(unsigned int k=0;k<hand.size();k++){
                if(hand[k].getTileInt()==newTile.getTileInt()){
                    hand.erase(hand.begin()+k);
                    break;
                }
            }
            pack.erase(pack.begin()+i);
            pack.push_back(make_pair("GANG",newTile));
            double maxResult2=Calculator::MajangScoreCalculator(pack,hand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);
            //cout << "[DEBUG] judgeBuGang Successed!\n";
            if(maxResult2-maxResult1>=1e-5) return true;
            else return false;
        }
    }
    return false;
}

int cmp(Majang a,Majang b){
    return a.getTileInt()<b.getTileInt();
}

//如果有特定的胡法，则往那条路走
const pair<double,Majang> Output::getBestPlay(
    StateContainer state,
    vector<pair<string,Majang> > pack,
    vector<Majang> hand
){  
    //clock_t start=clock();
    using namespace mahjong;   
    sort(hand.begin(),hand.end(),cmp);



//1.判断是不是特殊番型
    useful_table_t useful_table;
    tile_t form_flag;
    int shanten=14;
    double similarity=0;
    for(unsigned int i=0;i<hand.size();i++){
        vector<Majang> newHand(hand);
        newHand.erase(newHand.begin()+i);//从手牌中打出这一张牌
        auto p=ShantenJudge(pack, newHand, state, useful_table);
        if(shanten>p.second.first){
            shanten=p.second.first;
            similarity=p.second.second;
            form_flag=p.first;
        }
        else if(shanten==p.second.first&&similarity<p.second.second){
            similarity=p.second.second;
            form_flag=p.first;
        }
    }
    //如果存在一个特殊番型，且相似度应大于一定值(minLimit)
    int bestChoice=0;
    double maxResult=-1e5;


    if(form_flag!=0x01&&((similarity>=0.100&&shanten<=2)||(similarity>=0.075&&shanten<=1)||(shanten==0))){
        for(unsigned int i=0;i<hand.size();i++){
            vector<Majang> newHand(hand);
            newHand.erase(newHand.begin()+i);//从手牌中打出这一张牌
            double ans=Calculator::MajangScoreCalculator(pack,newHand,state.getFlowerTilesOf(state.getCurPosition()).size(),state,form_flag,shanten);
            if(ans>maxResult){
                maxResult=ans;
                bestChoice=i;
            }
            else if(ans==maxResult){
                //比如在听一个对子时,该怎么抉择留哪一张呢？
                if(state.getTileLeft(hand[i].getTileInt())<state.getTileLeft(hand[bestChoice].getTileInt())){
                    bestChoice=i;
                }
                }
        }
    }

    else{
//2.判断有没有我们想要的目标番型
        auto p=specialShantenJudge(pack,hand,state);                    
        set<string> notplay;
        if(p.first.formFlag==8){
            notplay.insert(p.first.tileForm.substr(0,2));
            notplay.insert(p.first.tileForm.substr(2,2));
            notplay.insert(p.first.tileForm.substr(4,2));
            notplay.insert(p.first.tileForm.substr(6,2));
        }
        //如果有，之后出牌就要从其他牌里选出最优解，shanten=0时或许要单独考虑.
        if(p.second.first==0||(p.second.first<=1&&p.second.second>=0.0250)||(p.second.first<=2&&p.second.second>=0.050)||(p.second.first<=3&&p.second.second>=0.075)){
            for(unsigned int i=0;i<hand.size();i++){
                vector<Majang> newHand(hand);
                newHand.erase(newHand.begin()+i);//从手牌中打出这一张牌
                if(p.first.formFlag==8){
                    if(notplay.count(to_string(hand[i].getTileInt()))==1) continue;
                }
                else{
                    if(specialShantenCalc(pack,newHand,p.first.tileForm)>p.second.first) continue; //shanten数变大说明此牌不能打
                }
                double ans=Calculator::MajangScoreCalculator(pack,newHand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);
                if(ans>maxResult){
                    maxResult=ans;
                    bestChoice=i;
                }
                else if(ans==maxResult){
                    //比如在听一个对子时,该怎么抉择留哪一张呢？
                    if(state.getTileLeft(hand[i].getTileInt())<state.getTileLeft(hand[bestChoice].getTileInt())){
                        bestChoice=i;
                    }
                }
            }        
        }        

//3.都没有，则贪心.
        else{
            for(unsigned int i=0;i<hand.size();i++){
                vector<Majang> newHand(hand);
                newHand.erase(newHand.begin()+i);//从手牌中打出这一张牌
                double ans=Calculator::MajangScoreCalculator(pack,newHand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);
                if(ans>maxResult){
                    maxResult=ans;
                    bestChoice=i;
                }
                else if(ans==maxResult){
                    //比如在听一个对子时,该怎么抉择留哪一张呢？
                    if(state.getTileLeft(hand[i].getTileInt())<state.getTileLeft(hand[bestChoice].getTileInt())){
                        bestChoice=i;
                    }
                }
            }
        }
    }
    //clock_t end=clock();
    //cout<<end-start<<endl;
    return make_pair(maxResult,hand[bestChoice]);
}


const Majang Output::getBestCP(
    StateContainer state,
    vector<pair<string,Majang> > pack,
    vector<Majang> hand,
    const Majang& newTile,
    int & pos
){

    //先得到不进行操作时最优得分
    using namespace mahjong;   
    sort(hand.begin(),hand.end(),cmp);
    int tileAmount[70];
    memset(tileAmount,0,sizeof(tileAmount));
    for(const auto item: hand)
        tileAmount[item.getTileInt()]++;

    useful_table_t useful_table;

    tile_t form_flag;
    int shanten=14;
    double similarity=0;
    auto p=ShantenJudge(pack, hand, state, useful_table);
    shanten=p.second.first;
    similarity=p.second.second;
    form_flag=p.first;

    //如果存在一个特殊番型，且相似度应大于一定值(minLimit)
    double maxResult1=-1e5;
    bool quanqiuren=pack.size()<3;
    //这里得好好想想，是不是就找定这组胡型不去吃碰杠了.
    if(quanqiuren&&form_flag!=0x01&&((similarity>=0.075&&shanten<=2)||(similarity>=0.050&&shanten<=1)||(shanten==0)))
        return Majang(1);
    else{
        auto p=specialShantenJudge(pack,hand,state);        
        //看看有没有目标番型，如果有，则评估标准就变成目标番型中是否有这对吃、碰
        //if(pack.size()>=1&&p.second.first!=0){
        //    string newPack="";
        //}
        maxResult1=Calculator::MajangScoreCalculator(pack,hand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);

        pair<double,Majang> r={0,Majang(1)};
        //进行操作,改变hand和pack；若考虑到博弈过程，同时要修改state,在这里未对state进行修改.

        //杠
        if(tileAmount[newTile.getTileInt()]==3){
            vector<Majang> newHand(hand);
            vector<pair<string,Majang> > newPack(pack);
            for(unsigned int i=0;i<newHand.size();i++){
                if(newHand[i].getTileInt()==newTile.getTileInt()){
                    newHand.erase(newHand.begin()+i);
                    i--;
            }
        }
            newPack.push_back(make_pair("GANG",newTile));
            pair<double,Majang> r1=getBestPlay(state,newPack,newHand);
            if(r.second.getTileInt()==1){
                r=r1;                
                pos=-1;  
            }        
            else{
                if(r.first<r1.first){r=r1;pos=1;}
            }        
        }

        //碰
        if(tileAmount[newTile.getTileInt()]==2){
            vector<Majang> newHand(hand);
            vector<pair<string,Majang> > newPack(pack);               
            for(unsigned int i=0;i<newHand.size();i++){
                if(newHand[i].getTileInt()==newTile.getTileInt()){
                    newHand.erase(newHand.begin()+i);
                    i--;
                }
            }
            newPack.push_back(make_pair("PENG",newTile));
            pair<double,Majang> r1=getBestPlay(state,newPack,newHand);
            if(r.second.getTileInt()==1){
                r=r1;                
                pos=0;  
            }        
            else{
                if(r.first<r1.first){r=r1;pos=1;}
            }
        }

        //吃
        if(newTile.getTileInt()/10<=3&&(state.getCurTurnPlayer()+1)%4==state.getCurPosition()){  
            if(newTile.getTileNum()<=7&&tileAmount[newTile.getTileInt()+1]&&tileAmount[newTile.getTileInt()+2]){
                vector<Majang> newHand(hand);
                vector<pair<string,Majang> > newPack(pack);
                int k1=1,k2=1;
                unsigned int i=0;
                while((k1||k2)&&i<newHand.size()){
                    if(k1&&newHand[i].getTileInt()==newTile.getTileInt()+1){
                        k1--;
                        newHand.erase(newHand.begin()+i);
                    }
                    else if(k2&&newHand[i].getTileInt()==newTile.getTileInt()+2){
                        k2--;
                        newHand.erase(newHand.begin()+i);
                    }
                    else{
                        i++;
                    }
                }
                newPack.push_back(make_pair("CHI",newTile.getNxtMajang()));
                pair<double,Majang> r1=getBestPlay(state,newPack,newHand);
                if(r.second.getTileInt()==1){
                    r=r1;                
                    pos=1;  
                }        
                else{
                    if(r.first<r1.first){r=r1;pos=1;}
                }
      
            }
            if(newTile.getTileNum()>=2&&newTile.getTileNum()<=8&&tileAmount[newTile.getTileInt()-1]&&tileAmount[newTile.getTileInt()+1]){
                vector<Majang> newHand(hand);
                vector<pair<string,Majang> > newPack(pack);
                int k1=1,k2=1;
                unsigned int i=0;
                while((k1||k2)&&i<newHand.size()){
                    if(k1&&newHand[i].getTileInt()==newTile.getTileInt()-1){
                        k1--;
                        newHand.erase(newHand.begin()+i);
                    }
                    else if(k2&&newHand[i].getTileInt()==newTile.getTileInt()+1){
                        k2--;
                        newHand.erase(newHand.begin()+i);
                    }
                    else{
                        i++;
                    }
                } 
                newPack.push_back(make_pair("CHI",newTile));
                pair<double,Majang> r1=getBestPlay(state,newPack,newHand);
                if(r.second.getTileInt()==1){
                    r=r1;
                    pos=2;
                }        
                else{
                    if(r.first<r1.first){r=r1;pos=2;}
                } 
            }
            if(newTile.getTileNum()>=3&&tileAmount[newTile.getTileInt()-1]&&tileAmount[newTile.getTileInt()-2]){                    
                vector<Majang> newHand(hand);
                vector<pair<string,Majang> > newPack(pack);
                int k1=1,k2=1;
                unsigned int i=0;
                while((k1||k2)&&i<hand.size()){
                    if(k1&&newHand[i].getTileInt()==newTile.getTileInt()-1){
                        k1--;
                        newHand.erase(newHand.begin()+i);
                    }
                    else if(k2&&newHand[i].getTileInt()==newTile.getTileInt()-2){
                        k2--;
                        newHand.erase(newHand.begin()+i);
                    }
                    else{
                        i++;
                    }
                }
                newPack.push_back(make_pair("CHI",newTile.getPrvMajang()));
                pair<double,Majang> r1=getBestPlay(state,newPack,newHand);
                if(r.second.getTileInt()==1){
                    r=r1;
                    pos=3;
                }        
                else{
                    if(r.first<r1.first) {r=r1;pos=3;}
                }  
            }            
        }
        if(p.first.formFlag==8&&pos==0) quanqiuren=false;
        //得到操作过后的最优解
        double maxResult2=r.first;
        if(!quanqiuren||maxResult2-maxResult1>=1e-5){
            return r.second;
        }
        else return Majang(1);
    }
}