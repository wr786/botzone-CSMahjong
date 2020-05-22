
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
#include "ShantenCalculator.h"

#ifndef _PREPROCESS_ONLY
#include <iostream>
#endif

int StateContainer::quan=0;
int StateContainer::lastRequest=0;
int main() {
#ifndef _BOTZONE_ONLINE
    ShantenTest();
    cout << endl << "=== shanten test control group end ===" << endl;
    // [111m]5m12p1569sSWP
    vector<pair<string, Majang>> pack;
    vector<Majang> hand;
    pack.push_back({ "GANG", Majang(WANN * 10 + 1) });
    hand.push_back(Majang(WANN * 10 + 5));
    hand.push_back(Majang(BING * 10 + 1));
    hand.push_back(Majang(BING * 10 + 2));
    hand.push_back(Majang(TIAO * 10 + 1));
    hand.push_back(Majang(TIAO * 10 + 5));
    hand.push_back(Majang(TIAO * 10 + 6));
    hand.push_back(Majang(TIAO * 10 + 9));
    hand.push_back(Majang(FENG * 10 + 2));
    hand.push_back(Majang(FENG * 10 + 3));
    hand.push_back(Majang(JIAN * 10 + 3));
    cout << ComplicatedShantenCalc(pack, hand) << endl;
    cout << "=== complicated shanten test end ===" << endl;
    int param1, param2; // shanten, effective tiles
    auto p = ShantenCalc(pack, hand);
    param1 = p.first; param2 = p.second;
    cout << "shanten: " << param1 << endl
        << "effective tiles: " << param2 << endl;
    cout << "=== simplified shanten test end ===" << endl;
    cout << "=== shanten test end ===" << endl;
#endif // !_BOTZONE_ONLINE
    //clock_t start=clock();
    specialShantenInit();
    int turnID; Reader::readIn(turnID);
    string tmp;
    int lastRequest;
    StateContainer basicState;
    for (int i = 1; i < turnID; i++) {
        lastRequest = Reader::readRequest(basicState);
        getline(cin, tmp);   // 过滤掉我们发出的无用的信息
//        vector<Majang> & tmpM=basicState.getInHand();
//        for(auto & mahjong:tmpM){
//            cout<<mahjong.getTileString()<<" ";
//        }
//        cout<<endl;
    }
    StateContainer::lastRequest = lastRequest;
    int t = Reader::readRequest(basicState);
    //        vector<Majang> & tmpM=basicState.getInHand();
    //        for(auto & mahjong:tmpM){
    //            cout<<mahjong.getTileString()<<" ";
    //        }
    //        cout<<endl;      
    
    Output::Response(t, basicState);
    //clock_t end=clock();
    //cout<<endl;
    //cout<<end-start<<endl;
    return 0;
}