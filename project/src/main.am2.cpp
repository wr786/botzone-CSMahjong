#include<bits/stdc++.h> 
#include "MahjongGB/MahjongGB.h" 
# 1 ".\\main.cpp"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 ".\\main.cpp"
# 12 ".\\main.cpp"
# 1 ".\\Majang.h" 1
# 13 ".\\Majang.h"
using namespace std;
# 23 ".\\Majang.h"
typedef int TILE;
typedef enum TILETYPE {
    NILL = 0,
    WANN,
    BING,
    TIAO,
    FENG,
    JIAN,
    HANA,
    DRAW,
} TILE_T;

class Majang {
private:
    TILE innerType;
public:
    Majang(): innerType(0) {}
    Majang(const Majang& other);
    Majang(const char* cstrExpr);
    explicit Majang(const int& intExpr): innerType(intExpr) {}
    explicit Majang(const string& strExpr);

    Majang& operator = (const Majang& other);
    bool operator == (const Majang& other) const;

    void resetFromString(const string& strExpr);

    static TILE_T getTileTypeFromChar(char ch);
    static int parseTileType(const string& strExpr);
    static int parseTileNum(const string& strExpr);
    static TILE parseTile(const string& strExpr);
    [[nodiscard]] char getTileType() const;
    [[nodiscard]] int getTileNum() const;
    [[nodiscard]] TILE getTileInt() const;
    [[nodiscard]] bool isFlowerTile() const;
    [[nodiscard]] string getTileString() const;

    [[nodiscard]] Majang getNxtMajang() const;
    [[nodiscard]] Majang getPrvMajang() const;
};
# 13 ".\\main.cpp" 2
# 1 ".\\Majang.cpp" 1

# 1 ".\\Majang.h" 1
# 3 ".\\Majang.cpp" 2
# 15 ".\\Majang.cpp"
TILE_T Majang::getTileTypeFromChar(char ch) {

    switch(ch) {
        case 'W': return WANN;
        case 'B': return BING;
        case 'T': return TIAO;
        case 'F': return FENG;
        case 'J': return JIAN;
        case 'H': return HANA;
        case 'D': return DRAW;
        default: return NILL;
    }
}

int Majang::parseTileType(const string& strExpr) {
    return getTileTypeFromChar(strExpr[0]);
}

int Majang::parseTileNum(const string& strExpr) {
    return strExpr[1] - '0';
}

TILE Majang::parseTile(const string& strExpr) {
    assert(strExpr.length() == 2);
    return parseTileType(strExpr) * 10 + parseTileNum(strExpr);
}





Majang::Majang(const Majang &other) : innerType(other.innerType) {}

Majang::Majang(const char *cstrExpr) {
    innerType = getTileTypeFromChar(cstrExpr[0]) * 10 + cstrExpr[1] - '0';
}



Majang::Majang(const string& strExpr) {
    innerType = parseTile(strExpr);
}





Majang& Majang::operator = (const Majang& other) {
    if(&other == this) { return *this; }
    innerType = other.innerType;
    return *this;
}

bool Majang::operator == (const Majang &other) const {
    return innerType == other.innerType;
}







void Majang::resetFromString(const string& strExpr) {
    innerType = parseTile(strExpr);
}

char Majang::getTileType() const {
    auto tile_t = TILE_T(innerType / 10);
    switch(tile_t) {
        case WANN: return 'W';
        case BING: return 'B';
        case TIAO: return 'T';
        case FENG: return 'F';
        case JIAN: return 'J';
        case HANA: return 'H';
        case DRAW: return 'D';
        default: return 'N';
    }
}

int Majang::getTileNum() const {
    return innerType % 10;
}

TILE Majang::getTileInt() const {
    return innerType;
}


bool Majang::isFlowerTile() const {
    return getTileType() == 'H';
}

string Majang::getTileString() const{
    string r="";
    r=r+getTileType()+(char)(getTileNum() + '0');
    return r;
}

Majang Majang::getNxtMajang() const {

    return Majang(innerType + 1);
}

Majang Majang::getPrvMajang() const {

    return Majang(innerType - 1);
}
# 14 ".\\main.cpp" 2
# 1 ".\\StateContainer.h" 1
# 15 ".\\StateContainer.h"
# 1 ".\\Majang.h" 1
# 16 ".\\StateContainer.h" 2

using namespace std;
# 30 ".\\StateContainer.h"
class StateContainer {
private:
    int curPosition;
    int curTurnPlayer;







    vector<Majang> inHand;
    vector<Majang> flowerTilesOf[4];
    vector<Majang> chiOf[4];
    vector<Majang> pengOf[4];
    vector<Majang> gangOf[4];

    vector<Majang> tilePlayedOf[4];
    int secretGangCntOf[4];

    Majang lastPlayed;
    int tileLeft[70];
    int totalLeft;
    int inHandCnt[4];
    int tileWallLeft[4];

public:
    static int quan;
    static int lastRequest;

    explicit StateContainer(int curP=0, int curT=0);
    StateContainer(const StateContainer& other);
# 79 ".\\StateContainer.h"
    [[nodiscard]] vector<Majang>& getInHand();
    [[nodiscard]] vector<Majang>& getFlowerTilesOf(int idx);
    [[nodiscard]] vector<Majang>& getChiOf(int idx);
    [[nodiscard]] vector<Majang>& getPengOf(int idx);
    [[nodiscard]] vector<Majang>& getGangOf(int idx);
    [[nodiscard]] vector<Majang>& getTilePlayedOf(int idx);

    [[nodiscard]] const vector<Majang>& getInHand() const;
    [[nodiscard]] const vector<Majang>& getFlowerTilesOf(int idx) const;
    [[nodiscard]] const vector<Majang>& getChiOf(int idx) const;
    [[nodiscard]] const vector<Majang>& getPengOf(int idx) const;
    [[nodiscard]] const vector<Majang>& getGangOf(int idx) const;
    [[nodiscard]] const vector<Majang>& getTilePlayedOf(int idx) const;

    void decTileLeft(int idx);
    void decTileLeft(Majang mj);
    [[nodiscard]] const int & getTileLeft(int idx) const;
    [[nodiscard]] const int & getTotalLeft() const;

    void incSecretGangCntOf(int idx);
    [[nodiscard]] int getSecretGangCntOf(int idx) const;

    void setCurPosition(int curP);
    [[nodiscard]] int getCurPosition() const;
    void setCurTurnPlayer(int curTP);
    [[nodiscard]] int getCurTurnPlayer() const;
    void setLastPlayed(const Majang& lastTile);
    [[nodiscard]] const Majang& getLastPlayed() const;
    void setInHandCntOf(int idx, int cnt);
    [[nodiscard]] int getInHandCntOf(int idx) const;
    void incInHandCntOf(int idx);
    void decInHandCntOf(int idx);

    void deleteFromInHand(const Majang& toDelete);

    void nxtPosition();
    void nxtTurn();

    int getTileWallLeftOf(int idx) const;
    bool isTileWallEmpty(int idx) const;
    void decTileWallLeftOf(int idx, int amount=1);
};
# 15 ".\\main.cpp" 2
# 1 ".\\StateContainer.cpp" 1
# 1 ".\\StateContainer.h" 1
# 2 ".\\StateContainer.cpp" 2




StateContainer::StateContainer(int curP, int curT) : curPosition(curP), curTurnPlayer(curT), inHand(13), totalLeft(144) {
    for(int i = 1; i < 10; i++) {
        tileLeft[10 + i] = 4;
        tileLeft[20 + i] = 4;
        tileLeft[30 + i] = 4;
    }
    for(int i = 1; i < 5; i++) {
        tileLeft[40 + i] = 4;
        tileLeft[50 + i] = 4;
    }
    for(int i = 1; i < 9; i++) {
        tileLeft[60 + i] = 1;
    }
    lastPlayed = Majang("N0");
    for(int& i : inHandCnt) {
        i = 13;
    }
    for(int i = 0; i < 4; i++)
        tileWallLeft[i] = 34;
}

StateContainer::StateContainer(const StateContainer &other) {
    curPosition = other.curPosition;
    inHand = other.inHand;
    curTurnPlayer = other.curTurnPlayer;
    lastPlayed = other.lastPlayed;
    totalLeft = other.totalLeft;
    for (int i = 0; i < 4; i++) {
        flowerTilesOf[i] = other.flowerTilesOf[i];
        chiOf[i] = other.chiOf[i];
        pengOf[i] = other.pengOf[i];
        gangOf[i] = other.gangOf[i];

        tilePlayedOf[i] = other.tilePlayedOf[i];
        secretGangCntOf[i] = other.secretGangCntOf[i];
        inHandCnt[i] = other.inHandCnt[i];
        tileWallLeft[i] = other.tileWallLeft[i];
    }
    for (int i = 0; i < 70; i++) {
        tileLeft[i] = other.tileLeft[i];
    }
}
# 65 ".\\StateContainer.cpp"
vector<Majang> &StateContainer::getInHand() { return inHand; }
vector<Majang> &StateContainer::getFlowerTilesOf(int idx) { return flowerTilesOf[idx]; }
vector<Majang> &StateContainer::getChiOf(int idx) { return chiOf[idx]; }
vector<Majang> &StateContainer::getPengOf(int idx) { return pengOf[idx]; }
vector<Majang> &StateContainer::getGangOf(int idx) { return gangOf[idx]; }
vector<Majang> &StateContainer::getTilePlayedOf(int idx) { return tilePlayedOf[idx]; }

const vector<Majang> &StateContainer::getInHand() const { return inHand; }
const vector<Majang> &StateContainer::getFlowerTilesOf(int idx) const { return flowerTilesOf[idx]; }
const vector<Majang> &StateContainer::getChiOf(int idx) const { return chiOf[idx]; }
const vector<Majang> &StateContainer::getPengOf(int idx) const { return pengOf[idx]; }
const vector<Majang> &StateContainer::getGangOf(int idx) const { return gangOf[idx]; }
const vector<Majang> &StateContainer::getTilePlayedOf(int idx) const { return tilePlayedOf[idx]; }

void StateContainer::decTileLeft(int idx) { tileLeft[idx]--; totalLeft--; }
void StateContainer::decTileLeft(Majang mj) {
    tileLeft[mj.getTileInt()]--;
    totalLeft--;
}
const int & StateContainer::getTileLeft(int idx) const {return tileLeft[idx];}
const int & StateContainer::getTotalLeft() const {return totalLeft;}

void StateContainer::incSecretGangCntOf(int idx) {secretGangCntOf[idx]++;}
int StateContainer::getSecretGangCntOf(int idx) const { return secretGangCntOf[idx]; }

void StateContainer::setCurPosition(int curP) { curPosition = curP; }
int StateContainer::getCurPosition() const { return curPosition; }
void StateContainer::setCurTurnPlayer(int curTP) { curTurnPlayer = curTP; }
int StateContainer::getCurTurnPlayer() const { return curTurnPlayer; }
void StateContainer::setLastPlayed(const Majang &lastTile) { lastPlayed = lastTile; }
const Majang &StateContainer::getLastPlayed() const { return lastPlayed; }
void StateContainer::setInHandCntOf(int idx, int cnt) { inHandCnt[idx] = cnt; }
int StateContainer::getInHandCntOf(int idx) const { return inHandCnt[idx]; }
void StateContainer::incInHandCntOf(int idx) { inHandCnt[idx]++; }
void StateContainer::decInHandCntOf(int idx) { inHandCnt[idx]--; }

void StateContainer::deleteFromInHand(const Majang &toDelete) {
    int lim = inHand.size();
    for(int i=0; i<lim; i++) {
        if(inHand[i] == toDelete) {
            swap(inHand[i], inHand[lim-1]);
            break;
        }
    }
    inHand.resize(lim-1);
}

void StateContainer::nxtPosition() { curPosition = (curPosition + 1) % 4; }
void StateContainer::nxtTurn() { curTurnPlayer = (curTurnPlayer + 1) % 4; }

int StateContainer::getTileWallLeftOf(int idx) const {return tileWallLeft[idx];}
bool StateContainer::isTileWallEmpty(int idx) const {return tileWallLeft[idx] == 0;}
void StateContainer::decTileWallLeftOf(int idx, int amount) {tileWallLeft[idx] -= amount;}
# 16 ".\\main.cpp" 2
# 1 ".\\RequestReader.h" 1
# 17 ".\\RequestReader.h"
# 1 ".\\Majang.h" 1
# 18 ".\\RequestReader.h" 2
# 1 ".\\StateContainer.h" 1
# 19 ".\\RequestReader.h" 2






using namespace std;

class Reader{
public:
    static void readIn(string& str);
    static void readIn(int& x);
    static void readIn(Majang& tile);







    static int readRequest(StateContainer& state);
};
# 17 ".\\main.cpp" 2
# 1 ".\\RequestReader.cpp" 1
# 1 ".\\RequestReader.h" 1
# 2 ".\\RequestReader.cpp" 2




using namespace std;

void Reader::readIn(string &str) {
    str = "";
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


int Reader::readRequest(StateContainer &state) {
    int requestID, tmp;
    int ret = 0;
    readIn(requestID);

    switch (requestID) {
        case 0: {
            readIn(tmp);
            state.setCurPosition(tmp);
            readIn(StateContainer::quan);
            state.setLastPlayed("I0");
            ret = 0;
            break;
        }
        case 1: {

            for (int i = 0; i < 4; i++) {
                readIn(tmp);
                state.getFlowerTilesOf(i).resize(tmp);
            }

            assert(state.getInHand().size() == 13);
            for (int i = 0; i < 13; i++) {
                Majang tmpM;
                readIn(tmpM);
                state.getInHand()[i] = tmpM;

                state.decTileLeft(state.getInHand()[i]);
            }

            for(int i = 0; i < 4; i++) {
                assert(state.getTileWallLeftOf(i) == 34);
                state.decTileWallLeftOf(i, 13);
            }

            for (int i = 0; i < 4; i++) {
                int lim = state.getFlowerTilesOf(i).size();
                for (int j = 0; j < lim; j++) {
                    readIn(state.getFlowerTilesOf(i)[j]);
                    state.decTileLeft(state.getFlowerTilesOf(i)[j]);
                }
            }
            state.setLastPlayed("I1");
            ret = 1;
            break;
        }
        case 2: {
            vector<Majang>& tmpInHand = state.getInHand();
            Majang tmpM; readIn(tmpM);
            tmpInHand.push_back(tmpM);
            state.setLastPlayed("D6");
            state.incInHandCntOf(state.getCurPosition());
            state.setCurTurnPlayer(state.getCurPosition());
            state.decTileLeft(tmpM);
            ret = 2;
            state.decTileWallLeftOf(state.getCurPosition());
            break;
        }
        case 3: {
            ret = 30;
            int playerID; readIn(playerID);
            state.setCurTurnPlayer(playerID);
            string op; readIn(op);
            if (op == "BUHUA") {
                ret += 0;
                vector<Majang> &tmpHana = state.getFlowerTilesOf(playerID);
                Majang tmpM; readIn(tmpM);
                tmpHana.push_back(tmpM);
                state.decTileLeft(tmpM);
                state.setLastPlayed("D8");
            } else if (op == "DRAW") {
                ret += 1;
                state.incInHandCntOf(playerID);
                state.setLastPlayed("D0");
                state.decTileWallLeftOf(playerID);
            } else if (op == "PLAY") {
                Majang tmpPlayed; readIn(tmpPlayed);
                state.setLastPlayed(tmpPlayed);
                vector<Majang>& tmpTilePlayed = state.getTilePlayedOf(playerID);
                tmpTilePlayed.push_back(tmpPlayed);
                state.decInHandCntOf(playerID);
                if(playerID == state.getCurPosition()) {

                    state.deleteFromInHand(tmpPlayed);
                } else {
                    state.decTileLeft(tmpPlayed);
                }
                ret += 2;
            } else if (op == "PENG") {
                Majang tmpPlayed; readIn(tmpPlayed);
                Majang pengTile = state.getLastPlayed();
                vector<Majang>& tmpPengOf = state.getPengOf(playerID);
                tmpPengOf.push_back(pengTile);
                vector<Majang>& tmpTilePlayed = state.getTilePlayedOf(playerID);
                tmpTilePlayed.push_back(tmpPlayed);
                state.setLastPlayed(tmpPlayed);
                state.setInHandCntOf(playerID, state.getInHandCntOf(playerID)-3);
                if(playerID == state.getCurPosition()) {

                    state.deleteFromInHand(pengTile);
                    state.deleteFromInHand(pengTile);
                    state.deleteFromInHand(tmpPlayed);
                } else {
                    state.decTileLeft(pengTile);
                    state.decTileLeft(pengTile);
                    state.decTileLeft(tmpPlayed);
                }
                ret += 3;
            } else if (op == "CHI") {
                Majang tmpCHI, tmpPlayed;
                readIn(tmpCHI); readIn(tmpPlayed);
                vector<Majang>& tmpChiOf = state.getChiOf(playerID);
                tmpChiOf.push_back(tmpCHI);

                Majang tmpCHIprv = tmpCHI.getPrvMajang();
                Majang tmpCHInxt = tmpCHI.getNxtMajang();
                const Majang& lastPlayed = state.getLastPlayed();
                vector<Majang>& tmpTilePlayed = state.getTilePlayedOf(playerID);
                tmpTilePlayed.push_back(tmpPlayed);
                state.setInHandCntOf(playerID, state.getInHandCntOf(playerID)-3);
                if(playerID == state.getCurPosition()) {

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
                    state.deleteFromInHand(tmpPlayed);
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

                if(state.getLastPlayed().getTileType() == 'D') {

                    state.incSecretGangCntOf(playerID);
                    state.setInHandCntOf(playerID, state.getInHandCntOf(playerID) - 4);

                    if(playerID == state.getCurPosition()) {

                        Majang gangTile = state.getInHand()[state.getInHand().size()-1];

                        state.getGangOf(playerID).push_back(gangTile);
                        state.deleteFromInHand(gangTile);
                        state.deleteFromInHand(gangTile);
                        state.deleteFromInHand(gangTile);
                        state.deleteFromInHand(gangTile);
                    }
                } else {

                    const Majang& gangTile = state.getLastPlayed();
                    vector<Majang>& tmpGangOf = state.getGangOf(playerID);
                    tmpGangOf.push_back(gangTile);

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

                vector<Majang>& tmpPengOf = state.getPengOf(playerID);
                int lim = tmpPengOf.size();
                for(int i=0; i<lim; i++) {
                    if(tmpPengOf[i] == tmpBuGang) {
                        swap(tmpPengOf[i], tmpPengOf[lim-1]);
                        break;
                    }
                }

                tmpPengOf.pop_back();
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
# 18 ".\\main.cpp" 2
# 1 ".\\ScoreCalculator.h" 1
# 15 ".\\ScoreCalculator.h"
# 1 ".\\Majang.h" 1
# 16 ".\\ScoreCalculator.h" 2
# 1 ".\\StateContainer.h" 1
# 17 ".\\ScoreCalculator.h" 2
# 1 ".\\ShantenCalculator.h" 1

       
# 16 ".\\ShantenCalculator.h"
# 1 ".\\../utils/MahjongGB/MahjongGB.h" 1
# 11 ".\\../utils/MahjongGB/MahjongGB.h"
# 1 ".\\../utils/MahjongGB/MahjongGB.cpp" 1
# 1 ".\\../utils/MahjongGB/MahjongGB.h" 1
# 2 ".\\../utils/MahjongGB/MahjongGB.cpp" 2
# 13 ".\\../utils/MahjongGB/MahjongGB.cpp"
# 1 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.h" 1
# 26 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.h"
# 1 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h" 1
# 53 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h"
namespace mahjong {
# 91 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h"
typedef uint8_t suit_t;




typedef uint8_t rank_t;
# 116 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h"
typedef uint8_t tile_t;
# 125 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h"
static __inline__ __attribute__((__always_inline__)) tile_t make_tile(suit_t suit, rank_t rank) {
    return (((suit & 0xF) << 4) | (rank & 0xF));
}







static __inline__ __attribute__((__always_inline__)) suit_t tile_get_suit(tile_t tile) {
    return ((tile >> 4) & 0xF);
}







static __inline__ __attribute__((__always_inline__)) bool is_flower(tile_t tile) {
    return ((tile >> 4) & 0xF) == 5;
}







static __inline__ __attribute__((__always_inline__)) rank_t tile_get_rank(tile_t tile) {
    return (tile & 0xF);
}




enum tile_value_t {
    TILE_1m = 0x11, TILE_2m, TILE_3m, TILE_4m, TILE_5m, TILE_6m, TILE_7m, TILE_8m, TILE_9m,
    TILE_1s = 0x21, TILE_2s, TILE_3s, TILE_4s, TILE_5s, TILE_6s, TILE_7s, TILE_8s, TILE_9s,
    TILE_1p = 0x31, TILE_2p, TILE_3p, TILE_4p, TILE_5p, TILE_6p, TILE_7p, TILE_8p, TILE_9p,
    TILE_E = 0x41, TILE_S , TILE_W , TILE_N , TILE_C , TILE_F , TILE_P ,
    TILE_TABLE_SIZE
};




static const tile_t all_tiles[] = {
    TILE_1m, TILE_2m, TILE_3m, TILE_4m, TILE_5m, TILE_6m, TILE_7m, TILE_8m, TILE_9m,
    TILE_1s, TILE_2s, TILE_3s, TILE_4s, TILE_5s, TILE_6s, TILE_7s, TILE_8s, TILE_9s,
    TILE_1p, TILE_2p, TILE_3p, TILE_4p, TILE_5p, TILE_6p, TILE_7p, TILE_8p, TILE_9p,
    TILE_E , TILE_S , TILE_W , TILE_N , TILE_C , TILE_F , TILE_P
};
# 187 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h"
typedef uint16_t tile_table_t[TILE_TABLE_SIZE];
# 209 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h"
typedef uint16_t pack_t;
# 218 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h"
static __inline__ __attribute__((__always_inline__)) pack_t make_pack(uint8_t offer, uint8_t type, tile_t tile) {
    return (offer << 12 | (type << 8) | tile);
}







static __inline__ __attribute__((__always_inline__)) bool is_pack_melded(pack_t pack) {
    return !!(pack & 0x3000);
}
# 239 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h"
static __inline__ __attribute__((__always_inline__)) bool is_promoted_kong(pack_t pack) {
    return !!(pack & 0x4000);
}
# 250 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h"
static __inline__ __attribute__((__always_inline__)) pack_t promote_pung_to_kong(pack_t pack) {
    return pack | 0x4300;
}







static __inline__ __attribute__((__always_inline__)) uint8_t pack_get_offer(pack_t pack) {
    return ((pack >> 12) & 0x3);
}







static __inline__ __attribute__((__always_inline__)) uint8_t pack_get_type(pack_t pack) {
    return ((pack >> 8) & 0xF);
}







static __inline__ __attribute__((__always_inline__)) tile_t pack_get_tile(pack_t pack) {
    return (pack & 0xFF);
}





struct hand_tiles_t {
    pack_t fixed_packs[5];
    intptr_t pack_count;
    tile_t standing_tiles[13];
    intptr_t tile_count;
};
# 302 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h"
static __inline__ __attribute__((__always_inline__)) bool is_green(tile_t tile) {







    return !!(0x0020000000AE0000ULL & (1ULL << (tile - TILE_1m)));
}







static __inline__ __attribute__((__always_inline__)) bool is_reversible(tile_t tile) {






    return !!(0x0040019F01BA0000ULL & (1ULL << (tile - TILE_1m)));
}







static __inline__ __attribute__((__always_inline__)) bool is_terminal(tile_t tile) {
# 350 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h"
    return ((tile & 0xC7) == 1);
}






static __inline__ __attribute__((__always_inline__)) bool is_winds(tile_t tile) {
    return (tile > 0x40 && tile < 0x45);
}






static __inline__ __attribute__((__always_inline__)) bool is_dragons(tile_t tile) {
    return (tile > 0x44 && tile < 0x48);
}






static __inline__ __attribute__((__always_inline__)) bool is_honor(tile_t tile) {
    return (tile > 0x40 && tile < 0x48);
}






static __inline__ __attribute__((__always_inline__)) bool is_numbered_suit(tile_t tile) {
    if (tile < 0x1A) return (tile > 0x10);
    if (tile < 0x2A) return (tile > 0x20);
    if (tile < 0x3A) return (tile > 0x30);
    return false;
}
# 399 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h"
static __inline__ __attribute__((__always_inline__)) bool is_numbered_suit_quick(tile_t tile) {

    return !(tile & 0xC0);
}






static __inline__ __attribute__((__always_inline__)) bool is_terminal_or_honor(tile_t tile) {
    return is_terminal(tile) || is_honor(tile);
}
# 420 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h"
static __inline__ __attribute__((__always_inline__)) bool is_suit_equal_quick(tile_t tile0, tile_t tile1) {

    return ((tile0 & 0xF0) == (tile1 & 0xF0));
}
# 432 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h"
static __inline__ __attribute__((__always_inline__)) bool is_rank_equal_quick(tile_t tile0, tile_t tile1) {

    return ((tile0 & 0xCF) == (tile1 & 0xCF));
}






}
# 27 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.h" 2



namespace mahjong {
# 40 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.h"
enum fan_t {
    FAN_NONE = 0,
    BIG_FOUR_WINDS,
    BIG_THREE_DRAGONS,
    ALL_GREEN,
    NINE_GATES,
    FOUR_KONGS,
    SEVEN_SHIFTED_PAIRS,
    THIRTEEN_ORPHANS,

    ALL_TERMINALS,
    LITTLE_FOUR_WINDS,
    LITTLE_THREE_DRAGONS,
    ALL_HONORS,
    FOUR_CONCEALED_PUNGS,
    PURE_TERMINAL_CHOWS,

    QUADRUPLE_CHOW,
    FOUR_PURE_SHIFTED_PUNGS,

    FOUR_PURE_SHIFTED_CHOWS,
    THREE_KONGS,
    ALL_TERMINALS_AND_HONORS,

    SEVEN_PAIRS,
    GREATER_HONORS_AND_KNITTED_TILES,
    ALL_EVEN_PUNGS,
    FULL_FLUSH,
    PURE_TRIPLE_CHOW,
    PURE_SHIFTED_PUNGS,
    UPPER_TILES,
    MIDDLE_TILES,
    LOWER_TILES,

    PURE_STRAIGHT,
    THREE_SUITED_TERMINAL_CHOWS,
    PURE_SHIFTED_CHOWS,
    ALL_FIVE,
    TRIPLE_PUNG,
    THREE_CONCEALED_PUNGS,

    LESSER_HONORS_AND_KNITTED_TILES,
    KNITTED_STRAIGHT,
    UPPER_FOUR,
    LOWER_FOUR,
    BIG_THREE_WINDS,

    MIXED_STRAIGHT,
    REVERSIBLE_TILES,
    MIXED_TRIPLE_CHOW,
    MIXED_SHIFTED_PUNGS,
    CHICKEN_HAND,
    LAST_TILE_DRAW,
    LAST_TILE_CLAIM,
    OUT_WITH_REPLACEMENT_TILE,
    ROBBING_THE_KONG,

    ALL_PUNGS,
    HALF_FLUSH,
    MIXED_SHIFTED_CHOWS,
    ALL_TYPES,
    MELDED_HAND,
    TWO_CONCEALED_KONGS,
    TWO_DRAGONS_PUNGS,

    OUTSIDE_HAND,
    FULLY_CONCEALED_HAND,
    TWO_MELDED_KONGS,
    LAST_TILE,

    DRAGON_PUNG,
    PREVALENT_WIND,
    SEAT_WIND,
    CONCEALED_HAND,
    ALL_CHOWS,
    TILE_HOG,
    DOUBLE_PUNG,
    TWO_CONCEALED_PUNGS,
    CONCEALED_KONG,
    ALL_SIMPLES,

    PURE_DOUBLE_CHOW,
    MIXED_DOUBLE_CHOW,
    SHORT_STRAIGHT,
    TWO_TERMINAL_CHOWS,
    PUNG_OF_TERMINALS_OR_HONORS,
    MELDED_KONG,
    ONE_VOIDED_SUIT,
    NO_HONORS,
    EDGE_WAIT,
    CLOSED_WAIT,
    SINGLE_WAIT,
    SELF_DRAWN,

    FLOWER_TILES,


    CONCEALED_KONG_AND_MELDED_KONG,


    FAN_TABLE_SIZE
};




enum class wind_t {
    EAST, SOUTH, WEST, NORTH
};




typedef uint8_t win_flag_t;
# 190 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.h"
int check_calculator_input(const hand_tiles_t *hand_tiles, tile_t win_tile);




struct calculate_param_t {
    hand_tiles_t hand_tiles;
    tile_t win_tile;
    uint8_t flower_count;
    win_flag_t win_flag;
    wind_t prevalent_wind;
    wind_t seat_wind;
};




typedef uint16_t fan_table_t[FAN_TABLE_SIZE];
# 219 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.h"
int calculate_fan(const calculate_param_t *calculate_param, fan_table_t *fan_table);
# 270 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.h"
static const char *fan_name[] = {
    u8"无",
    u8"大四喜", u8"大三元", u8"绿一色", u8"九莲宝灯", u8"四杠", u8"连七对", u8"十三幺",
    u8"清幺九", u8"小四喜", u8"小三元", u8"字一色", u8"四暗刻", u8"一色双龙会",
    u8"一色四同顺", u8"一色四节高",
    u8"一色四步高", u8"三杠", u8"混幺九",
    u8"七对", u8"七星不靠", u8"全双刻", u8"清一色", u8"一色三同顺", u8"一色三节高", u8"全大", u8"全中", u8"全小",
    u8"清龙", u8"三色双龙会", u8"一色三步高", u8"全带五", u8"三同刻", u8"三暗刻",
    u8"全不靠", u8"组合龙", u8"大于五", u8"小于五", u8"三风刻",
    u8"花龙", u8"推不倒", u8"三色三同顺", u8"三色三节高", u8"无番和", u8"妙手回春", u8"海底捞月", u8"杠上开花", u8"抢杠和",
    u8"碰碰和", u8"混一色", u8"三色三步高", u8"五门齐", u8"全求人", u8"双暗杠", u8"双箭刻",
    u8"全带幺", u8"不求人", u8"双明杠", u8"和绝张",
    u8"箭刻", u8"圈风刻", u8"门风刻", u8"门前清", u8"平和", u8"四归一", u8"双同刻", u8"双暗刻", u8"暗杠", u8"断幺",
    u8"一般高", u8"喜相逢", u8"连六", u8"老少副", u8"幺九刻", u8"明杠", u8"缺一门", u8"无字", u8"边张", u8"嵌张", u8"单钓将", u8"自摸",
    u8"花牌"

    , u8"明暗杠"

};






static const uint16_t fan_value_table[FAN_TABLE_SIZE] = {
    0,
    88, 88, 88, 88, 88, 88, 88,
    64, 64, 64, 64, 64, 64,
    48, 48,
    32, 32, 32,
    24, 24, 24, 24, 24, 24, 24, 24, 24,
    16, 16, 16, 16, 16, 16,
    12, 12, 12, 12, 12,
    8, 8, 8, 8, 8, 8, 8, 8, 8,
    6, 6, 6, 6, 6, 6, 6,
    4, 4, 4, 4,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1

    , 5

};
# 324 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.h"
bool is_standing_tiles_contains_win_tile(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t win_tile);
# 335 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.h"
size_t count_win_tile_in_fixed_packs(const pack_t *fixed_packs, intptr_t fixed_cnt, tile_t win_tile);
# 344 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.h"
bool is_fixed_packs_contains_kong(const pack_t *fixed_packs, intptr_t fixed_cnt);






}
# 14 ".\\../utils/MahjongGB/MahjongGB.cpp" 2

using namespace std;

static unordered_map<string, mahjong::tile_t> str2tile;

vector<pair<int, string> > MahjongFanCalculator(
    vector<pair<string, pair<string, int> > > pack,
    vector<string> hand,
    string winTile,
    int flowerCount,
    bool isZIMO,
    bool isJUEZHANG,
    bool isGANG,
    bool isLAST,
    int menFeng,
    int quanFeng)
{
    vector<pair<int,string>> ans;
    mahjong::calculate_param_t calculate_param;
    mahjong::fan_table_t fan_table;
    memset(&calculate_param, 0, sizeof(mahjong::calculate_param_t));
    memset(&fan_table, 0, sizeof(mahjong::fan_table_t));
    calculate_param.hand_tiles.tile_count = hand.size();
    for(unsigned int i = 0; i < hand.size(); i++) {
        if(str2tile.find(hand[i]) == str2tile.end()){
            throw string("ERROE_WRONG_TILE_CODE");
        }
        calculate_param.hand_tiles.standing_tiles[i] = str2tile[hand[i]];
    }
    calculate_param.hand_tiles.pack_count = pack.size();
    for(unsigned int i = 0; i < pack.size(); i++) {
        pair<string, pair<string, int>> &sPack = pack[i];
        mahjong::pack_t &dPack = calculate_param.hand_tiles.fixed_packs[i];
        if(sPack.first == "PENG") {
            dPack = mahjong::make_pack(sPack.second.second, 2, str2tile[sPack.second.first]);
        } else if(sPack.first == "GANG") {
            dPack = mahjong::make_pack(sPack.second.second, 3, str2tile[sPack.second.first]);
        } else if(sPack.first == "CHI"){
            dPack = mahjong::make_pack(sPack.second.second, 1, str2tile[sPack.second.first]);
        } else {
            throw string("ERROE_WRONG_PACK_CODE");
        }
    }
    calculate_param.win_tile = str2tile[winTile];
    calculate_param.flower_count = flowerCount;
    if(isZIMO) {
        calculate_param.win_flag |= 1;
    }
    if(isLAST) {
        calculate_param.win_flag |= 8;
    }
    if(isJUEZHANG) {
        calculate_param.win_flag |= 2;
    }
    if(isGANG) {
        calculate_param.win_flag |= 4;
    }
    calculate_param.prevalent_wind = (mahjong::wind_t)quanFeng;
    calculate_param.seat_wind = (mahjong::wind_t)menFeng;
    int re = mahjong::calculate_fan(&calculate_param, &fan_table);
    if(re == -1) {
        throw string("ERROR_WRONG_TILES_COUNT");
    }else if(re == -2) {
        throw string("ERROR_TILE_COUNT_GREATER_THAN_4");
    }else if(re == -3) {
        throw string("ERROR_NOT_WIN");
    }
    for(int i = 0; i < mahjong::FAN_TABLE_SIZE; i++) {
        if(fan_table[i] > 0) {
            ans.push_back(make_pair(fan_table[i]*mahjong::fan_value_table[i],mahjong::fan_name[i]));
        }
    }
    return ans;
}

void MahjongInit()
{
    for(int i = 1; i <= 9; i++) {
        str2tile["W" + to_string(i)] = mahjong::make_tile(1, i);
        str2tile["B" + to_string(i)] = mahjong::make_tile(3, i);
        str2tile["T" + to_string(i)] = mahjong::make_tile(2, i);
    }
    for(int i = 1; i <= 4; i++) {
        str2tile["F" + to_string((i))] = mahjong::make_tile(4, i);
    }
    for(int i = 1; i <= 3; i++) {
        str2tile["J" + to_string((i))] = mahjong::make_tile(4, i + 4);
    }
}
# 12 ".\\../utils/MahjongGB/MahjongGB.h" 2
# 1 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.cpp" 1
# 23 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.cpp"
# 1 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.h" 1
# 24 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.cpp" 2







# 1 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/standard_tiles.h" 1
# 28 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/standard_tiles.h"
namespace mahjong {


static const tile_t standard_thirteen_orphans[13] = {
    TILE_1m, TILE_9m, TILE_1s, TILE_9s, TILE_1p, TILE_9p, TILE_E, TILE_S, TILE_W, TILE_N, TILE_C, TILE_F, TILE_P
};
# 42 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/standard_tiles.h"
static const tile_t standard_knitted_straight[6][9] = {
    { TILE_1m, TILE_4m, TILE_7m, TILE_2s, TILE_5s, TILE_8s, TILE_3p, TILE_6p, TILE_9p },
    { TILE_1m, TILE_4m, TILE_7m, TILE_3s, TILE_6s, TILE_9s, TILE_2p, TILE_5p, TILE_8p },
    { TILE_2m, TILE_5m, TILE_8m, TILE_1s, TILE_4s, TILE_7s, TILE_3p, TILE_6p, TILE_9p },
    { TILE_2m, TILE_5m, TILE_8m, TILE_3s, TILE_6s, TILE_9s, TILE_1p, TILE_4p, TILE_7p },
    { TILE_3m, TILE_6m, TILE_9m, TILE_1s, TILE_4s, TILE_7s, TILE_2p, TILE_5p, TILE_8p },
    { TILE_3m, TILE_6m, TILE_9m, TILE_2s, TILE_5s, TILE_8s, TILE_1p, TILE_4p, TILE_7p },
};

}
# 32 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.cpp" 2
# 1 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h" 1
# 28 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
namespace mahjong {
# 39 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
intptr_t packs_to_tiles(const pack_t *packs, intptr_t pack_cnt, tile_t *tiles, intptr_t tile_cnt);
# 48 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
void map_tiles(const tile_t *tiles, intptr_t cnt, tile_table_t *cnt_table);
# 57 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
bool map_hand_tiles(const hand_tiles_t *hand_tiles, tile_table_t *cnt_table);
# 67 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
intptr_t table_to_tiles(const tile_table_t &cnt_table, tile_t *tiles, intptr_t max_cnt);




typedef bool useful_table_t[TILE_TABLE_SIZE];
# 92 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
int basic_form_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);
# 102 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
bool is_basic_form_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);
# 112 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
bool is_basic_form_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);
# 132 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
int seven_pairs_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);
# 142 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
bool is_seven_pairs_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);
# 152 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
bool is_seven_pairs_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);
# 172 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
int thirteen_orphans_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);
# 182 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
bool is_thirteen_orphans_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);
# 192 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
bool is_thirteen_orphans_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);
# 212 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
int knitted_straight_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);
# 222 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
bool is_knitted_straight_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);
# 232 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
bool is_knitted_straight_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);
# 252 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
int honors_and_knitted_tiles_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);
# 262 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
bool is_honors_and_knitted_tiles_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);
# 272 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
bool is_honors_and_knitted_tiles_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);
# 286 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
bool is_waiting(const hand_tiles_t &hand_tiles, useful_table_t *useful_table);
# 311 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
struct enum_result_t {
    tile_t discard_tile;
    uint8_t form_flag;
    int shanten;
    useful_table_t useful_table;
};
# 326 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
typedef bool (*enum_callback_t)(void *context, const enum_result_t *result);
# 337 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.h"
void enum_discard_tile(const hand_tiles_t *hand_tiles, tile_t serving_tile, uint8_t form_flag,
    void *context, enum_callback_t enum_callback);

}
# 33 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.cpp" 2
# 73 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.cpp"
namespace mahjong {







namespace {


    struct division_t {
        pack_t packs[5];
    };


    struct division_result_t {
        division_t divisions[20];
        intptr_t count;
    };
}


static void divide_tail_add_division(intptr_t fixed_cnt, const division_t *work_division, division_result_t *result) {


    division_t temp;
    memcpy(&temp, work_division, sizeof(temp));
    std::sort(temp.packs + fixed_cnt, temp.packs + 4);


    if (std::none_of(&result->divisions[0], &result->divisions[result->count],
        [&temp, fixed_cnt](const division_t &od) {
        return std::equal(&od.packs[fixed_cnt], &od.packs[4], &temp.packs[fixed_cnt]);
    })) {

        memcpy(&result->divisions[result->count], &temp, sizeof(temp));
        ++result->count;
    }
    else {
        ((void)0);
    }
}


static bool divide_tail(tile_table_t &cnt_table, intptr_t fixed_cnt, division_t *work_division, division_result_t *result) {
    for (int i = 0; i < 34; ++i) {
        tile_t t = all_tiles[i];
        if (cnt_table[t] < 2) {
            continue;
        }

        cnt_table[t] -= 2;

        if (std::all_of(std::begin(cnt_table), std::end(cnt_table), [](int n) { return n == 0; })) {
            cnt_table[t] += 2;


            work_division->packs[4] = make_pack(0, 4, t);
            divide_tail_add_division(fixed_cnt, work_division, result);
            return true;
        }
        cnt_table[t] += 2;
    }

    return false;
}


static bool is_division_branch_exist(intptr_t fixed_cnt, intptr_t step, const division_t *work_division, const division_result_t *result) {

    if (result->count <= 0 || step < 3) {
        return false;
    }



    division_t temp;
    memcpy(&temp.packs[fixed_cnt], &work_division->packs[fixed_cnt], step * sizeof(pack_t));
    std::sort(&temp.packs[fixed_cnt], &temp.packs[fixed_cnt + step]);


    return std::any_of(&result->divisions[0], &result->divisions[result->count],
        [&temp, fixed_cnt, step](const division_t &od) {
        return std::includes(&od.packs[fixed_cnt], &od.packs[4], &temp.packs[fixed_cnt], &temp.packs[fixed_cnt + step]);
    });
}


static bool divide_recursively(tile_table_t &cnt_table, intptr_t fixed_cnt, intptr_t step, division_t *work_division, division_result_t *result) {
    const intptr_t idx = step + fixed_cnt;
    if (idx == 4) {
        return divide_tail(cnt_table, fixed_cnt, work_division, result);
    }

    bool ret = false;


    for (int i = 0; i < 34; ++i) {
        tile_t t = all_tiles[i];
        if (cnt_table[t] < 1) {
            continue;
        }


        if (cnt_table[t] > 2) {
            work_division->packs[idx] = make_pack(0, 2, t);
            if (!is_division_branch_exist(fixed_cnt, step + 1, work_division, result)) {

                cnt_table[t] -= 3;
                if (divide_recursively(cnt_table, fixed_cnt, step + 1, work_division, result)) {
                    ret = true;
                }

                cnt_table[t] += 3;
            }
        }


        if (is_numbered_suit(t)) {
            if (tile_get_rank(t) < 8 && cnt_table[t + 1] && cnt_table[t + 2]) {
                work_division->packs[idx] = make_pack(0, 1, static_cast<tile_t>(t + 1));
                if (!is_division_branch_exist(fixed_cnt, step + 1, work_division, result)) {

                    --cnt_table[t];
                    --cnt_table[t + 1];
                    --cnt_table[t + 2];
                    if (divide_recursively(cnt_table, fixed_cnt, step + 1, work_division, result)) {
                        ret = true;
                    }

                    ++cnt_table[t];
                    ++cnt_table[t + 1];
                    ++cnt_table[t + 2];
                }
            }
        }
    }

    return ret;
}


static bool divide_win_hand(const tile_t *standing_tiles, const pack_t *fixed_packs, intptr_t fixed_cnt, division_result_t *result) {
    intptr_t standing_cnt = 14 - fixed_cnt * 3;


    tile_table_t cnt_table;
    map_tiles(standing_tiles, standing_cnt, &cnt_table);

    result->count = 0;


    division_t work_division;
    memcpy(work_division.packs, fixed_packs, fixed_cnt * sizeof(pack_t));
    return divide_recursively(cnt_table, fixed_cnt, 0, &work_division, result);
}




static __inline__ __attribute__((__always_inline__)) bool is_four_shifted_1(rank_t r0, rank_t r1, rank_t r2, rank_t r3) {
    return (r0 + 1 == r1 && r1 + 1 == r2 && r2 + 1 == r3);
}


static __inline__ __attribute__((__always_inline__)) bool is_four_shifted_2(rank_t r0, rank_t r1, rank_t r2, rank_t r3) {
    return (r0 + 2 == r1 && r1 + 2 == r2 && r2 + 2 == r3);
}


static __inline__ __attribute__((__always_inline__)) bool is_shifted_1(rank_t r0, rank_t r1, rank_t r2) {
    return (r0 + 1 == r1 && r1 + 1 == r2);
}


static __inline__ __attribute__((__always_inline__)) bool is_shifted_2(rank_t r0, rank_t r1, rank_t r2) {
    return (r0 + 2 == r1 && r1 + 2 == r2);
}


static __inline__ __attribute__((__always_inline__)) bool is_mixed(suit_t s0, suit_t s1, suit_t s2) {
    return (s0 != s1 && s0 != s2 && s1 != s2);
}


static __inline__ __attribute__((__always_inline__)) bool is_shifted_1_unordered(rank_t r0, rank_t r1, rank_t r2) {
    return is_shifted_1(r1, r0, r2) || is_shifted_1(r2, r0, r1) || is_shifted_1(r0, r1, r2)
        || is_shifted_1(r2, r1, r0) || is_shifted_1(r0, r2, r1) || is_shifted_1(r1, r2, r0);
}


static fan_t get_4_chows_fan(tile_t t0, tile_t t1, tile_t t2, tile_t t3) {



    if (is_four_shifted_2(t0, t1, t2, t3) || is_four_shifted_1(t0, t1, t2, t3)) {
        return FOUR_PURE_SHIFTED_CHOWS;
    }

    if (t0 == t1 && t0 == t2 && t0 == t3) {
        return QUADRUPLE_CHOW;
    }

    return FAN_NONE;
}


static fan_t get_3_chows_fan(tile_t t0, tile_t t1, tile_t t2) {
    suit_t s0 = tile_get_suit(t0);
    suit_t s1 = tile_get_suit(t1);
    suit_t s2 = tile_get_suit(t2);

    rank_t r0 = tile_get_rank(t0);
    rank_t r1 = tile_get_rank(t1);
    rank_t r2 = tile_get_rank(t2);



    if (is_mixed(s0, s1, s2)) {

        if (is_shifted_1_unordered(r1, r0, r2)) {
            return MIXED_SHIFTED_CHOWS;
        }

        if (r0 == r1 && r1 == r2) {
            return MIXED_TRIPLE_CHOW;
        }

        if ((r0 == 2 && r1 == 5 && r2 == 8) || (r0 == 2 && r1 == 8 && r2 == 5)
            || (r0 == 5 && r1 == 2 && r2 == 8) || (r0 == 5 && r1 == 8 && r2 == 2)
            || (r0 == 8 && r1 == 2 && r2 == 5) || (r0 == 8 && r1 == 5 && r2 == 2)) {
            return MIXED_STRAIGHT;
        }
    }
    else {

        if (t0 + 3 == t1 && t1 + 3 == t2) {
            return PURE_STRAIGHT;
        }

        if (is_shifted_2(t0, t1, t2) || is_shifted_1(t0, t1, t2)) {
            return PURE_SHIFTED_CHOWS;
        }

        if (t0 == t1 && t0 == t2) {
            return PURE_TRIPLE_CHOW;
        }
    }

    return FAN_NONE;
}


static fan_t get_2_chows_fan_unordered(tile_t t0, tile_t t1) {


    if (!is_suit_equal_quick(t0, t1)) {

        if (is_rank_equal_quick(t0, t1)) {
            return MIXED_DOUBLE_CHOW;
        }
    }
    else {

        if (t0 + 3 == t1 || t1 + 3 == t0) {
            return SHORT_STRAIGHT;
        }

        rank_t r0 = tile_get_rank(t0);
        rank_t r1 = tile_get_rank(t1);
        if ((r0 == 2 && r1 == 8) || (r0 == 8 && r1 == 2)) {
            return TWO_TERMINAL_CHOWS;
        }

        if (t0 == t1) {
            return PURE_DOUBLE_CHOW;
        }
    }

    return FAN_NONE;
}


static fan_t get_4_pungs_fan(tile_t t0, tile_t t1, tile_t t2, tile_t t3) {

    if (is_numbered_suit_quick(t0) && t0 + 1 == t1 && t1 + 1 == t2 && t2 + 1 == t3) {
        return FOUR_PURE_SHIFTED_PUNGS;
    }

    if (t0 == TILE_E && t1 == TILE_S && t2 == TILE_W && t3 == TILE_N) {
        return BIG_FOUR_WINDS;
    }

    return FAN_NONE;
}


static fan_t get_3_pungs_fan(tile_t t0, tile_t t1, tile_t t2) {


    if (is_numbered_suit_quick(t0) && is_numbered_suit_quick(t1) && is_numbered_suit_quick(t2)) {
        suit_t s0 = tile_get_suit(t0);
        suit_t s1 = tile_get_suit(t1);
        suit_t s2 = tile_get_suit(t2);

        rank_t r0 = tile_get_rank(t0);
        rank_t r1 = tile_get_rank(t1);
        rank_t r2 = tile_get_rank(t2);

        if (is_mixed(s0, s1, s2)) {

            if (is_shifted_1_unordered(r1, r0, r2)) {
                return MIXED_SHIFTED_PUNGS;
            }

            if (r0 == r1 && r1 == r2) {
                return TRIPLE_PUNG;
            }
        }
        else {

            if (t0 + 1 == t1 && t1 + 1 == t2) {
                return PURE_SHIFTED_PUNGS;
            }
        }
    }
    else {

        if ((t0 == TILE_E && t1 == TILE_S && t2 == TILE_W)
            || (t0 == TILE_E && t1 == TILE_S && t2 == TILE_N)
            || (t0 == TILE_E && t1 == TILE_W && t2 == TILE_N)
            || (t0 == TILE_S && t1 == TILE_W && t2 == TILE_N)) {
            return BIG_THREE_WINDS;
        }

        if (t0 == TILE_C && t1 == TILE_F && t2 == TILE_P) {
            return BIG_THREE_DRAGONS;
        }
    }


    return FAN_NONE;
}


static fan_t get_2_pungs_fan_unordered(tile_t t0, tile_t t1) {

    if (is_numbered_suit_quick(t0) && is_numbered_suit_quick(t1)) {

        if (is_rank_equal_quick(t0, t1)) {
            return DOUBLE_PUNG;
        }
    }
    else {

        if (is_dragons(t0) && is_dragons(t1)) {
            return TWO_DRAGONS_PUNGS;
        }
    }

    return FAN_NONE;
}


static fan_t get_1_pung_fan(tile_t mid_tile) {

    if (is_dragons(mid_tile)) {
        return DRAGON_PUNG;
    }

    if (is_terminal(mid_tile) || is_winds(mid_tile)) {
        return PUNG_OF_TERMINALS_OR_HONORS;
    }

    return FAN_NONE;
}


static fan_t get_1_chow_extra_fan(tile_t tile0, tile_t tile1, tile_t tile2, tile_t tile_extra) {
    fan_t fan0 = get_2_chows_fan_unordered(tile0, tile_extra);
    fan_t fan1 = get_2_chows_fan_unordered(tile1, tile_extra);
    fan_t fan2 = get_2_chows_fan_unordered(tile2, tile_extra);



    if (fan0 == PURE_DOUBLE_CHOW || fan1 == PURE_DOUBLE_CHOW || fan2 == PURE_DOUBLE_CHOW) {
        return PURE_DOUBLE_CHOW;
    }

    if (fan0 == MIXED_DOUBLE_CHOW || fan1 == MIXED_DOUBLE_CHOW || fan2 == MIXED_DOUBLE_CHOW) {
        return MIXED_DOUBLE_CHOW;
    }

    if (fan0 == SHORT_STRAIGHT || fan1 == SHORT_STRAIGHT || fan2 == SHORT_STRAIGHT) {
        return SHORT_STRAIGHT;
    }

    if (fan0 == TWO_TERMINAL_CHOWS || fan1 == TWO_TERMINAL_CHOWS || fan2 == TWO_TERMINAL_CHOWS) {
        return TWO_TERMINAL_CHOWS;
    }

    return FAN_NONE;
}
# 489 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.cpp"
static void exclusionary_rule(const fan_t *all_fans, long fan_cnt, long max_cnt, fan_table_t &fan_table) {

    uint16_t table[4] = { 0 };
    long cnt = 0;
    for (long i = 0; i < fan_cnt; ++i) {
        if (all_fans[i] != FAN_NONE) {
            ++cnt;
            ++table[all_fans[i] - PURE_DOUBLE_CHOW];
        }
    }


    int limit_cnt = 1;

    while (cnt > max_cnt && limit_cnt >= 0) {
        int idx = 4;
        while (cnt > max_cnt && idx-- > 0) {
            while (static_cast<int>(table[idx]) > limit_cnt && cnt > max_cnt) {
                --table[idx];
                --cnt;
            }
        }
        --limit_cnt;
    }

    fan_table[PURE_DOUBLE_CHOW] = table[0];
    fan_table[MIXED_DOUBLE_CHOW] = table[1];
    fan_table[SHORT_STRAIGHT] = table[2];
    fan_table[TWO_TERMINAL_CHOWS] = table[3];
}


static void calculate_4_chows(const tile_t (&mid_tiles)[4], fan_table_t &fan_table) {
    fan_t fan;

    if ((fan = get_4_chows_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
        fan_table[fan] = 1;
        return;
    }



    if ((fan = get_3_chows_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
        fan_table[fan] = 1;

        if ((fan = get_1_chow_extra_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
            fan_table[fan] = 1;
        }
        return;
    }

    else if ((fan = get_3_chows_fan(mid_tiles[0], mid_tiles[1], mid_tiles[3])) != FAN_NONE) {
        fan_table[fan] = 1;

        if ((fan = get_1_chow_extra_fan(mid_tiles[0], mid_tiles[1], mid_tiles[3], mid_tiles[2])) != FAN_NONE) {
            fan_table[fan] = 1;
        }
        return;
    }

    else if ((fan = get_3_chows_fan(mid_tiles[0], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
        fan_table[fan] = 1;

        if ((fan = get_1_chow_extra_fan(mid_tiles[0], mid_tiles[2], mid_tiles[3], mid_tiles[1])) != FAN_NONE) {
            fan_table[fan] = 1;
        }
        return;
    }

    else if ((fan = get_3_chows_fan(mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
        fan_table[fan] = 1;

        if ((fan = get_1_chow_extra_fan(mid_tiles[1], mid_tiles[2], mid_tiles[3], mid_tiles[0])) != FAN_NONE) {
            fan_table[fan] = 1;
        }
        return;
    }


    fan_t all_fans[6] = {
        get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[1]),
        get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[2]),
        get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[3]),
        get_2_chows_fan_unordered(mid_tiles[1], mid_tiles[2]),
        get_2_chows_fan_unordered(mid_tiles[1], mid_tiles[3]),
        get_2_chows_fan_unordered(mid_tiles[2], mid_tiles[3])
    };

    int max_cnt = 3;


    if (all_fans[0] == FAN_NONE && all_fans[1] == FAN_NONE && all_fans[2] == FAN_NONE) {
        --max_cnt;
    }


    if (all_fans[0] == FAN_NONE && all_fans[3] == FAN_NONE && all_fans[4] == FAN_NONE) {
        --max_cnt;
    }


    if (all_fans[1] == FAN_NONE && all_fans[3] == FAN_NONE && all_fans[5] == FAN_NONE) {
        --max_cnt;
    }


    if (all_fans[2] == FAN_NONE && all_fans[4] == FAN_NONE && all_fans[5] == FAN_NONE) {
        --max_cnt;
    }

    if (max_cnt > 0) {
        exclusionary_rule(all_fans, 6, max_cnt, fan_table);
    }
}


static void calculate_3_chows(const tile_t (&mid_tiles)[3], fan_table_t &fan_table) {
    fan_t fan;


    if ((fan = get_3_chows_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
        fan_table[fan] = 1;
        return;
    }


    fan_t all_fans[3] = {
        get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[1]),
        get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[2]),
        get_2_chows_fan_unordered(mid_tiles[1], mid_tiles[2])
    };
    exclusionary_rule(all_fans, 3, 2, fan_table);
}


static void calculate_2_chows_unordered(const tile_t (&mid_tiles)[2], fan_table_t &fan_table) {
    fan_t fan;
    if ((fan = get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[1])) != FAN_NONE) {
        ++fan_table[fan];
    }
}


static void calculate_kongs(const pack_t *pung_packs, intptr_t pung_cnt, fan_table_t &fan_table) {

    int melded_kong_cnt = 0;
    int concealed_kong_cnt = 0;
    int concealed_pung_cnt = 0;
    for (intptr_t i = 0; i < pung_cnt; ++i) {
        if (is_pack_melded(pung_packs[i])) {
            if (pack_get_type(pung_packs[i]) == 3) {
                ++melded_kong_cnt;
            }
        }
        else {
            if (pack_get_type(pung_packs[i]) == 3) {
                ++concealed_kong_cnt;
            }
            else {
                ++concealed_pung_cnt;
            }
        }
    }
# 668 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.cpp"
    int kong_cnt = melded_kong_cnt + concealed_kong_cnt;
    switch (kong_cnt) {
    case 0:
        switch (concealed_pung_cnt) {
        case 2: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
        case 3: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
        case 4: fan_table[FOUR_CONCEALED_PUNGS] = 1; break;
        default: break;
        }
        break;
    case 1:
        if (melded_kong_cnt == 1) {
            fan_table[MELDED_KONG] = 1;
            switch (concealed_pung_cnt) {
            case 2: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
            case 3: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
            default: break;
            }
        }
        else {
            fan_table[CONCEALED_KONG] = 1;
            switch (concealed_pung_cnt) {
            case 1: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
            case 2: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
            case 3: fan_table[FOUR_CONCEALED_PUNGS] = 1; break;
            default: break;
            }
        }
        break;
    case 2:
        switch (concealed_kong_cnt) {
        case 0:
            fan_table[TWO_MELDED_KONGS] = 1;
            switch (concealed_pung_cnt) {
            case 2: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
            default: break;
            }
            break;
        case 1:

            fan_table[CONCEALED_KONG_AND_MELDED_KONG] = 1;




            switch (concealed_pung_cnt) {
            case 1: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
            case 2: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
            default: break;
            }
            break;
        case 2:
            fan_table[TWO_CONCEALED_KONGS] = 1;
            switch (concealed_pung_cnt) {
            case 1: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
            case 2: fan_table[FOUR_CONCEALED_PUNGS] = 1; break;
            default: break;
            }
            break;
        default:
            break;
        }
        break;
    case 3:
        fan_table[THREE_KONGS] = 1;
        switch (concealed_kong_cnt) {
        case 0:
            break;
        case 1:
            if (concealed_pung_cnt > 0) {
                fan_table[TWO_CONCEALED_PUNGS] = 1;
            }
            break;
        case 2:
            if (concealed_pung_cnt == 0) {
                fan_table[TWO_CONCEALED_PUNGS] = 1;
            }
            else {
                fan_table[THREE_CONCEALED_PUNGS] = 1;
            }
            break;
        case 3:
            if (concealed_pung_cnt == 0) {
                fan_table[THREE_CONCEALED_PUNGS] = 1;
            }
            else {
                fan_table[FOUR_CONCEALED_PUNGS] = 1;
            }
            break;
        default:
            break;
        }
        break;
    case 4:
        fan_table[FOUR_KONGS] = 1;
        switch (concealed_kong_cnt) {
        case 2: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
        case 3: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
        case 4: fan_table[FOUR_CONCEALED_PUNGS] = 1; break;
        default: break;
        }
        break;
    default:
        __builtin_unreachable();
        break;
    }


    if (pung_cnt == 4) {
        if (fan_table[FOUR_KONGS] == 0 && fan_table[FOUR_CONCEALED_PUNGS] == 0) {
            fan_table[ALL_PUNGS] = 1;
        }
    }


    for (intptr_t i = 0; i < pung_cnt; ++i) {
        fan_t fan = get_1_pung_fan(pack_get_tile(pung_packs[i]));
        if (fan != FAN_NONE) {
            ++fan_table[fan];
        }
    }
}


static void calculate_4_pungs(const tile_t (&mid_tiles)[4], fan_table_t &fan_table) {
    fan_t fan;

    if ((fan = get_4_pungs_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
        fan_table[fan] = 1;
        return;
    }


    bool _3_pungs_has_fan = false;
    int free_pack_idx = -1;

    if ((fan = get_3_pungs_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
        fan_table[fan] = 1;
        free_pack_idx = 3;
        _3_pungs_has_fan = true;
    }

    else if ((fan = get_3_pungs_fan(mid_tiles[0], mid_tiles[1], mid_tiles[3])) != FAN_NONE) {
        fan_table[fan] = 1;
        free_pack_idx = 2;
        _3_pungs_has_fan = true;
    }

    else if ((fan = get_3_pungs_fan(mid_tiles[0], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
        fan_table[fan] = 1;
        free_pack_idx = 1;
        _3_pungs_has_fan = true;
    }

    else if ((fan = get_3_pungs_fan(mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
        fan_table[fan] = 1;
        free_pack_idx = 0;
        _3_pungs_has_fan = true;
    }


    if (_3_pungs_has_fan) {
        for (int i = 0; i < 4; ++i) {
            if (i == free_pack_idx) {
                continue;
            }

            if ((fan = get_2_pungs_fan_unordered(mid_tiles[i], mid_tiles[free_pack_idx])) != FAN_NONE) {
                ++fan_table[fan];
                break;
            }
        }
        return;
    }


    if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[1])) != FAN_NONE) {
        ++fan_table[fan];
    }
    if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[2])) != FAN_NONE) {
        ++fan_table[fan];
    }
    if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[3])) != FAN_NONE) {
        ++fan_table[fan];
    }
    if ((fan = get_2_pungs_fan_unordered(mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
        ++fan_table[fan];
    }
    if ((fan = get_2_pungs_fan_unordered(mid_tiles[1], mid_tiles[3])) != FAN_NONE) {
        ++fan_table[fan];
    }
    if ((fan = get_2_pungs_fan_unordered(mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
        ++fan_table[fan];
    }
}


static void calculate_3_pungs(const tile_t (&mid_tiles)[3], fan_table_t &fan_table) {
    fan_t fan;


    if ((fan = get_3_pungs_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
        fan_table[fan] = 1;
        return;
    }


    if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[1])) != FAN_NONE) {
        ++fan_table[fan];
    }
    if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[2])) != FAN_NONE) {
        ++fan_table[fan];
    }
    if ((fan = get_2_pungs_fan_unordered(mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
        ++fan_table[fan];
    }
}


static void calculate_2_pungs_unordered(const tile_t (&mid_tiles)[2], fan_table_t &fan_table) {
    fan_t fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[1]);
    if (fan != FAN_NONE) {
        ++fan_table[fan];
    }
}


static bool is_nine_gates(const tile_t *tiles) {

    tile_table_t cnt_table;
    map_tiles(tiles, 13, &cnt_table);


    return (cnt_table[0x11] == 3 && cnt_table[0x19] == 3 && std::all_of(cnt_table + 0x12, cnt_table + 0x19, [](int n) { return n == 1; }))
        || (cnt_table[0x21] == 3 && cnt_table[0x29] == 3 && std::all_of(cnt_table + 0x22, cnt_table + 0x29, [](int n) { return n == 1; }))
        || (cnt_table[0x31] == 3 && cnt_table[0x39] == 3 && std::all_of(cnt_table + 0x32, cnt_table + 0x39, [](int n) { return n == 1; }));
}


static bool is_pure_terminal_chows(const pack_t (&chow_packs)[4], pack_t pair_pack) {
    if (tile_get_rank(pack_get_tile(pair_pack)) != 5) {
        return false;
    }

    int _123_cnt = 0, _789_cnt = 0;
    suit_t pair_suit = tile_get_suit(pack_get_tile(pair_pack));
    for (int i = 0; i < 4; ++i) {
        suit_t suit = tile_get_suit(pack_get_tile(chow_packs[i]));
        if (suit != pair_suit) {
            return false;
        }
        rank_t rank = tile_get_rank(pack_get_tile(chow_packs[i]));
        switch (rank) {
        case 2: ++_123_cnt; break;
        case 8: ++_789_cnt; break;
        default: return false;
        }
    }
    return (_123_cnt == 2 && _789_cnt == 2);
}


static bool is_three_suited_terminal_chows(const pack_t (&chow_packs)[4], pack_t pair_pack) {
    if (tile_get_rank(pack_get_tile(pair_pack)) != 5) {
        return false;
    }

    int _123_suit_table[4] = { 0 };
    int _789_suit_table[4] = { 0 };
    suit_t pair_suit = tile_get_suit(pack_get_tile(pair_pack));
    for (int i = 0; i < 4; ++i) {
        suit_t suit = tile_get_suit(pack_get_tile(chow_packs[i]));
        if (suit == pair_suit) {
            return false;
        }
        rank_t rank = tile_get_rank(pack_get_tile(chow_packs[i]));
        switch (rank) {
        case 2: ++_123_suit_table[suit]; break;
        case 8: ++_789_suit_table[suit]; break;
        default: return false;
        }
    }


    switch (pair_suit) {
    case 1: return (_123_suit_table[2] && _123_suit_table[3] && _789_suit_table[2] && _789_suit_table[3]);
    case 2: return (_123_suit_table[1] && _123_suit_table[3] && _789_suit_table[1] && _789_suit_table[3]);
    case 3: return (_123_suit_table[1] && _123_suit_table[2] && _789_suit_table[1] && _789_suit_table[2]);
    default: return false;
    }
}


static void adjust_by_self_drawn(const pack_t (&packs)[5], intptr_t fixed_cnt, bool self_drawn, fan_table_t &fan_table) {
    ptrdiff_t melded_cnt = std::count_if(&packs[0], &packs[fixed_cnt], &is_pack_melded);

    switch (melded_cnt) {
    case 0:
        fan_table[self_drawn ? FULLY_CONCEALED_HAND : CONCEALED_HAND] = 1;
        break;
    case 4:

        fan_table[self_drawn ? SELF_DRAWN : MELDED_HAND] = 1;
        break;
    default:
        if (self_drawn) {
            fan_table[SELF_DRAWN] = 1;
        }
        break;
    }
}


static void adjust_by_pair_tile(tile_t pair_tile, intptr_t chow_cnt, fan_table_t &fan_table) {
    if (chow_cnt == 4) {
        if (is_numbered_suit_quick(pair_tile)) {
            fan_table[ALL_CHOWS] = 1;
        }
        return;
    }


    if (fan_table[TWO_DRAGONS_PUNGS]) {
        if (is_dragons(pair_tile)) {
            fan_table[LITTLE_THREE_DRAGONS] = 1;
            fan_table[TWO_DRAGONS_PUNGS] = 0;
        }
        return;
    }

    if (fan_table[BIG_THREE_WINDS]) {
        if (is_winds(pair_tile)) {
            fan_table[LITTLE_FOUR_WINDS] = 1;
            fan_table[BIG_THREE_WINDS] = 0;
        }
        return;
    }
}


static void adjust_by_suits(const tile_t *tiles, intptr_t tile_cnt, fan_table_t &fan_table) {

    uint8_t suit_flag = 0;
    for (intptr_t i = 0; i < tile_cnt; ++i) {
        suit_flag |= (1 << tile_get_suit(tiles[i]));
    }


    if (!(suit_flag & 0xF1U)) {
        fan_table[NO_HONORS] = 1;
    }


    if (!(suit_flag & 0xE3U)) {
        ++fan_table[ONE_VOIDED_SUIT];
    }

    if (!(suit_flag & 0xE5U)) {
        ++fan_table[ONE_VOIDED_SUIT];
    }

    if (!(suit_flag & 0xE9U)) {
        ++fan_table[ONE_VOIDED_SUIT];
    }


    if (fan_table[ONE_VOIDED_SUIT] == 2) {
        fan_table[ONE_VOIDED_SUIT] = 0;
        fan_table[suit_flag & 0xF1U ? HALF_FLUSH : FULL_FLUSH] = 1;
    }


    if (suit_flag == 0x1EU) {
        if (std::any_of(tiles, tiles + tile_cnt, &is_winds)
            && std::any_of(tiles, tiles + tile_cnt, &is_dragons)) {
            fan_table[ALL_TYPES] = 1;
        }
    }
}


static void adjust_by_rank_range(const tile_t *tiles, intptr_t tile_cnt, fan_table_t &fan_table) {







    uint16_t rank_flag = 0;
    for (intptr_t i = 0; i < tile_cnt; ++i) {
        if (!is_numbered_suit_quick(tiles[i])) {
            return;
        }
        rank_flag |= (1 << tile_get_rank(tiles[i]));
    }



    if (!(rank_flag & 0xFFE1)) {

        fan_table[rank_flag & 0x0010 ? LOWER_FOUR : LOWER_TILES] = 1;
        return;
    }


    if (!(rank_flag & 0xFC3F)) {

        fan_table[rank_flag & 0x0040 ? UPPER_FOUR : UPPER_TILES] = 1;
        return;
    }


    if (!(rank_flag & 0xFF8F)) {

        fan_table[MIDDLE_TILES] = 1;
    }
}


static void adjust_by_packs_traits(const pack_t (&packs)[5], fan_table_t &fan_table) {

    int terminal_pack = 0;
    int honor_pack = 0;
    int _5_pack = 0;
    int even_pack = 0;
    for (int i = 0; i < 5; ++i) {
        tile_t tile = pack_get_tile(packs[i]);
        if (is_numbered_suit_quick(tile)) {
            rank_t rank = tile_get_rank(tile);
            if (pack_get_type(packs[i]) == 1) {
                switch (rank) {
                case 2: case 8: ++terminal_pack; break;
                case 4: case 5: case 6: ++_5_pack; break;
                default: break;
                }
            }
            else {
                switch (rank) {
                case 1: case 9: ++terminal_pack; break;
                case 5: ++_5_pack; break;
                case 2: case 4: case 6: case 8: ++even_pack; break;
                default: break;
                }
            }
        }
        else {
            ++honor_pack;
        }
    }


    if (terminal_pack + honor_pack == 5) {
        fan_table[OUTSIDE_HAND] = 1;
        return;
    }

    if (_5_pack == 5) {
        fan_table[ALL_FIVE] = 1;
        return;
    }

    if (even_pack == 5) {
        fan_table[ALL_EVEN_PUNGS] = 1;
    }
}


static void adjust_by_tiles_traits(const tile_t *tiles, intptr_t tile_cnt, fan_table_t &fan_table) {

    if (std::none_of(tiles, tiles + tile_cnt, &is_terminal_or_honor)) {
        fan_table[ALL_SIMPLES] = 1;
    }


    if (std::all_of(tiles, tiles + tile_cnt, &is_reversible)) {
        fan_table[REVERSIBLE_TILES] = 1;
    }
# 1154 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.cpp"
    if (std::all_of(tiles, tiles + tile_cnt, &is_green)) {
        fan_table[ALL_GREEN] = 1;
    }


    if (fan_table[ALL_SIMPLES] != 0) {
        return;
    }


    if (std::all_of(tiles, tiles + tile_cnt, &is_honor)) {
        fan_table[ALL_HONORS] = 1;
        return;
    }

    if (std::all_of(tiles, tiles + tile_cnt, &is_terminal)) {
        fan_table[ALL_TERMINALS] = 1;
        return;
    }

    if (std::all_of(tiles, tiles + tile_cnt, &is_terminal_or_honor)) {
        fan_table[ALL_TERMINALS_AND_HONORS] = 1;
    }
}


static void adjust_by_tiles_hog(const tile_t *tiles, intptr_t tile_cnt, fan_table_t &fan_table) {
    intptr_t kong_cnt = tile_cnt - 14;
    tile_table_t cnt_table;
    map_tiles(tiles, tile_cnt, &cnt_table);

    intptr_t _4_cnt = std::count(std::begin(cnt_table), std::end(cnt_table), 4);
    fan_table[TILE_HOG] = static_cast<uint8_t>(_4_cnt - kong_cnt);
}


static void adjust_by_waiting_form(const pack_t *concealed_packs, intptr_t pack_cnt, const tile_t *standing_tiles, intptr_t standing_cnt,
    tile_t win_tile, fan_table_t &fan_table) {

    if (fan_table[MELDED_HAND] || fan_table[FOUR_KONGS]) {
        return;
    }

    useful_table_t waiting_table;
    if (!is_basic_form_wait(standing_tiles, standing_cnt, &waiting_table)) {
        return;
    }

    if (pack_cnt == 5) {

        useful_table_t temp_table;
        if (is_seven_pairs_wait(standing_tiles, standing_cnt, &temp_table)) {

            std::transform(std::begin(temp_table), std::end(temp_table), std::begin(waiting_table),
                std::begin(waiting_table), [](bool w, bool t) { return w || t; });
        }
    }


    if (1 != std::count(std::begin(waiting_table), std::end(waiting_table), true)) {
        return;
    }



    uint8_t pos_flag = 0;

    for (intptr_t i = 0; i < pack_cnt; ++i) {
        switch (pack_get_type(concealed_packs[i])) {
        case 1: {
            tile_t mid_tile = pack_get_tile(concealed_packs[i]);
            if (mid_tile == win_tile) {
                pos_flag |= 0x02U;
            }
            else if (mid_tile + 1 == win_tile || mid_tile - 1 == win_tile) {
                pos_flag |= 0x01U;
            }
            break;
        }
        case 4: {
            tile_t mid_tile = pack_get_tile(concealed_packs[i]);
            if (mid_tile == win_tile) {
                pos_flag |= 0x04U;
            }
            break;
        }
        default:
            break;
        }
    }


    if (pos_flag & 0x01U) {
        fan_table[EDGE_WAIT] = 1;
    }
    else if (pos_flag & 0x02U) {
        fan_table[CLOSED_WAIT] = 1;
    }
    else if (pos_flag & 0x04U) {
        fan_table[SINGLE_WAIT] = 1;
    }
}


static void adjust_fan_table(fan_table_t &fan_table) {

    if (fan_table[BIG_FOUR_WINDS]) {
        fan_table[BIG_THREE_WINDS] = 0;
        fan_table[ALL_PUNGS] = 0;
        fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
    }

    if (fan_table[BIG_THREE_DRAGONS]) {
        fan_table[TWO_DRAGONS_PUNGS] = 0;
        fan_table[DRAGON_PUNG] = 0;



    }

    if (fan_table[ALL_GREEN]) {
        fan_table[HALF_FLUSH] = 0;
        fan_table[ONE_VOIDED_SUIT] = 0;
    }

    if (fan_table[NINE_GATES]) {
        fan_table[FULL_FLUSH] = 0;
        fan_table[CONCEALED_HAND] = 0;
        --fan_table[PUNG_OF_TERMINALS_OR_HONORS];
        fan_table[ONE_VOIDED_SUIT] = 0;
        fan_table[NO_HONORS] = 0;
        if (fan_table[FULLY_CONCEALED_HAND]) {
            fan_table[FULLY_CONCEALED_HAND] = 0;
            fan_table[SELF_DRAWN] = 1;
        }
    }

    if (fan_table[FOUR_KONGS]) {
        fan_table[SINGLE_WAIT] = 0;
    }

    if (fan_table[SEVEN_SHIFTED_PAIRS]) {
        fan_table[SEVEN_PAIRS] = 0;
        fan_table[FULL_FLUSH] = 0;
        fan_table[CONCEALED_HAND] = 0;
        fan_table[ONE_VOIDED_SUIT] = 0;
        fan_table[NO_HONORS] = 0;
    }

    if (fan_table[THIRTEEN_ORPHANS]) {
        fan_table[ALL_TYPES] = 0;
        fan_table[CONCEALED_HAND] = 0;
        fan_table[SINGLE_WAIT] = 0;
    }


    if (fan_table[ALL_TERMINALS]) {
        fan_table[ALL_TERMINALS_AND_HONORS] = 0;
        fan_table[ALL_PUNGS] = 0;
        fan_table[OUTSIDE_HAND] = 0;
        fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
        fan_table[NO_HONORS] = 0;
        fan_table[DOUBLE_PUNG] = 0;




    }


    if (fan_table[LITTLE_FOUR_WINDS]) {
        fan_table[BIG_THREE_WINDS] = 0;



        fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
    }


    if (fan_table[LITTLE_THREE_DRAGONS]) {
        fan_table[TWO_DRAGONS_PUNGS] = 0;
        fan_table[DRAGON_PUNG] = 0;



    }


    if (fan_table[ALL_HONORS]) {
        fan_table[ALL_TERMINALS_AND_HONORS] = 0;
        fan_table[ALL_PUNGS] = 0;
        fan_table[OUTSIDE_HAND] = 0;
        fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
        fan_table[ONE_VOIDED_SUIT] = 0;
    }

    if (fan_table[FOUR_CONCEALED_PUNGS]) {
        fan_table[ALL_PUNGS] = 0;
        fan_table[CONCEALED_HAND] = 0;
        if (fan_table[FULLY_CONCEALED_HAND]) {
            fan_table[FULLY_CONCEALED_HAND] = 0;
            fan_table[SELF_DRAWN] = 1;
        }
    }

    if (fan_table[PURE_TERMINAL_CHOWS]) {
        fan_table[SEVEN_PAIRS] = 0;
        fan_table[FULL_FLUSH] = 0;
        fan_table[ALL_CHOWS] = 0;
        fan_table[PURE_DOUBLE_CHOW] = 0;
        fan_table[TWO_TERMINAL_CHOWS] = 0;
        fan_table[ONE_VOIDED_SUIT] = 0;
        fan_table[NO_HONORS] = 0;
    }


    if (fan_table[QUADRUPLE_CHOW]) {
        fan_table[PURE_SHIFTED_PUNGS] = 0;
        fan_table[TILE_HOG] = 0;
        fan_table[PURE_DOUBLE_CHOW] = 0;



    }

    if (fan_table[FOUR_PURE_SHIFTED_PUNGS]) {
        fan_table[PURE_TRIPLE_CHOW] = 0;
        fan_table[ALL_PUNGS] = 0;



    }


    if (fan_table[FOUR_PURE_SHIFTED_CHOWS]) {
        fan_table[PURE_SHIFTED_CHOWS] = 0;
        fan_table[TWO_TERMINAL_CHOWS] = 0;
        fan_table[SHORT_STRAIGHT] = 0;



    }


    if (fan_table[ALL_TERMINALS_AND_HONORS]) {
        fan_table[ALL_PUNGS] = 0;
        fan_table[OUTSIDE_HAND] = 0;
        fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
    }


    if (fan_table[SEVEN_PAIRS]) {
        fan_table[CONCEALED_HAND] = 0;
        fan_table[SINGLE_WAIT] = 0;
    }

    if (fan_table[GREATER_HONORS_AND_KNITTED_TILES]) {
        fan_table[ALL_TYPES] = 0;
        fan_table[CONCEALED_HAND] = 0;
    }

    if (fan_table[ALL_EVEN_PUNGS]) {
        fan_table[ALL_PUNGS] = 0;
        fan_table[ALL_SIMPLES] = 0;
        fan_table[NO_HONORS] = 0;
    }

    if (fan_table[FULL_FLUSH]) {
        fan_table[ONE_VOIDED_SUIT] = 0;
        fan_table[NO_HONORS] = 0;
    }

    if (fan_table[PURE_TRIPLE_CHOW]) {
        fan_table[PURE_SHIFTED_PUNGS] = 0;
        fan_table[PURE_DOUBLE_CHOW] = 0;
    }

    if (fan_table[PURE_SHIFTED_PUNGS]) {
        fan_table[PURE_TRIPLE_CHOW] = 0;
    }

    if (fan_table[UPPER_TILES]) {
        fan_table[UPPER_FOUR] = 0;
        fan_table[NO_HONORS] = 0;
    }

    if (fan_table[MIDDLE_TILES]) {
        fan_table[ALL_SIMPLES] = 0;
        fan_table[NO_HONORS] = 0;
    }

    if (fan_table[LOWER_TILES]) {
        fan_table[LOWER_FOUR] = 0;
        fan_table[NO_HONORS] = 0;
    }


    if (fan_table[THREE_SUITED_TERMINAL_CHOWS]) {
        fan_table[ALL_CHOWS] = 0;
        fan_table[NO_HONORS] = 0;
        fan_table[MIXED_DOUBLE_CHOW] = 0;
        fan_table[TWO_TERMINAL_CHOWS] = 0;
    }

    if (fan_table[ALL_FIVE]) {
        fan_table[ALL_SIMPLES] = 0;
        fan_table[NO_HONORS] = 0;
    }


    if (fan_table[LESSER_HONORS_AND_KNITTED_TILES]) {
        fan_table[ALL_TYPES] = 0;
        fan_table[CONCEALED_HAND] = 0;
    }

    if (fan_table[UPPER_FOUR]) {
        fan_table[NO_HONORS] = 0;
    }

    if (fan_table[LOWER_FOUR]) {
        fan_table[NO_HONORS] = 0;
    }

    if (fan_table[BIG_THREE_WINDS]) {

        if (!fan_table[ALL_HONORS] && !fan_table[ALL_TERMINALS_AND_HONORS]) {
            assert(fan_table[PUNG_OF_TERMINALS_OR_HONORS] >= 3);
            fan_table[PUNG_OF_TERMINALS_OR_HONORS] -= 3;
        }



    }


    if (fan_table[REVERSIBLE_TILES]) {
        fan_table[ONE_VOIDED_SUIT] = 0;
    }

    if (fan_table[LAST_TILE_DRAW]) {
        fan_table[SELF_DRAWN] = 0;
    }

    if (fan_table[OUT_WITH_REPLACEMENT_TILE]) {
        fan_table[SELF_DRAWN] = 0;
    }

    if (fan_table[ROBBING_THE_KONG]) {
        fan_table[LAST_TILE] = 0;
    }

    if (fan_table[TWO_CONCEALED_KONGS]) {
        fan_table[CONCEALED_KONG] = 0;
    }


    if (fan_table[HALF_FLUSH]) {
        fan_table[ONE_VOIDED_SUIT] = 0;
    }

    if (fan_table[MELDED_HAND]) {
        fan_table[SINGLE_WAIT] = 0;
    }

    if (fan_table[TWO_DRAGONS_PUNGS]) {
        fan_table[DRAGON_PUNG] = 0;
    }


    if (fan_table[FULLY_CONCEALED_HAND]) {
        fan_table[SELF_DRAWN] = 0;
    }

    if (fan_table[TWO_MELDED_KONGS]) {
        fan_table[MELDED_KONG] = 0;
    }


    if (fan_table[ALL_CHOWS]) {
        fan_table[NO_HONORS] = 0;
    }

    if (fan_table[ALL_SIMPLES]) {
        fan_table[NO_HONORS] = 0;
    }
}



static void adjust_by_winds(tile_t tile, wind_t prevalent_wind, wind_t seat_wind, fan_table_t &fan_table) {

    bool is_deducted = (fan_table[BIG_THREE_WINDS] || fan_table[ALL_TERMINALS_AND_HONORS] || fan_table[ALL_HONORS] || fan_table[LITTLE_FOUR_WINDS]);

    rank_t delta = tile - TILE_E;
    if (delta == static_cast<int>(prevalent_wind) - static_cast<int>(wind_t::EAST)) {
        fan_table[PREVALENT_WIND] = 1;
        if (!is_deducted) {
            --fan_table[PUNG_OF_TERMINALS_OR_HONORS];
        }
    }
    if (delta == static_cast<int>(seat_wind) - static_cast<int>(wind_t::EAST)) {
        fan_table[SEAT_WIND] = 1;

        if (seat_wind != prevalent_wind && !is_deducted) {
            --fan_table[PUNG_OF_TERMINALS_OR_HONORS];
        }
    }
}


static void adjust_by_win_flag(win_flag_t win_flag, fan_table_t &fan_table) {
    if (win_flag & 2) {
        fan_table[LAST_TILE] = 1;
    }
    if (win_flag & 8) {
        fan_table[win_flag & 1 ? LAST_TILE_DRAW : LAST_TILE_CLAIM] = 1;
    }
    if (win_flag & 4) {
        fan_table[win_flag & 1 ? OUT_WITH_REPLACEMENT_TILE : ROBBING_THE_KONG] = 1;
    }
    if (win_flag & 1) {
        fan_table[SELF_DRAWN] = 1;
    }
}


static void calculate_basic_form_fan(const pack_t (&packs)[5], const calculate_param_t *calculate_param, win_flag_t win_flag, fan_table_t &fan_table) {
    pack_t pair_pack = 0;
    pack_t chow_packs[4];
    pack_t pung_packs[4];
    intptr_t chow_cnt = 0;
    intptr_t pung_cnt = 0;
    for (int i = 0; i < 5; ++i) {
        switch (pack_get_type(packs[i])) {
        case 1: chow_packs[chow_cnt++] = packs[i]; break;
        case 2:
        case 3: pung_packs[pung_cnt++] = packs[i]; break;
        case 4: pair_pack = packs[i]; break;
        default: __builtin_unreachable(); return;
        }
    }

    if (pair_pack == 0 || chow_cnt + pung_cnt != 4) {
        return;
    }

    tile_t win_tile = calculate_param->win_tile;


    adjust_by_win_flag(win_flag, fan_table);


    if ((win_flag & 1) == 0) {

        if (std::none_of(chow_packs, chow_packs + chow_cnt, [win_tile](pack_t chow_pack) {
            tile_t tile = pack_get_tile(chow_pack);
            return !is_pack_melded(chow_pack)
                && (tile - 1 == win_tile || tile == win_tile || tile + 1 == win_tile);
        })) {
            for (intptr_t i = 0; i < pung_cnt; ++i) {
                if (pack_get_tile(pung_packs[i]) == win_tile && !is_pack_melded(pung_packs[i])) {
                    pung_packs[i] |= (1 << 12);
                }
            }
        }
    }

    if (pung_cnt > 0) {
        calculate_kongs(pung_packs, pung_cnt, fan_table);
    }

    switch (chow_cnt) {
    case 4: {

        if (is_three_suited_terminal_chows(chow_packs, pair_pack)) {
            fan_table[THREE_SUITED_TERMINAL_CHOWS] = 1;
            break;
        }
        if (is_pure_terminal_chows(chow_packs, pair_pack)) {
            fan_table[PURE_TERMINAL_CHOWS] = 1;
            break;
        }

        tile_t mid_tiles[4];
        mid_tiles[0] = pack_get_tile(chow_packs[0]);
        mid_tiles[1] = pack_get_tile(chow_packs[1]);
        mid_tiles[2] = pack_get_tile(chow_packs[2]);
        mid_tiles[3] = pack_get_tile(chow_packs[3]);
        std::sort(std::begin(mid_tiles), std::end(mid_tiles));

        calculate_4_chows(mid_tiles, fan_table);
        break;
    }
    case 3: {
        tile_t mid_tiles[3];
        mid_tiles[0] = pack_get_tile(chow_packs[0]);
        mid_tiles[1] = pack_get_tile(chow_packs[1]);
        mid_tiles[2] = pack_get_tile(chow_packs[2]);
        std::sort(std::begin(mid_tiles), std::end(mid_tiles));

        calculate_3_chows(mid_tiles, fan_table);
        break;
    }
    case 2: {
        tile_t mid_tiles_chow[2];
        mid_tiles_chow[0] = pack_get_tile(chow_packs[0]);
        mid_tiles_chow[1] = pack_get_tile(chow_packs[1]);

        tile_t mid_tiles_pung[2];
        mid_tiles_pung[0] = pack_get_tile(pung_packs[0]);
        mid_tiles_pung[1] = pack_get_tile(pung_packs[1]);

        calculate_2_chows_unordered(mid_tiles_chow, fan_table);
        calculate_2_pungs_unordered(mid_tiles_pung, fan_table);
        break;
    }
    case 1: {
        tile_t mid_tiles[3];
        mid_tiles[0] = pack_get_tile(pung_packs[0]);
        mid_tiles[1] = pack_get_tile(pung_packs[1]);
        mid_tiles[2] = pack_get_tile(pung_packs[2]);
        std::sort(std::begin(mid_tiles), std::end(mid_tiles));

        calculate_3_pungs(mid_tiles, fan_table);
        break;
    }
    case 0: {
        tile_t mid_tiles[4];
        mid_tiles[0] = pack_get_tile(pung_packs[0]);
        mid_tiles[1] = pack_get_tile(pung_packs[1]);
        mid_tiles[2] = pack_get_tile(pung_packs[2]);
        mid_tiles[3] = pack_get_tile(pung_packs[3]);
        std::sort(std::begin(mid_tiles), std::end(mid_tiles));

        calculate_4_pungs(mid_tiles, fan_table);
        break;
    }
    default:
        __builtin_unreachable();
        break;
    }

    intptr_t fixed_cnt = calculate_param->hand_tiles.pack_count;
    const tile_t *standing_tiles = calculate_param->hand_tiles.standing_tiles;
    intptr_t standing_cnt = calculate_param->hand_tiles.tile_count;
    wind_t prevalent_wind = calculate_param->prevalent_wind;
    wind_t seat_wind = calculate_param->seat_wind;

    bool heaven_win = (win_flag & (16 | 1)) == (16 | 1);


    if (!heaven_win && standing_cnt == 13) {
        if (is_nine_gates(standing_tiles)) {
            fan_table[NINE_GATES] = 1;
        }
    }


    adjust_by_self_drawn(packs, fixed_cnt, (win_flag & 1) != 0, fan_table);

    adjust_by_pair_tile(pack_get_tile(pair_pack), chow_cnt, fan_table);

    adjust_by_packs_traits(packs, fan_table);

    tile_t tiles[18];
    memcpy(tiles, standing_tiles, standing_cnt * sizeof(tile_t));
    intptr_t tile_cnt = packs_to_tiles(packs, fixed_cnt, &tiles[standing_cnt], 18 - standing_cnt);
    tile_cnt += standing_cnt;
    tiles[tile_cnt++] = win_tile;


    adjust_by_suits(tiles, tile_cnt, fan_table);

    adjust_by_tiles_traits(tiles, tile_cnt, fan_table);

    adjust_by_rank_range(tiles, tile_cnt, fan_table);

    adjust_by_tiles_hog(tiles, tile_cnt, fan_table);

    if (!heaven_win) {

        adjust_by_waiting_form(packs + fixed_cnt, 5 - fixed_cnt, standing_tiles, standing_cnt, win_tile, fan_table);
    }


    adjust_fan_table(fan_table);


    if (fan_table[BIG_FOUR_WINDS] == 0) {
        for (intptr_t i = 0; i < pung_cnt; ++i) {
            tile_t tile = pack_get_tile(pung_packs[i]);
            if (is_winds(tile)) {
                adjust_by_winds(tile, prevalent_wind, seat_wind, fan_table);
            }
        }
    }


    if (std::all_of(std::begin(fan_table), std::end(fan_table), [](uint16_t p) { return p == 0; })) {
        fan_table[CHICKEN_HAND] = 1;
    }
}


static bool calculate_knitted_straight_fan(const calculate_param_t *calculate_param, win_flag_t win_flag, fan_table_t &fan_table) {
    const hand_tiles_t *hand_tiles = &calculate_param->hand_tiles;
    tile_t win_tile = calculate_param->win_tile;
    wind_t prevalent_wind = calculate_param->prevalent_wind;
    wind_t seat_wind = calculate_param->seat_wind;

    intptr_t fixed_cnt = hand_tiles->pack_count;
    if (fixed_cnt > 1) {
        return false;
    }

    const pack_t *fixed_packs = hand_tiles->fixed_packs;
    intptr_t standing_cnt = hand_tiles->tile_count;


    tile_table_t cnt_table;
    map_tiles(hand_tiles->standing_tiles, standing_cnt, &cnt_table);
    ++cnt_table[win_tile];


    const tile_t (*matched_seq)[9] = std::find_if(&standard_knitted_straight[0], &standard_knitted_straight[6],
        [&cnt_table](const tile_t (&seq)[9]) {
        return std::all_of(std::begin(seq), std::end(seq), [&cnt_table](tile_t t) { return cnt_table[t] > 0; });
    });

    if (matched_seq == &standard_knitted_straight[6]) {
        return false;
    }


    std::for_each(std::begin(*matched_seq), std::end(*matched_seq), [&cnt_table](tile_t t) { --cnt_table[t]; });


    division_result_t result;
    result.count = 0;
    division_t work_division;
    memset(&work_division, 0, sizeof(work_division));





    if (fixed_cnt == 1) {
        work_division.packs[3] = fixed_packs[0];
    }
    divide_recursively(cnt_table, fixed_cnt + 3, 0, &work_division, &result);
    if (result.count != 1) {
        return false;
    }

    const pack_t *packs = result.divisions[0].packs;


    fan_table[KNITTED_STRAIGHT] = 1;
    if (pack_get_type(packs[3]) == 1) {
        if (is_numbered_suit_quick(pack_get_tile(packs[4]))) {
            fan_table[ALL_CHOWS] = 1;
        }
    }
    else {
        calculate_kongs(&packs[3], 1, fan_table);
    }

    adjust_by_win_flag(win_flag, fan_table);

    if (fixed_cnt == 0 || (pack_get_type(packs[3]) == 3 && !is_pack_melded(packs[3]))) {
        if (win_flag & 1) {
            fan_table[FULLY_CONCEALED_HAND] = 1;
        }
        else {
            fan_table[CONCEALED_HAND] = 1;
        }
    }


    tile_t tiles[15];
    memcpy(tiles, matched_seq, sizeof(*matched_seq));
    intptr_t tile_cnt = packs_to_tiles(&packs[3], 2, tiles + 9, 6);
    tile_cnt += 9;


    adjust_by_suits(tiles, tile_cnt, fan_table);


    adjust_by_tiles_hog(tiles, tile_cnt, fan_table);


    if (std::none_of(std::begin(*matched_seq), std::end(*matched_seq), [win_tile](tile_t t) { return t == win_tile; })) {
        if (fixed_cnt == 0) {

            --cnt_table[win_tile];
            tile_t temp[4];
            intptr_t cnt = table_to_tiles(cnt_table, temp, 4);


            adjust_by_waiting_form(packs + 3, 2, temp, cnt, win_tile, fan_table);
        }
        else {

            fan_table[SINGLE_WAIT] = 1;
        }
    }


    adjust_fan_table(fan_table);


    tile_t tile = pack_get_tile(packs[3]);
    if (is_winds(tile)) {
        adjust_by_winds(tile, prevalent_wind, seat_wind, fan_table);
    }

    return true;
}


static __inline__ __attribute__((__always_inline__)) bool is_thirteen_orphans(const tile_t (&tiles)[14]) {
    return std::all_of(std::begin(tiles), std::end(tiles), &is_terminal_or_honor)
        && std::includes(std::begin(tiles), std::end(tiles),
        std::begin(standard_thirteen_orphans), std::end(standard_thirteen_orphans));
}


static bool calculate_honors_and_knitted_tiles(const tile_t (&standing_tiles)[14], fan_table_t &fan_table) {
    const tile_t *honor_begin = std::find_if(std::begin(standing_tiles), std::end(standing_tiles), &is_honor);
    int numbered_cnt = static_cast<int>(honor_begin - standing_tiles);

    if (numbered_cnt > 9 || numbered_cnt < 7) {
        return false;
    }


    if (std::none_of(&standard_knitted_straight[0], &standard_knitted_straight[6],
        [&standing_tiles, honor_begin](const tile_t (&seq)[9]) {
        return std::includes(std::begin(seq), std::end(seq), std::begin(standing_tiles), honor_begin);
    })) {
        return false;
    }

    if (numbered_cnt == 7 && std::equal(std::begin(standard_thirteen_orphans) + 6, std::end(standard_thirteen_orphans), standing_tiles + 7)) {

        fan_table[GREATER_HONORS_AND_KNITTED_TILES] = 1;
        return true;
    }
    else if (std::includes(std::begin(standard_thirteen_orphans) + 6, std::end(standard_thirteen_orphans), honor_begin, std::end(standing_tiles))) {

        fan_table[LESSER_HONORS_AND_KNITTED_TILES] = 1;
        if (numbered_cnt == 9) {
            fan_table[KNITTED_STRAIGHT] = 1;
        }
        return true;
    }

    return false;
}


static bool calculate_special_form_fan(const tile_t (&standing_tiles)[14], win_flag_t win_flag, fan_table_t &fan_table) {

    if (standing_tiles[0] == standing_tiles[1]
        && standing_tiles[2] == standing_tiles[3]
        && standing_tiles[4] == standing_tiles[5]
        && standing_tiles[6] == standing_tiles[7]
        && standing_tiles[8] == standing_tiles[9]
        && standing_tiles[10] == standing_tiles[11]
        && standing_tiles[12] == standing_tiles[13]) {

        if (is_numbered_suit_quick(standing_tiles[0])
            && standing_tiles[0] + 1 == standing_tiles[2]
            && standing_tiles[2] + 1 == standing_tiles[4]
            && standing_tiles[4] + 1 == standing_tiles[6]
            && standing_tiles[6] + 1 == standing_tiles[8]
            && standing_tiles[8] + 1 == standing_tiles[10]
            && standing_tiles[10] + 1 == standing_tiles[12]) {

            fan_table[SEVEN_SHIFTED_PAIRS] = 1;
            adjust_by_tiles_traits(standing_tiles, 14, fan_table);
        }
        else {

            fan_table[SEVEN_PAIRS] = 1;


            adjust_by_suits(standing_tiles, 14, fan_table);

            adjust_by_tiles_traits(standing_tiles, 14, fan_table);

            adjust_by_rank_range(standing_tiles, 14, fan_table);

            adjust_by_tiles_hog(standing_tiles, 14, fan_table);
        }
    }

    else if (is_thirteen_orphans(standing_tiles)) {
        fan_table[THIRTEEN_ORPHANS] = 1;
    }

    else if (calculate_honors_and_knitted_tiles(standing_tiles, fan_table)) {
    }
    else {
        return false;
    }

    adjust_by_win_flag(win_flag, fan_table);

    adjust_fan_table(fan_table);

    return true;
}


static int get_fan_by_table(const fan_table_t &fan_table) {
    int fan = 0;
    for (int i = 1; i < FAN_TABLE_SIZE; ++i) {
        if (fan_table[i] == 0) {
            continue;
        }
        fan += fan_value_table[i] * fan_table[i];
# 1984 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/fan_calculator.cpp"
    }
    return fan;
}


bool is_standing_tiles_contains_win_tile(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t win_tile) {
    return std::any_of(standing_tiles, standing_tiles + standing_cnt,
        [win_tile](tile_t tile) { return tile == win_tile; });
}


size_t count_win_tile_in_fixed_packs(const pack_t *fixed_packs, intptr_t fixed_cnt, tile_t win_tile) {
    tile_table_t cnt_table = { 0 };
    for (intptr_t i = 0; i < fixed_cnt; ++i) {
        pack_t pack = fixed_packs[i];
        tile_t tile = pack_get_tile(pack);
        switch (pack_get_type(pack)) {
        case 1: ++cnt_table[tile - 1]; ++cnt_table[tile]; ++cnt_table[tile + 1]; break;
        case 2: cnt_table[tile] += 3; break;
        case 3: cnt_table[tile] += 4; break;
        default: break;
        }
    }
    return cnt_table[win_tile];
}


bool is_fixed_packs_contains_kong(const pack_t *fixed_packs, intptr_t fixed_cnt) {
    return std::any_of(fixed_packs, fixed_packs + fixed_cnt,
        [](pack_t pack) { return pack_get_type(pack) == 3; });
}


int check_calculator_input(const hand_tiles_t *hand_tiles, tile_t win_tile) {

    tile_table_t cnt_table;
    if (!map_hand_tiles(hand_tiles, &cnt_table)) {
        return -1;
    }
    if (win_tile != 0) {
        ++cnt_table[win_tile];
    }


    if (std::any_of(std::begin(cnt_table), std::end(cnt_table), [](int cnt) { return cnt > 4; })) {
        return -2;
    }

    return 0;
}




int calculate_fan(const calculate_param_t *calculate_param, fan_table_t *fan_table) {
    const hand_tiles_t *hand_tiles = &calculate_param->hand_tiles;
    tile_t win_tile = calculate_param->win_tile;
    win_flag_t win_flag = calculate_param->win_flag;

    if (int ret = check_calculator_input(hand_tiles, win_tile)) {
        return ret;
    }

    intptr_t fixed_cnt = hand_tiles->pack_count;
    intptr_t standing_cnt = hand_tiles->tile_count;



    const bool standing_tiles_contains_win_tile = is_standing_tiles_contains_win_tile(hand_tiles->standing_tiles, standing_cnt, win_tile);
    if (standing_tiles_contains_win_tile) {
        win_flag &= ~2;
    }


    const size_t win_tile_in_fixed_packs = count_win_tile_in_fixed_packs(hand_tiles->fixed_packs, fixed_cnt, win_tile);
    if (3 == win_tile_in_fixed_packs) {
        win_flag |= 2;
    }


    if (win_flag & 4) {
        if (win_flag & 1) {

            if (!is_fixed_packs_contains_kong(hand_tiles->fixed_packs, fixed_cnt)) {
                win_flag &= ~4;
            }
        }
        else {

            if (win_tile_in_fixed_packs > 0 || standing_tiles_contains_win_tile) {
                win_flag &= ~4;
            }
        }
    }


    tile_t standing_tiles[14];
    memcpy(standing_tiles, hand_tiles->standing_tiles, standing_cnt * sizeof(tile_t));
    standing_tiles[standing_cnt] = win_tile;
    std::sort(standing_tiles, standing_tiles + standing_cnt + 1);


    int max_fan = 0;
    const fan_table_t *selected_fan_table = nullptr;


    fan_table_t special_fan_table = { 0 };


    if (fixed_cnt == 0) {
        if (calculate_knitted_straight_fan(calculate_param, win_flag, special_fan_table)) {
            max_fan = get_fan_by_table(special_fan_table);
            selected_fan_table = &special_fan_table;
            ((void)0);
        }
        else if (calculate_special_form_fan(standing_tiles, win_flag, special_fan_table)) {
            max_fan = get_fan_by_table(special_fan_table);
            selected_fan_table = &special_fan_table;
            ((void)0);
        }
    }
    else if (fixed_cnt == 1) {
        if (calculate_knitted_straight_fan(calculate_param, win_flag, special_fan_table)) {
            max_fan = get_fan_by_table(special_fan_table);
            selected_fan_table = &special_fan_table;
            ((void)0);
        }
    }



    if (selected_fan_table == nullptr || special_fan_table[SEVEN_PAIRS] == 1) {

        division_result_t result;
        if (divide_win_hand(standing_tiles, hand_tiles->fixed_packs, fixed_cnt, &result)) {
            fan_table_t fan_tables[20] = { { 0 } };


            for (intptr_t i = 0; i < result.count; ++i) {





                calculate_basic_form_fan(result.divisions[i].packs, calculate_param, win_flag, fan_tables[i]);
                int current_fan = get_fan_by_table(fan_tables[i]);
                if (current_fan > max_fan) {
                    max_fan = current_fan;
                    selected_fan_table = &fan_tables[i];
                }
                ((void)0);
            }
        }
    }

    if (selected_fan_table == nullptr) {
        return -3;
    }


    max_fan += calculate_param->flower_count;

    if (fan_table != nullptr) {
        memcpy(*fan_table, *selected_fan_table, sizeof(*fan_table));
        (*fan_table)[FLOWER_TILES] = calculate_param->flower_count;
    }

    return max_fan;
}

}
# 13 ".\\../utils/MahjongGB/MahjongGB.h" 2
# 1 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.cpp" 1
# 33 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.cpp"
namespace mahjong {


intptr_t packs_to_tiles(const pack_t *packs, intptr_t pack_cnt, tile_t *tiles, intptr_t tile_cnt) {
    if (packs == nullptr || tiles == nullptr) {
        return 0;
    }

    intptr_t cnt = 0;
    for (int i = 0; i < pack_cnt && cnt < tile_cnt; ++i) {
        tile_t tile = pack_get_tile(packs[i]);
        switch (pack_get_type(packs[i])) {
        case 1:
            if (cnt < tile_cnt) tiles[cnt++] = static_cast<tile_t>(tile - 1);
            if (cnt < tile_cnt) tiles[cnt++] = tile;
            if (cnt < tile_cnt) tiles[cnt++] = static_cast<tile_t>(tile + 1);
            break;
        case 2:
            if (cnt < tile_cnt) tiles[cnt++] = tile;
            if (cnt < tile_cnt) tiles[cnt++] = tile;
            if (cnt < tile_cnt) tiles[cnt++] = tile;
            break;
        case 3:
            if (cnt < tile_cnt) tiles[cnt++] = tile;
            if (cnt < tile_cnt) tiles[cnt++] = tile;
            if (cnt < tile_cnt) tiles[cnt++] = tile;
            if (cnt < tile_cnt) tiles[cnt++] = tile;
            break;
        case 4:
            if (cnt < tile_cnt) tiles[cnt++] = tile;
            if (cnt < tile_cnt) tiles[cnt++] = tile;
            break;
        default:
            __builtin_unreachable();
            break;
        }
    }
    return cnt;
}


void map_tiles(const tile_t *tiles, intptr_t cnt, tile_table_t *cnt_table) {
    memset(*cnt_table, 0, sizeof(*cnt_table));
    for (intptr_t i = 0; i < cnt; ++i) {
        ++(*cnt_table)[tiles[i]];
    }
}


bool map_hand_tiles(const hand_tiles_t *hand_tiles, tile_table_t *cnt_table) {

    if (hand_tiles->tile_count <= 0 || hand_tiles->pack_count < 0 || hand_tiles->pack_count > 4
        || hand_tiles->pack_count * 3 + hand_tiles->tile_count != 13) {
        return false;
    }


    tile_t tiles[18];
    intptr_t tile_cnt = 0;
    if (hand_tiles->pack_count == 0) {
        memcpy(tiles, hand_tiles->standing_tiles, 13 * sizeof(tile_t));
        tile_cnt = 13;
    }
    else {
        tile_cnt = packs_to_tiles(hand_tiles->fixed_packs, hand_tiles->pack_count, tiles, 18);
        memcpy(tiles + tile_cnt, hand_tiles->standing_tiles, hand_tiles->tile_count * sizeof(tile_t));
        tile_cnt += hand_tiles->tile_count;
    }


    map_tiles(tiles, tile_cnt, cnt_table);
    return true;
}


intptr_t table_to_tiles(const tile_table_t &cnt_table, tile_t *tiles, intptr_t max_cnt) {
    intptr_t cnt = 0;
    for (int i = 0; i < 34; ++i) {
        tile_t t = all_tiles[i];
        for (int n = 0; n < cnt_table[t]; ++n) {
            *tiles++ = t;
            ++cnt;
            if (cnt == max_cnt) {
                return max_cnt;
            }
        }
    }
    return cnt;
}

namespace {





    typedef uint16_t path_unit_t;
# 146 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.cpp"
    struct work_path_t {
        path_unit_t units[7];
        uint16_t depth;
    };


    struct work_state_t {
        work_path_t paths[512];
        intptr_t count;
    };
}


static bool is_basic_form_branch_exist(const intptr_t fixed_cnt, const work_path_t *work_path, const work_state_t *work_state) {
    if (work_state->count <= 0 || work_path->depth == 0) {
        return false;
    }


    const uint16_t depth = static_cast<uint16_t>(work_path->depth + 1);


    work_path_t temp;
    std::copy(&work_path->units[fixed_cnt], &work_path->units[depth], &temp.units[fixed_cnt]);
    std::sort(&temp.units[fixed_cnt], &temp.units[depth]);

    return std::any_of(&work_state->paths[0], &work_state->paths[work_state->count],
        [&temp, fixed_cnt, depth](const work_path_t &path) {
        return std::includes(&path.units[fixed_cnt], &path.units[path.depth], &temp.units[fixed_cnt], &temp.units[depth]);
    });
}


static void save_work_path(const intptr_t fixed_cnt, const work_path_t *work_path, work_state_t *work_state) {

    work_path_t temp;
    temp.depth = work_path->depth;
    std::copy(&work_path->units[fixed_cnt], &work_path->units[temp.depth + 1], &temp.units[fixed_cnt]);
    std::sort(&temp.units[fixed_cnt], &temp.units[temp.depth + 1]);


    if (std::none_of(&work_state->paths[0], &work_state->paths[work_state->count],
        [&temp, fixed_cnt](const work_path_t &path) {
        return (path.depth == temp.depth && std::equal(&path.units[fixed_cnt], &path.units[path.depth + 1], &temp.units[fixed_cnt]));
    })) {
        if (work_state->count < 512) {
            work_path_t &path = work_state->paths[work_state->count++];
            path.depth = temp.depth;
            std::copy(&temp.units[fixed_cnt], &temp.units[temp.depth + 1], &path.units[fixed_cnt]);
        }
        else {
            assert(0 && "too many state!");
        }
    }
}
# 212 ".\\../utils/MahjongGB/../ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/shanten.cpp"
static int basic_form_shanten_recursively(tile_table_t &cnt_table, const bool has_pair, const unsigned pack_cnt, const unsigned incomplete_cnt,
    const intptr_t fixed_cnt, work_path_t *work_path, work_state_t *work_state) {
    if (fixed_cnt == 4) {
        for (int i = 0; i < 34; ++i) {
            tile_t t = all_tiles[i];
            if (cnt_table[t] > 1) {
                return -1;
            }
        }
        return 0;
    }

    if (pack_cnt == 4) {
        return has_pair ? -1 : 0;
    }

    int max_ret;





    int incomplete_need = 4 - pack_cnt - incomplete_cnt;
    if (incomplete_need > 0) {


        max_ret = incomplete_cnt + incomplete_need * 2 - (has_pair ? 1 : 0);
    }
    else {


        max_ret = (has_pair ? 3 : 4) - pack_cnt;
    }


    const unsigned depth = pack_cnt + incomplete_cnt + has_pair;
    work_path->depth = static_cast<uint16_t>(depth);

    int result = max_ret;

    if (pack_cnt + incomplete_cnt > 4) {
        save_work_path(fixed_cnt, work_path, work_state);
        return max_ret;
    }

    for (int i = 0; i < 34; ++i) {
        tile_t t = all_tiles[i];
        if (cnt_table[t] < 1) {
            continue;
        }


        if (!has_pair && cnt_table[t] > 1) {
            work_path->units[depth] = static_cast<path_unit_t>(((4) << 8) | (t));
            if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {

                cnt_table[t] -= 2;
                int ret = basic_form_shanten_recursively(cnt_table, true, pack_cnt, incomplete_cnt,
                    fixed_cnt, work_path, work_state);
                result = std::min(ret, result);

                cnt_table[t] += 2;
            }
        }


        if (cnt_table[t] > 2) {
            work_path->units[depth] = static_cast<path_unit_t>(((2) << 8) | (t));
            if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {

                cnt_table[t] -= 3;
                int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt + 1, incomplete_cnt,
                    fixed_cnt, work_path, work_state);
                result = std::min(ret, result);

                cnt_table[t] += 3;
            }
        }


        bool is_numbered = is_numbered_suit(t);

        if (is_numbered && tile_get_rank(t) < 8 && cnt_table[t + 1] && cnt_table[t + 2]) {
            work_path->units[depth] = static_cast<path_unit_t>(((1) << 8) | (t));
            if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {

                --cnt_table[t];
                --cnt_table[t + 1];
                --cnt_table[t + 2];
                int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt + 1, incomplete_cnt,
                    fixed_cnt, work_path, work_state);
                result = std::min(ret, result);

                ++cnt_table[t];
                ++cnt_table[t + 1];
                ++cnt_table[t + 2];
            }
        }


        if (result < max_ret) {
            continue;
        }


        if (cnt_table[t] > 1) {
            work_path->units[depth] = static_cast<path_unit_t>(((7) << 8) | (t));
            if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {

                cnt_table[t] -= 2;
                int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt, incomplete_cnt + 1,
                    fixed_cnt, work_path, work_state);
                result = std::min(ret, result);

                cnt_table[t] += 2;
            }
        }


        if (is_numbered) {

            if (tile_get_rank(t) < 9 && cnt_table[t + 1]) {
                work_path->units[depth] = static_cast<path_unit_t>(((5) << 8) | (t));
                if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {

                    --cnt_table[t];
                    --cnt_table[t + 1];
                    int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt, incomplete_cnt + 1,
                        fixed_cnt, work_path, work_state);
                    result = std::min(ret, result);

                    ++cnt_table[t];
                    ++cnt_table[t + 1];
                }
            }

            if (tile_get_rank(t) < 8 && cnt_table[t + 2]) {
                work_path->units[depth] = static_cast<path_unit_t>(((6) << 8) | (t));
                if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {

                    --cnt_table[t];
                    --cnt_table[t + 2];
                    int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt, incomplete_cnt + 1,
                        fixed_cnt, work_path, work_state);
                    result = std::min(ret, result);

                    ++cnt_table[t];
                    ++cnt_table[t + 2];
                }
            }
        }
    }

    if (result == max_ret) {
        save_work_path(fixed_cnt, work_path, work_state);
    }

    return result;
}


static bool numbered_tile_has_neighbor(const tile_table_t &cnt_table, tile_t t) {
    rank_t r = tile_get_rank(t);
    if (r < 9) { if (cnt_table[t + 1]) return true; }
    if (r < 8) { if (cnt_table[t + 2]) return true; }
    if (r > 1) { if (cnt_table[t - 1]) return true; }
    if (r > 2) { if (cnt_table[t - 2]) return true; }
    return false;
}


static int basic_form_shanten_from_table(tile_table_t &cnt_table, intptr_t fixed_cnt, useful_table_t *useful_table) {

    work_path_t work_path;
    work_state_t work_state;
    work_state.count = 0;
    int result = basic_form_shanten_recursively(cnt_table, false, static_cast<uint16_t>(fixed_cnt), 0,
        fixed_cnt, &work_path, &work_state);

    if (useful_table == nullptr) {
        return result;
    }


    for (int i = 0; i < 34; ++i) {
        tile_t t = all_tiles[i];
        if (cnt_table[t] == 4 && result > 0) {
            continue;
        }

        if (cnt_table[t] == 0) {

            if (is_honor(t) || !numbered_tile_has_neighbor(cnt_table, t)) {
                continue;
            }
        }

        ++cnt_table[t];
        work_state.count = 0;
        int temp = basic_form_shanten_recursively(cnt_table, false, static_cast<uint16_t>(fixed_cnt), 0,
            fixed_cnt, &work_path, &work_state);
        if (temp < result) {
            (*useful_table)[t] = true;
        }
        --cnt_table[t];
    }

    return result;
}


int basic_form_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
    if (standing_tiles == nullptr || (standing_cnt != 13
        && standing_cnt != 10 && standing_cnt != 7 && standing_cnt != 4 && standing_cnt != 1)) {
        return std::numeric_limits<int>::max();
    }


    tile_table_t cnt_table;
    map_tiles(standing_tiles, standing_cnt, &cnt_table);

    if (useful_table != nullptr) {
        memset(*useful_table, 0, sizeof(*useful_table));
    }
    return basic_form_shanten_from_table(cnt_table, (13 - standing_cnt) / 3, useful_table);
}


static bool is_basic_form_wait_1(tile_table_t &cnt_table, useful_table_t *waiting_table) {
    for (int i = 0; i < 34; ++i) {
        tile_t t = all_tiles[i];
        if (cnt_table[t] != 1) {
            continue;
        }


        cnt_table[t] = 0;
        if (std::all_of(std::begin(cnt_table), std::end(cnt_table), [](int n) { return n == 0; })) {
            cnt_table[t] = 1;
            if (waiting_table != nullptr) {
                (*waiting_table)[t] = true;
            }
            return true;
        }
        cnt_table[t] = 1;
    }

    return false;
}


static bool is_basic_form_wait_2(const tile_table_t &cnt_table, useful_table_t *waiting_table) {
    bool ret = false;
    for (int i = 0; i < 34; ++i) {
        tile_t t = all_tiles[i];
        if (cnt_table[t] < 1) {
            continue;
        }
        if (cnt_table[t] > 1) {
            if (waiting_table != nullptr) {
                (*waiting_table)[t] = true;
                ret = true;
                continue;
            }
            else {
                return true;
            }
        }
        if (is_numbered_suit_quick(t)) {
            rank_t r = tile_get_rank(t);
            if (r > 1 && cnt_table[t - 1]) {
                if (waiting_table != nullptr) {
                    if (r < 9) (*waiting_table)[t + 1] = true;
                    if (r > 2) (*waiting_table)[t - 2] = true;
                    ret = true;
                    continue;
                }
                else {
                    return true;
                }
            }
            if (r > 2 && cnt_table[t - 2]) {
                if (waiting_table != nullptr) {
                    (*waiting_table)[t - 1] = true;
                    ret = true;
                    continue;
                }
                else {
                    return true;
                }
            }
        }
    }
    return ret;
}


static bool is_basic_form_wait_4(tile_table_t &cnt_table, useful_table_t *waiting_table) {
    bool ret = false;

    for (int i = 0; i < 34; ++i) {
        tile_t t = all_tiles[i];
        if (cnt_table[t] < 2) {
            continue;
        }

        cnt_table[t] -= 2;
        if (is_basic_form_wait_2(cnt_table, waiting_table)) {
            ret = true;
        }

        cnt_table[t] += 2;
        if (ret && waiting_table == nullptr) {
            return true;
        }
    }

    return ret;
}


static bool is_basic_form_wait_recursively(tile_table_t &cnt_table, intptr_t left_cnt, useful_table_t *waiting_table) {
    if (left_cnt == 1) {
        return is_basic_form_wait_1(cnt_table, waiting_table);
    }

    bool ret = false;
    if (left_cnt == 4) {
        ret = is_basic_form_wait_4(cnt_table, waiting_table);
        if (ret && waiting_table == nullptr) {
            return true;
        }
    }

    for (int i = 0; i < 34; ++i) {
        tile_t t = all_tiles[i];
        if (cnt_table[t] < 1) {
            continue;
        }


        if (cnt_table[t] > 2) {

            cnt_table[t] -= 3;
            if (is_basic_form_wait_recursively(cnt_table, left_cnt - 3, waiting_table)) {
                ret = true;
            }

            cnt_table[t] += 3;
            if (ret && waiting_table == nullptr) {
                return true;
            }
        }


        if (is_numbered_suit(t)) {

            if (tile_get_rank(t) < 8 && cnt_table[t + 1] && cnt_table[t + 2]) {

                --cnt_table[t];
                --cnt_table[t + 1];
                --cnt_table[t + 2];
                if (is_basic_form_wait_recursively(cnt_table, left_cnt - 3, waiting_table)) {
                    ret = true;
                }

                ++cnt_table[t];
                ++cnt_table[t + 1];
                ++cnt_table[t + 2];
                if (ret && waiting_table == nullptr) {
                    return true;
                }
            }
        }
    }

    return ret;
}




bool is_basic_form_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {

    tile_table_t cnt_table;
    map_tiles(standing_tiles, standing_cnt, &cnt_table);

    if (waiting_table != nullptr) {
        memset(*waiting_table, 0, sizeof(*waiting_table));
    }
    return is_basic_form_wait_recursively(cnt_table, standing_cnt, waiting_table);
}


static bool is_basic_form_win_2(const tile_table_t &cnt_table) {

    typedef std::remove_all_extents<tile_table_t>::type table_elem_t;
    const table_elem_t *it = std::find_if(std::begin(cnt_table), std::end(cnt_table), [](table_elem_t n) { return n > 0; });

    if (it == std::end(cnt_table) || *it != 2) {
        return false;
    }

    return std::none_of(it + 1, std::end(cnt_table), [](int n) { return n > 0; });
}




static bool is_basic_form_win_recursively(tile_table_t &cnt_table, intptr_t left_cnt) {
    if (left_cnt == 2) {
        return is_basic_form_win_2(cnt_table);
    }

    for (int i = 0; i < 34; ++i) {
        tile_t t = all_tiles[i];
        if (cnt_table[t] < 1) {
            continue;
        }


        if (cnt_table[t] > 2) {

            cnt_table[t] -= 3;
            bool ret = is_basic_form_win_recursively(cnt_table, left_cnt - 3);

            cnt_table[t] += 3;
            if (ret) {
                return true;
            }
        }


        if (is_numbered_suit(t)) {

            if (tile_get_rank(t) < 8 && cnt_table[t + 1] && cnt_table[t + 2]) {

                --cnt_table[t];
                --cnt_table[t + 1];
                --cnt_table[t + 2];
                bool ret = is_basic_form_win_recursively(cnt_table, left_cnt - 3);

                ++cnt_table[t];
                ++cnt_table[t + 1];
                ++cnt_table[t + 2];
                if (ret) {
                    return true;
                }
            }
        }
    }

    return false;
}


bool is_basic_form_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {

    tile_table_t cnt_table;
    map_tiles(standing_tiles, standing_cnt, &cnt_table);
    ++cnt_table[test_tile];
    return is_basic_form_win_recursively(cnt_table, standing_cnt + 1);
}




int seven_pairs_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
    if (standing_tiles == nullptr || standing_cnt != 13) {
        return std::numeric_limits<int>::max();
    }


    int pair_cnt = 0;
    tile_table_t cnt_table = { 0 };
    for (intptr_t i = 0; i < standing_cnt; ++i) {
        tile_t tile = standing_tiles[i];
        ++cnt_table[tile];
        if (cnt_table[tile] == 2) {
            ++pair_cnt;
            cnt_table[tile] = 0;
        }
    }


    if (useful_table != nullptr) {
        std::transform(std::begin(cnt_table), std::end(cnt_table), std::begin(*useful_table), [](int n) { return n != 0; });
    }
    return 6 - pair_cnt;
}


bool is_seven_pairs_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {

    if (waiting_table == nullptr) {
        return (0 == seven_pairs_shanten(standing_tiles, standing_cnt, nullptr));
    }

    useful_table_t useful_table;
    if (0 == seven_pairs_shanten(standing_tiles, standing_cnt, &useful_table)) {
        memcpy(*waiting_table, useful_table, sizeof(*waiting_table));
        return true;
    }
    return false;
}


bool is_seven_pairs_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {
    useful_table_t useful_table;
    return (0 == seven_pairs_shanten(standing_tiles, standing_cnt, &useful_table)
        && useful_table[test_tile]);
}




int thirteen_orphans_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
    if (standing_tiles == nullptr || standing_cnt != 13) {
        return std::numeric_limits<int>::max();
    }


    tile_table_t cnt_table;
    map_tiles(standing_tiles, standing_cnt, &cnt_table);

    bool has_pair = false;
    int cnt = 0;
    for (int i = 0; i < 13; ++i) {
        int n = cnt_table[standard_thirteen_orphans[i]];
        if (n > 0) {
            ++cnt;
            if (n > 1) {
                has_pair = true;
            }
        }
    }



    int ret = has_pair ? 12 - cnt : 13 - cnt;

    if (useful_table != nullptr) {

        memset(*useful_table, 0, sizeof(*useful_table));
        std::for_each(std::begin(standard_thirteen_orphans), std::end(standard_thirteen_orphans),
            [useful_table](tile_t t) {
            (*useful_table)[t] = true;
        });


        if (has_pair) {
            for (int i = 0; i < 13; ++i) {
                tile_t t = standard_thirteen_orphans[i];
                int n = cnt_table[t];
                if (n > 0) {
                    (*useful_table)[t] = false;
                }
            }
        }
    }

    return ret;
}


bool is_thirteen_orphans_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {

    if (waiting_table == nullptr) {
        return (0 == thirteen_orphans_shanten(standing_tiles, standing_cnt, nullptr));
    }

    useful_table_t useful_table;
    if (0 == thirteen_orphans_shanten(standing_tiles, standing_cnt, &useful_table)) {
        memcpy(*waiting_table, useful_table, sizeof(*waiting_table));
        return true;
    }
    return false;
}


bool is_thirteen_orphans_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {
    useful_table_t useful_table;
    return (0 == thirteen_orphans_shanten(standing_tiles, standing_cnt, &useful_table)
        && useful_table[test_tile]);
}




static bool is_knitted_straight_wait_from_table(const tile_table_t &cnt_table, intptr_t left_cnt, useful_table_t *waiting_table) {

    const tile_t (*matched_seq)[9] = nullptr;
    tile_t missing_tiles[9];
    int missing_cnt = 0;
    for (int i = 0; i < 6; ++i) {
        missing_cnt = 0;
        for (int k = 0; k < 9; ++k) {
            tile_t t = standard_knitted_straight[i][k];
            if (cnt_table[t] == 0) {
                missing_tiles[missing_cnt++] = t;
            }
        }
        if (missing_cnt < 2) {
            matched_seq = &standard_knitted_straight[i];
            break;
        }
    }

    if (matched_seq == nullptr || missing_cnt > 2) {
        return false;
    }

    if (waiting_table != nullptr) {
        memset(*waiting_table, 0, sizeof(*waiting_table));
    }


    tile_table_t temp_table;
    memcpy(&temp_table, &cnt_table, sizeof(temp_table));
    for (int i = 0; i < 9; ++i) {
        tile_t t = (*matched_seq)[i];
        if (temp_table[t]) {
            --temp_table[t];
        }
    }

    if (missing_cnt == 1) {
        if (left_cnt == 10) {
            if (is_basic_form_win_recursively(temp_table, 2)) {
                if (waiting_table != nullptr) {
                    (*waiting_table)[missing_tiles[0]] = true;
                }
                return true;
            }
        }
        else {
            if (is_basic_form_win_recursively(temp_table, 5)) {
                if (waiting_table != nullptr) {
                    (*waiting_table)[missing_tiles[0]] = true;
                }
                return true;
            }
        }
    }
    else if (missing_cnt == 0) {
        if (left_cnt == 10) {
            return is_basic_form_wait_1(temp_table, waiting_table);
        }
        else {
            return is_basic_form_wait_recursively(temp_table, 4, waiting_table);
        }
    }

    return false;
}


static int basic_form_shanten_specified(const tile_table_t &cnt_table, const tile_t *main_tiles, int main_cnt,
    intptr_t fixed_cnt, useful_table_t *useful_table) {

    tile_table_t temp_table;
    memcpy(&temp_table, &cnt_table, sizeof(temp_table));
    int exist_cnt = 0;


    for (int i = 0; i < main_cnt; ++i) {
        tile_t t = main_tiles[i];
        int n = cnt_table[t];
        if (n > 0) {
            ++exist_cnt;
            --temp_table[t];
        }
    }


    if (useful_table != nullptr) {
        memset(*useful_table, 0, sizeof(*useful_table));


        for (int i = 0; i < main_cnt; ++i) {
            tile_t t = main_tiles[i];
            int n = cnt_table[t];
            if (n <= 0) {
                (*useful_table)[t] = true;
            }
        }
    }


    int result = basic_form_shanten_from_table(temp_table, fixed_cnt + main_cnt / 3, useful_table);


    return (main_cnt - exist_cnt) + result;
}


int knitted_straight_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
    if (standing_tiles == nullptr || (standing_cnt != 13 && standing_cnt != 10)) {
        return std::numeric_limits<int>::max();
    }


    tile_table_t cnt_table;
    map_tiles(standing_tiles, standing_cnt, &cnt_table);

    int ret = std::numeric_limits<int>::max();


    if (useful_table != nullptr) {
        memset(*useful_table, 0, sizeof(*useful_table));

        useful_table_t temp_table;


        for (int i = 0; i < 6; ++i) {
            int fixed_cnt = (13 - static_cast<int>(standing_cnt)) / 3;
            int st = basic_form_shanten_specified(cnt_table, standard_knitted_straight[i], 9, fixed_cnt, &temp_table);
            if (st < ret) {
                ret = st;
                memcpy(*useful_table, temp_table, sizeof(*useful_table));
            }
            else if (st == ret) {
                std::transform(std::begin(*useful_table), std::end(*useful_table), std::begin(temp_table),
                    std::begin(*useful_table), [](bool u, bool t) { return u || t; });
            }
        }
    }
    else {

        for (int i = 0; i < 6; ++i) {
            int fixed_cnt = (13 - static_cast<int>(standing_cnt)) / 3;
            int st = basic_form_shanten_specified(cnt_table, standard_knitted_straight[i], 9, fixed_cnt, nullptr);
            if (st < ret) {
                ret = st;
            }
        }
    }

    return ret;
}


bool is_knitted_straight_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {
    if (standing_tiles == nullptr || (standing_cnt != 13 && standing_cnt != 10)) {
        return false;
    }


    tile_table_t cnt_table;
    map_tiles(standing_tiles, standing_cnt, &cnt_table);

    return is_knitted_straight_wait_from_table(cnt_table, standing_cnt, waiting_table);
}


bool is_knitted_straight_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {
    useful_table_t waiting_table;
    return (is_knitted_straight_wait(standing_tiles, standing_cnt, &waiting_table)
        && waiting_table[test_tile]);
}




static int honors_and_knitted_tiles_shanten_1(const tile_t *standing_tiles, intptr_t standing_cnt, int which_seq, useful_table_t *useful_table) {
    if (standing_tiles == nullptr || standing_cnt != 13) {
        return std::numeric_limits<int>::max();
    }


    tile_table_t cnt_table;
    map_tiles(standing_tiles, standing_cnt, &cnt_table);

    int cnt = 0;


    for (int i = 0; i < 9; ++i) {
        tile_t t = standard_knitted_straight[which_seq][i];
        int n = cnt_table[t];
        if (n > 0) {
            ++cnt;
        }
    }


    for (int i = 6; i < 13; ++i) {
        tile_t t = standard_thirteen_orphans[i];
        int n = cnt_table[t];
        if (n > 0) {
            ++cnt;
        }
    }


    if (useful_table != nullptr) {
        memset(*useful_table, 0, sizeof(*useful_table));


        for (int i = 0; i < 9; ++i) {
            tile_t t = standard_knitted_straight[which_seq][i];
            int n = cnt_table[t];
            if (n <= 0) {
                (*useful_table)[t] = true;
            }
        }


        for (int i = 6; i < 13; ++i) {
            tile_t t = standard_thirteen_orphans[i];
            int n = cnt_table[t];
            if (n <= 0) {
                (*useful_table)[t] = true;
            }
        }
    }


    return 13 - cnt;
}


int honors_and_knitted_tiles_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
    int ret = std::numeric_limits<int>::max();


    if (useful_table != nullptr) {
        memset(*useful_table, 0, sizeof(*useful_table));

        useful_table_t temp_table;


        for (int i = 0; i < 6; ++i) {
            int st = honors_and_knitted_tiles_shanten_1(standing_tiles, standing_cnt, i, &temp_table);
            if (st < ret) {
                ret = st;
                memcpy(*useful_table, temp_table, sizeof(*useful_table));
            }
            else if (st == ret) {
                std::transform(std::begin(*useful_table), std::end(*useful_table), std::begin(temp_table),
                    std::begin(*useful_table), [](bool u, bool t) { return u || t; });
            }
        }
    }
    else {

        for (int i = 0; i < 6; ++i) {
            int st = honors_and_knitted_tiles_shanten_1(standing_tiles, standing_cnt, i, nullptr);
            if (st < ret) {
                ret = st;
            }
        }
    }
    return ret;
}


bool is_honors_and_knitted_tiles_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {

    if (waiting_table == nullptr) {
        return (0 == honors_and_knitted_tiles_shanten(standing_tiles, standing_cnt, nullptr));
    }

    useful_table_t useful_table;
    if (0 == honors_and_knitted_tiles_shanten(standing_tiles, standing_cnt, &useful_table)) {
        memcpy(*waiting_table, useful_table, sizeof(*waiting_table));
        return true;
    }
    return false;
}


bool is_honors_and_knitted_tiles_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {
    useful_table_t useful_table;
    if (0 == honors_and_knitted_tiles_shanten(standing_tiles, standing_cnt, &useful_table)) {
        return useful_table[test_tile];
    }
    return false;
}



bool is_waiting(const hand_tiles_t &hand_tiles, useful_table_t *useful_table) {
    bool spcial_waiting = false, basic_waiting = false;
    useful_table_t table_special, table_basic;

    if (hand_tiles.tile_count == 13) {
        if (is_thirteen_orphans_wait(hand_tiles.standing_tiles, 13, &table_special)) {
            spcial_waiting = true;
        }
        else if (is_honors_and_knitted_tiles_wait(hand_tiles.standing_tiles, 13, &table_special)) {
            spcial_waiting = true;
        }
        else if (is_seven_pairs_wait(hand_tiles.standing_tiles, 13, &table_special)) {
            spcial_waiting = true;
        }
        else if (is_knitted_straight_wait(hand_tiles.standing_tiles, 13, &table_special)) {
            spcial_waiting = true;
        }
    }
    else if (hand_tiles.tile_count == 10) {
        if (is_knitted_straight_wait(hand_tiles.standing_tiles, 10, &table_special)) {
            spcial_waiting = true;
        }
    }

    if (is_basic_form_wait(hand_tiles.standing_tiles, hand_tiles.tile_count, &table_basic)) {
        basic_waiting = true;
    }

    if (useful_table != nullptr) {
        if (spcial_waiting && basic_waiting) {
            std::transform(std::begin(table_special), std::end(table_special), std::begin(table_basic), std::begin(*useful_table),
                [](bool a, bool b) { return a || b; });
        }
        else if (basic_waiting) {
            memcpy(*useful_table, table_basic, sizeof(table_basic));
        }
        else if (spcial_waiting) {
            memcpy(*useful_table, table_special, sizeof(table_special));
        }
    }

    return (spcial_waiting || basic_waiting);
}




static bool enum_discard_tile_1(const hand_tiles_t *hand_tiles, tile_t discard_tile, uint8_t form_flag,
    void *context, enum_callback_t enum_callback) {
    enum_result_t result;
    result.discard_tile = discard_tile;
    result.form_flag = 0x01;
    result.shanten = basic_form_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
    if (result.shanten == 0 && result.useful_table[discard_tile]) {
        result.shanten = -1;
    }
    if (!enum_callback(context, &result)) {
        return false;
    }


    if (hand_tiles->tile_count == 13) {
        if (form_flag | 0x02) {
            result.form_flag = 0x02;
            result.shanten = seven_pairs_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
            if (result.shanten == 0 && result.useful_table[discard_tile]) {
                result.shanten = -1;
            }
            if (!enum_callback(context, &result)) {
                return false;
            }
        }

        if (form_flag | 0x04) {
            result.form_flag = 0x04;
            result.shanten = thirteen_orphans_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
            if (result.shanten == 0 && result.useful_table[discard_tile]) {
                result.shanten = -1;
            }
            if (!enum_callback(context, &result)) {
                return false;
            }
        }

        if (form_flag | 0x08) {
            result.form_flag = 0x08;
            result.shanten = honors_and_knitted_tiles_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
            if (result.shanten == 0 && result.useful_table[discard_tile]) {
                result.shanten = -1;
            }
            if (!enum_callback(context, &result)) {
                return false;
            }
        }
    }


    if (hand_tiles->tile_count == 13 || hand_tiles->tile_count == 10) {
        if (form_flag | 0x10) {
            result.form_flag = 0x10;
            result.shanten = knitted_straight_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
            if (result.shanten == 0 && result.useful_table[discard_tile]) {
                result.shanten = -1;
            }
            if (!enum_callback(context, &result)) {
                return false;
            }
        }
    }

    return true;
}


void enum_discard_tile(const hand_tiles_t *hand_tiles, tile_t serving_tile, uint8_t form_flag,
    void *context, enum_callback_t enum_callback) {

    if (!enum_discard_tile_1(hand_tiles, serving_tile, form_flag, context, enum_callback)) {
        return;
    }

    if (serving_tile == 0) {
        return;
    }


    tile_table_t cnt_table;
    map_tiles(hand_tiles->standing_tiles, hand_tiles->tile_count, &cnt_table);


    hand_tiles_t temp;
    memcpy(&temp, hand_tiles, sizeof(temp));


    for (int i = 0; i < 34; ++i) {
        tile_t t = all_tiles[i];
        if (cnt_table[t] && t != serving_tile && cnt_table[serving_tile] < 4) {
            --cnt_table[t];
            ++cnt_table[serving_tile];


            table_to_tiles(cnt_table, temp.standing_tiles, temp.tile_count);


            if (!enum_discard_tile_1(&temp, t, form_flag, context, enum_callback)) {
                return;
            }


            --cnt_table[serving_tile];
            ++cnt_table[t];
        }
    }
}

}
# 14 ".\\../utils/MahjongGB/MahjongGB.h" 2


using namespace std;

void MahjongInit();

vector<pair<int, string> > MahjongFanCalculator(
    vector<pair<string, pair<string, int> > > pack,
    vector<string> hand,
    string winTile,
    int flowerCount,
    bool isZIMO,
    bool isJUEZHANG,
    bool isGANG,
    bool isLAST,
    int menFeng,
    int quanFeng);
# 17 ".\\ShantenCalculator.h" 2
# 1 ".\\../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.cpp" 1
# 23 ".\\../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.cpp"
# 1 ".\\../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.h" 1
# 26 ".\\../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.h"
# 1 ".\\../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/tile.h" 1
# 27 ".\\../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.h" 2

namespace mahjong {
# 78 ".\\../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.h"
intptr_t parse_tiles(const char *str, tile_t *tiles, intptr_t max_cnt);
# 94 ".\\../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.h"
intptr_t string_to_tiles(const char *str, hand_tiles_t *hand_tiles, tile_t *serving_tile);
# 104 ".\\../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.h"
intptr_t tiles_to_string(const tile_t *tiles, intptr_t tile_cnt, char *str, intptr_t max_size);
# 114 ".\\../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.h"
intptr_t packs_to_string(const pack_t *packs, intptr_t pack_cnt, char *str, intptr_t max_size);
# 123 ".\\../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.h"
intptr_t hand_tiles_to_string(const hand_tiles_t *hand_tiles, char *str, intptr_t max_size);






}
# 24 ".\\../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.cpp" 2






namespace mahjong {


static intptr_t parse_tiles_impl(const char *str, tile_t *tiles, intptr_t max_cnt, intptr_t *out_tile_cnt) {




    intptr_t tile_cnt = 0;
# 60 ".\\../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.cpp"
    const char *p = str;
    for (; tile_cnt < max_cnt && *p != '\0'; ++p) {
        char c = *p;
        switch (c) {
        case '0': tiles[tile_cnt++] = 5; break;
        case '1': tiles[tile_cnt++] = 1; break;
        case '2': tiles[tile_cnt++] = 2; break;
        case '3': tiles[tile_cnt++] = 3; break;
        case '4': tiles[tile_cnt++] = 4; break;
        case '5': tiles[tile_cnt++] = 5; break;
        case '6': tiles[tile_cnt++] = 6; break;
        case '7': tiles[tile_cnt++] = 7; break;
        case '8': tiles[tile_cnt++] = 8; break;
        case '9': tiles[tile_cnt++] = 9; break;
        case 'm': for (intptr_t i = tile_cnt; i > 0;) { if (tiles[--i] & 0xF0) break; tiles[i] |= 0x10; } (void)0; break;
        case 's': for (intptr_t i = tile_cnt; i > 0;) { if (tiles[--i] & 0xF0) break; tiles[i] |= 0x20; } (void)0; break;
        case 'p': for (intptr_t i = tile_cnt; i > 0;) { if (tiles[--i] & 0xF0) break; tiles[i] |= 0x30; } (void)0; break;
        case 'z': for (intptr_t i = tile_cnt; i > 0;) { if (tiles[--i] & 0xF0) break; if (tiles[i] > 7) return -1; tiles[i] |= 0x40; } (void)0; break;
        case 'E': if ((tile_cnt > 0 && !(tiles[tile_cnt - 1] & 0xF0))) return -2; tiles[tile_cnt++] = TILE_E; break;
        case 'S': if ((tile_cnt > 0 && !(tiles[tile_cnt - 1] & 0xF0))) return -2; tiles[tile_cnt++] = TILE_S; break;
        case 'W': if ((tile_cnt > 0 && !(tiles[tile_cnt - 1] & 0xF0))) return -2; tiles[tile_cnt++] = TILE_W; break;
        case 'N': if ((tile_cnt > 0 && !(tiles[tile_cnt - 1] & 0xF0))) return -2; tiles[tile_cnt++] = TILE_N; break;
        case 'C': if ((tile_cnt > 0 && !(tiles[tile_cnt - 1] & 0xF0))) return -2; tiles[tile_cnt++] = TILE_C; break;
        case 'F': if ((tile_cnt > 0 && !(tiles[tile_cnt - 1] & 0xF0))) return -2; tiles[tile_cnt++] = TILE_F; break;
        case 'P': if ((tile_cnt > 0 && !(tiles[tile_cnt - 1] & 0xF0))) return -2; tiles[tile_cnt++] = TILE_P; break;
        default: goto finish_parse;
        }
    }

finish_parse:

    if ((tile_cnt > 0 && !(tiles[tile_cnt - 1] & 0xF0))) {

        const char *p1 = strpbrk(p, "mspz");
        if (p1 == nullptr) {
            return -2;
        }

        switch (*p1) {
        case 'm': for (intptr_t i = tile_cnt; i > 0;) { if (tiles[--i] & 0xF0) break; tiles[i] |= 0x10; } (void)0; break;
        case 's': for (intptr_t i = tile_cnt; i > 0;) { if (tiles[--i] & 0xF0) break; tiles[i] |= 0x20; } (void)0; break;
        case 'p': for (intptr_t i = tile_cnt; i > 0;) { if (tiles[--i] & 0xF0) break; tiles[i] |= 0x30; } (void)0; break;
        case 'z': for (intptr_t i = tile_cnt; i > 0;) { if (tiles[--i] & 0xF0) break; if (tiles[i] > 7) return -1; tiles[i] |= 0x40; } (void)0; break;
        default: return -2;
        }

        if (p1 != p) {
            return -6;
        }

        p = p1 + 1;
    }
# 121 ".\\../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.cpp"
    *out_tile_cnt = tile_cnt;
    return static_cast<intptr_t>(p - str);
}


intptr_t parse_tiles(const char *str, tile_t *tiles, intptr_t max_cnt) {
    intptr_t tile_cnt;
    if (parse_tiles_impl(str, tiles, max_cnt, &tile_cnt) > 0) {
        return tile_cnt;
    }
    return 0;
}


static intptr_t make_fixed_pack(const tile_t *tiles, intptr_t tile_cnt, pack_t *pack, uint8_t offer) {
    if (tile_cnt > 0) {
        if (tile_cnt != 3 && tile_cnt != 4) {
            return -3;
        }
        if (tile_cnt == 3) {
            if (offer == 0) {
                offer = 1;
            }
            if (tiles[0] == tiles[1] && tiles[1] == tiles[2]) {
                *pack = make_pack(offer, 2, tiles[0]);
            }
            else {
                if (tiles[0] + 1 == tiles[1] && tiles[1] + 1 == tiles[2]) {
                    *pack = make_pack(offer, 1, tiles[1]);
                }
                else if (tiles[0] + 1 == tiles[2] && tiles[2] + 1 == tiles[1]) {
                    *pack = make_pack(offer, 1, tiles[2]);
                }
                else if (tiles[1] + 1 == tiles[0] && tiles[0] + 1 == tiles[2]) {
                    *pack = make_pack(offer, 1, tiles[0]);
                }
                else if (tiles[1] + 1 == tiles[2] && tiles[2] + 1 == tiles[0]) {
                    *pack = make_pack(offer, 1, tiles[2]);
                }
                else if (tiles[2] + 1 == tiles[0] && tiles[0] + 1 == tiles[1]) {
                    *pack = make_pack(offer, 1, tiles[0]);
                }
                else if (tiles[2] + 1 == tiles[1] && tiles[1] + 1 == tiles[0]) {
                    *pack = make_pack(offer, 1, tiles[1]);
                }
                else {
                    return -4;
                }
            }
        }
        else {
            if (tiles[0] != tiles[1] || tiles[1] != tiles[2] || tiles[2] != tiles[3]) {
                return -4;
            }
            *pack = make_pack(offer, 3, tiles[0]);
        }
        return 1;
    }
    return 0;
}


intptr_t string_to_tiles(const char *str, hand_tiles_t *hand_tiles, tile_t *serving_tile) {
    size_t len = strlen(str);
    if (strspn(str, "0123456789mpszESWNCFP,[]") != len) {
        return -1;
    }

    pack_t packs[4];
    intptr_t pack_cnt = 0;
    tile_t standing_tiles[14];
    intptr_t standing_cnt = 0;

    bool in_brackets = false;
    tile_t temp_tiles[14];
    intptr_t temp_cnt = 0;
    intptr_t max_cnt = 14;
    uint8_t offer = 0;

    tile_table_t cnt_table = { 0 };

    const char *p = str;
    while (char c = *p) {
        const char *q;
        switch (c) {
        case ',': {
            if (!in_brackets) {
                return -1;
            }
            offer = static_cast<uint8_t>(*++p - '0');
            q = ++p;
            if (*p != ']') {
                return -1;
            }
            break;
        }
        case '[': {
            if (in_brackets) {
                return -1;
            }
            if (pack_cnt > 4) {
                return -5;
            }
            if (temp_cnt > 0) {
                if (standing_cnt + temp_cnt >= max_cnt) {
                    return -6;
                }

                memcpy(&standing_tiles[standing_cnt], temp_tiles, temp_cnt * sizeof(tile_t));
                standing_cnt += temp_cnt;
                temp_cnt = 0;
            }

            q = ++p;
            in_brackets = true;
            offer = 0;
            max_cnt = 4;
            break;
        }
        case ']': {
            if (!in_brackets) {
                return -1;
            }

            intptr_t ret = make_fixed_pack(temp_tiles, temp_cnt, &packs[pack_cnt], offer);
            if (ret < 0) {
                return ret;
            }

            q = ++p;
            temp_cnt = 0;
            in_brackets = false;
            ++pack_cnt;
            max_cnt = 14 - standing_cnt - pack_cnt * 3;
            break;
        }
        default: {
            if (temp_cnt != 0) {
                return -6;
            }

            intptr_t ret = parse_tiles_impl(p, temp_tiles, max_cnt, &temp_cnt);
            if (ret < 0) {
                return ret;
            }
            if (ret == 0) {
                return -1;
            }

            for (intptr_t i = 0; i < temp_cnt; ++i) {
                ++cnt_table[temp_tiles[i]];
            }
            q = p + ret;
            break;
        }
        }
        p = q;
    }

    max_cnt = 14 - pack_cnt * 3;
    if (temp_cnt > 0) {
        if (standing_cnt + temp_cnt > max_cnt) {
            return -6;
        }

        memcpy(&standing_tiles[standing_cnt], temp_tiles, temp_cnt * sizeof(tile_t));
        standing_cnt += temp_cnt;
    }

    if (standing_cnt > max_cnt) {
        return -6;
    }


    if (std::any_of(std::begin(cnt_table), std::end(cnt_table), [](int cnt) { return cnt > 4; })) {
        return -7;
    }


    tile_t last_tile = 0;
    if (standing_cnt == max_cnt) {
        memcpy(hand_tiles->standing_tiles, standing_tiles, (max_cnt - 1) * sizeof(tile_t));
        hand_tiles->tile_count = max_cnt - 1;
        last_tile = standing_tiles[max_cnt - 1];
    }
    else {
        memcpy(hand_tiles->standing_tiles, standing_tiles, standing_cnt * sizeof(tile_t));
        hand_tiles->tile_count = standing_cnt;
    }

    memcpy(hand_tiles->fixed_packs, packs, pack_cnt * sizeof(pack_t));
    hand_tiles->pack_count = pack_cnt;
    *serving_tile = last_tile;

    return 0;
}


intptr_t tiles_to_string(const tile_t *tiles, intptr_t tile_cnt, char *str, intptr_t max_size) {
    bool tenhon = false;
    char *p = str, *end = str + max_size;

    static const char suffix[] = "mspz";
    static const char honor_text[] = "ESWNCFP";
    suit_t last_suit = 0;
    for (intptr_t i = 0; i < tile_cnt && p < end; ++i) {
        tile_t t = tiles[i];
        suit_t s = tile_get_suit(t);
        rank_t r = tile_get_rank(t);
        if (s == 1 || s == 2 || s == 3) {
            if (r >= 1 && r <= 9) {
                if (last_suit != s && last_suit != 0) {
                    if (last_suit != 4 || tenhon) {
                        *p++ = suffix[last_suit - 1];
                    }
                }
                if (p < end) {
                    *p++ = '0' + r;
                }
                last_suit = s;
            }
        }
        else if (s == 4) {
            if (r >= 1 && r <= 7) {
                if (last_suit != s && last_suit != 0) {
                    if (last_suit != 4) {
                        *p++ = suffix[last_suit - 1];
                    }
                }
                if (p < end) {
                    if (tenhon) {
                        *p++ = '0' + r;
                    }
                    else {
                        *p++ = honor_text[r - 1];
                    }
                    last_suit = s;
                }
            }
        }
    }


    if (p != str && p < end && (last_suit != 4 || tenhon)) {
        *p++ = suffix[last_suit - 1];
    }

    if (p < end) {
        *p = '\0';
    }
    return static_cast<intptr_t>(p - str);
}


intptr_t packs_to_string(const pack_t *packs, intptr_t pack_cnt, char *str, intptr_t max_size) {
    char *p = str, *end = str + max_size;
    tile_t temp[4];
    for (intptr_t i = 0; i < pack_cnt && p < end; ++i) {
        pack_t pack = packs[i];
        uint8_t o = pack_get_offer(pack);
        tile_t t = pack_get_tile(pack);
        uint8_t pt = pack_get_type(pack);
        switch (pt) {
        case 1:
            if (p >= end) break;
            *p++ = '[';
            temp[0] = static_cast<tile_t>(t - 1); temp[1] = t; temp[2] = static_cast<tile_t>(t + 1);
            p += tiles_to_string(temp, 3, p, static_cast<intptr_t>(end - p));
            if (p >= end) break;
            *p++ = ',';
            if (p >= end) break;
            *p++ = '0' + o;
            if (p >= end) break;
            *p++ = ']';
            break;
        case 2:
            if (p >= end) break;
            *p++ = '[';
            temp[0] = t; temp[1] = t; temp[2] = t;
            p += tiles_to_string(temp, 3, p, static_cast<intptr_t>(end - p));
            if (p >= end) break;
            *p++ = ',';
            if (p >= end) break;
            *p++ = '0' + o;
            if (p >= end) break;
            *p++ = ']';
            break;
        case 3:
            if (p >= end) break;
            *p++ = '[';
            temp[0] = t; temp[1] = t; temp[2] = t; temp[3] = t;
            p += tiles_to_string(temp, 4, p, static_cast<intptr_t>(end - p));
            if (p >= end) break;
            *p++ = ',';
            if (p >= end) break;
            *p++ = '0' + (is_promoted_kong(pack) ? o | 0x4 : o);
            if (p >= end) break;
            *p++ = ']';
            break;
        case 4:
            temp[0] = t; temp[1] = t;
            p += tiles_to_string(temp, 2, p, static_cast<intptr_t>(end - p));
            break;
        default: break;
        }
    }

    if (p < end) {
        *p = '\0';
    }
    return static_cast<intptr_t>(p - str);
}


intptr_t hand_tiles_to_string(const hand_tiles_t *hand_tiles, char *str, intptr_t max_size) {
    char *p = str, *end = str + max_size;
    p += packs_to_string(hand_tiles->fixed_packs, hand_tiles->pack_count, str, max_size);
    if (p < end) p += tiles_to_string(hand_tiles->standing_tiles, hand_tiles->tile_count, p, static_cast<intptr_t>(end - p));
    return static_cast<intptr_t>(p - str);
}

}
# 18 ".\\ShantenCalculator.h" 2






using TileTableT = mahjong::tile_table_t;
using UsefulTableT = mahjong::useful_table_t;
using TileT = mahjong::tile_t;

int CountUsefulTiles(const TileTableT& used_table, const UsefulTableT& useful_table) {
    int cnt = 0;
    for (int i = 0; i < 34; ++i) {
        TileT t = mahjong::all_tiles[i];
        if (useful_table[t]) {
            cnt += 4 - used_table[t];
        }
    }
    return cnt;
}

void ShantenTest()
{
    auto str = "[111m]5m12p1569sSWP";

    using namespace mahjong;
    hand_tiles_t hand_tiles;
    tile_t serving_tile;
    long ret = string_to_tiles(str, &hand_tiles, &serving_tile);
    if (ret != 0) {
        printf("error at line %d error = %ld\n", 48, ret);
        return;
    }

    char buf[20];
    ret = hand_tiles_to_string(&hand_tiles, buf, sizeof(buf));
    for (size_t i = 0; i < ret; i++) {
        cout << buf[i];
    }
    cout << endl;

    auto display = [](const hand_tiles_t* hand_tiles, useful_table_t& useful_table) {
        char buf[64];
        for (tile_t t = TILE_1m; t < TILE_TABLE_SIZE; ++t) {
            if (useful_table[t]) {
                tiles_to_string(&t, 1, buf, sizeof(buf));
                printf("%s ", buf);
            }
        }

        tile_table_t cnt_table;
        map_hand_tiles(hand_tiles, &cnt_table);

        printf("%d", CountUsefulTiles(cnt_table, useful_table));
    };

    puts(str);
    useful_table_t useful_table ;
    int ret0;
    ret0 = thirteen_orphans_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("13 orphans ===> %d shanten\n", ret0);
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);

    ret0 = seven_pairs_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("7 pairs ===> %d shanten\n", ret0);
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);

    ret0 = honors_and_knitted_tiles_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("honors and knitted tiles ===> %d shanten\n", ret0);
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);

    ret0 = knitted_straight_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("knitted straight in basic form ===> %d shanten\n", ret0);
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);
    puts("\n");

    ret0 = basic_form_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("basic form ===> %d shanten\n", ret0);
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);
    puts("\n");
}

string tileToStr(const Majang& t)
{
    auto& h = t;
    auto tileType = TILE_T(h.getTileInt() / 10);
    string s;
    switch (tileType) {
    case WANN:
    case BING:
    case TIAO:
        s.push_back('0' + h.getTileNum());
    }
    switch (tileType) {
    case WANN: s += 'm'; break;
    case BING: s += 'p'; break;
    case TIAO: s += 's'; break;
    case FENG:
        switch (h.getTileNum()) {
        case 1:
            return "E";
        case 2:
            return "S";
        case 3:
            return "W";
        case 4:
            return "N";
        }
    case JIAN:
        switch (h.getTileNum()) {
        case 1:
            return "C";
        case 2:
            return "F";
        case 3:
            return "P";
        }
    }
    return s;
}

int ComplicatedShantenCalc(const vector<pair<string, Majang> >& pack,
    const vector<Majang>& hand
){
    int shanten = std::numeric_limits<int>::max();

    using namespace mahjong;
    hand_tiles_t hand_tiles;
    tile_t serving_tile;

#pragma region 转换成字符串
    string s;
    for (size_t i = 0; i < pack.size(); i++) {
        auto& m = pack[i].second;
        auto& t = pack[i].first;
        auto tileType = TILE_T(m.getTileInt() / 10);
        s += '[';
        if (t == "CHI") {
            s += tileToStr(m.getPrvMajang());
            s += tileToStr(m);
            s += tileToStr(m.getNxtMajang());
        }
        else if (t == "PENG" || t == "GANG") {
            s += tileToStr(m);
            s += tileToStr(m);
            s += tileToStr(m);
            if (t == "GANG") {
                s += tileToStr(m);
            }
        }
        s += ']';
    }
    for (size_t i = 0; i < hand.size(); i++) {
        s += tileToStr(hand[i]);
    }
#pragma endregion

#pragma region 字符串再转换成库中的表示形式
    size_t len = s.size();

    pack_t packs[4];
    intptr_t pack_cnt = 0;
    tile_t standing_tiles[14];
    intptr_t standing_cnt = 0;

    bool in_brackets = false;
    tile_t temp_tiles[14];
    intptr_t temp_cnt = 0;
    intptr_t max_cnt = 14;
    uint8_t offer = 0;

    tile_table_t cnt_table = { 0 };

    const char* p = s.c_str();
    while (char c = *p) {
        const char* q;
        switch (c) {
        case ',': {
            offer = static_cast<uint8_t>(*++p - '0');
            q = ++p;
            break;
        }
        case '[': {
            if (temp_cnt > 0) {

                memcpy(&standing_tiles[standing_cnt], temp_tiles, temp_cnt * sizeof(tile_t));
                standing_cnt += temp_cnt;
                temp_cnt = 0;
            }

            q = ++p;
            in_brackets = true;
            offer = 0;
            max_cnt = 4;
            break;
        }
        case ']': {

            intptr_t ret = make_fixed_pack(temp_tiles, temp_cnt, &packs[pack_cnt], offer);
            if (ret < 0) {
                return ret;
            }

            q = ++p;
            temp_cnt = 0;
            in_brackets = false;
            ++pack_cnt;
            max_cnt = 14 - standing_cnt - pack_cnt * 3;
            break;
        }
        default: {

            intptr_t ret = parse_tiles_impl(p, temp_tiles, max_cnt, &temp_cnt);

            for (intptr_t i = 0; i < temp_cnt; ++i) {
                ++cnt_table[temp_tiles[i]];
            }
            q = p + ret;
            break;
        }
        }
        p = q;
    }

    max_cnt = 14 - pack_cnt * 3;
    if (temp_cnt > 0) {

        memcpy(&standing_tiles[standing_cnt], temp_tiles, temp_cnt * sizeof(tile_t));
        standing_cnt += temp_cnt;
    }


    tile_t last_tile = 0;
    if (standing_cnt == max_cnt) {
        memcpy(hand_tiles.standing_tiles, standing_tiles, (max_cnt - 1) * sizeof(tile_t));
        hand_tiles.tile_count = max_cnt - 1;
        last_tile = standing_tiles[max_cnt - 1];
    }
    else {
        memcpy(hand_tiles.standing_tiles, standing_tiles, standing_cnt * sizeof(tile_t));
        hand_tiles.tile_count = standing_cnt;
    }

    memcpy(hand_tiles.fixed_packs, packs, pack_cnt * sizeof(pack_t));
    hand_tiles.pack_count = pack_cnt;
    serving_tile = last_tile;
#pragma endregion

    useful_table_t useful_table = {false};
    int ret0;
    ret0 = thirteen_orphans_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    shanten = min(shanten, ret0);

    ret0 = seven_pairs_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    shanten = min(shanten, ret0);

    ret0 = honors_and_knitted_tiles_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    shanten = min(shanten, ret0);

    ret0 = knitted_straight_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    shanten = min(shanten, ret0);

    ret0 = basic_form_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    shanten = min(shanten, ret0);

    return shanten;
}
# 299 ".\\ShantenCalculator.h"
Majang MahjongToMajang(mahjong::tile_t h) {
    using namespace mahjong;
    auto tileType = h / 16;
    auto num = h % 16;
    int ret = 0;
    switch (tileType)
    {
    case 1:
    case 2:
    case 3:
        ret = num;
        break;
    }
    switch (tileType)
    {
    case 1:
        ret += WANN * 10;
        break;
    case 2:
        ret += TIAO * 10;
        break;
    case 3:
        ret += BING * 10;
        break;
    case 4:
        switch (h)
        {
        case TILE_E:
            ret = FENG * 10 + 1;
            break;
        case TILE_S:
            ret = FENG * 10 + 2;
            break;
        case TILE_W:
            ret = FENG * 10 + 3;
            break;
        case TILE_N:
            ret = FENG * 10 + 4;
            break;
        case TILE_C:
            ret = JIAN * 10 + 1;
            break;
        case TILE_F:
            ret = JIAN * 10 + 2;
            break;
        case TILE_P:
            ret = JIAN * 10 + 3;
            break;
        default:
            assert(false);
        }
        break;
    default:
        assert(false);
    }
    return Majang(ret);
}

mahjong::tile_t MajangToMahjong(const Majang& h){
    using namespace mahjong;
    auto tileType = TILE_T(h.getTileInt() / 10);
    tile_t ret = 0;
    switch (tileType) {
    case WANN:
    case BING:
    case TIAO:
        ret = h.getTileNum();
    }
    switch (tileType) {
    case WANN: ret |= 0x10; break;
    case BING: ret |= 0x30; break;
    case TIAO: ret |= 0x20; break;

    case FENG:
        switch (h.getTileNum()) {
        case 1:
            ret = TILE_E; break;
        case 2:
            ret = TILE_S; break;
        case 3:
            ret = TILE_W; break;
        case 4:
            ret = TILE_N; break;
        default:
            assert(false);
        }
        break;
    case JIAN:
        switch (h.getTileNum()) {
        case 1:
            ret = TILE_C; break;
        case 2:
            ret = TILE_F; break;
        case 3:
            ret = TILE_P; break;
        default:
            assert(false);
        }
        break;
    }
    return ret;
}

void ClearTable(mahjong::useful_table_t& ut) {
    memset(ut, 0, sizeof(bool) * 72);
}

int CountTable(mahjong::useful_table_t& ut) {
    int etc = 0;
    for (auto tile : ut)
        if (tile)
            etc++;
    return etc;
}




pair<int, int> ShantenCalc(
    const vector<pair<string, Majang> >& pack,
    const vector<Majang>& hand,
    mahjong::useful_table_t useful_table = nullptr
) {
    using namespace mahjong;

    hand_tiles_t hand_tiles;


    pack_t packs[4];
    intptr_t pack_cnt = 0;
    tile_t standing_tiles[14];
    intptr_t standing_cnt = 0;



    const int offer = 0;

    for (size_t i = 0; i < pack.size(); i++) {
        auto& m = pack[i].second;
        auto& t = pack[i].first;
        auto tileType = TILE_T(m.getTileInt() / 10);
        auto tt = MajangToMahjong(m);
        if (t == "CHI") {
            packs[pack_cnt] = make_pack(offer, 1, tt);
        }
        else if (t == "PENG") {
            packs[pack_cnt] = make_pack(offer, 2, tt);
        }
        else if (t == "GANG") {
            packs[pack_cnt] = make_pack(offer, 3, tt);
        }
        ++pack_cnt;
    }

    for (size_t i = 0; i < hand.size(); i++) {
# 497 ".\\ShantenCalculator.h"
        standing_tiles[standing_cnt] = MajangToMahjong(hand[i]);
        ++standing_cnt;
    }





    memcpy(hand_tiles.standing_tiles, standing_tiles, (standing_cnt) * sizeof(tile_t));
    hand_tiles.tile_count = standing_cnt;


    memcpy(hand_tiles.fixed_packs, packs, pack_cnt * sizeof(pack_t));
    hand_tiles.pack_count = pack_cnt;


    useful_table_t useful_table_ret = { false };
    useful_table_t temp_table = { false };
    int ret0;
    int effectiveTileCount = 0;

    int ret_shanten = std::numeric_limits<int>::max();

    auto Check = [&]() -> void {
        if (ret0 == std::numeric_limits<int>::max())
            return;
        if (ret0 < ret_shanten) {

            ret_shanten = ret0;
            memcpy(useful_table_ret, temp_table, sizeof(useful_table_ret));
        }
        else if (ret_shanten == ret0) {

            std::transform(std::begin(useful_table_ret), std::end(useful_table_ret),
                std::begin(temp_table),
                std::begin(useful_table_ret),
                [](bool u, bool t) { return u || t; });
        }
    };



    ret0 = thirteen_orphans_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &temp_table);
    Check();

    ret0 = seven_pairs_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &temp_table);
    Check();

    ret0 = honors_and_knitted_tiles_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &temp_table);
    Check();

    ret0 = knitted_straight_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &temp_table);
    Check();

    ret0 = basic_form_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &temp_table);
    Check();

    effectiveTileCount = CountTable(useful_table_ret);
    if (useful_table != nullptr)
        memcpy(useful_table, useful_table_ret, sizeof(useful_table_ret));

    return { ret_shanten, effectiveTileCount };
}
# 18 ".\\ScoreCalculator.h" 2
# 28 ".\\ScoreCalculator.h"
using namespace std;
# 37 ".\\ScoreCalculator.h"
class Calculator{
public:

    static double MajangScoreCalculator(
        vector<pair<string, Majang> > pack,

        vector<Majang> hand,

        int flowerCount,

        StateContainer state

    );


    static double ProbabilityCalc(const StateContainer& state,
        const Majang& aim
    );


    static double SimilarityCalc(const StateContainer& state,
        const UsefulTableT& aim
    );


    static double FanScoreCalculator(
        vector<pair<string, Majang> > pack,
        vector<Majang> hand,
        int flowerCount,
        Majang winTile,
        StateContainer state
    );


    static double MajangFanScore(
        vector<pair<string, Majang> > pack,
        vector<Majang> hand,
        int flowerCount,
        StateContainer state,
        int depth
    );


    static double MajangHandScore(
        vector<pair<string, Majang> > pack,
        vector<Majang> hand
    );

    static double HandScoreCalculator(
        int TileAmount[70]
    );
};
# 19 ".\\main.cpp" 2
# 1 ".\\ScoreCalculator.cpp" 1
# 1 ".\\ScoreCalculator.h" 1
# 2 ".\\ScoreCalculator.cpp" 2



using namespace std;


double Calculator::MajangScoreCalculator(
    vector<pair<string, Majang> > pack,
    vector<Majang> hand,
    int flowerCount,
    StateContainer state
) {

    const double k1 = 0.2;
    const double k2 = 0.15;
    const double k3 = 0.15;
    const double k4 = 0.5;

    double r1 = MajangHandScore(pack, hand);
    double r2 = MajangFanScore(pack, hand, flowerCount, state, 0);

    double resultShanten = 0;

    int param1, param2, param3;
    mahjong::useful_table_t useful_table;
    auto p = ShantenCalc(pack, hand, useful_table);
    param1 = p.first;
    param2 = p.second;
    param3 = SimilarityCalc(state, useful_table);
# 46 ".\\ScoreCalculator.cpp"
    const double k5 = 1 / 2;
    resultShanten = -(param1 - 1 - log(param3) * k5);




    return r1 * k1 + r2 * (k2 + k3) + resultShanten * k4;
}


double Calculator::FanScoreCalculator(
    vector<pair<string, Majang> > pack,
    vector<Majang> hand,
    int flowerCount,
    Majang winTile,
    StateContainer state
){
    double k4=120.0;
    vector <pair<string,pair<string,int> > > p;
    for(unsigned int i=0;i<pack.size();++i){
        p.push_back(make_pair(pack[i].first,make_pair(pack[i].second.getTileString(),1)));
    }
    vector <string> h;
    for(unsigned int i=0;i<hand.size();++i){
        h.push_back(hand[i].getTileString());
    }

    MahjongInit();
    try{
        bool isJUEZHANG=state.getTileLeft(winTile.getTileInt())==0;
        bool isGANG=(StateContainer::lastRequest==36);
        bool isLast=(state.getTotalLeft()-state.getTileLeft(0)-state.getTileLeft(1)-state.getTileLeft(2)-state.getTileLeft(3)-state.getSecretGangCntOf(0)-state.getSecretGangCntOf(1)-state.getSecretGangCntOf(2)-state.getSecretGangCntOf(3))==0;
        auto re=MahjongFanCalculator(p,h,winTile.getTileString(),flowerCount,1,isJUEZHANG,isGANG,isLast,state.getCurPosition(),StateContainer::quan);
        int r=0;
        for(unsigned int i=0;i<re.size();i++) r+=re[i].first;
        return r*k4;
    }
    catch(const string &error){
        return 0;
    }
}

double Calculator::MajangFanScore(
    vector<pair<string, Majang> > pack,
    vector<Majang> hand,
    int flowerCount,
    StateContainer state,
    int depth
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
    if(depth>=1) return r;
    for(int i=61;i<=68;i++){
      if(state.getTileLeft(i)){
           StateContainer newstate(state);
           newstate.decTileLeft(i);
           r+=(double)state.getTileLeft(i)/state.getTotalLeft()*MajangFanScore(pack,hand,flowerCount+1,newstate,depth+1);
       }
    }
    return r;
}



double Calculator::MajangHandScore(
    vector<pair<string, Majang> > pack,
    vector<Majang> hand
) {
    double c = 1;
    double result = 0;
    int tileAmount[70];
    memset(tileAmount, 0, sizeof(tileAmount));
    for (unsigned int i = 0; i < hand.size(); i++) {
        tileAmount[hand[i].getTileInt()]++;
    }
    for (unsigned int i = 0; i < pack.size(); i++) {
        if (pack[i].first == "GANG") result += 16;
        else if (pack[i].first == "PENG") result += 9;
        else {
            result += 10;
        }
    }
    result += HandScoreCalculator(tileAmount);

    return result * c;
}


double Calculator::SimilarityCalc(const StateContainer& state,
    const UsefulTableT& aim
){
    using namespace mahjong;
    vector<Majang> vct;
    for (tile_t i = 0; i < TILE_TABLE_SIZE; ++i)
    {
        if (aim[i])
        {
            auto mj = MahjongToMajang(i);
            vct.push_back(mj);
        }
    }
    double sim = 0;
    for (size_t i = 0; i < vct.size(); i++)
    {
        sim += ProbabilityCalc(state, vct[i]);
    }
    return sim;
}

double Calculator::ProbabilityCalc(const StateContainer& state,
    const Majang& aim
){
    const int playerIdx = state.getCurTurnPlayer();

    int OtherMingTilesCnt = 0;
    for (int i = 0; i < 4; ++i) {
        if (i != playerIdx) {

            OtherMingTilesCnt += state.getPengOf(i).size() * 3;
            OtherMingTilesCnt += state.getChiOf(i).size() * 3;
            OtherMingTilesCnt += state.getGangOf(i).size() * 4;
        }
    }
    int allSecretCnt = 136 - OtherMingTilesCnt - 14;

    int thisMjCnt = 0;
    auto& MyMj = state.getInHand();
    for (auto& mj : MyMj) {

        if (mj == aim)
            thisMjCnt++;
    }
    for (int i = 0; i < 4; ++i) {
        if (i != playerIdx) {

            for (auto& mj : state.getPengOf(i)) {
                if (mj == aim)
                    thisMjCnt += 3;
            }
            for (auto& mj : state.getChiOf(i)) {
                if (mj == aim
                    || mj.getPrvMajang() == aim
                    || mj.getNxtMajang() == aim) {
                    thisMjCnt++;
                }
            }
            for (auto& mj : state.getGangOf(i)) {
                if (mj == aim)
                    thisMjCnt += 4;
            }
        }
    }

    double pRet = (4 - thisMjCnt) / allSecretCnt;
    return pRet;
}

double SimilarityCalc(const StateContainer& state,
    mahjong::useful_table_t useful_table
){

    return 1.0;
}



double Calculator::HandScoreCalculator(
    int tileAmount[70]
) {
    double valueW = 0, valueB = 0, valueT = 0, valueF = 0, valueJ = 0;
    int sumW = 0, sumB = 0, sumT = 0, sumF = 0, sumJ = 0;
    double r = 0;
    for (int i = 11; i <= 19; i++) {
        if (tileAmount[i]) {
            double singleValue = 0;
            if (i >= 13) singleValue += tileAmount[i - 2] * 1;
            if (i >= 12) singleValue += tileAmount[i - 1] * 2;
            if (i <= 17) singleValue += tileAmount[i + 2] * 1;
            if (i <= 18) singleValue += tileAmount[i + 1] * 2;
            if (tileAmount[i] == 2) singleValue += 2;
            else if (tileAmount[i] == 3) singleValue += 3;
            else if (tileAmount[i] == 4) singleValue += 4;
            valueW += tileAmount[i] * singleValue;
            sumW += tileAmount[i];
        }
    }
    for (int i = 21; i <= 29; i++) {
        if (tileAmount[i]) {
            double singleValue = 0;
            if (i >= 23) singleValue += tileAmount[i - 2] * 1;
            if (i >= 22) singleValue += tileAmount[i - 1] * 2;
            if (i <= 27) singleValue += tileAmount[i + 2] * 1;
            if (i <= 28) singleValue += tileAmount[i + 1] * 2;
            if (tileAmount[i] == 2) singleValue += 2;
            else if (tileAmount[i] == 3) singleValue += 3;
            else if (tileAmount[i] == 4) singleValue += 4;
            valueB += tileAmount[i] * singleValue;
            sumB += tileAmount[i];
        }
    }
    for (int i = 31; i <= 39; i++) {
        if (tileAmount[i]) {
            double singleValue = 0;
            if (i >= 33) singleValue += tileAmount[i - 2] * 1;
            if (i >= 32) singleValue += tileAmount[i - 1] * 2;
            if (i <= 37) singleValue += tileAmount[i + 2] * 1;
            if (i <= 38) singleValue += tileAmount[i + 1] * 2;
            if (tileAmount[i] == 2) singleValue += 2;
            else if (tileAmount[i] == 3) singleValue += 3;
            else if (tileAmount[i] == 4) singleValue += 4;
            valueT += tileAmount[i] * singleValue;
            sumT += tileAmount[i];
        }
    }

    for (int i = 41; i <= 44; i++) {
        if (tileAmount[i]) {
            double singleValue = 0;




            if (tileAmount[i] == 2) singleValue += 2;
            else if (tileAmount[i] == 3) singleValue += 3;
            else if (tileAmount[i] == 4) singleValue += 4;
            valueF += tileAmount[i] * singleValue;
            sumF += tileAmount[i];
        }
    }
    for (int i = 51; i <= 53; i++) {
        if (tileAmount[i]) {
            double singleValue = 0;




            if (tileAmount[i] == 2) singleValue += 2;
            else if (tileAmount[i] == 3) singleValue += 3;
            else if (tileAmount[i] == 4) singleValue += 4;
            valueJ += tileAmount[i] * singleValue;
            sumJ += tileAmount[i];
        }
    }

    int sum = sumW + sumB + sumT + sumF + sumJ;
    valueW *= (1 + (double)sumW / sum);
    valueB *= (1 + (double)sumB / sum);
    valueT *= (1 + (double)sumT / sum);
    valueF *= (1 + (double)sumF / sum);
    valueJ *= (1 + (double)sumJ / sum);
    r = valueW + valueB + valueT + valueF + valueJ;
    return r;
}
# 20 ".\\main.cpp" 2
# 1 ".\\ResponseOutput.h" 1
# 14 ".\\ResponseOutput.h"
# 1 ".\\Majang.h" 1
# 15 ".\\ResponseOutput.h" 2
# 1 ".\\StateContainer.h" 1
# 16 ".\\ResponseOutput.h" 2
# 1 ".\\ScoreCalculator.h" 1
# 17 ".\\ResponseOutput.h" 2

using namespace std;

class Output{
public:
    static void Response(int request,StateContainer state);
    static bool judgeHu(vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& winTile,StateContainer state,bool isZIMO);
    static bool judgeGang(int tileAmout[70],vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& newTile,StateContainer state,int status);
    static bool judgeBuGang(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& newTile);
    static bool judgePeng(int tileAmout[70], const Majang& newTile);
    static int judgeChi(int tileAmout[70], const Majang& newTile);
    static const pair<double,Majang> getBestPlay(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand);
    static const Majang getBestCP(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& newTile,int pos);
};
# 21 ".\\main.cpp" 2
# 1 ".\\ResponseOutput.cpp" 1

# 1 ".\\ResponseOutput.h" 1
# 3 ".\\ResponseOutput.cpp" 2





using namespace std;

void Output::Response(int request, StateContainer state){


    vector<Majang> hand;
    for(size_t i=0;i<state.getInHand().size();i++) hand.push_back(state.getInHand()[i]);
    vector<pair<string,Majang> > pack;
    for(size_t i=0;i<state.getChiOf(state.getCurPosition()).size();i++) pack.push_back(make_pair("CHI",state.getChiOf(state.getCurPosition())[i]));
    for(size_t i=0;i<state.getPengOf(state.getCurPosition()).size();i++) pack.push_back(make_pair("PENG",state.getPengOf(state.getCurPosition())[i]));
    for(size_t i=0;i<state.getGangOf(state.getCurPosition()).size();i++) pack.push_back(make_pair("GANG",state.getGangOf(state.getCurPosition())[i]));


    int tileAmount[70];
    memset(tileAmount,0,sizeof(tileAmount));


    for(const auto& item: hand)
        tileAmount[item.getTileInt()]++;


    if(request==2){

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


    else if((request==32||request==33||request==34)&&state.getCurTurnPlayer() != state.getCurPosition()){
        Majang lastTile=state.getLastPlayed();
        int chi=judgeChi(tileAmount,lastTile);

        if(judgeHu(pack,hand,lastTile,state,false)){
            printf("HU");
        }

        else if(judgeGang(tileAmount,pack,hand,lastTile,state,3)){
            printf("GANG");
        }

        else if(judgePeng(tileAmount,lastTile)){
            Majang MajangPlay = getBestCP(state,pack,hand,lastTile,0);
            if(MajangPlay.getTileInt()==1){
                printf("PASS");
            }
            else{
                printf("PENG %s",MajangPlay.getTileString().c_str());
            }
        }

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


    else if(request==36&&judgeHu(pack,hand,state.getLastPlayed(),state,false)){
        printf("HU");
    }


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


    vector <pair<string,pair<string,int> > > p;
    for(unsigned int i=0;i<pack.size();++i){
        p.push_back(make_pair(pack[i].first,make_pair(pack[i].second.getTileString(),1)));
    }

    vector <string> h;

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


    MahjongInit();

    try{
        bool isJUEZHANG=state.getTileLeft(winTile.getTileInt())==0;
        bool isGANG=(StateContainer::lastRequest==36);
        bool isLast=(state.getTotalLeft()-state.getTileLeft(0)-state.getTileLeft(1)-state.getTileLeft(2)-state.getTileLeft(3)-state.getSecretGangCntOf(0)-state.getSecretGangCntOf(1)-state.getSecretGangCntOf(2)-state.getSecretGangCntOf(3))==0;
        auto re=MahjongFanCalculator(p,h,winTile.getTileString(),0,isZIMO,isJUEZHANG,isGANG,isLast,state.getCurPosition(),StateContainer::quan);
        int r=0;

        for(unsigned int i=0;i<re.size();i++) {
         r+=re[i].first;

        }
        return r >= 8;
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

    if(status==3){
        if(tileAmout[newTile.getTileInt()]==3){

            double maxResult1=Calculator::MajangScoreCalculator(pack,hand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);

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

            double maxResult1=getBestPlay(state,pack,hand).first;

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

    for(unsigned int i=0;i<pack.size();i++){
        if(pack[i].first=="PENG"&&pack[i].second.getTileInt()==newTile.getTileInt()){

            double maxResult1=getBestPlay(state,pack,hand).first;

            for(unsigned int k=0;k<hand.size();k++){
                if(hand[k].getTileInt()==newTile.getTileInt()){
                    hand.erase(hand.begin()+k);
                    break;
                }
            }
            pack.erase(pack.begin()+i);
            pack.push_back(make_pair("GANG",newTile));
            double maxResult2=Calculator::MajangScoreCalculator(pack,hand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);

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
        newHand.erase(newHand.begin()+i);
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

    double maxResult1=Calculator::MajangScoreCalculator(pack,hand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);

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

    pair<double,Majang> r=getBestPlay(state,pack,hand);
    double maxResult2=r.first;
    if(maxResult2-maxResult1>=1e-5){
        return r.second;
    }
    else return Majang(1);
}
# 22 ".\\main.cpp" 2






int StateContainer::quan=0;
int StateContainer::lastRequest=0;
int main() {
# 58 ".\\main.cpp"
    int turnID; Reader::readIn(turnID);
    string tmp;
    int lastRequest;
    StateContainer basicState;
    for (int i = 1; i < turnID; i++) {
        lastRequest = Reader::readRequest(basicState);
        getline(cin, tmp);





    }
    StateContainer::lastRequest = lastRequest;
    int t = Reader::readRequest(basicState);





    Output::Response(t, basicState);
    return 0;
}
