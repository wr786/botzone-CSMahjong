#ifdef _BOTZONE_ONLINE
#include "MahjongGB/MahjongGB.h"
#endif

#include "Mahjong.h"
#include "Mahjong.cpp"
#include "StateContainer.h"
#include "StateContainer.cpp"
#include "RequestReader.h"
#include "RequestReader.cpp"
#include "ScoreCalculator.h"
#include "ScoreCalculator.cpp"
#include "ResponseOutput.h"
#include "ResponseOutput.cpp"

int main() {
    int turnID; Reader::readIn(turnID);
    StateContainer basicState;
    for(int i=1; i<turnID; i++) {
        Reader::readRequest(basicState);
    }
    Output::Response(basicState, Reader::readRequest(basicState));
    return 0;
}