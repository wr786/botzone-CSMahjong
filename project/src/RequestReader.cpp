#include "RequestReader.h"
#ifndef _PREPROCESS_ONLY
#include <cassert>
#include <iostream>
#endif
using namespace std;

void Reader::readIn(string &str) {
    str = ""; // 初始化
    unsigned char c = getchar();
    while(isspace(c)) c = getchar();
    while(!isspace(c)) {
        str += c;
        c = getchar();
    }
}

void Reader::readIn(int &x) {
    x = 0;
    unsigned char c = getchar();
    while(isspace(c)) c = getchar();
    while(!isspace(c)) {
        x = x * 10 + c - '0';
        c = getchar();
    }
}

void Reader::readIn(Majang &tile) {
    string tmp;
    readIn(tmp);
    tile.resetFromString(tmp);
}

// 每次使用可以读取一条request
int Reader::readRequest(StateContainer &state) {
    int requestID, tmp;
    int ret = 0;
    readIn(requestID);
    // 这里因为request只有四种，所以直接上switch了
    switch (requestID) {
        case 0: { // 初始化
            readIn(tmp);
            state.setCurPosition(tmp);
            readIn(StateContainer::quan);
            state.setLastPlayed("I0"); // I0 -> Initialize 0
            ret = 0;
            break;
        }
        case 1: { // 初始手牌
            // 读取花牌数量
            for (int i = 0; i < 4; i++) {
                readIn(tmp);
                state.getFlowerTilesOf(i).resize(tmp);
            }
            // 读取手牌
            assert(state.getInHand().size() == 13);
            for (int i = 0; i < 13; i++) {
                Majang tmpM;
                readIn(tmpM);
                state.getInHand()[i] = tmpM;
//                readIn(state.getInHand()[i]);
                state.decTileLeft(state.getInHand()[i]);
            }
            // 设置牌墙
            for(int i = 0; i < 4; i++) {
                assert(state.getTileWallLeftOf(i) == 34);
                state.decTileWallLeftOf(i, 13); // 每个人都抽了13张起始手牌
            }
            // 读取花牌
            for (int i = 0; i < 4; i++) {
                int lim = state.getFlowerTilesOf(i).size();
                for (int j = 0; j < lim; j++) {
                    readIn(state.getFlowerTilesOf(i)[j]);
                    state.decTileLeft(state.getFlowerTilesOf(i)[j]);
                }
            }
            state.setLastPlayed("I1"); // I1 -> Initialize 1
            ret = 1;
            break;
        }
        case 2: { // 我们抽牌
            vector<Majang>& tmpInHand = state.getInHand();
            Majang tmpM; readIn(tmpM);
            tmpInHand.push_back(tmpM);
            state.setLastPlayed("D6"); // D6 -> Draw!
            state.incInHandCntOf(state.getCurPosition());
            state.setCurTurnPlayer(state.getCurPosition());
            state.decTileLeft(tmpM);
            ret = 2;
            state.decTileWallLeftOf(state.getCurPosition());
            break;
        }
        case 3: { // 其他情况
            ret = 30;
            int playerID; readIn(playerID);
            state.setCurTurnPlayer(playerID); // 这条request谁进行了操作，谁就是curTurnPlayer
            string op; readIn(op);
            if (op == "BUHUA") {
                ret += 0;
                vector<Majang> &tmpHana = state.getFlowerTilesOf(playerID);
                Majang tmpM; readIn(tmpM);
                tmpHana.push_back(tmpM);
                state.decTileLeft(tmpM);
                state.setLastPlayed("D8");  // D8 -> 补花（8 => HAna)
            } else if (op == "DRAW") {
                ret += 1;
                state.incInHandCntOf(playerID);
                state.setLastPlayed("D0");  // D0 -> 其他玩家抽牌
                state.decTileWallLeftOf(playerID);  // 抽牌减牌
            } else if (op == "PLAY") {
                Majang tmpPlayed; readIn(tmpPlayed);
                state.setLastPlayed(tmpPlayed);
                vector<Majang>& tmpTilePlayed = state.getTilePlayedOf(playerID);
                tmpTilePlayed.push_back(tmpPlayed);
                state.decInHandCntOf(playerID);
                if(playerID == state.getCurPosition()) {
                    // 是我们打出的这张牌,这时需要从我们的手牌中去除这张牌
                    state.deleteFromInHand(tmpPlayed);
                } else {
                    state.decTileLeft(tmpPlayed); // 如果不是我们打出的，才需要dec
                }
                ret += 2;
            } else if (op == "PENG") {
                Majang tmpPlayed; readIn(tmpPlayed);
                Majang pengTile = state.getLastPlayed();   // 碰的牌为上一回合打出的牌
                vector<Majang>& tmpPengOf = state.getPengOf(playerID);
                tmpPengOf.push_back(pengTile);
                vector<Majang>& tmpTilePlayed = state.getTilePlayedOf(playerID);
                tmpTilePlayed.push_back(tmpPlayed);
                state.setLastPlayed(tmpPlayed);
                state.setInHandCntOf(playerID, state.getInHandCntOf(playerID)-3);  // 减少了三张牌
                if(playerID == state.getCurPosition()) {
                    // 是我们进行的碰的操作,这时需要从我们的手牌中去除这三张牌
                    state.deleteFromInHand(pengTile);
                    state.deleteFromInHand(pengTile);
                    state.deleteFromInHand(tmpPlayed);
                } else {
                    state.decTileLeft(pengTile);    // 被碰的牌又会打出两张
                    state.decTileLeft(pengTile);
                    state.decTileLeft(tmpPlayed);     // 打出的牌也是知道的
                }
                ret += 3;
            } else if (op == "CHI") {
                Majang tmpCHI, tmpPlayed;
                readIn(tmpCHI); readIn(tmpPlayed);
                vector<Majang>& tmpChiOf = state.getChiOf(playerID);
                tmpChiOf.push_back(tmpCHI);
                // 这里需要判断出该玩家为了吃打出来的是哪两张牌
                Majang tmpCHIprv = tmpCHI.getPrvMajang();
                Majang tmpCHInxt = tmpCHI.getNxtMajang();
                const Majang& lastPlayed = state.getLastPlayed();
                vector<Majang>& tmpTilePlayed = state.getTilePlayedOf(playerID);
                tmpTilePlayed.push_back(tmpPlayed);
                state.setInHandCntOf(playerID, state.getInHandCntOf(playerID)-3);  // 减少了三张牌
                if(playerID == state.getCurPosition()) {
                    // 再来一次判断
                    if(tmpCHIprv == lastPlayed) {
                        state.deleteFromInHand(tmpCHI);
                        state.deleteFromInHand(tmpCHInxt);
                    } else if(tmpCHI == lastPlayed) {
                        state.deleteFromInHand(tmpCHIprv);
                        state.deleteFromInHand(tmpCHInxt);
                    } else if(tmpCHInxt == lastPlayed) {
                        state.deleteFromInHand(tmpCHIprv);
                        state.deleteFromInHand(tmpCHI);
                    } else {
                        assert(strcmp("[ERROR] remove CHI tiles from inHand failed!",""));
                    }
                    state.deleteFromInHand(tmpPlayed);  // 以及打出的牌
                } else {
                    if(tmpCHIprv == lastPlayed) {
                        state.decTileLeft(tmpCHI);
                        state.decTileLeft(tmpCHInxt);
                    } else if(tmpCHI == lastPlayed) {
                        state.decTileLeft(tmpCHIprv);
                        state.decTileLeft(tmpCHInxt);
                    } else if(tmpCHInxt == lastPlayed) {
                        state.decTileLeft(tmpCHIprv);
                        state.decTileLeft(tmpCHI);
                    } else {
                        assert(strcmp("[ERROR] judge CHI failed!",""));
                    }
                    state.decTileLeft(tmpPlayed);
                }
                state.setLastPlayed(tmpPlayed);
                ret += 4;
            } else if (op == "GANG") {
                // cout << "[DEBUG]"<< state.getLastPlayed().getTileType() << endl;
                if(state.getLastPlayed().getTileType() == 'D') {
                    // 如果上一回合是摸牌，表示进行暗杠
                    state.incSecretGangCntOf(playerID);
                    state.setInHandCntOf(playerID, state.getInHandCntOf(playerID) - 4);
                    // cout << "[DEBUG] playerID: " << playerID <<" cp: " << state.getCurPosition() << endl;
                    if(playerID == state.getCurPosition()) {
                        // 自己GANG
                        Majang gangTile = state.getInHand()[state.getInHand().size()-1];
                        // cout << "[DEBUG]" << gangTile.getTileString() << endl;
                        state.getGangOf(playerID).push_back(gangTile); // 加入鸣牌
                        state.deleteFromInHand(gangTile);
                        state.deleteFromInHand(gangTile);
                        state.deleteFromInHand(gangTile);
                        state.deleteFromInHand(gangTile);
                    }
                } else {
                    // 明杠，这里假设抽牌操作和打牌操作会在之后以draw和play的request呈现
                    const Majang& gangTile = state.getLastPlayed();
                    vector<Majang>& tmpGangOf = state.getGangOf(playerID);
                    tmpGangOf.push_back(gangTile);
                    // 因为要打出三张gangTile
                    if(playerID == state.getCurPosition()) {
                        state.deleteFromInHand(gangTile);
                        state.deleteFromInHand(gangTile);
                        state.deleteFromInHand(gangTile);
                    } else {
                        state.decTileLeft(gangTile);
                        state.decTileLeft(gangTile);
                        state.decTileLeft(gangTile);
                    }
                }
                ret += 5;
            } else if (op == "BUGANG") {
                Majang tmpBuGang; readIn(tmpBuGang);
                vector<Majang>& tmpGangOf = state.getGangOf(playerID);
                tmpGangOf.push_back(tmpBuGang);
                // 同时还要从碰中去除
                vector<Majang>& tmpPengOf = state.getPengOf(playerID);
                int lim = tmpPengOf.size();
                for(int i=0; i<lim; i++) {
                    if(tmpPengOf[i] == tmpBuGang) {
                        swap(tmpPengOf[i], tmpPengOf[lim-1]);
                        break;
                    }
                }
//                tmpPengOf.resize(lim-1);
                tmpPengOf.pop_back(); // 换成这个了，但是显然有更好的做法，是优化的一个点
                if(playerID == state.getCurPosition()) {
                    state.deleteFromInHand(tmpBuGang);
                } else {
                    state.decTileLeft(tmpBuGang);
                }
                ret += 6;
            } else {
                assert(strcmp("[ERROR] readOP failed!",""));
            }
            break;
        }
        default: {
            assert(strcmp("[ERROR] readRequestID failed!",""));
            break;
        }
    }
    return ret;
}
