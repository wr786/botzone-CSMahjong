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

       
# 26 ".\\ShantenCalculator.h"
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
        printf("error at line %d error = %ld\n", 50, ret);
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
# 301 ".\\ShantenCalculator.h"
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
            packs[pack_cnt] = make_pack(offer, PACK_TYPE_CHOW, tt);
        }
        else if (t == "PENG") {
            packs[pack_cnt] = make_pack(offer, PACK_TYPE_PUNG, tt);
        }
        else if (t == "GANG") {
            packs[pack_cnt] = make_pack(offer, PACK_TYPE_KONG, tt);
        }
        ++pack_cnt;
    }

    for (size_t i = 0; i < hand.size(); i++) {
# 499 ".\\ShantenCalculator.h"
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

    const double k1 = 0.4;
    const double k2 = 0.3;
    const double k3 = 0.3;
    const double k4 = 0.0;

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
    double k5 = 1 / 2;
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
        bool isLast=state.isTileWallEmpty((state.getCurTurnPlayer()+1)%4);
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

    bool isLast=state.isTileWallEmpty((state.getCurTurnPlayer()+1)%4);
    bool myEmpty=state.isTileWallEmpty((state.getCurPosition()));

    if(request==2){

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


    else if((request==32||request==33||request==34)&&state.getCurTurnPlayer() != state.getCurPosition()){
        Majang lastTile=state.getLastPlayed();
        int chi=judgeChi(tileAmount,lastTile);

        if(judgeHu(pack,hand,lastTile,state,false)){
            printf("HU");
        }

        else if(!myEmpty&&!isLast&&judgeGang(tileAmount,pack,hand,lastTile,state,3)){
            printf("GANG");
        }

        else if(!isLast&&judgePeng(tileAmount,lastTile)){
            Majang MajangPlay = getBestCP(state,pack,hand,lastTile,0);
            if(MajangPlay.getTileInt()==1){
                printf("PASS");
            }
            else{
                printf("PENG %s",MajangPlay.getTileString().c_str());
            }
        }

        else if((!isLast&&state.getCurTurnPlayer()+1)%4==state.getCurPosition()&&chi){
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
        bool isLast=state.isTileWallEmpty((state.getCurTurnPlayer()+1)%4);

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
