
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
    
    //注意：若此回合为抽牌后,此时应比正常情况多出1张手牌
    int tileAmount[70];
    memset(tileAmount,0,sizeof(tileAmount));
    //! 这里显然可以优化，可能还有很多相似的地方，我就先不找了
//    for(size_t i=0;i<hand.size();i++){
    for(const auto& item: hand)
        tileAmount[item.getTileInt()]++;

    //如果是抽牌
    if(request==2){
        //此时手牌中最后一个元素即为抽到的牌
        if(judgeHu(pack,hand,hand.back(),state,true)){
            printf("HU");
        } 
        else if(judgeBuGang(state,pack,hand,hand.back())){
            printf("BUGANG %s",hand.back().getTileString().c_str());
        }
        else if(judgeGang(tileAmount,pack,hand,hand.back(),state,2)){
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
        int chi=judgeChi(tileAmount,lastTile);
        //HU
        if(judgeHu(pack,hand,lastTile,state,false)){
            printf("HU");
        }
        //GANG      
        else if(judgeGang(tileAmount,pack,hand,lastTile,state,3)){
            printf("GANG");
        }
        //PENG
        else if(judgePeng(tileAmount,lastTile)){
            Majang MajangPlay = getBestCP(state,pack,hand,lastTile,0);
            if(MajangPlay.getTileInt()==1){
                printf("PASS");
            }
            else{            
                printf("PENG %s",MajangPlay.getTileString().c_str());
            }
        }
        //chi
        else if((state.getCurTurnPlayer()+1)%4==state.getCurPosition()&&chi){
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
        bool isLast=(state.getTotalLeft()-state.getTileLeft(0)-state.getTileLeft(1)-state.getTileLeft(2)-state.getTileLeft(3)-state.getSecretGangCntOf(0)-state.getSecretGangCntOf(1)-state.getSecretGangCntOf(2)-state.getSecretGangCntOf(3))==0;
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


const pair<double,Majang> Output::getBestPlay(
    StateContainer state,
    vector<pair<string,Majang> > pack,
    vector<Majang> hand
){
    int bestChoice=0;
    double maxResult=-1e5;
    for(unsigned int i=0;i<hand.size();i++){
        vector<Majang> newHand(hand);
        newHand.erase(newHand.begin()+i);//从手牌中打出这一张牌
        double ans=Calculator::MajangScoreCalculator(pack,newHand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);
        if(ans>maxResult){
            maxResult=ans;
            bestChoice=i;
        }
    }
    return make_pair(maxResult,hand[bestChoice]);
}


const Majang Output::getBestCP(
    StateContainer state,
    vector<pair<string,Majang> > pack,
    vector<Majang> hand,
    const Majang& newTile,
    int pos
){
    //先得到不进行操作时最优得分
    double maxResult1=Calculator::MajangScoreCalculator(pack,hand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);
    //进行操作,改变hand和pack；若考虑到博弈过程，同时要修改state,在这里未对state进行修改.
    if(pos==0){
        for(unsigned int i=0;i<hand.size();i++){
            if(hand[i].getTileInt()==newTile.getTileInt()){
                hand.erase(hand.begin()+i);
                i--;
            }
        }
            pack.push_back(make_pair("PENG",newTile));
    }
    else{            
        //把吃掉的牌从手牌hand中去掉,再把顺子加到pack中
        if(pos==1){
            int k1=1,k2=1;
            unsigned int i=0;
            while((k1||k2)&&i<hand.size()){
                if(k1&&hand[i].getTileInt()==newTile.getTileInt()+1){
                    k1--;
                    hand.erase(hand.begin()+i);
                }
                else if(k2&&hand[i].getTileInt()==newTile.getTileInt()+2){
                    k2--;
                    hand.erase(hand.begin()+i);
                }
                else{
                    i++;
                }
            }
            pack.push_back(make_pair("CHI",newTile.getNxtMajang()));
        }
        else if(pos==2){
            int k1=1,k2=1;
            unsigned int i=0;
            while((k1||k2)&&i<hand.size()){
                if(k1&&hand[i].getTileInt()==newTile.getTileInt()-1){
                    k1--;
                    hand.erase(hand.begin()+i);
                }
                else if(k2&&hand[i].getTileInt()==newTile.getTileInt()+1){
                    k2--;
                    hand.erase(hand.begin()+i);
                }
                else{
                    i++;
                }
            } 
            pack.push_back(make_pair("CHI",newTile));           
        }
        else{
            int k1=1,k2=1;
            unsigned int i=0;
            while((k1||k2)&&i<hand.size()){
                if(k1&&hand[i].getTileInt()==newTile.getTileInt()-1){
                    k1--;
                    hand.erase(hand.begin()+i);
                }
                else if(k2&&hand[i].getTileInt()==newTile.getTileInt()-2){
                    k2--;
                    hand.erase(hand.begin()+i);
                }
                else{
                    i++;
                }
            }
            pack.push_back(make_pair("CHI",newTile.getPrvMajang()));            
        }
    }
    //得到操作过后的最优解
    pair<double,Majang> r=getBestPlay(state,pack,hand);
    double maxResult2=r.first;
    if(maxResult2-maxResult1>=1e-5){
        return r.second;
    }
    else return Majang(1);
}