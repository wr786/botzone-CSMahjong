
#ifdef _BOTZONE_ONLINE
#include "MahjongGB/MahjongGB.h"
#endif

#include "Majang.h"
#include "Majang.cpp"
#include "StateContainer.h"
#include "StateContainer.cpp"
#include "RequestReader.h"
#include "RequestReader.cpp"
#include "ScoreCalculator.h"
#include "ScoreCalculator.cpp"
#include "ResponseOutput.h"
#include "ResponseOutput.cpp"
#include <iostream>

int StateContainer::quan=0;
int main() {
    int turnID; Reader::readIn(turnID);
    string tmp;
    StateContainer basicState;
    for(int i=1; i<turnID; i++) {
        Reader::readRequest(basicState);
        getline(cin, tmp);   // 过滤掉我们发出的无用的信息
//        vector<Majang> & tmpM=basicState.getInHand();
//        for(auto & mahjong:tmpM){
//            cout<<mahjong.getTileString()<<" ";
//        }
//        cout<<endl;
    }
    int t=Reader::readRequest(basicState);
//        vector<Majang> & tmpM=basicState.getInHand();
//        for(auto & mahjong:tmpM){
//            cout<<mahjong.getTileString()<<" ";
//        }
//        cout<<endl;    
    Output::Response(t, basicState);
    return 0;
}