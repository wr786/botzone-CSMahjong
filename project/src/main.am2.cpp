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
    bool operator == (const Majang& other);

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

bool Majang::operator == (const Majang &other) {
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

public:
    static int quan;
    static int lastRequest;

    explicit StateContainer(int curP=0, int curT=0);
    StateContainer(const StateContainer& other);
# 78 ".\\StateContainer.h"
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
    }
    for (int i = 0; i < 70; i++) {
        tileLeft[i] = other.tileLeft[i];
    }
}
# 62 ".\\StateContainer.cpp"
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
# 27 ".\\ScoreCalculator.h"
using namespace std;
# 36 ".\\ScoreCalculator.h"
class Calculator{
public:

    static double MajangScoreCalculator(
        vector<pair<string, Majang> > pack,

        vector<Majang> hand,

        int flowerCount,

        StateContainer state

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
){

    double k1=0.4;
    double k2=0.3;
    double k3=0.3;

    double r1=MajangHandScore(pack,hand);
    double r2=MajangFanScore(pack,hand,flowerCount,state,0);


    return r1*k1+r2*(k2+k3);
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
){
    double c=1;
    double result=0;
    int tileAmount[70];
    memset(tileAmount,0,sizeof(tileAmount));
    for(unsigned int i=0;i<hand.size();i++){
        tileAmount[hand[i].getTileInt()]++;
    }
    for(unsigned int i=0;i<pack.size();i++){
        if(pack[i].first=="GANG") result+=16;
        else if(pack[i].first=="PENG") result+=9;
        else{
            result+=10;
        }
    }
    result+=HandScoreCalculator(tileAmount);
    return result*c;
}



double Calculator::HandScoreCalculator(
    int tileAmount[70]
){
    double valueW=0,valueB=0,valueT=0,valueF=0,valueJ=0;
    int sumW=0,sumB=0,sumT=0,sumF=0,sumJ=0;
    double r=0;
    for(int i=11;i<=19;i++){
        if(tileAmount[i]){
            double singleValue=0;
            if(i>=13) singleValue+=tileAmount[i-2]*1;
            if(i>=12) singleValue+=tileAmount[i-1]*2;
            if(i<=17) singleValue+=tileAmount[i+2]*1;
            if(i<=18) singleValue+=tileAmount[i+1]*2;
            if(tileAmount[i]==2) singleValue+=2;
            else if(tileAmount[i]==3) singleValue+=3;
            else if(tileAmount[i]==4) singleValue+=4;
            valueW+=tileAmount[i]*singleValue;
            sumW+=tileAmount[i];
        }
    }
    for(int i=21;i<=29;i++){
        if(tileAmount[i]){
            double singleValue=0;
            if(i>=23) singleValue+=tileAmount[i-2]*1;
            if(i>=22) singleValue+=tileAmount[i-1]*2;
            if(i<=27) singleValue+=tileAmount[i+2]*1;
            if(i<=28) singleValue+=tileAmount[i+1]*2;
            if(tileAmount[i]==2) singleValue+=2;
            else if(tileAmount[i]==3) singleValue+=3;
            else if(tileAmount[i]==4) singleValue+=4;
            valueB+=tileAmount[i]*singleValue;
            sumB+=tileAmount[i];
        }
    }
    for(int i=31;i<=39;i++){
        if(tileAmount[i]){
            double singleValue=0;
            if(i>=33) singleValue+=tileAmount[i-2]*1;
            if(i>=32) singleValue+=tileAmount[i-1]*2;
            if(i<=37) singleValue+=tileAmount[i+2]*1;
            if(i<=38) singleValue+=tileAmount[i+1]*2;
            if(tileAmount[i]==2) singleValue+=2;
            else if(tileAmount[i]==3) singleValue+=3;
            else if(tileAmount[i]==4) singleValue+=4;
            valueT+=tileAmount[i]*singleValue;
            sumT+=tileAmount[i];
        }
    }

    for(int i=41;i<=44;i++){
        if(tileAmount[i]){
            double singleValue=0;




            if(tileAmount[i]==2) singleValue+=2;
            else if(tileAmount[i]==3) singleValue+=3;
            else if(tileAmount[i]==4) singleValue+=4;
            valueF+=tileAmount[i]*singleValue;
            sumF+=tileAmount[i];
        }
    }
    for(int i=51;i<=53;i++){
        if(tileAmount[i]){
            double singleValue=0;




            if(tileAmount[i]==2) singleValue+=2;
            else if(tileAmount[i]==3) singleValue+=3;
            else if(tileAmount[i]==4) singleValue+=4;
            valueJ+=tileAmount[i]*singleValue;
            sumJ+=tileAmount[i];
        }
    }

    int sum=sumW+sumB+sumT+sumF+sumJ;
    valueW*=(1+(double)sumW/sum);
    valueB*=(1+(double)sumB/sum);
    valueT*=(1+(double)sumT/sum);
    valueF*=(1+(double)sumF/sum);
    valueJ*=(1+(double)sumJ/sum);
    r=valueW+valueB+valueT+valueF+valueJ;
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
    int turnID; Reader::readIn(turnID);
    string tmp;
    int lastRequest;
    StateContainer basicState;
    for(int i=1; i<turnID; i++) {
        lastRequest = Reader::readRequest(basicState);
        getline(cin, tmp);





    }
    StateContainer::lastRequest=lastRequest;
    int t=Reader::readRequest(basicState);





    Output::Response(t, basicState);
    return 0;
}
