
#ifdef _MSC_VER
#pragma warning(disable:4819)
#endif

#ifdef _BOTZONE_ONLINE
#ifndef _PREPROCESS_ONLY
#include "MahjongGB/MahjongGB.h"
#endif
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

#ifndef _PREPROCESS_ONLY
#include <iostream>
#endif

int StateContainer::quan=0;
int StateContainer::lastRequest=0;
int main() {
    int turnID; Reader::readIn(turnID);
    string tmp;
    int lastRequest;
    StateContainer basicState;
    for(int i=1; i<turnID; i++) {
        lastRequest = Reader::readRequest(basicState);
        getline(cin, tmp);   // 过滤掉我们发出的无用的信息
//        vector<Majang> & tmpM=basicState.getInHand();
//        for(auto & mahjong:tmpM){
//            cout<<mahjong.getTileString()<<" ";
//        }
//        cout<<endl;
    }
    StateContainer::lastRequest=lastRequest;
    int t=Reader::readRequest(basicState);
//        vector<Majang> & tmpM=basicState.getInHand();
//        for(auto & mahjong:tmpM){
//            cout<<mahjong.getTileString()<<" ";
//        }
//        cout<<endl;    
    Output::Response(t, basicState);
    return 0;
}