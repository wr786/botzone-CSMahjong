#include "./src/Majang.h"
#include "./src/Majang.cpp"
#include "./src/StateContainer.h"
#include "./src/StateContainer.cpp"
#include "./src/RequestReader.h"
#include "./src/RequestReader.cpp"
#include "./src/ScoreCalculator.h"
#include "./src/ScoreCalculator.cpp"
#include "./src/ResponseOutput.h"
#include "./src/ResponseOutput.cpp"
#include <iostream>
using namespace std;

int StateContainer::quan=0;
int main() {
    int turnID; Reader::readIn(turnID);
    string tmp;
    StateContainer basicState;
    for(int i=1; i<turnID; i++) {
        Reader::readRequest(basicState);
        getline(cin, tmp);   // 过滤掉我们发出的无用的信息
        vector<Majang>& tmpM = basicState.getInHand();
        cout << "[DEBUG] curInHand: ";
        for(auto& mahjong : tmpM) {
            cout << mahjong.getTileString() << " ";
        }
        cout << endl;
    }
    int forTest = Reader::readRequest(basicState);
    cout << "[DEBUG] curInHand: ";
    vector<Majang>& tmpM = basicState.getInHand();
    for(auto& mahjong : tmpM) {
        cout << mahjong.getTileString() << " ";
    }
    cout << endl;
    Output::Response(forTest, basicState);
    return 0;
}